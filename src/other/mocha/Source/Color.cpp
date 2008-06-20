/*
-----------------------------------------------------------------------------
This source file is part of Mocha
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

#include "Mocha/Color.h"

namespace Mocha
{

//--------------------------------------------
const Color Color::Transparent( 0.0f, 0.0f, 0.0f, 0.0f );

//--------------------------------------------
const Color Color::Black( 0.0f, 0.0f, 0.0f, 1.0f );

//--------------------------------------------
const Color Color::White( 1.0f, 1.0f, 1.0f, 1.0f );

//--------------------------------------------
const Color Color::Red( 1.0f, 0.0f, 0.0f, 1.0f );

//--------------------------------------------
const Color Color::Blue( 0.0f, 0.0f, 1.0f, 1.0f );

//--------------------------------------------
const Color Color::Green( 0.0f, 1.0f, 0.0f, 1.0f );

//--------------------------------------------
const Color Color::Yellow( 1.0f, 1.0f, 0.0f, 1.0f );

//--------------------------------------------
const Color Color::Magenta( 1.0f, 0.0f, 1.0f, 1.0f );

//--------------------------------------------
const Color Color::Gray( 0.5f, 0.5f, 0.5f, 1.0f );

//--------------------------------------------
void Color::setHSVA( float h, float s, float v, float va )
{
	h = (h * 360.0f);
	h = floatModulos(h, 360.0f );

	if ( s == 0.0f ) 
	{
		r = v;
		g = v;
		b = v;
	} 
	else 
	{
		int i;
		float f;
		float p;
		float q;
		float t;

		h /= 60.0;

		i = (int)floor( h );
		f = h - i;
		p = v * ( 1.0f - s );
		q = v * ( 1.0f - ( s * f ) );
		t = v * ( 1.0f - ( s * ( 1.0f - f ) ) );

		switch ( i ) 
		{

		case 0: 
			r = v;
			g = t;
			b = p;
			break;

		case 1: 
			r = q;
			g = v;
			b = p;
			break;
		case 2: 
			r = p;
			g = v;
			b = t;
			break;
		case 3: 
            r = p;
			g = q;
			b = v;
			break;
		case 4: 
			r = t;
			g = p;
			b = v;
			break;
		case 5: 
			r = v;
			g = p;
			b = q;
			break;
		}
	}

	a = va;
}

//--------------------------------------------
void Color::getHSV( float& h, float& s, float& v ) const
{
	float max_v,min_v,diff,r_dist,g_dist,b_dist;
	float undefined = 0.0;
		
	max_v = max(r, max(g,b));
	min_v = min(r, min(g,b));
	diff = max_v - min_v;
	v = max_v;
		
	if( max_v != 0 )
	{
		s = diff/max_v;
	}
	else
	{
		s = 0.0f;
	}

	if( s == 0 )
	{
		h = 0.0f;
	}
	else 
	{
		r_dist = (max_v - r)/diff;
		g_dist = (max_v - g)/diff;
		b_dist = (max_v - b)/diff;
		if( r == max_v ) 
		{
			h = b_dist - g_dist;
		}
		else
		{
			if( g == max_v )
			{
				h = 2 + r_dist - b_dist;
			}
			else
			{
				if( b == max_v )
				{
					h = 4 + g_dist - r_dist;
				}
			}
		}
		h *= 60;
		if( h < 0)
		{
			h += 360.0;
		}
	}

	h /= 360.0f;
}

}
