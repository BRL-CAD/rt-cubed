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

#ifndef GUI_OGREBRUSH_H
#define GUI_OGREBRUSH_H

#include "Ogre.h"

#include "RBGui/OgreSupport/Defines.h"

#include "RBGui/Brush.h"

namespace RBGui
{

//--------------------------------
struct GuiVertex;

//--------------------------------
class OGREGUISUPPORT_EXPORT OgreBrush : public Brush
{
private:
	Ogre::SceneManager* mSceneManager;

	Ogre::Viewport* mMainView;

	Ogre::RenderSystem* mRenderSystem;

	Ogre::HardwareVertexBufferSharedPtr mBuffer;

	Ogre::RenderOperation mRenderOp;

	Ogre::TexturePtr mDefaultTexture;

	Ogre::MaterialPtr mMaterial;

	GuiVertex* mBatchPointer;

	Mocha::Rectangle mClipRegion;

	float mTargetWidth;

	float mTargetHeight;

	size_t mBatchCount;

	Mocha::RefPointer<Texture> mTexture;

	Mocha::RefPointer<Texture> mTarget;

	Mocha::Color mColor;

	bool mFlipY;
	
	float mTexelOffsetX;

	float mTexelOffsetY;

	void setupHardwareBuffer( );

	void getFinalRect( const Mocha::Rectangle& vIn, Mocha::Rectangle& vOut ) const;

	void getFinalPoint( const Mocha::Vector2& vIn, Mocha::Vector3& vOut ) const;

	void buildVertices( const Mocha::Rectangle& vIn, Mocha::Vector3* vOut ) const;

	void buildUV( const Mocha::Rectangle& vIn, Mocha::Vector2* vOut ) const;

	void renderGlyphs( );

	void renderLines( );

	void renderTriangles( );

public:
	OgreBrush( Ogre::SceneManager* vSceneManager, Ogre::Viewport* vMainView );

	virtual ~OgreBrush( );

	virtual Mocha::Vector2 getScreenSize( );

	virtual Mocha::Rectangle getScreenRectangle( const Mocha::Rectangle& vRectangle );

	virtual void setTarget( Texture* vTexture );

	virtual void setTexture( Texture* vTexture );

	virtual void setColor( const Mocha::Color& vColor );

	virtual void setClipRegion( const Mocha::Rectangle& vRectangle );

	virtual const Mocha::Rectangle& getClipRegion( ) const;

	virtual void setFont( Font* vFont );

	virtual void setBlendMode( BrushBlendMode vMode );

	virtual void setFilterMode( BrushFilterMode vMode );

	virtual void drawTiledRectangle( const Mocha::Rectangle& vRectangle );

	virtual void drawTiledRectangle( const Mocha::Rectangle& vRectangle, const Mocha::Rectangle& vSubRect );

	virtual void drawColorRectangle( const Mocha::Rectangle& vRect, const Mocha::Color& vTopLeft, const Mocha::Color& vTopRight, const Mocha::Color& vLowerLeft, const Mocha::Color& vLowerRight );

	virtual void drawGradient( const Mocha::Rectangle& vRect, GradientType vType, const Mocha::Color& vColor1, const Mocha::Color& vColor2 );

	virtual void drawRectangle( const Mocha::Rectangle& vRectangle, const Mocha::Rectangle& vUV = Mocha::Rectangle( 0.0f, 0.0f, 1.0f, 1.0f ), bool vUVRelative = true );

	virtual void drawText( Font* vFont, const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap = false, TextAlignmentMode vHorzAlign = TEXTALIGN_LEFT, TextAlignmentMode vVertAlign = TEXTALIGN_TOP );

	virtual void drawText( Font* vFont, const LineInfoList& vText, const Mocha::Rectangle& vRect, TextAlignmentMode vHorzAlign = TEXTALIGN_LEFT, TextAlignmentMode vVertAlign = TEXTALIGN_TOP, bool vSelection = false, int vSelectionStart = -1, int vSelectionEnd = -1 );

	virtual void drawLine( const Mocha::Vector2& vPoint1, const Mocha::Vector2& vPoint2 );

	virtual void addGlyph( const Mocha::Rectangle& vRect, const Mocha::Rectangle& vUV, bool vUVRelative = true );

	virtual void beginLines( );

	virtual void addLine( const Mocha::Vector2& vPoint1, const Mocha::Vector2& vPoint2 );

	virtual void endLines( );

	virtual void drawLineRectangle( const Mocha::Rectangle& vRect );

	virtual void beginGlyphs( );

	virtual void endGlyphs( );

	virtual void beginTriangles( );

	virtual void addTriangleVertex( const Mocha::Vector2& vPoint, const Mocha::Vector2& vUV, bool vScreenSpace );

	virtual void endTriangles( );

	virtual void clear( );

	virtual void begin( );

	virtual void end( );
};

}

#endif
