/*                      C O N S T D A T A B A S E . C P P
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
/** @file ConstDatabase.cpp
 *
 *  BRL-CAD core C++ interface:
 *      implements a handle on a read-only database
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include <cstdlib>
#include <cstring>

#include <brlcad/ConstDatabase.h>

#include "common.h"
#include "raytrace.h"


using namespace BRLCAD;


ConstDatabase::ConstDatabase(void) throw() : m_rtip(0), m_resp(0) {
    m_resp = static_cast<resource*>(calloc(1, sizeof(resource)));
}


ConstDatabase::~ConstDatabase(void) throw() {
    if (m_rtip != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        rt_free_rti(m_rtip);

END_MARK:
        BU_UNSETJUMP;
    }

    if (m_resp != 0)
        free(m_resp);
}


bool ConstDatabase::Load
(
    const char* fileName
) throw() {
    if (m_resp != 0) {
        if (m_rtip != 0) {
            if (BU_SETJUMP)
                goto TRY_IT_MARK;

            rt_free_rti(m_rtip);
        }

TRY_IT_MARK:
        BU_UNSETJUMP;

        if (BU_SETJUMP)
            goto END_MARK;

        m_rtip = rt_dirbuild(fileName, 0, 0);

        if (m_rtip != 0)
            rt_init_resource(m_resp, 0, m_rtip);

END_MARK:
        BU_UNSETJUMP;
    }

    return (m_rtip != 0);
}


const char* ConstDatabase::Title(void) const throw() {
    return m_rtip->rti_dbip->dbi_title;
}


void ConstDatabase::ListTopObjects
(
    StringCalback& callback
) const {
    if (m_rtip != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        {
            db_update_nref(m_rtip->rti_dbip, m_resp);

            for (size_t i = 0; i < RT_DBNHASH; i++)
                for (directory* pDir = m_rtip->rti_dbip->dbi_Head[i]; pDir != DIR_NULL; pDir = pDir->d_forw)
                    if (pDir->d_nref == 0) {
                        try {
                            if (!callback(pDir->d_namep)) {
                                i = RT_DBNHASH - 1;
                                break;
                            }
                        }
                        catch(...) {
                            BU_UNSETJUMP;

                            throw;
                        }
                    }
        }

END_MARK:
        BU_UNSETJUMP;
    }
}


void ConstDatabase::Select
(
    const char* objectName
) throw() {
    if (m_rtip != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        rt_gettree(m_rtip, objectName);

END_MARK:
        BU_UNSETJUMP;
    }
}


void ConstDatabase::UnSelectAll(void) throw() {
    if (m_rtip != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        rt_clean(m_rtip);

END_MARK:
        BU_UNSETJUMP;
    }
}


bool ConstDatabase::SelectionIsEmpty(void) const throw() {
    bool ret = true;

    if (m_rtip != 0)
        ret = m_rtip->nsolids < 1;

    return ret;
}


Vector3D ConstDatabase::BoundingBoxMinima(void) const throw() {
    Vector3D ret = {0., 0., 0.};

    if (!SelectionIsEmpty()) {
        if (BU_SETJUMP)
            goto END_MARK;

        if (m_rtip->needprep)
            rt_prep(m_rtip);

        VMOVE(ret.coordinates, m_rtip->mdl_min);

END_MARK:
        BU_UNSETJUMP;
    }

    return ret;
}


Vector3D ConstDatabase::BoundingBoxMaxima(void) const throw() {
    Vector3D ret = {0., 0., 0.};

    if (!SelectionIsEmpty()) {
        if (BU_SETJUMP)
            goto END_MARK;

        if (m_rtip->needprep)
            rt_prep(m_rtip);

        VMOVE(ret.coordinates, m_rtip->mdl_max);

END_MARK:
        BU_UNSETJUMP;
    }

    return ret;
}


bool ConstDatabase::IsRegion
(
    const char* objectName
) const throw() {
    bool ret = false;

    if (m_rtip != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        if ((objectName != 0) && (strlen(objectName) > 0)) {
            directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISY);

            if (pDir != DIR_NULL) {
                if (pDir->d_flags & DIR_REGION)
                    ret = true;
            }
        }

END_MARK:
        BU_UNSETJUMP;
    }

    return ret;
}


void ConstDatabase::ListObjects
(
    const char*    objectName,
    StringCalback& callback
) const {
    if (m_rtip != 0) {
        if (BU_SETJUMP)
            goto END_MARK;

        if ((objectName != 0) && (strlen(objectName) > 0)) {
            directory* pDir = db_lookup(m_rtip->rti_dbip, objectName, LOOKUP_NOISY);

            if (pDir != DIR_NULL) {
                if (pDir->d_flags & DIR_COMB) {
                    struct rt_db_internal intern;
                    int                   id = rt_db_get_internal(&intern, pDir, m_rtip->rti_dbip, 0, m_resp);

                    if (id >= 0) {
                        rt_comb_internal* comb = static_cast<rt_comb_internal*>(intern.idb_ptr);

                        if (comb->tree != 0) {
                            if (db_ck_v4gift_tree(comb->tree) < 0)
                                db_non_union_push(comb->tree, m_resp);

                            if (db_ck_v4gift_tree(comb->tree) >= 0) {
                                int nodeCount = db_tree_nleaves(comb->tree);

                                if (nodeCount > 0) {
                                    rt_tree_array* pRtTreeArray = static_cast<rt_tree_array*>(bu_calloc(nodeCount, sizeof( struct rt_tree_array ), "tree list" ));
                                    int            actualCount  = db_flatten_tree(pRtTreeArray, comb->tree, OP_UNION, 1, m_resp) - pRtTreeArray;

                                    comb->tree = TREE_NULL;

                                    if (actualCount <= nodeCount) {
                                        for (int i = 0; i < actualCount; i++) {
                                            try {
                                                if (!callback(pRtTreeArray[i].tl_tree->tr_l.tl_name))
                                                    break;
                                            }
                                            catch(...) {
                                                db_free_tree(pRtTreeArray[i].tl_tree, m_resp);
                                                bu_free(pRtTreeArray, "tree list");
                                                rt_db_free_internal(&intern, m_resp);
                                                BU_UNSETJUMP;

                                                throw;
                                            }
                                            db_free_tree(pRtTreeArray[i].tl_tree, m_resp);
                                        }
                                    }

                                    bu_free(pRtTreeArray, "tree list");
                                }
                            }
                        }

                        rt_db_free_internal(&intern, m_resp);
                    }
                }
            }
        }

END_MARK:
        BU_UNSETJUMP;
    }
}
