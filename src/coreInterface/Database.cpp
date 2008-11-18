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
 *      implements the common part of the handles on a writable database
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include <brlcad/Database.h>

#include "raytrace.h"


using namespace BRLCAD;


Database::Database(void) throw() : ConstDatabase(), m_wdbp(0) {}


Database::~Database(void) throw() {
    if (m_wdbp != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        wdb_close(m_wdbp);
END_MARK:
        BU_UNSETJUMP;
    }
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


void Database::Get
(
    const char*     objectName,
    ObjectCallback& callback
) {
    if (m_rtip != 0) {
        class ObjectCallbackIntern : public ConstDatabase::ObjectCallback {
        public:
            ObjectCallbackIntern(Database::ObjectCallback& callback,
                                 db_i*                     dbip) : ConstDatabase::ObjectCallback(),
                                                                   m_callback(callback),
                                                                   m_dbip(dbip) {}

            virtual ~ObjectCallbackIntern(void) {}

            virtual void operator()(const Object& object) {
                Object& objectIntern = const_cast<Object&>(object);
                objectIntern.m_dbip  = m_dbip;

                m_callback(objectIntern);

                rt_db_put_internal(objectIntern.m_pDir, objectIntern.m_dbip, objectIntern.m_ip, objectIntern.m_resp);
            }

        private:
            Database::ObjectCallback& m_callback;
            db_i*                     m_dbip;
        } callbackIntern(callback, m_rtip->rti_dbip);

        ConstDatabase::Get(objectName, callbackIntern);
    }
}
