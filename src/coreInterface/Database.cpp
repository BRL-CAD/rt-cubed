/*                      D A T A B A S E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
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

#include <cassert>

#include "raytrace.h"
#include "rtgeom.h"

#include <brlcad/Halfspace.h>
#include <brlcad/Combination.h>
#include <brlcad/Database.h>


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


bool Database::Add
(
    const Object& object
) {
    bool  ret        = false;
    int   id         = ID_NULL;
    void* rtInternal = 0;

    if (object.Type() == Halfspace::ClassName()) {
        id = ID_HALF;

        const Halfspace* halfspace = dynamic_cast<const Halfspace*>(&object);

        assert(halfspace != 0);

        BU_GETSTRUCT(rtInternal, rt_half_internal);
        memcpy(rtInternal, halfspace->Internal(), sizeof(rt_half_internal));
    }
    else if (object.Type() == Combination::ClassName()) {
        id = ID_COMBINATION;

        const Combination* combination = dynamic_cast<const Combination*>(&object);

        assert(combination != 0);

        const rt_comb_internal* internalFrom = combination->Internal();

        BU_GETSTRUCT(rtInternal, rt_comb_internal);
        memcpy(rtInternal, internalFrom, sizeof(rt_comb_internal));

        rt_comb_internal* internalTo = static_cast<rt_comb_internal*>(rtInternal);

        if (internalFrom->tree != 0)
            internalTo->tree = db_dup_subtree(internalFrom->tree, object.m_resp);

        bu_vls_strcpy(&internalTo->shader, bu_vls_addr(&internalFrom->shader));
        bu_vls_strcpy(&internalTo->material, bu_vls_addr(&internalFrom->material));
    }

    if (id != ID_NULL)
        ret = (wdb_export(m_wdbp, object.Name(), rtInternal, id, 1.) == 0);

    return ret;
}


void Database::Get
(
    const char*     objectName,
    ObjectCallback& callback
) {
    if (m_rtip != 0) {
        class ObjectCallbackIntern : public ConstDatabase::ObjectCallback {
        public:
            ObjectCallbackIntern(Database::ObjectCallback& callback) : ConstDatabase::ObjectCallback(),
                                                                       m_callback(callback) {}

            virtual ~ObjectCallbackIntern(void) {}

            virtual void operator()(const Object& object) {
                Object& objectIntern = const_cast<Object&>(object);

                m_callback(objectIntern);

                rt_db_put_internal(objectIntern.m_pDir,
                                   objectIntern.m_dbip,
                                   objectIntern.m_ip,
                                   objectIntern.m_resp);
            }

        private:
            Database::ObjectCallback& m_callback;
        } callbackIntern(callback);

        ConstDatabase::Get(objectName, callbackIntern);
    }
}
