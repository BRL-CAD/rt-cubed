/*                      C O M B I N A T I O N . H
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
/** @file Combination.h
 *
 *  BRL-CAD core C++ interface:
 *      combination (ID_COMBINATION) database object declaration
 *
 *  Origin -
 *      TNO (Netherlands)
 *      IABG mbH (Germany)
 */

#ifndef BRLCAD_COMBINATION_INCLUDED
#define BRLCAD_COMBINATION_INCLUDED

#include <brlcad/Object.h>


struct rt_comb_internal;
union tree;


namespace BRLCAD {
    class BRLCAD_COREINTERFACE_EXPORT Combination : public Object {
    public:
        Combination(void);
        Combination(const Combination& original) throw();
        virtual ~Combination(void) throw();

        const Combination&    operator=(const Combination& original) throw();

        class BRLCAD_COREINTERFACE_EXPORT ConstTreeNode {
        public:
            enum Operator {
                Null,         ///< the empty tree of an empty combination, may signal an error too e.g. if an operator of a leaf was requested
                Union,        ///< a binary operation, the set theoretic union set of the two operands
                Intersection, ///< a binary operation, the set theoretic intersection set of the two operands
                Subtraction,  ///< a binary operation, the set theoretic complement or difference set of the two operands
                ExclusiveOr,  ///< a binary operation, the set theoretic symmetric difference set of the two operands
                Not,          ///< a unary operation, the complement with the whole space
                Leaf          ///< actually an operand
            };

            ConstTreeNode(void) throw() : m_tree(0) {}
            ConstTreeNode(const ConstTreeNode& original) throw() : m_tree(original.m_tree) {}
            ~ConstTreeNode(void) throw() {}

            const ConstTreeNode&  operator=(const ConstTreeNode& original) throw() {
                m_tree = original.m_tree;
                return *this;
            }

            Operator      Operation(void) const;
            ConstTreeNode LeftOperand(void) const;  ///< the left operand of a binary operation
            ConstTreeNode RightOperand(void) const; ///< the right operand of a binary operation
            ConstTreeNode Operand(void) const;      ///< the operand of a unary operation
            const char*   Name(void) const;         ///< the name of the operand object in a leaf
            const double* Matrix(void) const;       ///< the transformation matrix of the operand object in a leaf

        protected:
            tree* m_tree;

            ConstTreeNode(tree* original) throw() : m_tree(original) {}

            friend Combination;
        };

        ConstTreeNode         Tree(void) const;

        bool                  IsRegion(void) const throw();
        void                  SetIsRegion(bool value) throw();

        enum FastgenType {
            Non, ///< not a Fastgen region
            Plate,
            Volume
        };

        FastgenType           FastgenRegion(void) const throw();
        void                  SetFastgenRegion(FastgenType value) throw();
        int                   RegionId(void) const throw();
        void                  SetRegionId(int value) throw();
        int                   Aircode(void) const throw();
        void                  SetAircode(int value) throw();
        int                   GiftMaterial(void) const throw();
        void                  SetGiftMaterial(int value) throw();
        int                   LineOfSight(void) const throw();
        void                  SetLineOfSight(int value) throw();
        bool                  HasColor(void) const throw();
        void                  SetHasColor(bool value) throw();
        unsigned char         Red(void) const throw();
        void                  SetRed(unsigned char value) throw();
        unsigned char         Green(void) const throw();
        void                  SetGreen(unsigned char value) throw();
        unsigned char         Blue(void) const throw();
        void                  SetBlue(unsigned char value) throw();
        const char*           Shader(void) const throw();
        void                  SetShader(const char* value) throw();
        bool                  Inherit(void) const throw(); ///< override lower nodes color and shader
        void                  SetInherit(bool value) throw();
        const char*           Material(void) const throw();
        void                  SetMaterial(const char* value) throw();
        double                Temperature(void) const throw();
        void                  SetTemperature(double value) throw();

        // inherited from BRLCAD::Object
        virtual const Object& operator=(const Object& original) throw();
        virtual Object*       Clone(void) const throw(std::bad_alloc);
        static const char*    ClassName(void) throw();
        virtual const char*   Type(void) const throw();

    protected:
        Combination(resource*       resp,
                    directory*      pDir,
                    rt_db_internal* ip,
                    db_i*           dbip = 0) throw();

        friend class ConstDatabase;

    private:
        // holds Objects's content if not connected to a database
        rt_comb_internal* m_internalp;

        const rt_comb_internal*   Internal(void) const;
        virtual rt_comb_internal* Internal(void);

        friend class Database;
    };
}


#endif // BRLCAD_COMBINATION_INCLUDED
