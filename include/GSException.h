/*                   G S E X C E P T I O N . H
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
/** @file GSException.h
 * GSException.h
 *
 */

#ifndef __GSEXCEPTION_H__
#define __GSEXCEPTION_H__

#include <exception>
#include <QtCore/QString>

class GSException: public std::exception
{
public:
	GSException(QString reason);
	~GSException() throw ();

	QString getReason();
	void log(QString origin);

private:
	QString reason;
};

#endif /* __GSEXCEPTION_H__ */

/*
 * Local Variables:
 * tab-width: 8
 * mode: C
 * indent-tabs-mode: t
 * c-file-style: "stroustrup"
 * End:
 * ex: shiftwidth=4 tabstop=8
 */
