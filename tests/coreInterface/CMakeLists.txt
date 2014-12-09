#########################################################################
#
#	BRL-CAD
#
#	Copyright (c) 2011-2014 United States Government as represented by
#	the U.S. Army Research Laboratory.
#
#	This file is in the public domain.
#
#	DISCLAIMER OF LIABILITY
#
#	THIS FILE WAS CAREFULLY TESTED BY THE AUTHOR AND IS MADE AVAILABLE TO YOU
#	FREE-OF-CHARGE IN A HIGH-GRADE ACTUAL STATUS. REFERENCE IS MADE HEREWITH TO
#	THE FACT THAT IT IS NOT POSSIBLE TO DEVELOP SOFTWARE PROGRAMS SO THAT THEY
#	ARE ERROR-FREE FOR ALL APPLICATION CONDITIONS. AS THE FILE IS LICENSED FREE
#	OF CHARGE THERE IS NO WARRANTY FOR IT, INSOFAR AS SUCH WARRANTY IS NOT A
#	MANDATORY REQUIREMENT OF THE APPLICABLE LAW, SUCH AS IN CASE OF WILFUL ACTS.
#	IN ADDITION THERE IS NO LIABILITY ALSO INSOFAR AS SUCH LIABILITY IS NOT A
#	MANDATORY REQUIREMENT OF THE APPLICABLE LAW, SUCH AS IN CASE OF WILFUL ACTS.
#
#	YOU DECLARE YOU ARE IN AGREEMENT WITH THE USE OF THIS FILE UNDER THE
#	ABOVE-LISTED USAGE CONDITIONS AND THE EXCLUSION OF A GUARANTEE AND OF
#	LIABILITY. SHOULD INDIVIDUAL PROVISIONS IN THESE CONDITIONS BE IN FULL OR IN
#	PART VOID, INVALID OR CONTESTABLE, THE VALIDITY OF ALL OTHER PROVISIONS OR
#	AGREEMENTS ARE UNAFFECTED BY THIS. FURTHER THE PARTIES UNDERTAKE AT THIS
#	JUNCTURE TO AGREE A LEGALLY VALID REPLACEMENT CLAUSE WHICH MOST CLOSELY
#	APPROXIMATES THE ECONOMIC OBJECTIVES.
#
#########################################################################
#	@file rt^3/tests/coreInterface/CMakeLists.txt
##########################################################################

include_directories (
)

add_executable(printTitle PrintTitle.cpp)
target_link_libraries(printTitle coreinterface)

set (ciTests_SRC
	halfspace.cpp
	primitives.cpp
)

add_executable(tester_ci_primitives ${ciTests_SRC})
target_link_libraries(tester_ci_primitives coreinterface)
add_test(NAME tester_ci_primitives_01 COMMAND tester_ci_primitives test.g)
