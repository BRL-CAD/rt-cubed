/*                      S P H E R E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2014 United States Government as represented by
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
/** @file Sphere.cpp
 *
 *  BRL-CAD core C++ interface:
 *      SPHERE (ID_SPH) database object implementation
 */

#include <cassert>

#include "raytrace.h"
#include "rtgeom.h"
#include "bu/parallel.h"

#include <brlcad/Sphere.h>


using namespace BRLCAD;


Sphere::Sphere(void) throw(bad_alloc) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ell_internal);
        m_internalp->magic = RT_ELL_INTERNAL_MAGIC;
        Set(Vector3D(), 1.);
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::Sphere::Sphere");
    }

    BU_UNSETJUMP;
}


Sphere::Sphere
(
    const Vector3D& center,
    double          radius
) throw(bad_alloc) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ell_internal);
        m_internalp->magic = RT_ELL_INTERNAL_MAGIC;
        Set(center, radius);
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::Sphere::Sphere");
    }

    BU_UNSETJUMP;
}


Sphere::Sphere
(
    const Sphere& original
) throw(bad_alloc) : Object(original) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_ell_internal);
        memcpy(m_internalp, original.Internal(), sizeof(rt_ell_internal));
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::Sphere::Sphere");
    }

    BU_UNSETJUMP;

}


Sphere::~Sphere
(
    void
) throw() {
    if (m_internalp != 0)
        bu_free(m_internalp, "BRLCAD::Sphere::~Sphere::m_internalp");
}


const Sphere& Sphere::operator=(const Sphere& original) throw(bad_alloc) {
    if (&original != this) {
        Copy(original);
        memcpy(Internal(), original.Internal(), sizeof(rt_ell_internal));
    }

    return *this;
}


const Object& Sphere::operator=
(
    const Object& original
) throw(bad_alloc) {
    const Sphere* sph = dynamic_cast<const Sphere*>(&original);
    assert(sph != 0);

    if (sph != 0)
        *this = *sph;

    return *this;
}


Vector3D Sphere::Center(void) const throw() {
    return Vector3D(Internal()->v);
}


void Sphere::SetCenter(const Vector3D& center) throw(){
    VMOVE(Internal()->v, center.coordinates);
}


double Sphere::Radius(void) const throw() {
    return MAGNITUDE(Internal()->a);;
}


void Sphere::SetRadius(double radius) throw() {
    assert(radius > SMALL_FASTF);

    if (!NEAR_ZERO(radius, SMALL_FASTF)) {
        VSET(m_internalp->a, radius, 0., 0.);
        VSET(m_internalp->b, 0., radius, 0.);
        VSET(m_internalp->c, 0., 0., radius);
    }
}


void Sphere::Set
(
    const Vector3D& center,
    double          radius
) throw() {
    assert(radius > SMALL_FASTF);

    if (!NEAR_ZERO(radius, SMALL_FASTF)) {
        rt_ell_internal* internalp = Internal();

        VMOVE(internalp->v, center.coordinates);
        VSET(m_internalp->a, radius, 0., 0.);
        VSET(m_internalp->b, 0., radius, 0.);
        VSET(m_internalp->c, 0., 0., radius);
    }
}


Object* Sphere::Clone(void) const throw(bad_alloc, std::bad_alloc) {
    return new Sphere(*this);
}


const char* Sphere::ClassName(void) throw() {
    return "Sphere";
}


const char* Sphere::Type(void) const throw() {
    return ClassName();
}


bool Sphere::IsValid(void) const throw() {
    bool   ret                        = false;
    const  rt_ell_internal* internalp = Internal();
    double dist                       = 0.0005 * 0.0005;

    if (!VNEAR_ZERO(internalp->a, SMALL_FASTF) &&
        !VNEAR_ZERO(internalp->b, SMALL_FASTF) &&
        !VNEAR_ZERO(internalp->c, SMALL_FASTF) &&
        NEAR_ZERO(VDOT(internalp->b, Internal()->a ), RT_DOT_TOL)   &&
        NEAR_ZERO(VDOT(internalp->c, Internal()->a ), RT_DOT_TOL)   &&
        NEAR_ZERO(VDOT(internalp->b, Internal()->c ), RT_DOT_TOL)   &&
        NEAR_EQUAL(MAGNITUDE(internalp->a),MAGNITUDE(internalp->b), dist) &&
        NEAR_EQUAL(MAGNITUDE(internalp->b),MAGNITUDE(internalp->c), dist))
        ret = true;

    return ret;
}


Sphere::Sphere
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) throw() : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_ell_internal* Sphere::Internal(void) const throw() {
    const rt_ell_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_ell_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ELL_CK_MAGIC(ret);

    return ret;
}


rt_ell_internal* Sphere::Internal(void) throw() {
    rt_ell_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_ell_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_ELL_CK_MAGIC(ret);

    return ret;
}