/*               P R I N T T I T L E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2010 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * This file is in the public domain.
 *
 *                        DISCLAIMER OF LIABILITY
 *
 * THIS FILE WAS CAREFULLY TESTED BY THE AUTHOR AND IS MADE AVAILABLE TO YOU
 * FREE-OF-CHARGE IN A HIGH-GRADE ACTUAL STATUS. REFERENCE IS MADE HEREWITH TO
 * THE FACT THAT IT IS NOT POSSIBLE TO DEVELOP SOFTWARE PROGRAMS SO THAT THEY
 * ARE ERROR-FREE FOR ALL APPLICATION CONDITIONS. AS THE FILE IS LICENSED FREE
 * OF CHARGE THERE IS NO WARRANTY FOR IT, INSOFAR AS SUCH WARRANTY IS NOT A
 * MANDATORY REQUIREMENT OF THE APPLICABLE LAW, SUCH AS IN CASE OF WILFUL ACTS.
 * IN ADDITION THERE IS NO LIABILITY ALSO INSOFAR AS SUCH LIABILITY IS NOT A
 * MANDATORY REQUIREMENT OF THE APPLICABLE LAW, SUCH AS IN CASE OF WILFUL ACTS.
 *
 * YOU DECLARE YOU ARE IN AGREEMENT WITH THE USE OF THIS FILE UNDER THE
 * ABOVE-LISTED USAGE CONDITIONS AND THE EXCLUSION OF A GUARANTEE AND OF
 * LIABILITY. SHOULD INDIVIDUAL PROVISIONS IN THESE CONDITIONS BE IN FULL OR IN
 * PART VOID, INVALID OR CONTESTABLE, THE VALIDITY OF ALL OTHER PROVISIONS OR
 * AGREEMENTS ARE UNAFFECTED BY THIS. FURTHER THE PARTIES UNDERTAKE AT THIS
 * JUNCTURE TO AGREE A LEGALLY VALID REPLACEMENT CLAUSE WHICH MOST CLOSELY
 * APPROXIMATES THE ECONOMIC OBJECTIVES.
 */
/** @file PrintTitle.cpp
 *
 *  This is more of a "Hello World!" example program than a real test for the
 *  BRL-CAD core C++ interface library. On the other hand it's a test for the
 *  build system.
 *
 *  Origin -
 *      IABG mbH (Germany)
 */

#include <iostream>

#include <brlcad/ConstDatabase.h>

int main
(
    int   argc,
    char* argv[]
) {
    int ret = 0;

    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <BRL-CAD Database>";
        ret = 1;
    }
    else {
        try {
            BRLCAD::ConstDatabase database;

            if (database.Load(argv[1]))
                std::cout << database.Title();
            else {
                std::cout << "Could not load file: " << argv[1];
                ret = 2;
            }
        }
        catch(BRLCAD::bad_alloc& e) {
            std::cout << "Out of memory in: " << e.what();
            ret = 3;
        }
    }

    return ret;
}
