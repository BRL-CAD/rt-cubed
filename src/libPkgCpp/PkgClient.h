/*                    P K G C L I E N T . H
 * BRL-CAD
 *
 * Copyright (c) 2004-2010 United States Government as represented by
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
/** @file PkgClient.h
 *
 *
 */

#ifndef __PKGCLIENT_H__
#define __PKGCLIENT_H__

#include "brlcad/pkg.h"

class PkgClient
{
public:
    PkgClient();
    virtual ~PkgClient();

protected:
    PkgClient(pkg_conn* conn);
    int send(int opcode, const char* buffer, size_t bufferLen)

private:
    pkg_conn* conn;

    void _close();
};

#endif /* __PKGCLIENT_H__ */


/*
 * Local Variables:
 * mode: C
 * tab-width: 8
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
