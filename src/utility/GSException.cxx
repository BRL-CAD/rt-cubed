/*                 G S E X C E P T I O N . C X X
 * BRLCAD
 *
 * Copyright (c) 2010 United States Government as represented by
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
/** @file GSException.cxx
 * GSException.cxx
 *
 *  Created on: Apr 27, 2010
 */

#include "GSException.h"
#include "Logger.h"

GSException::GSException(QString reason)
{
    this->reason = reason;
}

GSException::~GSException() throw ()
{
}

QString GSException::getReason()
{
    return this->reason;
}

void GSException::log(QString origin)
{
    Logger::getInstance()->logERROR(origin, this->reason);
}

// Local Variables:
// tab-width: 8
// mode: C++
// c-basic-offset: 4
// indent-tabs-mode: t
// c-file-style: "stroustrup"
// End:
// ex: shiftwidth=4 tabstop=8
