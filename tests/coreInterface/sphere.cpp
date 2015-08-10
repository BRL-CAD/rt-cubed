/*                      S P H E R E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2015 United States Government as represented by
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
 * C++ core interface Sphere test
 *
 */

#include <iostream>
#include <string>
#include <brlcad/Sphere.h>
#include "primitives.h"
#include "bn.h"

using namespace BRLCAD;

#define ADD_TEST(expression, allTestsPassed)    \
    if (!expression) {    \
	std::cout << "Failed test: " << #expression << std::endl;    \
	allTestsPassed = false;    \
    } else {    \
	std::cout << "Passed test: " << #expression << std::endl;    \
    }

/* Tests Sphere's Center function */
bool testSphereCenter(const BRLCAD::Sphere &sphere, 
	const double expectedX, 
	const double expectedY, 
	const double expectedZ)
{
    const BRLCAD::Vector3D center = sphere.Center();
    return(EQUAL(center.coordinates[0], expectedX) &&
	    EQUAL(center.coordinates[1], expectedY) &&
	    EQUAL(center.coordinates[2], expectedZ));
}

/* Tests Sphere's ClassName function */
bool testSphereClassName(const BRLCAD::Sphere &sphere) 
{
    const std::string name = "Sphere";
    const std::string actualName = sphere.ClassName();
    return(actualName.compare(name) == 0);
}

/* Tests Sphere's Type function */
bool testSphereType(const BRLCAD::Sphere &sphere)
{
    return(sphere.Type() == sphere.ClassName());
}

/* Tests Sphere's IsValid function */
bool testSphereIsValid(const BRLCAD::Sphere &sphere) 
{
    return(sphere.IsValid());
}

/* Tests Sphere's SphereRadius function */
bool testSphereRadius(const BRLCAD::Sphere &sphere, const double expectedRadius)
{
    return(EQUAL(sphere.Radius(), expectedRadius));
}

/* Tests Sphere's Clone function */
bool testSphereClone(BRLCAD::Sphere sphere) 
{
    BRLCAD::Sphere sphere2;
    sphere2 = *static_cast<BRLCAD::Sphere*>(sphere.Clone());
    const BRLCAD::Vector3D center = sphere.Center();
    const BRLCAD::Vector3D center2 = sphere2.Center();
    return(EQUAL(center2.coordinates[0], center.coordinates[0]) &&
	    EQUAL(center2.coordinates[1], center.coordinates[1]) &&
	    EQUAL(center2.coordinates[2], center.coordinates[2]) &&
	    EQUAL(sphere2.Radius(), sphere.Radius()));
}

/* Tests Sphere's Set function */
bool testSphereSet() 
{
    BRLCAD::Sphere sphere;
    sphere.Set(Vector3D(1.0, 1.0, 1.0), 3.0);
    return(EQUAL(sphere.Center().coordinates[0], 1.0) &&
	    EQUAL(sphere.Center().coordinates[1], 1.0) &&
	    EQUAL(sphere.Center().coordinates[0], 1.0) &&
	    EQUAL(sphere.Radius(), 3.0));
}

/* Tests Sphere's SetCenter function */
bool testSphereSetCenter(const Vector3D &coords)
{
    BRLCAD::Sphere sphere;
    sphere.SetCenter(coords);
    const Vector3D center = sphere.Center();
    return(EQUAL(center.coordinates[0], coords.coordinates[0]) &&
	    EQUAL(center.coordinates[1], coords.coordinates[1]) &&
	    EQUAL(center.coordinates[2], coords.coordinates[2]));
}

/* Tests Sphere's SetRadius function */
bool testSphereSetRadius(const double expectedRadius)
{
    BRLCAD::Sphere sphere;
    sphere.SetRadius(expectedRadius);
    return(EQUAL(sphere.Radius(), expectedRadius));
}

/* Tests Sphere's Copy constructor */
bool testSphereCopy(const BRLCAD::Sphere &sphere)
{
    BRLCAD::Sphere sphere2(sphere);
    const Vector3D center = sphere.Center();
    const Vector3D center2 = sphere2.Center();
    return(sphere2.IsValid() &&
	    EQUAL(center2.coordinates[0], center.coordinates[0]) &&
	    EQUAL(center2.coordinates[1], center.coordinates[1]) &&
	    EQUAL(center2.coordinates[2], center.coordinates[2]) &&
	    EQUAL(sphere2.Radius(), sphere.Radius()));
}

/* Tests Sphere's default(unit) constructor */
bool testUnitSphereConstructor()
{
    BRLCAD::Sphere sphere;
    const Vector3D center = sphere.Center();
    return(EQUAL(center.coordinates[0], 0.0) &&
	    EQUAL(center.coordinates[1], 0.0) &&
	    EQUAL(center.coordinates[2], 0.0) &&
	    EQUAL(sphere.Radius(), 1.0));
}

/* Tests Sphere's general constructor */
bool testGeneralSphereConstructor(const Vector3D &center, const double radius)
{
    BRLCAD::Sphere sphere = BRLCAD::Sphere(center, radius);
    const Vector3D newCenter = sphere.Center();
    return(sphere.IsValid() &&
	    EQUAL(newCenter.coordinates[0], center.coordinates[0]) &&
	    EQUAL(newCenter.coordinates[1], center.coordinates[1]) &&
	    EQUAL(newCenter.coordinates[2], center.coordinates[2]) &&
	    EQUAL(sphere.Radius(), radius));
}

/* We now run all the tests */
void test_sphere(BRLCAD::Database& database)
{	

    /* Initialize a Sphere to test on */
    BRLCAD::Sphere sphere;
    const Vector3D center = Vector3D(1.0, 1.0, 1.0);
    sphere.SetCenter(center);
    sphere.SetRadius(3.0);

    bool allSphereTestsPassed = true;

    /* Runs all the tests */
    if(testSphereIsValid(sphere)) {
	std::cout << "Starting Sphere Unit testing . . ." << std::endl;
	ADD_TEST(testSphereCenter(sphere, 1.0, 1.0, 1.0), allSphereTestsPassed);
	ADD_TEST(testSphereRadius(sphere, 3.0), allSphereTestsPassed);
	ADD_TEST(testSphereClassName(sphere), allSphereTestsPassed);
	ADD_TEST(testSphereType(sphere), allSphereTestsPassed);
	ADD_TEST(testSphereSet(), allSphereTestsPassed);
	ADD_TEST(testSphereSetCenter(center), allSphereTestsPassed);
	ADD_TEST(testSphereSetRadius(3.0), allSphereTestsPassed);
	ADD_TEST(testSphereClone(sphere), allSphereTestsPassed);
	ADD_TEST(testSphereCopy(sphere), allSphereTestsPassed);
	ADD_TEST(testUnitSphereConstructor(), allSphereTestsPassed);
	ADD_TEST(testGeneralSphereConstructor(sphere.Center(), sphere.Radius()), allSphereTestsPassed);
    } else {
	std::cout << "Default Sphere is not valid" << std::endl;
	allSphereTestsPassed = false;
    }

    /* We only add the sphere to the database if it failed no tests */
    if(allSphereTestsPassed) {
	std::cout << "All Sphere tests passed; adding object to database . . ." << std::endl;
	database.Add(sphere);
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
