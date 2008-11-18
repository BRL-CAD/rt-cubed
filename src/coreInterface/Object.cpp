/*                      O B J E C T . C P P
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
/** @file Object.cpp
 *
 *  BRL-CAD core C++ interface:
 *      database object implementation
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include <cstring>
#include <cassert>

#include "bu.h"
#include "raytrace.h"

#include <brlcad/Object.h>


using namespace BRLCAD;


Object::~Object(void) throw() {
    if (m_name != 0)
        bu_free(m_name, "BRLCAD::Object::~Object");
};


const char* Object::Name(void) const throw() {
    const char* ret = 0;

    assert(!((m_pDir != RT_DIR_NULL) && (m_name != 0)));

    if (m_pDir != RT_DIR_NULL)
        ret = m_pDir->d_namep;
    else
        ret = m_name;

    return ret;
}


void Object::SetName
(
    const char* name
) throw() {
    assert(!((m_pDir != RT_DIR_NULL) && (m_name != 0)));

    // not connected with a non-writable database
    assert(((m_dbip != 0) && !m_dbip->dbi_read_only) || (m_pDir == 0));

    if ((m_dbip != 0) && !m_dbip->dbi_read_only) // connected with a writable BRLCAD::Database
        db_rename(m_dbip, m_pDir, name);
    else if (m_pDir == 0) {                      // connected with no database at all
        if (name != 0) {
            if (m_name != 0) {
                if (strcmp(m_name, name) != 0) {
                    bu_free(m_name, "BRLCAD::Object::SetName");
                    m_name = bu_strdupm(name, "BRLCAD::Object::SetName");
                }
            }
            else
                m_name = bu_strdupm(name, "BRLCAD::Object::SetName");
        }
        else if (m_name != 0) {
            bu_free(m_name, "BRLCAD::Object::SetName");
            m_name = 0;
        }
    }
    // else: do nothing if connected to a non-writable BRLCAD::ConstDatabase
}


Object::Object(void) throw() : m_resp(0), m_pDir(0), m_ip(0), m_dbip(0), m_name(0) {}


Object::Object
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) throw() : m_resp(resp), m_pDir(pDir), m_ip(ip), m_dbip(dbip), m_name(0) {
    assert((m_dbip == 0) || !m_dbip->dbi_read_only);
}


Object::Object
(
    const Object& original
) throw() : m_resp(original.m_resp), m_pDir(original.m_pDir), m_ip(original.m_ip), m_dbip(original.m_dbip), m_name(0) {
    if (original.m_name != 0)
        m_name = bu_strdupm(original.m_name, "BRLCAD::Object::Object");
}


const Object& Object::operator=
(
    const Object& original
) throw() {
    if (&original != this) {
        if (m_name != 0)
            bu_free(m_name, "BRLCAD::Object::operator=");

        m_resp = original.m_resp;
        m_pDir = original.m_pDir;
        m_ip   = original.m_ip;
        m_dbip = original.m_dbip;

        if (original.m_name != 0)
            m_name = bu_strdupm(original.m_name, "BRLCAD::Object::operator=");
        else
            m_name = 0;
    }

    return *this;
}
