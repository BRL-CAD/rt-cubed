/*                       G E D D A T A. H
 * BRL-CAD
 *
 * Copyright (c) 2008 United States Government as represented by
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

/** @file GedData.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Container for libged-related data (to not have it spread
 *	throughout the rest of the code).
 */

#ifndef __G3D_GEDDATA_H__
#define __G3D_GEDDATA_H__


struct db_i;
struct rt_wdb;
struct ged;


/** @brief Class containing libged-related data
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 */
class GedData
{
public:
  /** Singleton, access to the manager */
  static GedData& instance();

  /** Get pointer to the database (where the geometry is stored) */
  struct db_i* getDB();
  /** Get pointer to the working database */
  struct rt_wdb* getWDB();
  /** Get GED context */
  struct ged* getGED();

private:
  /** Singleton instance */
  static GedData* INSTANCE;

  /** In-memory geometry database */
  struct db_i* _dbi;
  /** Working database */
  struct rt_wdb* _wdb;
  /** GED context */
  struct ged* _ged;


  /** Default constructor */
  GedData();
};


#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
