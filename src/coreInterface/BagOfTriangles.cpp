/*                      B A G O F T R I A N G L E S . C P P
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
/** @file BagOfTriangles.cpp
 *
 *  BRL-CAD core C++ interface:
 *      sketch (ID_BOT) database object implementation
 */


#include <cstring>
#include <cassert>

#include "raytrace.h"
#include "rtgeom.h"
#include "bu/parallel.h"

#include <brlcad/BagOfTriangles.h>


using namespace BRLCAD;


static size_t AddToVerts
(
    const point_t&   point,
    rt_bot_internal& bot
) {
    size_t ret = 0; // index of the added vertex
    fastf_t tmp[3];

    //vertex already there?
    for(; ret < bot.num_vertices; ++ret) {
        tmp[0] = bot.vertices[ret];
        tmp[1] = bot.vertices[ret + 1];
        tmp[2] = bot.vertices[ret + 2];

        if (VNEAR_EQUAL(point, tmp, VUNITIZE_TOL))
            break;
    };

    if (ret == bot.num_vertices) {
        // add a new vertex
        ++bot.num_vertices;
        bot.vertices = (fastf_t* ) bu_realloc(bot.vertices, bot.num_vertices * 3 * sizeof(fastf_t), "bot interface AddToVerts()");
        bot.vertices[ret]     = point[0];
        bot.vertices[ret + 1] = point[1];
        bot.vertices[ret + 2] = point[2];
    };

    return ret;
};


static void RemoveFromVerts
(
    size_t           index,
    rt_bot_internal& bot
) {
    assert(index < bot.num_vertices);

    if(index < bot.num_vertices) {
        // is the vertex used elsewhere?
        size_t vertexUsage = 0;
        for(int i = 0; i < bot.num_faces; ++i) {
            if(bot.faces[i] == index) {
                vertexUsage++;
                break;
            };
        };

        if (vertexUsage <= 1) {
            // really remove it
            memcpy(bot.vertices + index, bot.vertices + index + 3, (bot.num_vertices - index - 1) * sizeof(fastf_t));

            --bot.num_vertices;
            bot.vertices = (fastf_t* ) bu_realloc(bot.vertices, bot.num_vertices * 3 * sizeof(fastf_t), "bot interface RemoveFromVerts()");
        }
    };
};


static size_t SwapVertex
(
    size_t           oldIndex,
    const point_t&   newPoint,
    rt_bot_internal& bot
) {
    size_t ret = -1; // index of the new vertex
    fastf_t tmp[3];
    tmp[0] = bot.vertices[oldIndex];
    tmp[1] = bot.vertices[oldIndex + 1];
    tmp[2] = bot.vertices[oldIndex + 2];

    if (VNEAR_EQUAL(newPoint, tmp, VUNITIZE_TOL))
        ret = oldIndex;
    else {
        RemoveFromVerts(oldIndex, bot);

        ret = AddToVerts(newPoint, bot);
    }

    return ret;
};


void bot_free(struct rt_bot_internal *bot_ip)
{
    RT_BOT_CK_MAGIC(bot_ip);
    bot_ip->magic = 0;          /* sanity */

    if (bot_ip->tie != NULL) {
    bot_ip->tie = NULL;
    }

    if (bot_ip->vertices != NULL) {
    bu_free(bot_ip->vertices, "BOT vertices");
    bot_ip->vertices = NULL;
    bot_ip->num_vertices = 0;
    }
    if (bot_ip->faces != NULL) {
    bu_free(bot_ip->faces, "BOT faces");
    bot_ip->faces = NULL;
    bot_ip->num_faces = 0;
    }

    if (bot_ip->mode == RT_BOT_PLATE || bot_ip->mode == RT_BOT_PLATE_NOCOS) {
    if (bot_ip->thickness != NULL) {
        bu_free(bot_ip->thickness, "BOT thickness");
        bot_ip->thickness = NULL;
    }
    if (bot_ip->face_mode != NULL) {
        bu_free(bot_ip->face_mode, "BOT face_mode");
        bot_ip->face_mode = NULL;
    }
    }

    if (bot_ip->normals != NULL) {
    bu_free(bot_ip->normals, "BOT normals");
    }

    if (bot_ip->face_normals != NULL) {
    bu_free(bot_ip->face_normals, "BOT normals");
    }

    bu_free(bot_ip, "bot ifree");
};


struct rt_bot_internal *
bot_copy(const struct rt_bot_internal *bot_ip) {

    struct rt_bot_internal *out;

    RT_BOT_CK_MAGIC(bot_ip);

    BU_ALLOC(out, struct rt_bot_internal);
    *out = *bot_ip;

    if(out->num_faces)
        out->faces =  (int*) bu_calloc(3 * out->num_faces, sizeof(int), "out->faces");

    for(int i = 0; i < 3 * out->num_faces; i++)
        out->faces[i] = bot_ip->faces[i];

    if(out->num_vertices)
        out->vertices = (fastf_t*) bu_calloc(3 * out->num_vertices, sizeof(fastf_t), "out->vertices");

    for(int i = 0; i < 3 * out->num_vertices; i++)
        out->vertices[i] = bot_ip->vertices[i];

    if((out->num_faces != 0) && (out->thickness != NULL))
        out->thickness =  (fastf_t*) bu_calloc(3 * out->num_faces, sizeof(fastf_t), "out->thickness");

    for(int i = 0; i < 3 * out->num_faces; i++)
        out->thickness[i] = bot_ip->thickness[i];

    if(out->num_normals)
        out->normals = (fastf_t*) bu_calloc(3 * out->num_normals, sizeof(fastf_t), "out->normals");

    for(int i = 0; i < 3 * out->num_normals; i++)
        out->normals[i] = bot_ip->normals[i];

    if((out->num_face_normals != 0) && (out->normals != NULL))
        out->face_normals = (int*) bu_calloc(3 * out->num_face_normals, sizeof(int), "out->face_normals");

    return out;
};


void deleteFace(
    size_t index,
    rt_bot_internal& bot
) {
    memcpy(bot.faces + index * 3, bot.faces + index * 3 + 3, (bot.num_faces - (index - 1) * 3) * sizeof(int));

    if(bot.mode != RT_BOT_SURFACE && bot.mode != RT_BOT_SOLID)
        memcpy(bot.thickness + index * 3, bot.thickness + index * 3 + 3, (bot.num_faces - (index - 1) * 3) * sizeof(fastf_t));

    --bot.num_faces;
    bot.faces = (int* ) bu_realloc(bot.faces, bot.num_faces * 3 * sizeof(int), "bot deleteFace()");

    if(bot.mode != RT_BOT_SURFACE && bot.mode != RT_BOT_SOLID)
            bot.thickness = (fastf_t* ) bu_realloc(bot.thickness, bot.num_faces * 3 * sizeof(fastf_t), "bot delete()");
};


BagOfTriangles::BagOfTriangles
(
    void
) throw(bad_alloc) : Object() {
    if (!BU_SETJUMP) {
        BU_GET(m_internalp, rt_bot_internal);
        m_internalp->magic = RT_BOT_INTERNAL_MAGIC;
        m_internalp->num_vertices = 0;
        m_internalp->num_faces = 0;
        m_internalp->num_normals = 0;
        m_internalp->num_face_normals = 0;
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::BagOfTriangles::BagOfTriangles");
    }

    BU_UNSETJUMP;
};


BagOfTriangles::BagOfTriangles
(
    const BagOfTriangles& original
) throw(bad_alloc) {
    if (!BU_SETJUMP)
        m_internalp = bot_copy(original.Internal());
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::BagOfTriangles::BagOfTriangles");
    }

    BU_UNSETJUMP;

};


BagOfTriangles::~BagOfTriangles
(
    void
) throw() {
    if (m_internalp != 0)
        bot_free(m_internalp);
};


const BagOfTriangles& BagOfTriangles::operator=
(
    const BagOfTriangles& original
) throw(bad_alloc) {
    if(&original != this) {
        Copy(original);

        if(!BU_SETJUMP) {
            rt_bot_internal*       thisInternal     = Internal();
            const rt_bot_internal* originalInternal = original.Internal();

            thisInternal = bot_copy(originalInternal);
        }
        else {
            BU_UNSETJUMP;
            throw bad_alloc("BRLAD::BagOfTriangles::operator=");
        }

        BU_UNSETJUMP;
    }
    return *this;
};


Vector3D BagOfTriangles::Face::Point
(
    size_t index
) const throw() {
    assert(index < 3);
    assert(m_bot != 0);

    fastf_t  tmp[3];
    Vector3D ret;

    if(m_bot != 0) {
        tmp[0] = m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index]];
        tmp[1] = m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index] + 1];
        tmp[2] = m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index] + 2];
        ret = Vector3D(tmp);
    }
    return ret;
};


void BagOfTriangles::Face::SetPoint
(
    size_t          index,
    const Vector3D& point
) throw(bad_alloc) {
    assert(index < 3);
    assert(m_bot != 0);

    if(m_bot != 0) {
        for(int i = 0; i < 3; i++)
            m_bot->vertices[m_bot->faces[m_faceIndex * 3 + index] + i] = point.coordinates[i]; 
    }
};


void BagOfTriangles::Face::SetPoints
(
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3
) throw(bad_alloc) {
    assert(m_bot != 0);

    if(m_bot != 0) {
        SetPoint(0, point1);
        SetPoint(1, point2);
        SetPoint(2, point3);
    };
};


double BagOfTriangles::Face::Thickness(void) const throw() {
    assert(m_bot != 0);
    if(m_bot != 0) 
        if(ApendThickness())
            return m_bot->thickness[m_faceIndex];
};


void BagOfTriangles::Face::SetThickness
(
    double t
) throw() {
    assert(m_bot != 0);
    if(m_bot != 0) 
        if(ApendThickness()) 
            m_bot->thickness[m_faceIndex] = t;
};


bool BagOfTriangles::Face::ApendThickness(void) const throw() {
    assert(m_bot != 0);
    if(m_bot != 0) 
        if(BU_BITSET(m_bot->face_mode, m_faceIndex))
            return true;

    return false;
};


void BagOfTriangles::Face::SetApendThickness
(
    bool apendThickness
) throw() {
    assert(m_bot != 0);
    if(m_bot != 0) {
        if(apendThickness)
            BU_BITSET(m_bot->face_mode, m_faceIndex);
        else
            BU_BITCLR(m_bot->face_mode, m_faceIndex);
    }
};


Vector3D BagOfTriangles::Face::Normal
(
    size_t index
) const throw() {
    fastf_t tmp[3];
    Vector3D ret;
    assert(m_bot != 0);

    if(m_bot != 0) {
        tmp[0] = m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3];
        tmp[1] = m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3 + 1];
        tmp[2] = m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3 + 2];
        ret = Vector3D(tmp);
    };

    return ret;
};


void BagOfTriangles::Face::SetNormal
(
    const Vector3D& normal,
    size_t          index
) throw() {
    assert(m_bot != 0);
    if(m_bot != 0) {
        if(m_bot->num_normals == 0) {
            m_bot->num_normals = m_bot->num_faces * 3;
            m_bot->num_face_normals = m_bot->num_faces;

            m_bot->normals = (fastf_t*) bu_calloc(m_bot->num_normals * 3, sizeof(fastf_t), "Face::SetNormal::m_bot->normals");
            m_bot->face_normals = (int*) bu_calloc(m_bot->num_face_normals * 3, sizeof(int), "Face::SetNormal::m_bot->face_normals");

            m_bot->face_normals[m_faceIndex * 3 + index] = 0; // TODO:: find real value

            for(int i = 0; i < 3; i++)
                m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3 + i] = normal.coordinates[i];
        }
        else {
            m_bot->face_normals[m_faceIndex * 3 + index] = 0; // TODO:: find real value

            for(int i = 0; i < 3; i++)
                m_bot->normals[m_bot->face_normals[m_faceIndex * 3 + index] * 3 + i] = normal.coordinates[i];
        }

    }
};


BagOfTriangles::BotMode BagOfTriangles::Mode(void) const throw() {
    BagOfTriangles::BotMode ret;

    switch(Internal()->mode) {
        case RT_BOT_SURFACE:
            ret = BagOfTriangles::Surface;
            break;

        case RT_BOT_SOLID:
            ret = BagOfTriangles::Solid;
            break;

        case RT_BOT_PLATE:
            ret = BagOfTriangles::Plate;
            break;

        case RT_BOT_PLATE_NOCOS:
            ret = EqualLineOfSightPlate;
    };

    return ret;
};


void BagOfTriangles::SetMode
(
    BotMode mode
) throw(bad_alloc) {
    switch(mode) {
        case Surface:
            Internal()->mode = RT_BOT_SURFACE;
            break;

        case Solid:
            Internal()->mode = RT_BOT_SOLID;
            break;

        case Plate:
            Internal()->mode = RT_BOT_PLATE;
            break;

        case EqualLineOfSightPlate:
            Internal()->mode = RT_BOT_PLATE_NOCOS;
    };
};


BagOfTriangles::BotOrientation BagOfTriangles::Orientation(void) const throw() {
    BagOfTriangles::BotOrientation ret = BagOfTriangles::Unoriented;

    switch(Internal()->orientation) {
        case RT_BOT_CW:
            ret = BagOfTriangles::ClockWise;
            break;

        case RT_BOT_CCW:
            ret = BagOfTriangles::CounterClockWise;
    };

    return ret;
};


void BagOfTriangles::SetOrientation
(
    BotOrientation orientation
) throw() {
    switch (orientation) {
        case Unoriented:
            Internal()->orientation = RT_BOT_UNORIENTED;
            break;

        case ClockWise:
            Internal()->orientation = RT_BOT_CW;
            break;

        case CounterClockWise:
            Internal()->orientation = RT_BOT_CCW;
    }
};


bool BagOfTriangles::FacesHaveNormals(void) const throw() {
    if (Internal()->bot_flags & RT_BOT_HAS_SURFACE_NORMALS)
        return true;
    return false;
};


void BagOfTriangles::SetFacesHaveNormals
(
    bool facesHaveNormals
) throw(bad_alloc) {
    if(facesHaveNormals) 
        Internal()->bot_flags |= RT_BOT_HAS_SURFACE_NORMALS;
    else
        Internal()->bot_flags &= (1 << RT_BOT_HAS_SURFACE_NORMALS);
};


bool BagOfTriangles::UseFaceNormals(void) const throw() {
    if(Internal()->bot_flags & RT_BOT_USE_NORMALS)
        return true;

    return false;
};


void BagOfTriangles::SetUseFaceNormals
(
    bool useFaceNormals
) throw() {
    if(useFaceNormals)
        Internal()->bot_flags |= RT_BOT_USE_NORMALS;
    else
        Internal()->bot_flags &= (1 << RT_BOT_USE_NORMALS);
};


bool BagOfTriangles::UseFloats(void) const throw() {
    if(Internal()->bot_flags & RT_BOT_USE_FLOATS)
        return true;
    return false;
};


void BagOfTriangles::SetUseFloats
(
    bool useFloats
) throw() {
    if(useFloats)
        Internal()->bot_flags |= RT_BOT_USE_FLOATS;
    else
        Internal()->bot_flags &= (1 << RT_BOT_USE_FLOATS);
};


int BagOfTriangles::NumberOfFaces(void) const throw() {
    return Internal()->num_faces;
};


BagOfTriangles::Face* BagOfTriangles::Get
(
    size_t index
) throw() {
    return new Face(Internal(), index);
};


BagOfTriangles::Face* BagOfTriangles::AppendFace(void) throw(bad_alloc) {
    BagOfTriangles::Face* ret         = 0;
    point_t               triangle[3] = {0.};
    size_t                faceIndex;

    if(!BU_SETJUMP) {
        rt_bot_internal* bot = Internal();
        if(Internal()->num_faces == 0) {
            Internal()->faces = static_cast<int*>(bu_malloc(3 * sizeof(int), "BagOfTriangles::AppendFace: faces"));

            if(Internal()->mode != RT_BOT_SURFACE && Internal()->mode != RT_BOT_SOLID)
                Internal()->thickness = static_cast<fastf_t*>(bu_malloc(3*sizeof(fastf_t), "BagOfTriangles::AppendFace: thickness"));

            Internal()->vertices     = static_cast<fastf_t*>(bu_malloc(9 * sizeof(fastf_t), "BagOfTriangles::AppendFace: vertices"));
            Internal()->num_vertices = 3;

            faceIndex = 0;

        }
        else {
            Internal()->faces = static_cast<int*>(bu_realloc(Internal()->faces, (3*Internal()->num_faces + 1) * sizeof(int), "BagOfTriangles::AppendFace: faces"));

            if(Internal()->mode != RT_BOT_SURFACE && Internal()->mode != RT_BOT_SOLID)
                Internal()->thickness =static_cast<fastf_t*>(bu_realloc(Internal()->thickness, (3*Internal()->num_faces + 1)*sizeof(fastf_t), "BagOfTriangles::AppendFace: thickness"));

            Internal()->vertices      = static_cast<fastf_t*>(bu_realloc(Internal()->vertices, 3 * (Internal()->num_vertices + 3 ) * sizeof(fastf_t), "BagOfTriangles::AppendFace: vertices"));
            Internal()->num_vertices += 3;

            faceIndex = Internal()->num_faces;
        };

        for(int i = 0; i < 3; i++) {
            Internal()->faces[Internal()->num_faces+i] = Internal()->num_vertices;
            AddToVerts(triangle[i], *bot);
        };

        Internal()->num_faces++;

        if(Internal()->num_normals > 0) {
            Internal()->normals           = static_cast<fastf_t*>(bu_realloc(Internal()->normals, 3 * (Internal()->num_normals + 3 ) * sizeof(fastf_t), "BagOfTriangles::AppendFace::normals"));
            Internal()->face_normals      = static_cast<int*>(bu_realloc(Internal()->face_normals, 3 * (Internal()->num_face_normals + 1) * sizeof(int), "BagOfTriangles::AppendFace::face_normals"));
            Internal()->num_normals      += 3;
            Internal()->num_face_normals += 1;
        };

        ret = new Face(bot, faceIndex);
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::BagOfTriangles::AppendFace");
    };

    BU_UNSETJUMP;

    return ret;
};


BagOfTriangles::Face* BagOfTriangles::InsertFace
(
    size_t          index,
    const Vector3D& point1,
    const Vector3D& point2,
    const Vector3D& point3
) throw(bad_alloc) {
    BagOfTriangles::Face* ret = 0;

    assert(Internal()->num_faces > 0);
    assert(index < Internal()->num_faces);

    if(Internal()-> num_faces <= 0 || index > Internal()->num_faces)
        return NULL;

    if (!BU_SETJUMP) {
        rt_bot_internal* bot = Internal();

        Internal()->faces = static_cast<int*>(bu_realloc(Internal()->faces, (Internal()->num_faces + 1) * 3 * sizeof(int), "BagOfTriangles::InsertFace: faces"));

        if(Internal()->mode != RT_BOT_SURFACE && Internal()->mode != RT_BOT_SOLID) {
            Internal()->thickness = static_cast<fastf_t*>(bu_realloc(Internal()->thickness, (Internal()->num_faces + 1) * 3 * sizeof(fastf_t), "BagOfTriangles::InsertFace: thickness"));

            memmove(Internal()->thickness + index * 3 + 3, Internal()->thickness + 3, (Internal()->num_faces - index) * 3 * sizeof(int));
        }

        if(Internal()->num_normals > 0) {
            Internal()->normals = static_cast<fastf_t*>(bu_realloc(Internal()->normals, 3 * (Internal()->num_normals + 3 ) * sizeof(fastf_t), "BagOfTriangles::InsertFace::normals"));
            Internal()->face_normals = static_cast<int*>(bu_realloc(Internal()->face_normals, 3 * (Internal()->num_face_normals + 1 ) * sizeof(int), "BagOfTriangles::InsertFace::face_normals"));

        };

        Internal()->vertices = static_cast<fastf_t*>(bu_realloc(Internal()->vertices, (Internal()->num_vertices + 3) * 3 * sizeof(fastf_t), "BagOfTriangles::InsertFace: vertices"));

        memmove(Internal()->faces + index * 3 + 3, Internal()->faces + 3, (Internal()->num_faces - index) * 3 * sizeof(int));

        if(Internal()->num_normals > 0) {
            memmove(Internal()->normals + Internal()->face_normals[index] * 3 + 3, Internal()->normals + 3, (Internal()->num_normals - Internal()->face_normals[index]) * 3 * sizeof(fastf_t));
            memmove(Internal()->face_normals + index * 3 + 3, Internal()->face_normals + 3, (Internal()->num_face_normals - index) * 3 * sizeof(int));
        }

        memmove(Internal()->vertices + (index +1) * 3,Internal()->vertices + index * 3, (Internal()->num_vertices - index * 3) * sizeof(fastf_t));

        Internal()->num_faces++;

        if(Internal()->num_normals > 0) {
            Internal()->num_normals      += 3;
            Internal()->num_face_normals += 1;
        }

        Internal()->num_vertices += 3;

        ret = new Face(bot, index);
        ret->SetPoints(point1, point2, point3);
    }
    else {
        BU_UNSETJUMP;
        throw bad_alloc("BRLCAD::BagOfTriangles::InsertFace");
    }

    BU_UNSETJUMP;

    return ret;
};


void BagOfTriangles::DeleteFace(
    size_t index
) throw(bad_alloc) {
    assert(index < Internal()->num_faces);

    if (!BU_SETJUMP) {
        for(int i = 0; i < 3; i++) 
            RemoveFromVerts(Internal()->faces[index + i], *Internal());

        deleteFace(index, *Internal());
    };
};


const Object& BagOfTriangles::operator=
(
    const Object& original
) throw(bad_alloc) {
    const BagOfTriangles* bot = dynamic_cast<const BagOfTriangles*>(&original);
    assert(bot != 0);

    if (bot != 0)
        *this = *bot;

    return *this;
};


Object* BagOfTriangles::Clone(void) const throw(bad_alloc, std::bad_alloc) {
    return new BagOfTriangles(*this);
};


const char* BagOfTriangles::ClassName(void) throw() {
    return "BagOfTriangles";
};


const char* BagOfTriangles::Type(void) const throw() {
    return ClassName();
};


bool BagOfTriangles::IsValid(void) const throw() {
    return true;
};


BagOfTriangles::BagOfTriangles
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) throw() : Object(resp, pDir, ip, dbip), m_internalp(0) {}



rt_bot_internal* BagOfTriangles::Internal(void) throw() {
    rt_bot_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_bot_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_BOT_CK_MAGIC(ret);

    return ret;
};


const rt_bot_internal* BagOfTriangles::Internal(void) const throw() {
    const rt_bot_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_bot_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_SKETCH_CK_MAGIC(ret);

    return ret;
}
