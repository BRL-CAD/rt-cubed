 
/*                  W R I T E S T R I N G . C P P
 * BRL-CAD
 *
 * Copyright (c) 2017 United States Government as represented by
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
/** @file writestring.cpp
 *
 *  BRL-CAD embedded lua script:
 *      standard io stream redirection
 */

#include <iostream>
#include <cstring>

#include "writestring.h"


void (*brlcad_stdoutstream)(const char* text) = 0;
void (*brlcad_sterrstream)(const char* text)  = 0;


void brlcad_writestring
(
    const char* text,
    size_t      textLength
) {
    if ((text != 0) && (textLength > 0)) {
        char* buffer = static_cast<char*>(malloc(textLength + 1));

        memcpy(buffer, text, textLength);
        buffer[textLength] = '\0';

        if (brlcad_stdoutstream != 0)
            brlcad_stdoutstream(buffer);
        else
            std::cout << buffer;

        free(buffer);
    }
}


void brlcad_writeline(void) {
    if (brlcad_stdoutstream != 0)
        brlcad_stdoutstream("\n");
    else
        std::cout << std::endl;
}


void brlcad_writestringerror
(
    const char* formatString,
    const char* textParameter
) {
    if ((formatString != 0) && (textParameter != 0)) {
        size_t bufferSize = 256;
        char*  buffer     = static_cast<char*>(malloc(bufferSize));

        while (snprintf(buffer, bufferSize - 1, formatString, textParameter) < 0) {
            bufferSize *= 2;
            buffer      = static_cast<char*>(realloc(buffer, bufferSize));
        }

        if (brlcad_stdoutstream != 0) {
            brlcad_stdoutstream(buffer);
            brlcad_stdoutstream("\n");
        }
        else
            std::cout << buffer << std::endl;

        free(buffer);
    }
}
