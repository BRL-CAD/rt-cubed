/*                      D A T A B A S E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this file; see the file named COPYING for more
 * information.
 */
/** @file Database.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implements a handle on a writable database
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include <brlcad/Database.h>

#include "raytrace.h"


using namespace BRLCAD;


Database::Database(void) throw() : ConstDatabase(), m_wdbp(0) {
    if (m_resp != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        if (rt_uniresource.re_magic != RESOURCE_MAGIC)
            rt_init_resource(&rt_uniresource, 0, NULL);

        db_i* dbip = db_create_inmem();

        if (dbip != DBI_NULL) {
            RT_CK_DBI(dbip);

            m_rtip = rt_new_rti(dbip);                       // clones dbip
            rt_init_resource(m_resp, 0, m_rtip);

            m_wdbp = wdb_dbopen(dbip, RT_WDB_TYPE_DB_INMEM); // takes ownership of dbip
        }

    END_MARK:
            BU_UNSETJUMP;
    }
}


Database::~Database(void) throw() {
    if (m_wdbp != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        wdb_close(m_wdbp);
END_MARK:
        BU_UNSETJUMP;
    }
}


bool Database::Load
(
    const char* fileName
) throw() {
    bool ret = false;

    if (m_wdbp != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        rt_i* source = rt_dirbuild(fileName, 0, 0);

        if (source != 0) {
            ret = (db_dump(m_wdbp, source->rti_dbip) == 0);
            rt_free_rti(source);;
        }

END_MARK:
        BU_UNSETJUMP;
    }

    return ret;
}


bool Database::Save
(
    const char* fileName
) throw() {
    bool ret = false;

    if (m_wdbp != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        rt_wdb* target = wdb_fopen(fileName);

        if (target != 0) {
            ret = (db_dump(target, m_wdbp->dbip) == 0);
            wdb_close(target);
        }

END_MARK:
        BU_UNSETJUMP;
    }

    return ret;
}


void Database::SetTitle
(
    const char* title
) throw() {
    if (m_wdbp != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        db_update_ident(m_wdbp->dbip, title, m_wdbp->dbip->dbi_base2local);

END_MARK:
        BU_UNSETJUMP;
    }
}
