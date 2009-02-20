/*                      C O M B I N A T I O N . C P P
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
/** @file Combination.cpp
 *
 *  BRL-CAD core C++ interface:
 *      combination (ID_COMBINATION) database object implementation
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#include <cassert>

#include "raytrace.h"

#include <brlcad/Combination.h>


using namespace BRLCAD;


static Combination::ConstTreeNode::Operator ConvertOperator
(
    tree* brlcadTree
) {
    Combination::ConstTreeNode::Operator ret = Combination::ConstTreeNode::Null;

    if (brlcadTree != 0) {
        switch (brlcadTree->tr_op) {
        case OP_UNION:
            ret = Combination::ConstTreeNode::Union;
            break;

        case OP_INTERSECT:
            ret = Combination::ConstTreeNode::Intersection;
            break;

        case OP_SUBTRACT:
            ret = Combination::ConstTreeNode::Subtraction;
            break;

        case OP_XOR:
            ret = Combination::ConstTreeNode::ExclusiveOr;
            break;

        case OP_NOT:
            ret = Combination::ConstTreeNode::Not;
            break;

        case OP_DB_LEAF:
            ret = Combination::ConstTreeNode::Leaf;
            break;

        default:
            assert(0);
        }
    }

    return ret;
}


//
// class Combination::ConstTreeNode
//

Combination::ConstTreeNode::Operator Combination::ConstTreeNode::Operation(void) const {
    return ConvertOperator(m_tree);
}


Combination::ConstTreeNode Combination::ConstTreeNode::LeftOperand(void) const {
    ConstTreeNode ret;

    switch (ConvertOperator(m_tree)) {
    case Union:
    case Intersection:
    case Subtraction:
    case ExclusiveOr:
        ret.m_tree = m_tree->tr_b.tb_left;
    }

    return ret;
}


Combination::ConstTreeNode Combination::ConstTreeNode::RightOperand(void) const {
    ConstTreeNode ret;

    switch (ConvertOperator(m_tree)) {
    case Union:
    case Intersection:
    case Subtraction:
    case ExclusiveOr:
        ret.m_tree = m_tree->tr_b.tb_right;
    }

    return ret;
}


Combination::ConstTreeNode Combination::ConstTreeNode::Operand(void) const {
    ConstTreeNode ret;

    switch (ConvertOperator(m_tree)) {
    case Not:
        ret.m_tree = m_tree->tr_b.tb_left;
    }

    return ret;
}


const char* Combination::ConstTreeNode::Name(void) const {
    const char* ret = 0;

    switch (ConvertOperator(m_tree)) {
    case Leaf:
        ret = m_tree->tr_l.tl_name;
    }

    return ret;
}


const double* Combination::ConstTreeNode::Matrix(void) const {
    const double* ret = 0;

    switch (ConvertOperator(m_tree)) {
    case Leaf:
        ret = m_tree->tr_l.tl_mat;
    }

    return ret;
}


//
// class Combination
//

Combination::Combination(void) throw() : Object() {
    m_internalp = static_cast<rt_comb_internal*>(bu_calloc(1, sizeof(rt_comb_internal), "BRLCAD::Combination::Combination::m_internalp"));

    m_internalp->magic = RT_COMB_MAGIC;
    bu_vls_init(&m_internalp->shader);
    bu_vls_init(&m_internalp->material);
    m_internalp->temperature = -1.;
}


Combination::Combination
(
    const Combination& original
) throw() : Object(original) {
    const rt_comb_internal* internalFrom = original.Internal();

    m_internalp = static_cast<rt_comb_internal*>(bu_calloc(1, sizeof(rt_comb_internal), "BRLCAD::Combination::Combination::m_internalp"));

    m_internalp->magic       = internalFrom->magic;

    if (internalFrom->tree != 0)
        m_internalp->tree = db_dup_subtree(internalFrom->tree, m_resp);

    m_internalp->region_flag = internalFrom->region_flag;
    m_internalp->is_fastgen  = internalFrom->is_fastgen;
    m_internalp->region_id   = internalFrom->region_id;
    m_internalp->aircode     = internalFrom->aircode;
    m_internalp->GIFTmater   = internalFrom->GIFTmater;
    m_internalp->los         = internalFrom->los;
    m_internalp->rgb_valid   = internalFrom->rgb_valid;
    m_internalp->rgb[0]      = internalFrom->rgb[0];
    m_internalp->rgb[1]      = internalFrom->rgb[1];
    m_internalp->rgb[2]      = internalFrom->rgb[2];
    m_internalp->temperature = internalFrom->temperature;
    bu_vls_strcpy(&m_internalp->shader, bu_vls_addr(&internalFrom->shader));
    bu_vls_strcpy(&m_internalp->material, bu_vls_addr(&internalFrom->material));
    m_internalp->inherit     = internalFrom->inherit;
}


Combination::~Combination(void) throw() {
    if (m_internalp != 0) {
        if (m_internalp->tree != 0)
            db_free_tree(m_internalp->tree, m_resp);

        bu_vls_free(&m_internalp->shader);
        bu_vls_free(&m_internalp->material);

        bu_free(m_internalp, "BRLCAD::Combination::~Combination::m_internalp");
    }
}


const Combination& Combination::operator=(const Combination& original) throw() {
    if (&original != this) {
        Copy(original);

        const rt_comb_internal* internalFrom = original.Internal();
        rt_comb_internal*       internalTo = Internal();

        if (internalTo->tree != 0)
            db_free_tree(m_internalp->tree, m_resp);

        if (internalFrom->tree != 0)
            internalTo->tree = db_dup_subtree(internalFrom->tree, m_resp);
        else
            internalTo->tree = 0;

        internalTo->region_flag = internalFrom->region_flag;
        internalTo->is_fastgen  = internalFrom->is_fastgen;
        internalTo->region_id   = internalFrom->region_id;
        internalTo->aircode     = internalFrom->aircode;
        internalTo->GIFTmater   = internalFrom->GIFTmater;
        internalTo->los         = internalFrom->los;
        internalTo->rgb_valid   = internalFrom->rgb_valid;
        internalTo->rgb[0]      = internalFrom->rgb[0];
        internalTo->rgb[1]      = internalFrom->rgb[1];
        internalTo->rgb[2]      = internalFrom->rgb[2];
        internalTo->temperature = internalFrom->temperature;
        bu_vls_strcpy(&internalTo->shader, bu_vls_addr(&internalFrom->shader));
        bu_vls_strcpy(&internalTo->material, bu_vls_addr(&internalFrom->material));
        internalTo->inherit     = internalFrom->inherit;
    }

    return *this;
}


Combination::ConstTreeNode Combination::Tree(void) const {
    return ConstTreeNode(Internal()->tree);
}


bool Combination::IsRegion(void) const throw() {
    return Internal()->region_flag != 0;
}


void Combination::SetIsRegion(bool value) throw() {
    Internal()->region_flag = (value) ? '\1' : '\0';
}


Combination::FastgenType Combination::FastgenRegion(void) const throw() {
    Combination::FastgenType ret = Non;

    switch (Internal()->is_fastgen) {
    case REGION_NON_FASTGEN:
        ret = Non;
        break;

    case REGION_FASTGEN_PLATE:
        ret = Plate;
        break;

    case REGION_FASTGEN_VOLUME:
        ret = Volume;
        break;

    default:
        assert(0);
    }

    return ret;
}


void Combination::SetFastgenRegion(Combination::FastgenType value) throw() {
    switch (value) {
    case Non:
        Internal()->is_fastgen = REGION_NON_FASTGEN;
        break;

    case Plate:
        Internal()->is_fastgen = REGION_FASTGEN_PLATE;
        break;

    case Volume:
        Internal()->is_fastgen = REGION_FASTGEN_VOLUME;
        break;

    default:
        assert(0);
    }
}


int Combination::RegionId(void) const throw() {
    return Internal()->region_id;
}


void Combination:: SetRegionId(int value) throw() {
    Internal()->region_id = value;
}


int Combination::Aircode(void) const throw() {
    return Internal()->aircode;
}


void Combination::SetAircode(int value) throw() {
    Internal()->aircode = value;
}


int Combination::GiftMaterial(void) const throw() {
    return Internal()->GIFTmater;
}


void Combination::SetGiftMaterial(int value) throw() {
    Internal()->GIFTmater = value;
}


int Combination::LineOfSight(void) const throw() {
    return Internal()->los;
}


void Combination::SetLineOfSight(int value) throw() {
    Internal()->los = value;
}


bool Combination::HasColor(void) const throw() {
    return Internal()->rgb_valid != 0;
}


void Combination::SetHasColor(bool value) throw() {
    Internal()->rgb_valid = (value) ? '\1' : '\0';
}


unsigned char Combination::Red(void) const throw() {
    return Internal()->rgb[0];
}


void Combination::SetRed(unsigned char value) throw() {
    Internal()->rgb[0] = value;
}


unsigned char Combination::Green(void) const throw() {
    return Internal()->rgb[1];
}


void Combination::SetGreen(unsigned char value) throw() {
    Internal()->rgb[1] = value;
}


unsigned char Combination::Blue(void) const throw() {
    return Internal()->rgb[2];
}


void Combination::SetBlue(unsigned char value) throw() {
    Internal()->rgb[2] = value;
}


const char* Combination::Shader(void) const throw() {
    return bu_vls_addr(&Internal()->shader);
}


void Combination::SetShader(const char* value) throw() {
    bu_vls_strcpy(&Internal()->shader, value);
}


bool Combination::Inherit(void) const throw() {
    return Internal()->inherit != 0;
}


void Combination::SetInherit(bool value) throw() {
    Internal()->inherit = (value) ? '\1' : '\0';
}


const char* Combination::Material(void) const throw() {
    return bu_vls_addr(&Internal()->material);
}


void Combination::SetMaterial(const char* value) throw() {
    bu_vls_strcpy(&Internal()->material, value);
}


double Combination::Temperature(void) const throw() {
    return Internal()->temperature;
}


void Combination::SetTemperature(double value) throw() {
    Internal()->temperature = static_cast<float>(value);
}


const Object& Combination::operator=
(
    const Object& original
) throw() {
    const Combination* comb = dynamic_cast<const Combination*>(&original);
    assert(comb != 0);

    if (comb != 0)
        *this = *comb;

    return *this;
}


Object* Combination::Clone(void) const throw(std::bad_alloc) {
    return new Combination(*this);
}


const char* Combination::ClassName(void) throw() {
    return "Combination";
}


const char* Combination::Type(void) const throw() {
    return ClassName();
}


Combination::Combination
(
    resource*       resp,
    directory*      pDir,
    rt_db_internal* ip,
    db_i*           dbip
) throw() : Object(resp, pDir, ip, dbip), m_internalp(0) {}


const rt_comb_internal* Combination::Internal(void) const {
    const rt_comb_internal* ret;

    if (m_ip != 0)
        ret = static_cast<const rt_comb_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_CHECK_COMB(ret);

    return ret;
}


rt_comb_internal* Combination::Internal(void) {
    rt_comb_internal* ret;

    if (m_ip != 0)
        ret = static_cast<rt_comb_internal*>(m_ip->idb_ptr);
    else
        ret = m_internalp;

    RT_CHECK_COMB(ret);

    return ret;
}
