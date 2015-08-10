/*                  E L L I P S O I D . C P P
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
/** @file ellipsoid.cpp
 *
 * C++ core interface Ellipsoid test
 *
 */

#include <iostream>

#include "brlcad/Ellipsoid.h"

#include "primitives.h"

#include "vmath.h"
#include "bn/tol.h"
#include "raytrace.h"

#define VECTOR3D_EQUAL(a, b) VNEAR_EQUAL(a.coordinates, b.coordinates, BN_TOL_DIST)

#define VECTOR3D_MAGEQUAL(a, b) (NEAR_EQUAL(MAGNITUDE(a.coordinates), b, BN_TOL_DIST))

#define AXIS_ORTHOGONAL(a, b, c)    \
    (NEAR_ZERO(VDOT(a.coordinates, b.coordinates), RT_DOT_TOL) &&    \
     NEAR_ZERO(VDOT(b.coordinates, c.coordinates), RT_DOT_TOL) &&    \
     NEAR_ZERO(VDOT(a.coordinates, c.coordinates), RT_DOT_TOL))

#define ADD_TEST(expression, allTestsPassed)    \
    if (!expression) {    \
	std::cout << "Failed test: " << #expression << std::endl;    \
	allTestsPassed = false;    \
    } else {    \
	std::cout << "Passed test: " << #expression << std::endl;    \
    }


bool testUnitEllipsoidConstructor()
{
    BRLCAD::Ellipsoid ellipsoid;
    BRLCAD::Vector3D semiPrincipalAxisA = ellipsoid.SemiPrincipalAxis(0);
    BRLCAD::Vector3D semiPrincipalAxisB = ellipsoid.SemiPrincipalAxis(1);
    BRLCAD::Vector3D semiPrincipalAxisC = ellipsoid.SemiPrincipalAxis(2);
    return (VECTOR3D_EQUAL(ellipsoid.Center(), BRLCAD::Vector3D()) &&
	    VECTOR3D_MAGEQUAL(semiPrincipalAxisA, 1) &&
	    VECTOR3D_MAGEQUAL(semiPrincipalAxisB, 1) &&
	    VECTOR3D_MAGEQUAL(semiPrincipalAxisC, 1) &&
	    AXIS_ORTHOGONAL(semiPrincipalAxisA, 
		semiPrincipalAxisB, 
		semiPrincipalAxisC));
}

bool testGeneralEllipsoidConstructor(BRLCAD::Vector3D center,
	BRLCAD::Vector3D semiPrincipalAxisA,
	BRLCAD::Vector3D semiPrincipalAxisB,
	BRLCAD::Vector3D semiPrincipalAxisC)
{
    BRLCAD::Ellipsoid ellipsoid(center, semiPrincipalAxisA, semiPrincipalAxisB, semiPrincipalAxisC);
    return (VECTOR3D_EQUAL(ellipsoid.Center(), center) &&
	    VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(0), semiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(1), semiPrincipalAxisB) &&
	    VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(2), semiPrincipalAxisC));
}

bool testBodyOfRevolutionConstructor(BRLCAD::Vector3D center,
	BRLCAD::Vector3D semiPrincipalAxis,
	const double radius)
{
    BRLCAD::Ellipsoid ellipsoid(center, semiPrincipalAxis, radius);
    BRLCAD::Vector3D actualSemiPrincipalAxisA = ellipsoid.SemiPrincipalAxis(0);
    BRLCAD::Vector3D actualSemiPrincipalAxisB = ellipsoid.SemiPrincipalAxis(1);
    BRLCAD::Vector3D actualSemiPrincipalAxisC = ellipsoid.SemiPrincipalAxis(2);

    return (VECTOR3D_EQUAL(ellipsoid.Center(), center) &&
	    VECTOR3D_EQUAL(actualSemiPrincipalAxisA, semiPrincipalAxis) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisB, radius) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisC, radius) &&
	    AXIS_ORTHOGONAL(actualSemiPrincipalAxisA,
		actualSemiPrincipalAxisB,
		actualSemiPrincipalAxisC));
}

bool testSphereConstructor(BRLCAD::Vector3D center, const double radius)
{
    BRLCAD::Ellipsoid ellipsoid(center, radius);
    BRLCAD::Vector3D actualSemiPrincipalAxisA = ellipsoid.SemiPrincipalAxis(0);
    BRLCAD::Vector3D actualSemiPrincipalAxisB = ellipsoid.SemiPrincipalAxis(1);
    BRLCAD::Vector3D actualSemiPrincipalAxisC = ellipsoid.SemiPrincipalAxis(2);
    return (VECTOR3D_EQUAL(ellipsoid.Center(), center) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisA, radius) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisB, radius) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisC, radius) &&
	    AXIS_ORTHOGONAL(actualSemiPrincipalAxisA,
		actualSemiPrincipalAxisB,
		actualSemiPrincipalAxisC));
}

bool testSetCenter(BRLCAD::Vector3D center)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.SetCenter(center);
    return (VECTOR3D_EQUAL(ellipsoid.Center(), center));
}

bool testSetSemiPrincipalAxis(size_t index, BRLCAD::Vector3D axis)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.SetSemiPrincipalAxis(index, axis);
    return (VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(index), axis));
}

bool testGeneralSet(BRLCAD::Vector3D center, BRLCAD::Vector3D semiPrincipalAxisA,
	BRLCAD::Vector3D semiPrincipalAxisB, BRLCAD::Vector3D semiPrincipalAxisC)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.Set(center, semiPrincipalAxisA, semiPrincipalAxisB, semiPrincipalAxisC);
    return (VECTOR3D_EQUAL(ellipsoid.Center(), center) &&
	    VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(0), semiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(1), semiPrincipalAxisB) &&
	    VECTOR3D_EQUAL(ellipsoid.SemiPrincipalAxis(2), semiPrincipalAxisC));
}

bool testBodyOfRevolutionSet(BRLCAD::Vector3D center,
	BRLCAD::Vector3D semiPrincipalAxis, const double radius)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.Set(center, semiPrincipalAxis, radius);
    BRLCAD::Vector3D actualSemiPrincipalAxisA = ellipsoid.SemiPrincipalAxis(0);
    BRLCAD::Vector3D actualSemiPrincipalAxisB = ellipsoid.SemiPrincipalAxis(1);
    BRLCAD::Vector3D actualSemiPrincipalAxisC = ellipsoid.SemiPrincipalAxis(2);

    return (VECTOR3D_EQUAL(ellipsoid.Center(), center) &&
	    VECTOR3D_EQUAL(actualSemiPrincipalAxisA, semiPrincipalAxis) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisB, radius) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisC, radius) &&
	    AXIS_ORTHOGONAL(actualSemiPrincipalAxisA,
		actualSemiPrincipalAxisB,
		actualSemiPrincipalAxisC));
}

bool testSetFocals(BRLCAD::Vector3D focalA, BRLCAD::Vector3D focalB, const double majorAxisLength)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.SetFocals(focalA, focalB, majorAxisLength);
    BRLCAD::Vector3D actualSemiPrincipalAxisA = ellipsoid.SemiPrincipalAxis(0);
    BRLCAD::Vector3D actualSemiPrincipalAxisB = ellipsoid.SemiPrincipalAxis(1);
    BRLCAD::Vector3D actualSemiPrincipalAxisC = ellipsoid.SemiPrincipalAxis(2);

    BRLCAD::Vector3D fociDistance;
    VADD2(fociDistance.coordinates, focalA.coordinates, focalB.coordinates);

    BRLCAD::Vector3D expectedCenter;
    VSCALE(expectedCenter.coordinates, fociDistance.coordinates, 0.5);

    double expectedMinorAxesLengths;
    expectedMinorAxesLengths = sqrt(majorAxisLength * majorAxisLength - MAGSQ(fociDistance.coordinates) * 0.25);

    return (VECTOR3D_EQUAL(ellipsoid.Center(), expectedCenter) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisA, majorAxisLength) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisB, expectedMinorAxesLengths) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisC, expectedMinorAxesLengths) &&
	    AXIS_ORTHOGONAL(actualSemiPrincipalAxisA,
		actualSemiPrincipalAxisB,
		actualSemiPrincipalAxisC));
}

bool testSetSphere(BRLCAD::Vector3D center, const double radius)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.SetSphere(center, radius);
    BRLCAD::Vector3D actualSemiPrincipalAxisA = ellipsoid.SemiPrincipalAxis(0);
    BRLCAD::Vector3D actualSemiPrincipalAxisB = ellipsoid.SemiPrincipalAxis(1);
    BRLCAD::Vector3D actualSemiPrincipalAxisC = ellipsoid.SemiPrincipalAxis(2);

    return (VECTOR3D_EQUAL(ellipsoid.Center(), center) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisA, radius) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisB, radius) &&
	    VECTOR3D_MAGEQUAL(actualSemiPrincipalAxisC, radius) &&
	    AXIS_ORTHOGONAL(actualSemiPrincipalAxisA,
		actualSemiPrincipalAxisB,
		actualSemiPrincipalAxisC));
}

bool testClone(BRLCAD::Vector3D center, BRLCAD::Vector3D semiPrincipalAxisA,
	BRLCAD::Vector3D semiPrincipalAxisB, BRLCAD::Vector3D semiPrincipalAxisC)
{
    BRLCAD::Ellipsoid original(center, semiPrincipalAxisA, semiPrincipalAxisB, semiPrincipalAxisC);
    BRLCAD::Ellipsoid cloned = *static_cast<BRLCAD::Ellipsoid*>(original.Clone());
    return (VECTOR3D_EQUAL(cloned.Center(), center) &&
	    VECTOR3D_EQUAL(cloned.SemiPrincipalAxis(0), semiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(cloned.SemiPrincipalAxis(1), semiPrincipalAxisB) &&
	    VECTOR3D_EQUAL(cloned.SemiPrincipalAxis(2), semiPrincipalAxisC));
}

void test_ellipsoid(BRLCAD::Database& database)
{
    BRLCAD::Ellipsoid ellipsoid;
    ellipsoid.SetName("Ellipsoid.s");

    bool allEllipsoidTestsPassed = true;

    if (ellipsoid.IsValid()) {
	std::cout << "Starting Ellipsoid Unit testing . . ." << std::endl;
	ADD_TEST(testUnitEllipsoidConstructor(), allEllipsoidTestsPassed);
	ADD_TEST(testGeneralEllipsoidConstructor(BRLCAD::Vector3D(0, 0, 0), 
		    BRLCAD::Vector3D(2, 0, 0), BRLCAD::Vector3D(0, 3, 0), BRLCAD::Vector3D(4, 2, 3)), allEllipsoidTestsPassed);
	ADD_TEST(testBodyOfRevolutionConstructor(BRLCAD::Vector3D(0, 0, 0), 
		    BRLCAD::Vector3D(2, 0, 0), 5), allEllipsoidTestsPassed);
	ADD_TEST(testSphereConstructor(BRLCAD::Vector3D(0, 0, 0), 5), allEllipsoidTestsPassed);
	ADD_TEST(testSetCenter(BRLCAD::Vector3D(0, 0, 0)), allEllipsoidTestsPassed);
	ADD_TEST(testSetSemiPrincipalAxis(0, BRLCAD::Vector3D(2, 0, 0)), allEllipsoidTestsPassed);
	ADD_TEST(testSetSemiPrincipalAxis(1, BRLCAD::Vector3D(0, 3, 0)), allEllipsoidTestsPassed);
	ADD_TEST(testSetSemiPrincipalAxis(2, BRLCAD::Vector3D(4, 2, 3)), allEllipsoidTestsPassed);
	ADD_TEST(testGeneralSet(BRLCAD::Vector3D(0, 0, 0), BRLCAD::Vector3D(2, 0, 0),
		    BRLCAD::Vector3D(0, 3, 0), BRLCAD::Vector3D(4, 2, 3)), allEllipsoidTestsPassed);
	ADD_TEST(testBodyOfRevolutionSet(BRLCAD::Vector3D(0, 0, 0), 
		    BRLCAD::Vector3D(2, 0, 0), 5), allEllipsoidTestsPassed);
	ADD_TEST(testSetFocals(BRLCAD::Vector3D(-1, 0, 0), 
		    BRLCAD::Vector3D(0, 1, 0), 10), allEllipsoidTestsPassed);
	ADD_TEST(testSetSphere(BRLCAD::Vector3D(0, 0, 0), 5), allEllipsoidTestsPassed);
	ADD_TEST(testClone(BRLCAD::Vector3D(0, 0, 0), BRLCAD::Vector3D(2, 0, 0),
		    BRLCAD::Vector3D(0, 3, 0), BRLCAD::Vector3D(4, 2, 3)), allEllipsoidTestsPassed);
    } else {
	std::cout << "default Ellipsoid not valid" << std::endl;
	allEllipsoidTestsPassed = false;
    }

    if(allEllipsoidTestsPassed) {
	std::cout << "All Ellipsoid tests passed; adding object to database . . ." << std::endl;
	database.Add(ellipsoid);
    }
}


/*
 * Local Variables:
 * mode: C++
 * tab-width: 8
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
