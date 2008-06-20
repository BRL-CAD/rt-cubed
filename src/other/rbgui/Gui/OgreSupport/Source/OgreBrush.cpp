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

#include "Mocha/Vector3.h"
#include "Mocha/Vector2.h"
#include "Mocha/Color.h"

#include "RBGui/OgreSupport/OgreBrush.h"
#include "RBGui/OgreSupport/OgreTexture.h"

#define VERTEX_COUNT 3072

namespace RBGui
{

//--------------------------------
struct GuiVertex
{
	Mocha::Vector3 pos;
	Mocha::Color color;
	Mocha::Vector2 uv;
};

//--------------------------------
OgreBrush::OgreBrush( Ogre::SceneManager* vSceneManager, Ogre::Viewport* vMainView )
: mSceneManager( vSceneManager ), mMainView( vMainView ), mTargetWidth( 0.0f ), mTargetHeight( 0.0f ), mBatchPointer( 0 ), mBatchCount( 0 )
{
	mRenderSystem = Ogre::Root::getSingleton( ).getRenderSystem( );

	// Setup the hardware buffer

	setupHardwareBuffer( );

	// Create default texture and fill it with white

	static size_t texCount = 0;

	std::ostringstream s;
	s << "_Gui_Brush_Texture_" << texCount++;

	mDefaultTexture = Ogre::TextureManager::getSingleton( ).createManual( s.str( ), Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
																		  Ogre::TEX_TYPE_2D, 64, 64, 1, 0, Ogre::PF_R8G8B8A8, Ogre::TU_DEFAULT );

	void* buffer = mDefaultTexture->getBuffer( )->lock( Ogre::HardwareBuffer::HBL_DISCARD );
	memset( buffer, 255, mDefaultTexture->getBuffer( )->getSizeInBytes( ) );
	mDefaultTexture->getBuffer( )->unlock( );

	// Load the material

	mMaterial = Ogre::MaterialManager::getSingleton( ).load( "GuiMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );

	// If we're using OpenGL, we do not need to flip the Y coordinates of rectangles

	mFlipY = ( mRenderSystem->getName( ) != "OpenGL Rendering Subsystem" );

	// Cache texel offsets

	mTexelOffsetX = mRenderSystem->getHorizontalTexelOffset( );
	mTexelOffsetY = -mRenderSystem->getVerticalTexelOffset( );
}

//--------------------------------
OgreBrush::~OgreBrush( )
{
	// Remove the GUI default texture

	if ( mDefaultTexture.isNull( ) == false )
		Ogre::TextureManager::getSingleton( ).remove( mDefaultTexture->getName( ) );
}

//--------------------------------
Mocha::Vector2 OgreBrush::getScreenSize( )
{
	return Mocha::Vector2( mMainView->getActualWidth( ), mMainView->getActualHeight( ) );
}

//--------------------------------
void OgreBrush::setupHardwareBuffer( )
{
	mRenderOp.vertexData = new Ogre::VertexData( );
	mRenderOp.vertexData->vertexStart = 0;

	Ogre::VertexDeclaration* vd = mRenderOp.vertexData->vertexDeclaration;

	// Add position

	vd->addElement( 0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION );

	// Add color

	vd->addElement( 0, Ogre::VertexElement::getTypeSize( Ogre::VET_FLOAT3 ), Ogre::VET_FLOAT4, Ogre::VES_DIFFUSE );

	// Add texture coordinates

	vd->addElement( 0, Ogre::VertexElement::getTypeSize( Ogre::VET_FLOAT3 ) +
					   Ogre::VertexElement::getTypeSize( Ogre::VET_FLOAT4 ),
					   Ogre::VET_FLOAT2, Ogre::VES_TEXTURE_COORDINATES );

	// Create buffer

	mBuffer = Ogre::HardwareBufferManager::getSingleton( ).createVertexBuffer(
		vd->getVertexSize( 0 ),
		VERTEX_COUNT,
		Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE,
		false );

	mRenderOp.vertexData->vertexBufferBinding->setBinding( 0, mBuffer );
	mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
	mRenderOp.useIndexes = false;
}


//--------------------------------
void OgreBrush::setTexture( Texture* vTexture )
{
	const Ogre::TexturePtr& tex = ( vTexture ? static_cast<OgreTexture*>( vTexture )->getOgreTexture( ) : mDefaultTexture );
	mRenderSystem->_setTexture( 0, true, tex );

	mTexture = vTexture;
}

//--------------------------------
void OgreBrush::setColor( const Mocha::Color& vColor )
{
	mColor = vColor;
}

//--------------------------------
void OgreBrush::setClipRegion( const Mocha::Rectangle& vRectangle )
{
	mRenderSystem->setScissorTest( true, vRectangle.left, vRectangle.top, vRectangle.right, vRectangle.bottom );
	mClipRegion = vRectangle;
}

//--------------------------------
const Mocha::Rectangle& OgreBrush::getClipRegion( ) const
{
	return mClipRegion;
}

//--------------------------------
void OgreBrush::setFont( Font* vFont )
{
	// ...
}

//--------------------------------
void OgreBrush::setTarget( Texture* vTexture )
{
	Ogre::Viewport* view = 0;

	// Get the target

	if ( vTexture )
	{
		// Make sure texture is a render target

		if ( vTexture->getRenderTarget( ) == false )
			return;

		// Set viewport of target

		view = static_cast<OgreTexture*>( vTexture )->getOgreTexture( )->getBuffer( )->getRenderTarget( )->getViewport( 0 );
	}
	else
		view = mMainView;

	// Set new viewport on render system and reset clip region

	mTargetWidth = view->getActualWidth( );
	mTargetHeight = view->getActualHeight( );

	mRenderSystem->_setViewport( view );
	mRenderSystem->_setCullingMode( Ogre::CULL_NONE );

	setClipRegion( Mocha::Rectangle( view->getActualLeft( ), view->getActualTop( ), view->getActualLeft( ) + view->getActualWidth( ), view->getActualTop( ) + view->getActualHeight( ) ) );
	
	// Save pointer to new target
	
	mTarget = vTexture;
}


//--------------------------------
void OgreBrush::begin( )
{
	// The OpenGL renderer for some reason requires the identity matrices
	// to be set manually, even though we are using a fully programmable pipline

	mRenderSystem->_setWorldMatrix( Ogre::Matrix4::IDENTITY );
	mRenderSystem->_setProjectionMatrix( Ogre::Matrix4::IDENTITY );
	mRenderSystem->_setViewMatrix( Ogre::Matrix4::IDENTITY );

	// Set material pass. This will bind the vertex and fragment program,
	// and setup some basic state settings for rendering 2D elements.

	mSceneManager->_setPass( mMaterial->getTechnique( 0 )->getPass( 0 ) );

	// Set default settings

	setTarget( 0 );
	setTexture( 0 );
	setColor( Mocha::Color::White );
	setBlendMode( BRUSHBLEND_NONE );
	setFilterMode( BRUSHFILTER_NEAREST );
}

//--------------------------------
void OgreBrush::getFinalRect( const Mocha::Rectangle& vIn, Mocha::Rectangle& vOut ) const
{
	// Flip Y coordinates if necessary

	if ( (mTarget != 0) && (mFlipY == false) )
	{
		vOut.left = (int)(vIn.left);
		vOut.right = (int)(vIn.right);
		vOut.top = (int)(vIn.top);
		vOut.bottom = (int)(vIn.bottom);
	}
	else
	{
		vOut.left = (int)(vIn.left);
		vOut.right = (int)(vIn.right);
		vOut.top = (int)(mTargetHeight - vIn.top);
		vOut.bottom = (int)(mTargetHeight - vIn.bottom);
	}

	// Align the rectangle properly to texel offset and whole pixels

	vOut.translate( mTexelOffsetX, mTexelOffsetY );

	// Convert quad co-ordinates for a -1 to 1 co-ordinate system.

	vOut.left /= ( mTargetWidth * 0.5f );
	vOut.right /= ( mTargetWidth * 0.5f );

	vOut.top /= ( mTargetHeight * 0.5f );
	vOut.bottom /= ( mTargetHeight * 0.5f );

	vOut.translate( -1.0f, -1.0f );
}

//--------------------------------
Mocha::Rectangle OgreBrush::getScreenRectangle( const Mocha::Rectangle& vRectangle )
{
	Mocha::Rectangle tmp;
	getFinalRect( vRectangle, tmp );

	return tmp;
}

//--------------------------------
void OgreBrush::getFinalPoint( const Mocha::Vector2& vIn, Mocha::Vector3& vOut ) const
{
	vOut.x = vIn.x + mRenderSystem->getHorizontalTexelOffset( );
	vOut.y = (int)(mTargetHeight - vIn.y) + -mRenderSystem->getVerticalTexelOffset( );
	vOut.z = 0.0f;

	vOut.x /= ( mTargetWidth * 0.5f );
	vOut.y /= ( mTargetHeight * 0.5f );

	vOut.x -= 1.0f;
	vOut.y -= 1.0f;
}

//--------------------------------
void OgreBrush::buildVertices( const Mocha::Rectangle& vIn, Mocha::Vector3* vOut ) const
{
	// Calculate final screen rectangle

	Mocha::Rectangle finalRect;
	getFinalRect( vIn, finalRect );

	// Setup the coordinates for the quad

	vOut[0] = Mocha::Vector3( finalRect.left, finalRect.bottom, 0.0f );
	vOut[1] = Mocha::Vector3( finalRect.right, finalRect.bottom, 0.0f );
	vOut[2] = Mocha::Vector3( finalRect.left, finalRect.top, 0.0f );
	vOut[3] = Mocha::Vector3( finalRect.right, finalRect.bottom, 0.0f );
	vOut[4] = Mocha::Vector3( finalRect.right, finalRect.top, 0.0f );
	vOut[5] = Mocha::Vector3( finalRect.left, finalRect.top, 0.0f );
}

//--------------------------------
void OgreBrush::buildUV( const Mocha::Rectangle& vIn, Mocha::Vector2* vOut ) const
{
	// Setup the UV coordinates for the rectangle

	vOut[0] = Mocha::Vector2( vIn.left, vIn.bottom );
	vOut[1] = Mocha::Vector2( vIn.right, vIn.bottom );
	vOut[2] = Mocha::Vector2( vIn.left, vIn.top );
	vOut[3] = Mocha::Vector2( vIn.right, vIn.bottom );
	vOut[4] = Mocha::Vector2( vIn.right, vIn.top );
	vOut[5] = Mocha::Vector2( vIn.left, vIn.top );
}

//--------------------------------
void OgreBrush::end( )
{
	// Reset scissor testing

	mRenderSystem->setScissorTest( false );
}

//--------------------------------
void OgreBrush::clear( )
{
	mRenderSystem->clearFrameBuffer( Ogre::FBT_COLOUR, Ogre::ColourValue( mColor.r, mColor.g, mColor.b, mColor.a ) );
}

//--------------------------------
void OgreBrush::renderGlyphs( )
{
	// Render!

	mRenderOp.vertexData->vertexCount = mBatchCount * 6;
	mRenderSystem->_render( mRenderOp );
}

//--------------------------------
void OgreBrush::renderTriangles( )
{
	// Render!

	mRenderOp.vertexData->vertexCount = mBatchCount;
	mRenderSystem->_render( mRenderOp );
}

//--------------------------------
void OgreBrush::renderLines( )
{
	// Render!

	mRenderOp.vertexData->vertexCount = mBatchCount * 2;
	mRenderOp.operationType = Ogre::RenderOperation::OT_LINE_LIST;

	mRenderSystem->_render( mRenderOp );

	// Reset operation type

	mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
}

//--------------------------------
void OgreBrush::beginGlyphs( )
{
	if ( mBatchPointer == 0 )
	{
		mBatchPointer = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::endGlyphs( )
{
	if ( mBatchPointer != 0 )
	{
		mBuffer->unlock( );

		if ( mBatchCount > 0 )
			renderGlyphs( );

		mBatchPointer = 0;
		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::addGlyph( const Mocha::Rectangle& vRect, const Mocha::Rectangle& vUV, bool vUVRelative )
{
	// Setup the vertex and uv coordinates for the quad

	Mocha::Vector3 verts[6];
	buildVertices( vRect, verts );

	Mocha::Vector2 uv[6];
	if ( mTexture && (vUVRelative == false) )
	{
		// Translate absolute coordinates to relative

		const Mocha::Vector2 size = mTexture->getSize( );

		Mocha::Rectangle r;
		r.top = vUV.top / size.y;
		r.bottom = vUV.bottom / size.y;
		r.left = vUV.left / size.x;
		r.right = vUV.right / size.x;

		buildUV( r, uv );
	}
	else
		buildUV( vUV, uv );

	// Write the quad to the buffer

	int x;
	for ( x = 0; x < 6; x++ )
	{
		mBatchPointer[x].pos = verts[x];
		mBatchPointer[x].color = mColor;
		mBatchPointer[x].uv = uv[x];
	}

	// Advance glyph pointer

	mBatchPointer += 6;

	// Increase glyph count

	mBatchCount++;

	// See if we're over the limit...

	if ( mBatchCount >= (VERTEX_COUNT/6) )
	{
		// First unlock the buffer

		mBuffer->unlock( );

		// Render whats in the buffer

		renderGlyphs( );

		// Re-lock buffer

		mBatchPointer = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
	
		// Reset glyph count

		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::drawTiledRectangle( const Mocha::Rectangle& vRectangle )
{
	if ( mTexture )
	{
		const Mocha::Vector2 size = mTexture->getSize( );

		Mocha::Rectangle subRect( 0.0f, 0.0f, size.x, size.y );
		drawTiledRectangle( vRectangle, subRect );
	}
}

//--------------------------------
void OgreBrush::drawTiledRectangle( const Mocha::Rectangle& vRectangle, const Mocha::Rectangle& vSubRect )
{
	if ( mTexture == 0 )
		return;

	Mocha::Rectangle clip = getClipRegion( );
	setClipRegion( clip.intersect( vRectangle ) );

	beginGlyphs( );

	int w = vSubRect.getWidth( );
	int h = vSubRect.getHeight( );

	const Mocha::Vector2 texSize = mTexture->getSize( );

	Mocha::Rectangle uv;
	uv.left = vSubRect.left / texSize.x;
	uv.right = vSubRect.right / texSize.x;
	uv.top = vSubRect.top / texSize.y;
	uv.bottom = vSubRect.bottom / texSize.y;

	int tilex = ceilf( vRectangle.getWidth( ) / w );
	if ( tilex < 1 )
		tilex = 1;

	int tiley = ceilf( vRectangle.getHeight( ) / h );
	if ( tiley < 1 )
		tiley = 1;

	int y;
	for ( y = 0; y < tiley; y++ )
	{
		int x;
		for ( x = 0; x < tilex; x++ )
		{
			Mocha::Rectangle c;
			c.setPosition( vRectangle.left + (x * w), vRectangle.top + (y * h) );
			c.setSize( 32, 32 );

			addGlyph( c, uv );
		}
	}

	endGlyphs( );
	setClipRegion( clip );
}

//--------------------------------
void OgreBrush::drawColorRectangle( const Mocha::Rectangle& vRect, const Mocha::Color& vTopLeft, const Mocha::Color& vTopRight, const Mocha::Color& vLowerLeft, const Mocha::Color& vLowerRight )
{
	// Setup the coordinates for the quad

	Mocha::Vector3 verts[6];
	buildVertices( vRect, verts );

	// Setup UV coords

	Mocha::Vector2 uv[6];
	buildUV( Mocha::Rectangle( 0.0f, 0.0f, 1.0f, 1.0f ), uv );

	// Setup colors

	Mocha::Color colors[6];
	colors[0] = vLowerLeft;
	colors[1] = vLowerRight;
	colors[2] = vTopLeft;
	colors[3] = vLowerRight;
	colors[4] = vTopRight;
	colors[5] = vTopLeft;

	// Lock buffer

	GuiVertex* data = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );

	// Write the quad to the buffer

	size_t x;
	for ( x = 0; x < 6; x++ )
	{
		data[x].pos = verts[x];
		data[x].color = colors[x];
		data[x].uv = uv[x];
	}

	// All done!

	mBuffer->unlock( );

	// Render!

	mRenderOp.vertexData->vertexCount = 6;
	mRenderSystem->_render( mRenderOp );
}

//--------------------------------
void OgreBrush::drawGradient( const Mocha::Rectangle& vRect, GradientType vType, const Mocha::Color& vColor1, const Mocha::Color& vColor2 )
{
	// Setup the coordinates for the quad

	Mocha::Vector3 verts[6];
	buildVertices( vRect, verts );

	// Get UV coordinates

	Mocha::Vector2 uv[6];
	buildUV( Mocha::Rectangle( 0.0f, 0.0f, 1.0f, 1.0f ), uv );

	// Setup colors

	Mocha::Color colors[6];
	if ( vType == GRADIENT_VERTICAL )
	{
		colors[0] = vColor2;
		colors[1] = vColor2;
		colors[2] = vColor1;
		colors[3] = vColor2;
		colors[4] = vColor1;
		colors[5] = vColor1;
	}
	else
	{
		colors[0] = vColor1;
		colors[1] = vColor2;
		colors[2] = vColor1;
		colors[3] = vColor2;
		colors[4] = vColor2;
		colors[5] = vColor1;
	}
	
	// Lock buffer

	GuiVertex* data = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );

	// Write vertices

	size_t x;
	for ( x = 0; x < 6; x++ )
	{
		data[x].pos = verts[x];
		data[x].color = colors[x];
		data[x].uv = uv[x];
	}

	// All done!

	mBuffer->unlock( );

	// Render!

	mRenderOp.vertexData->vertexCount = 6;
	mRenderSystem->_render( mRenderOp );
}

//--------------------------------
void OgreBrush::drawRectangle( const Mocha::Rectangle& vRectangle, const Mocha::Rectangle& vUV, bool vUVRelative )
{
	// Setup the vertex and uv coordinates for the quad

	Mocha::Vector3 verts[6];
	buildVertices( vRectangle, verts );

	Mocha::Vector2 uv[6];
	if ( mTexture && (vUVRelative == false) )
	{
		// Translate absolute coordinates to relative

		const Mocha::Vector2 size = mTexture->getSize( );

		Mocha::Rectangle r;
		r.top = vUV.top / size.y;
		r.bottom = vUV.bottom / size.y;
		r.left = vUV.left / size.x;
		r.right = vUV.right / size.x;

		buildUV( r, uv );
	}
	else
		buildUV( vUV, uv );

	// Lock buffer

	GuiVertex* data = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );

	// Write vertices

	size_t x;
	for ( x = 0; x < 6; x++ )
	{
		data[x].pos = verts[x];
		data[x].color = mColor;
		data[x].uv = uv[x];
	}

	// Unlock buffer

	mBuffer->unlock( );

	// Render!

	mRenderOp.vertexData->vertexCount = 6;
	mRenderSystem->_render( mRenderOp );
}


//--------------------------------------------
void OgreBrush::drawText( Font* vFont, const Mocha::String& vText, const Mocha::Rectangle& vRect, bool vWrap, TextAlignmentMode vHorzAlign, TextAlignmentMode vVertAlign )
{
	setTexture( vFont->getTexture( ) );

	beginGlyphs( );
	vFont->renderAligned( (*this), vText, mColor, vRect, true, vHorzAlign, vVertAlign, vWrap );
	endGlyphs( );
}

//--------------------------------------------
void OgreBrush::drawText( Font* vFont, const LineInfoList& vText, const Mocha::Rectangle& vRect, TextAlignmentMode vHorzAlign, TextAlignmentMode vVertAlign, bool vSelection, int vSelectionStart, int vSelectionEnd )
{
	if ( vSelection == false )
	{
		setTexture( vFont->getTexture( ) );
		beginGlyphs( );
	}
	else
	{
		setTexture( 0 );
		beginGlyphs( );
	}

	vFont->renderAligned( (*this), vText, mColor, vRect, true, vHorzAlign, vVertAlign, vSelection, vSelectionStart, vSelectionEnd );
	endGlyphs( );
}

//--------------------------------
void OgreBrush::setBlendMode( BrushBlendMode vMode )
{
	switch ( vMode )
	{
	case BRUSHBLEND_NONE:
		mRenderSystem->_setSceneBlending( Ogre::SBF_ONE, Ogre::SBF_ZERO );
		break;

	case BRUSHBLEND_MODULATE:
		mRenderSystem->_setSeparateSceneBlending( Ogre::SBF_ZERO, Ogre::SBF_SOURCE_COLOUR, Ogre::SBF_ONE, Ogre::SBF_ONE );
		break;

	case BRUSHBLEND_DISCARDALPHA:
		mRenderSystem->_setSeparateSceneBlending( Ogre::SBF_ONE, Ogre::SBF_ZERO, Ogre::SBF_ZERO, Ogre::SBF_ONE );
		break;

	case BRUSHBLEND_INVERT:
		mRenderSystem->_setSeparateSceneBlending( Ogre::SBF_ONE_MINUS_DEST_COLOUR, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA, Ogre::SBF_ONE, Ogre::SBF_ONE );
		break;

	case BRUSHBLEND_ALPHA:
		mRenderSystem->_setSeparateSceneBlending( Ogre::SBF_SOURCE_ALPHA, Ogre::SBF_ONE_MINUS_SOURCE_ALPHA, Ogre::SBF_ONE, Ogre::SBF_ONE );
		break;
	}
}

//--------------------------------
void OgreBrush::setFilterMode( BrushFilterMode vMode )
{
	switch ( vMode )
	{
	case BRUSHFILTER_NEAREST:
		mRenderSystem->_setTextureUnitFiltering( 0, Ogre::FO_POINT, Ogre::FO_POINT, Ogre::FO_POINT );
		break;

	case BRUSHFILTER_LINEAR:
		mRenderSystem->_setTextureUnitFiltering( 0, Ogre::FO_LINEAR, Ogre::FO_LINEAR, Ogre::FO_POINT );
		break;
	}
}

//--------------------------------
void OgreBrush::drawLine( const Mocha::Vector2& vPoint1, const Mocha::Vector2& vPoint2 )
{
	// Map points to screen space

	Mocha::Vector3 pointA;
	getFinalPoint( vPoint1, pointA );

	Mocha::Vector3 pointB;
	getFinalPoint( vPoint2, pointB );

	// Lock buffer

	GuiVertex* data = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );

	// Write line

	data[0].pos = pointA;
	data[0].color = mColor;
	data[0].uv = Mocha::Vector2( );

	data[1].pos = pointB;
	data[1].color = mColor;
	data[1].uv = Mocha::Vector2( );
	
	// All done!

	mBuffer->unlock( );

	// Render!

	mRenderOp.vertexData->vertexCount = 2;
	mRenderOp.operationType = Ogre::RenderOperation::OT_LINE_LIST;

	mRenderSystem->_render( mRenderOp );

	// Reset operation type

	mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_LIST;
}

//--------------------------------
void OgreBrush::drawLineRectangle( const Mocha::Rectangle& vRect )
{
	// Draw a set of lines for the rectangle

	beginLines( );

	addLine( Mocha::Vector2( vRect.left+1, vRect.top+1 ),
			 Mocha::Vector2( vRect.right, vRect.top+1 ) );

	addLine( Mocha::Vector2( vRect.left+0, vRect.top+0 ),
			 Mocha::Vector2( vRect.left+1, vRect.bottom ) );

	addLine( Mocha::Vector2( vRect.left+1, vRect.bottom ),
			 Mocha::Vector2( vRect.right, vRect.bottom ) );

	addLine( Mocha::Vector2( vRect.right, vRect.top+1 ),
			 Mocha::Vector2( vRect.right, vRect.bottom ) );

	endLines( );
}

//--------------------------------
void OgreBrush::beginLines( )
{
	if ( mBatchPointer == 0 )
	{
		mBatchPointer = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::addLine( const Mocha::Vector2& vPoint1, const Mocha::Vector2& vPoint2 )
{
	// Map points to screen space

	Mocha::Vector3 pointA;
	getFinalPoint( vPoint1, pointA );

	Mocha::Vector3 pointB;
	getFinalPoint( vPoint2, pointB );

	// Write line

	mBatchPointer[0].pos = pointA;
	mBatchPointer[0].color = mColor;
	mBatchPointer[0].uv = Mocha::Vector2( );

	mBatchPointer[1].pos = pointB;
	mBatchPointer[1].color = mColor;
	mBatchPointer[1].uv = Mocha::Vector2( );

	// Advance glyph pointer

	mBatchPointer += 2;

	// Increase glyph count

	mBatchCount += 1;

	// See if we're over the limit...

	if ( mBatchCount >= (VERTEX_COUNT/2) )
	{
		// First unlock the buffer

		mBuffer->unlock( );

		// Render whats in the buffer

		renderLines( );

		// Re-lock buffer

		mBatchPointer = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
	
		// Reset glyph count

		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::endLines( )
{
	if ( mBatchPointer != 0 )
	{
		mBuffer->unlock( );

		if ( mBatchCount > 0 )
			renderLines( );

		mBatchPointer = 0;
		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::beginTriangles( )
{
	if ( mBatchPointer == 0 )
	{
		mBatchPointer = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::addTriangleVertex( const Mocha::Vector2& vPoint, const Mocha::Vector2& vUV, bool vScreenSpace )
{
	// Map point to screen space if necessary

	Mocha::Vector3 point;
	if ( vScreenSpace == true )
	{
		point.x = vPoint.x;
		point.y = vPoint.y;
	}
	else
		getFinalPoint( vPoint, point );

	// Write vertex

	mBatchPointer->pos = point;
	mBatchPointer->color = mColor;
	mBatchPointer->uv = vUV;

	// Advance glyph pointer

	mBatchPointer++;

	// Increase glyph count

	mBatchCount++;

	// See if we're over the limit...

	if ( mBatchCount >= VERTEX_COUNT )
	{
		// First unlock the buffer

		mBuffer->unlock( );

		// Render whats in the buffer

		renderTriangles( );

		// Re-lock buffer

		mBatchPointer = (GuiVertex*)mBuffer->lock( Ogre::HardwareBuffer::HBL_DISCARD );
	
		// Reset glyph count

		mBatchCount = 0;
	}
}

//--------------------------------
void OgreBrush::endTriangles( )
{
	if ( mBatchPointer != 0 )
	{
		mBuffer->unlock( );

		if ( mBatchCount > 0 )
			renderTriangles( );

		mBatchPointer = 0;
		mBatchCount = 0;
	}
}

}
