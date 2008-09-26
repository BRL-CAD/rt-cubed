/*                      C O N S T D A T A B A S E . H
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
/** @file ConstDatabase.h
 *
 *  BRL-CAD core C++ interface:
 *      declares a handle on a read-only database
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_CONSTDATABASE_INCLUDED
#define BRLCAD_CONSTDATABASE_INCLUDED

#include <brlcad/common.h>
#include <brlcad/raytrace.h>


struct rt_i;
struct resource;


namespace BRLCAD {
    class ConstDatabase {
    public:
        ConstDatabase(void) throw();
        virtual ~ConstDatabase(void) throw();

        /// associates the handle with a BRL-CAD database file (*.g)
        /** If the handle was already associated with a database file this association will be discarded.
            The file will be opened for reading only. */
        virtual bool                            Load(const char* fileName) throw();

        /// @name Parsing the database
        //@{
        /// title string read from the database
        BRLCAD_COREINTERFACE_EXPORT const char* Title(void) const throw();
        /// returns the list of the top level objects via call-backs
        /** To get a list of objects contained in a combination see ListObjects(). */
        BRLCAD_COREINTERFACE_EXPORT void        ListTopObjects(StringCalback& callback) const;
        //@}

        /// @name Accessing objects
        //@{
        BRLCAD_COREINTERFACE_EXPORT bool        IsRegion(const char* objectName) const throw();
        /// returns the list of the objects contained in the combination \a objectName via call-backs
        /** To get a list of top level objects see ListTopObjects(). */
        BRLCAD_COREINTERFACE_EXPORT void        ListObjects(const char*    objectName,
                                                            StringCalback& callback) const;
        //@}

        /// @name Active set functions
        //@{
        /// add the database object \a objectName to the active set
        /** The function accepts a space separated list of object names too,
            but it is not sure that this behaviour will be kept in future versions. */
        BRLCAD_COREINTERFACE_EXPORT void        Select(const char* objectName) throw();
        /// clear the active set
        BRLCAD_COREINTERFACE_EXPORT void        UnSelectAll(void) throw();

        BRLCAD_COREINTERFACE_EXPORT bool        SelectionIsEmpty(void) const throw();
        BRLCAD_COREINTERFACE_EXPORT Vector3D    BoundingBoxMinima(void) const throw();
        BRLCAD_COREINTERFACE_EXPORT Vector3D    BoundingBoxMaxima(void) const throw();
        //@}

        /// @name Ray trace
        //@{
        BRLCAD_COREINTERFACE_EXPORT void        ShootRay(const Ray3D& ray,
                                                         HitCallback& callback) const throw();
        //@}

    protected:
        rt_i*     m_rtip;
        resource* m_resp;

    private:
        ConstDatabase(const ConstDatabase&) throw();                  // not implemented
        const ConstDatabase& operator=(const ConstDatabase&) throw(); // not implemented
    };
}


#endif // BRLCAD_CONSTDATABASE_INCLUDED
