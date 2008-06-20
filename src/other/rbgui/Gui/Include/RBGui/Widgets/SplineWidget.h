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

#ifndef TOI_SPLINEWIDGET_H
#define TOI_SPLINEWIDGET_H

#include "Mocha/Spline2.h"

#include "RBGui/Widget.h"

namespace RBGui
{

/// A widget that displays a spline and can be optionally edited
class GUI_EXPORT SplineWidget : public Widget
{
private:
	Mocha::Vector2List mHandles;

	Mocha::Spline2 mSpline;

	int mDraggingHandle;

	bool mDragging;

	bool mEditable;

	bool isFlipped( ) const;

	Mocha::Vector2 flipIfFlipped( const Mocha::Vector2& vA ) const;

protected:
	virtual void onDraw( Brush& vBrush ) const;

public:
	SplineWidget( GuiManager* vManager );

	virtual ~SplineWidget( );

	virtual void getValueList( Mocha::ObjectValueEntryList& vOut ) const;

	virtual Mocha::CommandResult invoke( const Mocha::String& vName, const Mocha::ValueList& vIn, Mocha::ValueList& vOut );

	virtual Mocha::String getClassName( ) const;

	virtual void onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMouseReleased( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMouseMotion( const Mocha::Vector2& vRelative, const Mocha::Vector2& vPoint );

	virtual CursorType getCursor( ) const;

	/// Sets the handles of the spline
	/*! \param vHandles a list of Mocha::Vector2 values that represent each handle point on the spline */
	void setHandles( const Mocha::Vector2List& vHandles );

	/// Sets the handles of the spline
	/*! \return vHandles a list of Mocha::Vector2 values that represent each handle point on the spline */
	const Mocha::Vector2List& getHandles( ) const;

	/// Adds a handle to the spline
	/*! \param vPoint The position of the handle */
	void addHandle( const Mocha::Vector2& vPoint );

	/// Removes all handles
	void clearHandles( );

	/// Inserts a handle into the spline
	/*! \param vAfter The index of the handle to insert after
		\param vPoint The position of the handle */
	void insertHandle( int vAfter, Mocha::Vector2& vPoint );

	/// Removes a handle from the spline
	void removeHandle( int vIndex );

	/// Sets whether or not the spline can be edited
	void setEditable( bool vEditable );

	/// Gets whether or not the spline can be edited
	bool getEditable( ) const;

	/// Samples a floating point value from the spline
	float sample( float vY );

	static Widget* factory( GuiManager* vManager );
};

}

#endif
