/*                      R A Y T R A C E . H
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
/** @file raytrace.h
 *
 *  BRL-CAD core C++ interface:
 *      declares some objects needed in the ray trace procedure
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_RAYTRACE_INCLUDED
#define BRLCAD_RAYTRACE_INCLUDED

#include "common.h"


namespace BRLCAD {
    class Hit {
    public:
        virtual ~Hit(void) throw() {}

        virtual const char* Name(void) const throw()                = 0;
        virtual double      DistanceIn(void) const throw()          = 0;
        virtual double      DistanceOut(void) const throw()         = 0;
        virtual Vector3D    PointIn(void) const throw()             = 0;
        virtual Vector3D    PointOut(void) const throw()            = 0;
        virtual Vector3D    SurfaceNormaleIn(void) const throw()    = 0;
        virtual Vector3D    SurfaceNormaleOut(void) const throw()   = 0;
        virtual Curvature3D SurfaceCurvatureIn(void) const throw()  = 0;
        virtual Curvature3D SurfaceCurvatureOut(void) const throw() = 0;
        virtual Mapping2D   Surface2DMappingIn(void) const throw()  = 0;
        virtual Mapping2D   Surface2DMappingOut(void) const throw() = 0;

    protected:
        Hit(void) throw() {}
        Hit(const Hit&) throw() {}
        const Hit& operator=(const Hit&) throw() {return *this;}
    };


    class HitCallback {
    public:
        virtual ~HitCallback(void) {}

        /** return true: go on; false: stop
            The return value gives the calling function the possibility to optimize.
            However be aware the return value may be ignored. */
        /** Do not throw en exception here.
            This method will be called from deep inside the brlcad libraries.
            The status of the program after an exception will be undetermined. */
        virtual bool operator()(const Hit& hit) throw() = 0;

    protected:
        HitCallback(void) {}
        HitCallback(const HitCallback&) {}
        const HitCallback& operator=(const HitCallback&) {return *this;}
    };
}


#endif // BRLCAD_RAYTRACE_INCLUDED
