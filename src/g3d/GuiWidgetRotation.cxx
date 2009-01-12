/*             G U I W I D G E T R O T A T I O N . C X X
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

/** @file GuiWidgetRotation.cxx
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Implementation of the GuiWidgetRotation class of 3D Geometry
 *	Editor (g3d).
 */

#include <iostream>
#include <sstream>

#include <RBGui/Widget.h>
#include <RBGui/GuiManager.h>

#include "GuiWidgetRotation.h"

#include "Logger.h"


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
  //Mocha::Color baseColor = getRenderColor();
  Mocha::Color baseColor = Mocha::Color(0, 0, 1, 1);
  brush.setColor(baseColor);
  brush.setTexture(_texture);
  brush.setFilterMode(RBGui::BRUSHFILTER_LINEAR);
  brush.setBlendMode(RBGui::BRUSHBLEND_ALPHA);

  Mocha::Rectangle rect = getClientRectangle();
  rect.setYPosition(rect.getPosition().y + rect.getSize().y * 0.45f);
  rect.setHeight(10.0f);
  rect.setWidth(rect.getWidth() * _progress);
  brush.drawRectangle(rect);
  brush.drawText(getRenderTheme()->getFont("ttf-bitstream-vera/VeraBd.ttf"),
                 getLabel(),
		 getClientRectangle());
/* dead code
  Logger::logDEBUG("rect: pos=(%g, %g) size=(%g, %g)",
		   getClientRectangle().getPosition().x,
		   getClientRectangle().getPosition().y,
		   getClientRectangle().getSize().x,
		   getClientRectangle().getSize().y);
*/
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
  return Widget::invoke(name, in, out);
}

void GuiWidgetRotation::setProgress(float progress)
{
  if (progress < 0.0f || progress > 1.0f) {
    Logger::logWARNING("GuiWidgetRotation: Progress out of range 0-1 (%g) corrected",
		       progress);
    if (progress > 1.0f) {
      progress = 1.0f;
    } else {
      progress = 0.0f;
    }
  }

  if (_progress != progress) {
    _progress = progress;
    //Logger::logDEBUG("GuiWidgetRotation: Progress set to: %g", _progress);
    flagDirty();
  }
}

float GuiWidgetRotation::getProgress() const
{
  return _progress;
}

void GuiWidgetRotation::setLabel(const std::string& label)
{
  RBGui::Widget::setText(label);
}

const std::string GuiWidgetRotation::getLabel() const
{
  std::stringstream conversion;
  conversion << std::fixed << std::setprecision(3) << _progress;
  std::string label = RBGui::Widget::getText() + ": " + conversion.str();
  return label;
}


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
