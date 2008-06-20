/*
-----------------------------------------------------------------------------
This source file is part of the Right Brain Games GUI
For the latest info, see http://www.rightbraingames.com/

Copyright (c) 2000-2007 Right Brain Games Inc.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.

This software may also be used under the terms of a separate unrestricted license,
provided that you have obtained such a license from Right Brain Games Inc.
-----------------------------------------------------------------------------
*/

#include "Mocha/StringTools.h"

#include "RBGui/Widgets/AttributeWidgets/EvaluatorAttributeWidget.h"

namespace RBGui
{

//--------------------------------
EvaluatorAttributeWidget::EvaluatorAttributeWidget( GuiManager* vManager, float vDefaultStep, float vRangeMin, float vRangeMax )
: AttributeWidget( vManager ), mDefaultStep( vDefaultStep ), mDefaultRangeMin( vRangeMin ), mDefaultRangeMax( vRangeMax )
{
	// ...
}

//--------------------------------
EvaluatorAttributeWidget::~EvaluatorAttributeWidget( )
{
	// ...
}

//--------------------------------
void EvaluatorAttributeWidget::setOptions( const Mocha::StringList& vTokens )
{
	EvaluatorWidgetMode i = EVALUATORMODE_FLOAT;

	float step = mDefaultStep;
	float min = mDefaultRangeMin;
	float max = mDefaultRangeMax;

	if ( vTokens.size( ) > 0 )
		step = Mocha::StringToFloat( vTokens[0] );
	
	if ( vTokens.size( ) > 1 )
		min = Mocha::StringToFloat( vTokens[1] );
	
	if ( vTokens.size( ) > 2 )
		max = Mocha::StringToFloat( vTokens[2] );

	if ( vTokens.size( ) > 3 )
	{
		if ( vTokens[3] == "int" )
			i = EVALUATORMODE_INTEGER;
	}

	setParams( step, min, max, i );
}

}
