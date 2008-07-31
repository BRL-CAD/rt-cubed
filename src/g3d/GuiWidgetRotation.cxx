/*             G U I W I D G E T R O T A T I O N . C X X
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

/** @file GuiWidgetRotation.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GuiWidgetRotation class of 3D Geometry
 *	Editor (g3d).
 */

#include "GuiWidgetRotation.h"

#include <RBGui/Widget.h>
#include <RBGui/GuiManager.h>


/*******************************************************************************
 * GuiWidgetRotation
 ******************************************************************************/
GuiWidgetRotation::GuiWidgetRotation(RBGui::GuiManager* guiManager) :
  Widget(guiManager),
  _texture(0),
  _progress(0.0f)
{
  _texture = getRenderTheme()->getTexture("BrlcadCameraRotation");
}

RBGui::Widget* GuiWidgetRotation::factory(RBGui::GuiManager* manager)
{
  return new GuiWidgetRotation(manager);
}

Mocha::String GuiWidgetRotation::getClassName() const
{
  return "GuiWidgetRotation";
}

void GuiWidgetRotation::onDraw(RBGui::Brush& brush) const
{
  brush.setColor(getRenderColor());

  brush.setFilterMode(RBGui::BRUSHFILTER_LINEAR);
  brush.setBlendMode(RBGui::BRUSHBLEND_ALPHA);
  brush.setTexture(_texture);

  brush.drawRectangle(getClientRectangle());
}

void GuiWidgetRotation::getValueList(Mocha::ObjectValueEntryList& out) const
{
  RBGui::Widget::getValueList(out);
  //out.push_back(Mocha::ObjectValueEntry("Image", "text", "Image" ));
}

Mocha::CommandResult GuiWidgetRotation::invoke(const Mocha::String& name,
					       const Mocha::ValueList& in,
					       Mocha::ValueList& out)
{
  // not configurable

  return Widget::invoke(name, in, out);
}

void GuiWidgetRotation::setProgress(float progress)
{
  _progress = progress;
}

float GuiWidgetRotation::getProgress() const
{
  return _progress;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
