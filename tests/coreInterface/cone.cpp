/*                      C O N E . C P P
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
/** @file cone.cpp
 *
 *  BRL-CAD core C++ interface:
 *      truncated general cone (ID_TGC) database object implementation
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include <iostream>
#include <string>
#include <vector>
#include <brlcad/Cone.h>
#include "bn.h"
#include "raytrace.h"
#include "primitives.h"
using namespace BRLCAD;

#define VECTOR3D_EQUAL(a, b) VNEAR_EQUAL(a.coordinates, b.coordinates, BN_TOL_DIST)

#define VECTOR3D_MAGEQUAL(a, b) (NEAR_EQUAL(MAGNITUDE(a.coordinates), b, BN_TOL_DIST))

#define AXIS_ORTHOGONAL(a, b)    \
    (NEAR_ZERO(VDOT(a.coordinates, b.coordinates), RT_DOT_TOL))

#define ADD_TEST(expression, allTestsPassed)    \
    if (!expression) {    \
	std::cout << "Failed test: " << #expression << std::endl;    \
	allTestsPassed = false;    \
    } else {    \
	std::cout << "Passed test: " << #expression << std::endl;    \
    }

/* Test Helper */
bool testHelper(const Cone &cone, const Vector3D &basePoint,
	const Vector3D &height)
{
    const Vector3D setBasePoint = cone.BasePoint();
    const Vector3D setHeight = cone.Height();
    return(VECTOR3D_EQUAL(basePoint, setBasePoint) &&
	    VECTOR3D_EQUAL(height, setHeight));
}

/* Test default unit constructor */
bool testConeUnitConstructor()
{
    Cone cone = Cone();
    Vector3D basePoint = cone.BasePoint();
    Vector3D height = cone.Height();
    Vector3D actualBasePoint = Vector3D();
    Vector3D actualHeight = Vector3D(0.0, 0.0, 1.0);
    return(VECTOR3D_EQUAL(basePoint, actualBasePoint) &&
	    VECTOR3D_EQUAL(height, actualHeight) &&
	    AXIS_ORTHOGONAL(cone.SemiPrincipalAxis(0), cone.SemiPrincipalAxis(1)));
}

/* Tests Cone's BasePoint function */
bool testConeBasePoint(const Cone &cone, const double expectedX,
	const double expectedY, const double expectedZ)
{
    Vector3D basePoint = cone.BasePoint();
    Vector3D actualBasePoint = Vector3D(expectedX, expectedY, expectedZ);
    return(VECTOR3D_EQUAL(basePoint, actualBasePoint));
}

/* Tests Cone's SetBasePoint function */
bool testConeSetBasePoint(Cone cone, const Vector3D &basePoint)
{
    cone.SetBasePoint(basePoint);
    Vector3D setBasePoint = cone.BasePoint();
    return(VECTOR3D_EQUAL(basePoint, setBasePoint));
}

/* Tests Cone's Height function */
bool testConeHeight(const Cone &cone, const double expectedX,
	const double expectedY, const double expectedZ)
{
    Vector3D height = cone.Height();
    Vector3D actualHeight = Vector3D(expectedX, expectedY, expectedZ);
    return(VECTOR3D_EQUAL(height, actualHeight));
}

/* Tests Cone's SetHeight function */
bool testConeSetHeight(Cone cone, const Vector3D height)
{
    cone.SetHeight(height);
    Vector3D setHeight = cone.Height();
    return(VECTOR3D_EQUAL(height, setHeight));
}

/* Tests Cone's SemiPrincipalAxis function */
bool testConeSemiPrincipalAxis(const Cone &cone, const Vector3D &actualSemiPrincipalAxis, size_t index)
{
    Vector3D semiPrincipalAxis = cone.SemiPrincipalAxis(index);
    return(VECTOR3D_EQUAL(semiPrincipalAxis, actualSemiPrincipalAxis));
}

/* Tests Cone's SetSemiPrincipalAxis function */
bool testConeSetSemiPrincipalAxis(Cone cone, const Vector3D &semiPrincipalAxis, size_t index)
{
    cone.SetSemiPrincipalAxis(index, semiPrincipalAxis);
    Vector3D setSemiPrincipalAxis = cone.SemiPrincipalAxis(index);
    return(VECTOR3D_EQUAL(semiPrincipalAxis, setSemiPrincipalAxis));
}

/* Tests Cone's ClassName function */
bool testConeClassName(const Cone &cone) 
{
    const std::string coneClassName = "Cone";
    const std::string actualClassName = cone.ClassName();
    return(coneClassName.compare(actualClassName) == 0);
}

/* Tests Cone's Type function */
bool testConeType(const Cone &cone)
{
    return(cone.Type() == cone.ClassName());
}

/* Tests Cone's Set function (Right Elliptical Cylinder) */
bool testConeSetREC(Cone cone, const Vector3D &basePoint,
	const Vector3D &height, const Vector3D &semiPrincipalAxisA,
	const Vector3D &semiPrincipalAxisB)
{
    cone.Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB);
    const Vector3D setSemiPrincipalAxisA = cone.SemiPrincipalAxis(0);
    const Vector3D setSemiPrincipalAxisB = cone.SemiPrincipalAxis(1);
    bool helper = testHelper((const Cone &)cone, basePoint, height);
    return (helper &&
	    VECTOR3D_EQUAL(semiPrincipalAxisA, setSemiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisB, setSemiPrincipalAxisB) &&
	    AXIS_ORTHOGONAL(setSemiPrincipalAxisA, setSemiPrincipalAxisB));
}

/* Tests Cone's Set function (Truncated General Cone) */
bool testConeSetTGC(Cone cone, const Vector3D &basePoint,
	const Vector3D &height, const Vector3D &semiPrincipalAxisA,
	const Vector3D &semiPrincipalAxisB, const double ratioCtoA,
	const double ratioDtoB)
{
    bool flag = false;
    cone.Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB,
	    ratioCtoA, ratioDtoB);
    const Vector3D setSemiPrincipalAxisA = cone.SemiPrincipalAxis(0);
    const Vector3D setSemiPrincipalAxisB = cone.SemiPrincipalAxis(1);
    const Vector3D setSemiPrincipalAxisC = cone.SemiPrincipalAxis(2);
    const Vector3D setSemiPrincipalAxisD = cone.SemiPrincipalAxis(3);
    double setRatioCtoA, setRatioDtoB;
    for(int i = 0; i < 3; i++) {
	if(!EQUAL(setSemiPrincipalAxisA.coordinates[i], 0.0)) {
	    setRatioCtoA = setSemiPrincipalAxisC.coordinates[i] / setSemiPrincipalAxisA.coordinates[i];
	    flag = true;
	    break;
	} /* If flag remains false, it means semi principal axis has zero magnitude */
    }
    if(flag) {
	for(int i = 0; i < 3; i++) {
	    if(!EQUAL(setSemiPrincipalAxisB.coordinates[i], 0.0)) {
		setRatioDtoB = setSemiPrincipalAxisD.coordinates[i] / setSemiPrincipalAxisB.coordinates[i];
		flag = true;
		break;
	    } /* If flag remains false, it means semi principal axis has zero magnitude */
	}
    }
    bool helper = testHelper((const Cone &)cone, basePoint, height);
    return (flag && helper &&
	    EQUAL(setRatioCtoA, ratioCtoA) &&
	    EQUAL(setRatioDtoB, ratioDtoB) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisA, setSemiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisB, setSemiPrincipalAxisB) &&
	    AXIS_ORTHOGONAL(setSemiPrincipalAxisA, setSemiPrincipalAxisB));
}

/* Tests Cone's Set function (Truncated Elliptical Cone) */
bool testConeSetTEC(Cone cone, const Vector3D &basePoint,
	const Vector3D &height, const Vector3D &semiPrincipalAxisA,
	const Vector3D &semiPrincipalAxisB, const double scale)
{
    bool flag = false;
    cone.Set(basePoint, height, semiPrincipalAxisA, semiPrincipalAxisB,
	    scale);
    const Vector3D setSemiPrincipalAxisA = cone.SemiPrincipalAxis(0);
    const Vector3D setSemiPrincipalAxisB = cone.SemiPrincipalAxis(1);
    const Vector3D setSemiPrincipalAxisC = cone.SemiPrincipalAxis(2);
    double setScale;
    for(int i = 0; i < 3; i++) {
	if(!EQUAL(setSemiPrincipalAxisA.coordinates[i], 0.0)) {
	    setScale = setSemiPrincipalAxisC.coordinates[i] / setSemiPrincipalAxisA.coordinates[i];
	    flag = true;
	    break;
	} /* If flag remains false, it means semi principal axis has zero magnitude */
    }
    bool helper = testHelper((const Cone &)cone, basePoint, height);
    return (flag && helper &&
	    EQUAL(setScale, scale) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisA, setSemiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisB, setSemiPrincipalAxisB) &&
	    AXIS_ORTHOGONAL(setSemiPrincipalAxisA, setSemiPrincipalAxisB));
}

/* Tests Cone's Set function (Truncated Right Cone) */
bool testConeSetTRC(Cone cone, const Vector3D &basePoint,
	const Vector3D &height, const double radiusBase,
	const double radiusTop)
{
    cone.Set(basePoint, height, radiusBase, radiusTop);
    const Vector3D semiPrincipalAxisA = cone.SemiPrincipalAxis(0);
    const Vector3D semiPrincipalAxisB = cone.SemiPrincipalAxis(1);
    const Vector3D semiPrincipalAxisC = cone.SemiPrincipalAxis(2);
    const Vector3D semiPrincipalAxisD = cone.SemiPrincipalAxis(3);
    Vector3D actualSemiPrincipalAxisC, actualSemiPrincipalAxisD;
    const double scale = radiusTop / radiusBase;
    for(int i = 0; i < 3; i++) {
	actualSemiPrincipalAxisC.coordinates[i] = semiPrincipalAxisA.coordinates[i] * scale;
	actualSemiPrincipalAxisD.coordinates[i] = semiPrincipalAxisB.coordinates[i] * scale;
    }
    bool helper = testHelper((const Cone &)cone, basePoint, height);
    return(helper &&
	    VECTOR3D_EQUAL(semiPrincipalAxisC, actualSemiPrincipalAxisC) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisD, actualSemiPrincipalAxisD) &&
	    AXIS_ORTHOGONAL(semiPrincipalAxisA, semiPrincipalAxisB));
}

/* Tests Cone's Set function (Right Circular Cylinder) */
bool testConeSetRCC(Cone cone, const Vector3D &basePoint,
	const Vector3D &height, const double radius)
{
    cone.Set(basePoint, height, radius);
    const Vector3D semiPrincipalAxisA = cone.SemiPrincipalAxis(0);
    const Vector3D semiPrincipalAxisB = cone.SemiPrincipalAxis(1);
    const Vector3D semiPrincipalAxisC = cone.SemiPrincipalAxis(2);
    const Vector3D semiPrincipalAxisD = cone.SemiPrincipalAxis(3);
    bool helper = testHelper((const Cone &)cone, basePoint, height);
    return(helper &&
	    VECTOR3D_EQUAL(semiPrincipalAxisC, semiPrincipalAxisA) &&
	    VECTOR3D_EQUAL(semiPrincipalAxisD, semiPrincipalAxisB) &&
	    AXIS_ORTHOGONAL(semiPrincipalAxisA, semiPrincipalAxisB));
}

/* Tests Cone's Clone function */
bool testConeClone(Cone cone)
{
    Cone clonedCone;
    clonedCone = *static_cast<Cone *>(cone.Clone());
    return clonedCone.IsValid();
}

/* Runs all the Cone tests */
void test_cone(Database& database)
{
    std::vector<Vector3D> semiPrincipalAxis;
    Cone cone;
    const Vector3D basePoint = Vector3D();
    const Vector3D height = Vector3D(0.0, 0.0, 1.0);
    Vector3D semiPrincipalAxisA, semiPrincipalAxisB;
    const double radius = 1.0;
    cone.Set(basePoint, height, radius);
    for(size_t i = 0; i < 3; i++) {
	semiPrincipalAxis.push_back(cone.SemiPrincipalAxis(i));
    }
    bool allConeTestsPassed = true;

    /* Run tests */
    if(cone.IsValid()) {
	std::cout << "Starting Cone Unit testing . . ." << std::endl;
	ADD_TEST(testConeUnitConstructor(), allConeTestsPassed);
	ADD_TEST(testConeBasePoint(cone, 0.0, 0.0, 0.0), allConeTestsPassed);
	ADD_TEST(testConeSetBasePoint(cone, basePoint), allConeTestsPassed);
	ADD_TEST(testConeHeight(cone, 0.0, 0.0, 1.0), allConeTestsPassed);
	ADD_TEST(testConeSetHeight(cone, height), allConeTestsPassed);
	for(size_t i = 0; i < 3; i++) {
	    ADD_TEST(testConeSemiPrincipalAxis(cone, semiPrincipalAxis[i], i), allConeTestsPassed);
	}
	for(size_t i = 0; i < 3; i++) {
	    ADD_TEST(testConeSetSemiPrincipalAxis(cone, semiPrincipalAxis[i], i), allConeTestsPassed);
	}
	ADD_TEST(testConeClassName(cone), allConeTestsPassed);
	ADD_TEST(testConeType(cone), allConeTestsPassed);
	semiPrincipalAxisA = Vector3D(1.0, 0.0, 0.0);
	semiPrincipalAxisB = Vector3D(0.0, 2.0, 0.0);
	ADD_TEST(testConeSetREC(cone, basePoint, height, semiPrincipalAxisA,
		    semiPrincipalAxisB), allConeTestsPassed);
	ADD_TEST(testConeSetTGC(cone, basePoint, height, semiPrincipalAxisA,
		    semiPrincipalAxisB, 2.0, 2.0), allConeTestsPassed);
	ADD_TEST(testConeSetTEC(cone, basePoint, height, semiPrincipalAxisA,
		    semiPrincipalAxisB, 1.5), allConeTestsPassed);
	ADD_TEST(testConeSetTRC(cone, basePoint, height, 4.0, 1.0), allConeTestsPassed);
	ADD_TEST(testConeSetRCC(cone, basePoint, height, 2.5), allConeTestsPassed);
	ADD_TEST(testConeClone(cone), allConeTestsPassed);
    } else {
	std::cout << "Default Cone is not valid" << std::endl;
	allConeTestsPassed = false;
    }

    /* We only add the cone to the database if it failed no tests */
    if(allConeTestsPassed) {
	std::cout << "All Cone tests passed; adding object to database . . ." << std::endl;
	database.Add(cone);
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
