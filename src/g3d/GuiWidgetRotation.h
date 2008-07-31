/*             G U I W I D G E T R O T A T I O N . H
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

/** @file GuiWidgetRotation.h
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * @brief
 *	Header of the GuiWidgetRotation class of 3D Geometry Editor
 *	(g3d).
 */

#ifndef __G3D_GUIWIDGETROTATION_H__
#define __G3D_GUIWIDGETROTATION_H__


#include <RBGui/Texture.h>
#include <RBGui/Widget.h>


/**
 * @brief GUI Widget Rotation class of the 3D Geometry Editor.
 *
 * @author Manuel A. Fernandez Montecelo <mafm@users.sourceforge.net>
 *
 * This class implements the Widget Rotation (a custom widget).
 */
class GuiWidgetRotation : public RBGui::Widget
{
public:
  /**
   * Default constructor
   *
   * @param guiMgr Link to RBGui's GuiManager
   */
  GuiWidgetRotation(RBGui::GuiManager* guiMgr);

  /** Destructor */
  virtual ~GuiWidgetRotation() { }

  /** @see RBGui::Widget::getClassName */
  virtual Mocha::String getClassName() const;
  /** @see RBGui::Widget::getValueList */
  virtual void getValueList(Mocha::ObjectValueEntryList& out) const;
  /** @see RBGui::Widget::invoke */
  virtual Mocha::CommandResult invoke(const Mocha::String& name,
				      const Mocha::ValueList& in,
				      Mocha::ValueList& out);
  /** @see RBGui::Widget::factory */
  static RBGui::Widget* factory(RBGui::GuiManager* manager);

  /** Set progress, in the range 0-1 */
  void setProgress(float progress);
  /** Get progress, in the range 0-1 */
  float getProgress() const;

protected:
  /** @see RBGui::Widget::onDraw */
  virtual void onDraw(RBGui::Brush& brush) const;

private:
  /** Texture */
  RBGui::Texture* _texture;

  /** Progress */
  float _progress;
};

#endif


// Local Variables: ***
// mode: C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
