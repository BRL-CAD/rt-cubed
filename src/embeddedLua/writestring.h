/*                  W R I T E S T R I N G . H
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
/** @file writestring.h
 *
 *  BRL-CAD embedded lua script:
 *      standard io stream redirection
 */

#ifdef __cplusplus
extern "C" {
#endif


extern void (*brlcad_stdoutstream)(const char* text);
extern void (*brlcad_sterrstream)(const char* text);


void brlcad_writestring
(
    const char* text,
    size_t      textLength
);


void brlcad_writeline(void);


void brlcad_writestringerror
(
    const char* formatString,
    const char* textParameter
);


#ifdef __cplusplus
}
#endif
