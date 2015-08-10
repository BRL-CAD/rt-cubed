/*                      P I P E . C P P
 * BRL-CAD
 *
 * Copyright (c) 2014 United States Government as represented by
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
/** @file Pipe.cpp
 *
 *  BRL-CAD core C++ interface:
 *      pipe (ID_PIPE) database object implementation
 */

#include <cstring>
#include <cassert>

#include "raytrace.h"
#include "rt/geom.h"
#include "bu/parallel.h"

#include <brlcad/Pipe.h>


using namespace BRLCAD;


static void PipeCopy
(
    rt_pipe_internal*       copiedPipe,
    const rt_pipe_internal* originalPipe
) {
    RT_PIPE_CK_MAGIC(copiedPipe);
    RT_PIPE_CK_MAGIC(originalPipe);

    /* Initialize the new pipe internal structure */
    bu_list_free(&copiedPipe->pipe_segs_head);
    copiedPipe->pipe_count = originalPipe->pipe_count;

    if (originalPipe->pipe_count > 0) {
        /* We use two pointers here : One traverses the pipe internal
        * to be copied and one traverses the pipe internal where it
        * is being copied.
        */
        wdb_pipept* temp = BU_LIST_FIRST(wdb_pipept, &(originalPipe->pipe_segs_head));
        wdb_pipept* itr  = BU_LIST_FIRST(wdb_pipept, &(copiedPipe->pipe_segs_head));

        /* Allocate memory for every new entry in the bu_list of the
        * new pipe internal and copy the contents of pipe internal to
        * be copied into it. We use a separate structure for that
        * and that push that structure into the list. ------> (1)
        */
        wdb_pipept* ctlPoint;
        BU_GET(ctlPoint, wdb_pipept);

        for(int i = 0; i < 3; i++) 
            ctlPoint->pp_coord[i] = temp->pp_coord[i];

        ctlPoint->pp_id         = temp->pp_id;
        ctlPoint->pp_od         = temp->pp_od;
        ctlPoint->pp_bendradius = temp->pp_bendradius;

        BU_LIST_PUSH(&itr->l, &ctlPoint->l);

        /* Perform the task done in (1) iteratively till the complete
        * list has been formed.
        */
        for (int count = 1; count < copiedPipe->pipe_count; ++count) {
            itr  = BU_LIST_NEXT(wdb_pipept, &itr->l);
            temp = BU_LIST_NEXT(wdb_pipept, &temp->l);
            BU_GET(ctlPoint, wdb_pipept);

            for(int i = 0; i < 3; i++)
                ctlPoint->pp_coord[i] = temp->pp_coord[i];

            ctlPoint->pp_id         = temp->pp_id;
            ctlPoint->pp_od         = temp->pp_od;
            ctlPoint->pp_bendradius = temp->pp_bendradius;

            BU_LIST_PUSH(&itr->l, &ctlPoint->l);
        }
    }
}


Pipe::Pipe(void) throw(bad_alloc) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_pipe_internal);
        m_internalp->pipe_magic = RT_PIPE_INTERNAL_MAGIC;
        m_internalp->pipe_count = 0;
        BU_LIST_INIT(&(m_internalp->pipe_segs_head));
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::Pipe::Pipe");
    }

    BU_UNSETJUMP;
}


Pipe::Pipe
(
    const Pipe& original
) throw(bad_alloc) {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_pipe_internal);
        m_internalp->pipe_magic = RT_PIPE_INTERNAL_MAGIC;
        m_internalp->pipe_count = 0;
        BU_LIST_INIT(&(m_internalp->pipe_segs_head));
        PipeCopy(m_internalp, original.Internal());
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::Pipe::Pipe");
    }

    BU_UNSETJUMP;
}


Pipe::~Pipe
(
    void
) throw() {
    if (m_internalp != 0) {
        bu_list_free(&m_internalp->pipe_segs_head);
        bu_free(m_internalp, "BRLCAD::Pipe::~Pipe::m_internalp");
    }
}


const Pipe& Pipe::operator=
(
    const Pipe& original
) throw(bad_alloc) {
    if(&original != this) {
        Copy(original);

        if(!BU_SETJUMP)
            PipeCopy(Internal(), original.Internal());
        else {
            BU_UNSETJUMP;
            throw bad_alloc("BRLAD::Pipe::operator=");
        }

        BU_UNSETJUMP;
    }

    return *this;
}


Vector3D Pipe::ControlPoint::Point(void) const throw() {
    assert(m_pipe != 0);

    Vector3D ret;

    if(m_pipe != 0)
        ret = Vector3D(m_controlPoint->pp_coord);

    return ret;
}


void Pipe::ControlPoint::SetPoint
(
    const Vector3D& point
) throw() {
    assert(m_pipe != 0);

    if(m_pipe != 0) {
        for(int i = 0; i < 3; i++)
            m_controlPoint->pp_coord[i] = point.coordinates[i];
    }
}


double Pipe::ControlPoint::InnerDiameter(void) const throw() {
    assert(m_pipe != 0);

    double ret;

    if(m_pipe != 0)
        ret = m_controlPoint->pp_id;

    return ret;
}


void Pipe::ControlPoint::SetInnerDiameter
(
    double id
) throw() {
    assert(m_pipe != 0);

    if(m_pipe != 0)
        m_controlPoint->pp_id = id;
}


double Pipe::ControlPoint::OuterDiameter(void) const throw() {
    assert(m_pipe != 0);

    double ret;

    if(m_pipe != 0)
        ret = m_controlPoint->pp_od;

    return ret;
}


void Pipe::ControlPoint::SetOuterDiameter
(
    double od
) throw() {
    assert(m_pipe != 0);

    if(m_pipe != 0)
        m_controlPoint->pp_od = od;
}


double Pipe::ControlPoint::BendRadius(void) const throw() {
    assert(m_pipe != 0);

    double ret;

    if(m_pipe != 0)
        ret = m_controlPoint->pp_bendradius;

    return ret;
}


void Pipe::ControlPoint::SetBendRadius
(
    double br
) throw() {
    assert(m_pipe != 0);

    if(m_pipe != 0)
        m_controlPoint->pp_bendradius = br;
}


Pipe::ControlPoint Pipe::Get
(
    size_t index
) throw() {
    assert(index < Internal()->pipe_count);

    Pipe::ControlPoint ret;
    bu_list*           seghead = &Internal()->pipe_segs_head;

    if(index < Internal()->pipe_count) {
        wdb_pipept* itr = BU_LIST_FIRST(wdb_pipept, seghead);

        for (size_t count = 0; count < index; ++count)
            itr = BU_LIST_NEXT(wdb_pipept, &itr->l);

        ret = ControlPoint(Internal(), itr);
    }

    return ret;
}


Pipe::ControlPoint Pipe::AppendControlPoint
(
    const Vector3D& point,
    double          innerDiameter,
    double          outerDiameter,
    double          bendRadius
) throw(bad_alloc) {
    Pipe::ControlPoint ret;

    if(!BU_SETJUMP) {
        wdb_pipept* ctlPoint = static_cast<wdb_pipept*>(bu_calloc(1, sizeof(wdb_pipept),"Pipe::AppendControlPoint: wdb_pipept"));

        for(int i = 0; i < 3; i++)
            ctlPoint->pp_coord[i] = point.coordinates[i];

        ctlPoint->pp_id         = innerDiameter;
        ctlPoint->pp_od         = outerDiameter;
        ctlPoint->pp_bendradius = bendRadius;

        BU_LIST_PUSH(&Internal()->pipe_segs_head, &ctlPoint->l);
        Internal()->pipe_count += 1;

        ret = ControlPoint(Internal(), ctlPoint);
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLAD::Pipe::AppendControlPoint");
    }

    return ret;
}


Pipe::ControlPoint Pipe::InsertControlPoint
(
    size_t          index,
    const Vector3D& point,
    double          innerDiameter,
    double          outerDiameter,
    double          bendRadius
) throw(bad_alloc) {
    assert(index <= Internal()->pipe_count);

    Pipe::ControlPoint ret;

    if (index <= Internal()->pipe_count) {
        if(!BU_SETJUMP) {
            wdb_pipept* ctlPoint = static_cast<wdb_pipept*>(bu_calloc(1, sizeof(wdb_pipept),"Pipe::InsertControlPoint: wdb_pipept"));

            for(int i = 0; i < 3; i++)
                ctlPoint->pp_coord[i] = point.coordinates[i];

            ctlPoint->pp_id         = innerDiameter;
            ctlPoint->pp_od         = outerDiameter;
            ctlPoint->pp_bendradius = bendRadius;

            wdb_pipept* itr = BU_LIST_FIRST(wdb_pipept, &Internal()->pipe_segs_head);

            for (size_t count = 0; count < index; ++count)
                itr = BU_LIST_NEXT(wdb_pipept, &itr->l);

            BU_LIST_INSERT(&itr->l, &ctlPoint->l);
            Internal()->pipe_count += 1;

            ret = ControlPoint(Internal(), ctlPoint);
        }
        else {
            BU_UNSETJUMP;
            throw bad_alloc("BRLAD::Pipe::InsertControlPoint");
        }
    }

    return ret;
}


void Pipe::DeleteControlPoint
(
    size_t index
) throw() {
    assert(index < Internal()->pipe_count);

    if (index < Internal()->pipe_count) {
        wdb_pipept* itr = BU_LIST_FIRST(wdb_pipept, &Internal()->pipe_segs_head);

        for (size_t count = 0; count < index; ++count)
            itr = BU_LIST_NEXT(wdb_pipept, &itr->l);

        BU_LIST_DEQUEUE(&(itr->l));
        bu_free(&(itr->l), "BRLCAD::Pipe::DeleteControlPoint");

        Internal()->pipe_count -= 1;
    }
}


const Object& Pipe::operator=
(
    const Object& original
) throw(bad_alloc) {
    const Pipe* pipe = dynamic_cast<const Pipe*>(&original);
    assert(pipe != 0);

    if (pipe != 0)
        *this = *pipe;

    return *this;
}


Object* Pipe::Clone(void) const throw(bad_alloc, std::bad_alloc) {
    return new Pipe(*this);
}


const char* Pipe::ClassName(void) throw() {
    return "Pipe";
}


const char* Pipe::Type(void) const throw() {
    return ClassName();
}


bool Pipe::IsValid(void) const throw() {
    const rt_pipe_internal* pipe = Internal();

    return ((bu_list_len(&pipe->pipe_segs_head) == pipe->pipe_count) &&
            (rt_pipe_ck(&pipe->pipe_segs_head) == 0));
}


Pipe::Pipe
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) throw() : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_pipe_internal* Pipe::Internal(void) const throw() {
    const rt_pipe_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_pipe_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_PIPE_CK_MAGIC(ret);

    return ret;
}


rt_pipe_internal* Pipe::Internal(void) throw() {
    rt_pipe_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_pipe_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_PIPE_CK_MAGIC(ret);

    return ret;
}
