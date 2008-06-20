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

#include "RBGui/Widget.h"
#include "Mocha/WeakRefPointer.h"

#include "RBGui/Widgets/ButtonWidget.h"
#include "RBGui/Widgets/SplineWidget.h"

namespace RBGui
{

//--------------------------------
/// A widget that contains a spline that can be edited with a drop-down window
class GUI_EXPORT DropSplineWidget : public Widget
{

friend class DropSplineDropButtonCallback;

private:
	Mocha::WeakRefPointer<Window> mDropWindow;

	SplineWidget* mPreviewSpline;

	ButtonWidget* mDropButton;

	void createDropWindow( );

	void dropButtonPressed( GuiElement& vElement, const Mocha::ValueList& vData );

	void splineChanged( GuiElement& vElement, const Mocha::ValueList& vData );

	void dropFocusLost( GuiElement& vElement, const Mocha::ValueList& vData );

protected:
	virtual void onRectangleChanged( );

	virtual void onDraw( Brush& vBrush ) const;

public:
	DropSplineWidget( GuiManager* vManager );

	virtual ~DropSplineWidget( );

	virtual Mocha::String getClassName( ) const;

	/// Sets the spline handles
	/*! \param vHandles A list of Mocha::Vector2 values that represent each handle in the spline */
	void setHandles( const Mocha::Vector2List& vHandles );

	/// Gets the spline handles
	/*! \return A reference to a list of Mocha::Vector2 values that represent each handle in the spline */
	const Mocha::Vector2List& getHandles( ) const;

	static Widget* factory( GuiManager* vManager );
};

}
