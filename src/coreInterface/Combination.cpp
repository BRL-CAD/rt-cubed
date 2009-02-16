/*                      C O M B I N A T I O N . C P P
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
/** @file Combination.cpp
 *
 *  BRL-CAD core C++ interface:
 *      combination (ID_COMBINATION) database object implementation
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include "raytrace.h"

#include <brlcad/Combination.h>


using namespace BRLCAD;


Combination::Combination(void) throw() : Object() {
    m_internalp = static_cast<rt_comb_internal*>(bu_calloc(1, sizeof(rt_comb_internal), "BRLCAD::Combination::Combination::m_internalp"));

    m_internalp->magic = RT_COMB_MAGIC;
    bu_vls_init(&m_internalp->shader);
    bu_vls_init(&m_internalp->material);
    m_internalp->temperature = -1.;
}


Combination::Combination
(
    const Combination& original
) throw() : Object(original) {
    const rt_comb_internal* internalFrom = original.Internal();

    m_internalp = static_cast<rt_comb_internal*>(bu_calloc(1, sizeof(rt_comb_internal), "BRLCAD::Combination::Combination::m_internalp"));

    m_internalp->magic       = internalFrom->magic;

    if (internalFrom->tree != 0)
        m_internalp->tree = db_dup_subtree(internalFrom->tree, m_resp);

    m_internalp->region_flag = internalFrom->region_flag;
    m_internalp->is_fastgen  = internalFrom->is_fastgen;
    m_internalp->region_id   = internalFrom->region_id;
    m_internalp->aircode     = internalFrom->aircode;
    m_internalp->GIFTmater   = internalFrom->GIFTmater;
    m_internalp->los         = internalFrom->los;
    m_internalp->rgb_valid   = internalFrom->rgb_valid;
    m_internalp->rgb[0]      = internalFrom->rgb[0];
    m_internalp->rgb[1]      = internalFrom->rgb[1];
    m_internalp->rgb[2]      = internalFrom->rgb[2];
    m_internalp->temperature = internalFrom->temperature;
    bu_vls_strcpy(&m_internalp->shader, bu_vls_addr(&internalFrom->shader));
    bu_vls_strcpy(&m_internalp->material, bu_vls_addr(&internalFrom->material));
    m_internalp->inherit     = internalFrom->inherit;
}


Combination::~Combination(void) throw() {
    if (m_internalp != 0) {
        if (m_internalp->tree != 0)
            db_free_tree(m_internalp->tree, m_resp);

        bu_vls_free(&m_internalp->shader);
        bu_vls_free(&m_internalp->material);

        bu_free(m_internalp, "BRLCAD::Combination::~Combination::m_internalp");
    }
}


const Combination& Combination::operator=(const Combination& original) throw() {
    if (&original != this) {
        Object::operator=(original);

        const rt_comb_internal* internalFrom = original.Internal();
        rt_comb_internal*       internalTo = Internal();

        if (internalTo->tree != 0)
            db_free_tree(m_internalp->tree, m_resp);

        if (internalFrom->tree != 0)
            internalTo->tree = db_dup_subtree(internalFrom->tree, m_resp);
        else
            internalTo->tree = 0;

        internalTo->region_flag = internalFrom->region_flag;
        internalTo->is_fastgen  = internalFrom->is_fastgen;
        internalTo->region_id   = internalFrom->region_id;
        internalTo->aircode     = internalFrom->aircode;
        internalTo->GIFTmater   = internalFrom->GIFTmater;
        internalTo->los         = internalFrom->los;
        internalTo->rgb_valid   = internalFrom->rgb_valid;
        internalTo->rgb[0]      = internalFrom->rgb[0];
        internalTo->rgb[1]      = internalFrom->rgb[1];
        internalTo->rgb[2]      = internalFrom->rgb[2];
        internalTo->temperature = internalFrom->temperature;
        bu_vls_strcpy(&internalTo->shader, bu_vls_addr(&internalFrom->shader));
        bu_vls_strcpy(&internalTo->material, bu_vls_addr(&internalFrom->material));
        internalTo->inherit     = internalFrom->inherit;
    }

    return *this;
}


const char* Combination::ClassName(void) throw() {
    return "Combination";
}


const char* Combination::Type(void) const throw() {
    return ClassName();
}


Combination::Combination
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) throw() : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_comb_internal* Combination::Internal(void) const {
    const rt_comb_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_comb_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_CHECK_COMB(ret);

    return ret;
}


rt_comb_internal* Combination::Internal(void) {
    rt_comb_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_comb_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_CHECK_COMB(ret);

    return ret;
}
