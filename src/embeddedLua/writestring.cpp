 
/*                  W R I T E S T R I N G . C P P
 * BRL-CAD
 *
 * Copyright (c) 2017 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/** @file writestring.cpp
 *
 *  BRL-CAD embedded lua script:
 *      standard io stream redirection
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

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
        int    printRet   = snprintf(buffer, bufferSize - 1, formatString, textParameter);

        while ((printRet < 0) || (printRet > (bufferSize - 1))) { // MSVS _snprintf vs. C99 snprintf
            if (printRet > 0)
                bufferSize = printRet + 1;
            else
                bufferSize *= 2;

            buffer   = static_cast<char*>(realloc(buffer, bufferSize));
            printRet = snprintf(buffer, bufferSize - 1, formatString, textParameter);
        }

        buffer[bufferSize - 1] = '\0';

        if (brlcad_sterrstream != 0) {
            brlcad_sterrstream(buffer);
            brlcad_sterrstream("\n");
        }
        else
            std::cerr << buffer << std::endl;

        free(buffer);
    }
}
