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
#include <cassert>

#include <brlcad/ConstDatabase.h>

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
            m_rtip = 0;
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
    const char* ret = 0;

    if (m_rtip != 0)
        ret = m_rtip->rti_dbip->dbi_title;

    return ret;
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
    Vector3D ret;

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
    Vector3D ret;

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
                    rt_db_internal intern;
                    int            id = rt_db_get_internal(&intern, pDir, m_rtip->rti_dbip, 0, m_resp);

                    if (id >= 0) {
                        rt_comb_internal* comb = static_cast<rt_comb_internal*>(intern.idb_ptr);

                        if (comb->tree != 0) {
                            if (db_ck_v4gift_tree(comb->tree) < 0)
                                db_non_union_push(comb->tree, m_resp);

                            if (db_ck_v4gift_tree(comb->tree) >= 0) {
                                int nodeCount = db_tree_nleaves(comb->tree);

                                if (nodeCount > 0) {
                                    rt_tree_array* pRtTreeArray = static_cast<rt_tree_array*>(bu_calloc(nodeCount, sizeof(rt_tree_array), "tree list" ));
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


class ConstDatabaseHit : public Hit {
public:
    ConstDatabaseHit(application* ap,
                     partition*   part) throw() : Hit(),
                                                  m_application(ap),
                                                  m_partition(part),
                                                  m_inVectorsComputed(false),
                                                  m_outVectorsComputed(false) {
        assert(m_application != 0);
        assert(m_partition != 0);
   }

    virtual const char* Name(void) const throw() {
        return m_partition->pt_regionp->reg_name;
    }

    virtual double      DistanceIn(void) const throw() {
        return m_partition->pt_inhit->hit_dist;
    }

    virtual double      DistanceOut(void) const throw() {
        return m_partition->pt_outhit->hit_dist;
    }

    virtual Vector3D    PointIn(void) const throw() {
        ComputeInVectors();
        return m_partition->pt_inhit->hit_point;
    }

    virtual Vector3D    PointOut(void) const throw() {
        ComputeOutVectors();
        return m_partition->pt_outhit->hit_point;
    }

    virtual Vector3D    SurfaceNormaleIn(void) const throw() {
        ComputeInVectors();
        return m_partition->pt_inhit->hit_normal;
    }

    virtual Vector3D    SurfaceNormaleOut(void) const throw() {
        ComputeOutVectors();
        return m_partition->pt_outhit->hit_normal;
    }

    virtual Curvature3D SurfaceCurvatureIn(void) const throw() {
        ComputeInVectors();

        curvature curv;
        RT_CURVATURE(&curv, m_partition->pt_inhit, m_partition->pt_inflip, m_partition->pt_inseg->seg_stp);

        return Curvature3D(curv.crv_pdir, curv.crv_c1, curv.crv_c2);
    }

    virtual Curvature3D SurfaceCurvatureOut(void) const throw() {
        ComputeOutVectors();

        curvature curv;
        RT_CURVATURE(&curv, m_partition->pt_outhit, m_partition->pt_outflip, m_partition->pt_outseg->seg_stp);

        return Curvature3D(curv.crv_pdir, curv.crv_c1, curv.crv_c2);
    }

    virtual Mapping2D   Surface2DMappingIn(void) const throw() {
        uvcoord uv;
        RT_HIT_UVCOORD(m_application, m_partition->pt_inseg->seg_stp, m_partition->pt_inhit, &uv);

        return Mapping2D(Vector2D(uv.uv_u, uv.uv_v), Vector2D(uv.uv_du, uv.uv_dv));
    }

    virtual Mapping2D   Surface2DMappingOut(void) const throw() {
        uvcoord uv;
        RT_HIT_UVCOORD(m_application, m_partition->pt_outseg->seg_stp, m_partition->pt_outhit, &uv);

        return Mapping2D(Vector2D(uv.uv_u, uv.uv_v), Vector2D(uv.uv_du, uv.uv_dv));
    }

private:
    application* m_application;
    partition*   m_partition;
    mutable bool m_inVectorsComputed;
    mutable bool m_outVectorsComputed;

    void ComputeInVectors(void) const throw() {
        if (!m_inVectorsComputed) {
            hit* pHit = m_partition->pt_inhit;

            RT_HIT_NORMAL(pHit->hit_normal, pHit, m_partition->pt_inseg->seg_stp, 0, m_partition->pt_inflip);
            m_inVectorsComputed = true;
        }
    }

    void ComputeOutVectors(void) const throw() {
        if (!m_outVectorsComputed) {
            hit* pHit = m_partition->pt_outhit;

            RT_HIT_NORMAL(pHit->hit_normal, pHit, m_partition->pt_outseg->seg_stp, 0, m_partition->pt_outflip);
            m_outVectorsComputed = true;
        }
    }
};


static int HitDo
(
    application* ap,
    partition*   partitionHead,
    seg*         segment
) {
    HitCallback* callback = static_cast<HitCallback*>(ap->a_uptr);

    for (partition* part = partitionHead->pt_forw;
         part != partitionHead;
         part = part->pt_forw) {
        if (!((*callback)(ConstDatabaseHit(ap, part))))
            break;
    }

    return 0; // return won't be evaluated
}


void ConstDatabase::ShootRay
(
    const Ray3D& ray,
    HitCallback& callback
) const throw() {
    if (!SelectionIsEmpty()) {
        application ap = {0};

        ap.a_hit      = HitDo;
        ap.a_miss     = 0;
        ap.a_overlap  = 0;
        ap.a_rt_i     = m_rtip;
        ap.a_level    = 0;
        ap.a_onehit   = 0; // all hits
        ap.a_resource = m_resp;
        ap.a_uptr     = &callback;

        VMOVE(ap.a_ray.r_pt, ray.origin.coordinates);
        VMOVE(ap.a_ray.r_dir, ray.direction.coordinates);

        if (BU_SETJUMP)
            goto END_MARK;

        VUNITIZE(ap.a_ray.r_dir);
        rt_shootray(&ap);

END_MARK:
        BU_UNSETJUMP;
    }
}
