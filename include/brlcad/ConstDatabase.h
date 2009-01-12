/*                      C O N S T D A T A B A S E . H
 * BRL-CAD
 *
 * Copyright (c) 2008-2009 United States Government as represented by
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

#include <brlcad/Object.h>


struct rt_i;
struct resource;


namespace BRLCAD {
    class BRLCAD_COREINTERFACE_EXPORT ConstDatabase {
    public:
        ConstDatabase(void) throw();
        virtual ~ConstDatabase(void) throw();

        /// associates the handle with a BRL-CAD database file (*.g)
        /** If the handle was already associated with a database file this association will be discarded.
            The file will be opened for reading only. */
        virtual bool Load(const char* fileName) throw();

        /// @name Parsing the database
        //@{
        /// title string read from the database
        const char*  Title(void) const throw();
        /// returns the list of the top level objects via call-backs
        /** To get a list of objects contained in a combination see ListObjects(). */
        void         ListTopObjects(StringCalback& callback) const;
        //@}

        /// @name Accessing objects
        //@{
        bool         IsRegion(const char* objectName) const throw();
        /// returns the list of the objects contained in the combination \a objectName via call-backs
        /** To get a list of top level objects see ListTopObjects(). */
        void         ListObjects(const char*    objectName,
                                 StringCalback& callback) const;

        class ObjectCallback {
        public:
            virtual ~ObjectCallback(void) {}

            /// the user has to implement this object method to evaluate the object
            virtual void operator()(const Object& object) = 0;

        protected:
            ObjectCallback(void) {}
            ObjectCallback(const ObjectCallback&) {}
            const ObjectCallback& operator=(const ObjectCallback&) {return *this;}
        };

        /// selects a single object and hand it over to an ObjectCallback (read only)
        void         Get(const char*     objectName,
                         ObjectCallback& callback);
        //@}

        /// @name Active set functions
        //@{
        /// add the database object \a objectName to the active set
        /** The function accepts a space separated list of object names too,
            but it is not sure that this behaviour will be kept in future versions. */
        void         Select(const char* objectName) throw();
        /// clear the active set
        void         UnSelectAll(void) throw();

        bool         SelectionIsEmpty(void) const throw();
        Vector3D     BoundingBoxMinima(void) const throw();
        Vector3D     BoundingBoxMaxima(void) const throw();

        /// ray trace
        void         ShootRay(const Ray3D& ray,
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
