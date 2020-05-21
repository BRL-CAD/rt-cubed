/*                        P I P E . C P P
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
/** @file pipe.cpp
 *
 * BRL-CAD core C++ interface :
 *		Unit tests for Pipe class implementation
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <brlcad/Pipe.h>
#include "bn.h"
#include "primitives.h"
using namespace BRLCAD;

#define VECTOR3D_EQUAL(a, b) VNEAR_EQUAL(a.coordinates, b.coordinates, BN_TOL_DIST)

#define ADD_TEST(expression, allTestsPassed)    \
    if (!expression) {    \
	std::cout << "Failed test: " << #expression << std::endl;    \
	allTestsPassed = false;    \
    } else {    \
	std::cout << "Passed test: " << #expression << std::endl;    \
    }

Pipe makePipe()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D p1 = Vector3D(500.0, 500.0, 50.0);
    const Vector3D p2 = Vector3D(500.0, -500.0, 150.0);
    const Vector3D p3 = Vector3D(-500.0, -500.0, 250.0);
    const Vector3D p4 = Vector3D(-500.0, 500.0, 350.0);
    const double innerDiameter = 0.0;
    const double outerDiameter = 200.0;
    const double bendRadius = 500.0;
    cp = p.AppendControlPoint(p1, innerDiameter, outerDiameter, bendRadius);
    cp = p.AppendControlPoint(p2, innerDiameter, outerDiameter, bendRadius);
    cp = p.AppendControlPoint(p3, innerDiameter, outerDiameter, bendRadius);
    cp = p.AppendControlPoint(p4, innerDiameter, outerDiameter, bendRadius);
    return p;
}

bool testPipeInsertControlPointMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.InsertControlPoint(0, point, innerDiameter, outerDiameter, bendRadius);
    const Vector3D setPoint = cp.Point();
    double setInnerDiameter = cp.InnerDiameter();
    double setOuterDiameter = cp.OuterDiameter();
    double setBendRadius = cp.BendRadius();
    return(VECTOR3D_EQUAL(point, setPoint) &&
	    EQUAL(innerDiameter, setInnerDiameter) &&
	    EQUAL(outerDiameter, setOuterDiameter) &&
	    EQUAL(bendRadius, setBendRadius));
}

bool testPipeAppendControlPointMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    const Vector3D setPoint = cp.Point();
    double setInnerDiameter = cp.InnerDiameter();
    double setOuterDiameter = cp.OuterDiameter();
    double setBendRadius = cp.BendRadius();
    return(VECTOR3D_EQUAL(point, setPoint) &&
	    EQUAL(innerDiameter, setInnerDiameter) &&
	    EQUAL(outerDiameter, setOuterDiameter) &&
	    EQUAL(bendRadius, setBendRadius));
}

bool testPipeGetControlPointMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    point = Vector3D(10.0, 10.0, 5.0);
    innerDiameter = 3.0;
    outerDiameter = 6.0;
    bendRadius = 5.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    cp = p.GetControlPoint(1);
    const Vector3D setPoint = cp.Point();
    double setInnerDiameter = cp.InnerDiameter();
    double setOuterDiameter = cp.OuterDiameter();
    double setBendRadius = cp.BendRadius();
    return(VECTOR3D_EQUAL(point, setPoint) &&
	    EQUAL(innerDiameter, setInnerDiameter) &&
	    EQUAL(outerDiameter, setOuterDiameter) &&
	    EQUAL(bendRadius, setBendRadius));
}

bool testControlPointGetPointMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    const Vector3D setPoint = cp.Point();
    return(VECTOR3D_EQUAL(point, setPoint));
}

bool testControlPointGetInnerDiameterMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    double setInnerDiameter = cp.InnerDiameter();
    return(EQUAL(innerDiameter, setInnerDiameter));
}

bool testControlPointGetOuterDiameterMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    double setOuterDiameter = cp.OuterDiameter();
    return(EQUAL(outerDiameter, setOuterDiameter));
}

bool testControlPointGetBendRadius()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    const Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    double setBendRadius = cp.BendRadius();
    return(EQUAL(bendRadius, setBendRadius));
}

bool testControlPointSetPointMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    point = Vector3D(10.0, 10.0, 5.0);
    innerDiameter = 3.0;
    outerDiameter = 6.0;
    bendRadius = 5.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    cp = p.GetControlPoint(1);
    cp.SetPoint(point);
    const Vector3D setPoint = cp.Point();
    return(VECTOR3D_EQUAL(point, setPoint));
}

bool testControlPointSetInnerDiameterMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    point = Vector3D(10.0, 10.0, 5.0);
    innerDiameter = 3.0;
    outerDiameter = 6.0;
    bendRadius = 5.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    cp = p.GetControlPoint(0);
    cp.SetInnerDiameter(innerDiameter);
    double setInnerDiameter = cp.InnerDiameter();
    return(EQUAL(innerDiameter, setInnerDiameter));
}

bool testControlPointSetOuterDiameterMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    point = Vector3D(10.0, 10.0, 5.0);
    innerDiameter = 3.0;
    outerDiameter = 6.0;
    bendRadius = 5.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    cp = p.GetControlPoint(0);
    cp.SetOuterDiameter(outerDiameter);
    double setOuterDiameter = cp.OuterDiameter();
    return(EQUAL(outerDiameter, setOuterDiameter));
}

bool testControlPointSetBendRadiusMethod()
{
    Pipe p = Pipe();
    Pipe::ControlPoint cp;
    Vector3D point = Vector3D(1.0, 1.0, 1.0);
    double innerDiameter = 3.0;
    double outerDiameter = 6.0;
    double bendRadius = 4.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    point = Vector3D(10.0, 10.0, 5.0);
    innerDiameter = 3.0;
    outerDiameter = 6.0;
    bendRadius = 5.0;		/* bendRadius > outerDiameter / 2 */
    cp = p.AppendControlPoint(point, innerDiameter, outerDiameter, bendRadius);
    cp = p.GetControlPoint(1);
    cp.SetBendRadius(bendRadius);
    double setBendRadius = cp.BendRadius();
    return(EQUAL(bendRadius, setBendRadius));
}

bool testPipeDeleteControlPointMethod()
{
    Pipe p1 = makePipe();
    Pipe p2 = makePipe();
    Pipe::ControlPoint cp1;
    Pipe::ControlPoint cp2;
    p1.DeleteControlPoint(0);
    cp1 = p1.GetControlPoint(0);
    cp2 = p2.GetControlPoint(0);
    const Vector3D point1 = cp1.Point();
    const Vector3D point2 = cp2.Point();
    const double innerDiameter1 = cp1.InnerDiameter();
    const double innerDiameter2 = cp2.InnerDiameter();
    const double outerDiameter1 = cp1.OuterDiameter();
    const double outerDiameter2 = cp2.OuterDiameter();
    const double bendRadius1 = cp1.BendRadius();
    const double bendRadius2 = cp2.BendRadius();
    return(!(VECTOR3D_EQUAL(point1, point2) &&
		EQUAL(innerDiameter1, innerDiameter2) &&
		EQUAL(outerDiameter1, outerDiameter2) &&
		EQUAL(bendRadius1, bendRadius2)));
}

bool testPipeCloneMethod()
{
    Pipe p = makePipe();
    Pipe *clonedPipe = static_cast<Pipe *>(p.Clone());
    return clonedPipe->IsValid();
}

void test_pipe(Database& database)
{
    Pipe p = makePipe();
    bool allPipeTestsPassed = true;

    /* Run tests */
    if(p.IsValid()) {
	std::cout << "Starting Pipe unit testing . . ." << std::endl;
	ADD_TEST(testPipeInsertControlPointMethod(), allPipeTestsPassed);
	ADD_TEST(testPipeAppendControlPointMethod(), allPipeTestsPassed);
	ADD_TEST(testPipeGetControlPointMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointGetPointMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointGetInnerDiameterMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointGetOuterDiameterMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointGetBendRadius(), allPipeTestsPassed);
	ADD_TEST(testControlPointSetPointMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointSetInnerDiameterMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointSetOuterDiameterMethod(), allPipeTestsPassed);
	ADD_TEST(testControlPointSetBendRadiusMethod(), allPipeTestsPassed);
	ADD_TEST(testPipeDeleteControlPointMethod(), allPipeTestsPassed);
	ADD_TEST(testPipeCloneMethod(), allPipeTestsPassed);
    } else {
	std::cout << "Default Pipe is not valid" << std::endl;
	allPipeTestsPassed = false;
    }

    /* We only add the pipe to the database if it failed no tests */
    if(allPipeTestsPassed) {
	std::cout << "All Pipe tests passed, adding object to database . . . " << std::endl;
	database.Add(p);
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
