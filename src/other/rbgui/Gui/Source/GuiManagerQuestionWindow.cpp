
#include "Mocha/StringTools.h"

#include "RBGui/GuiManager.h"

#include "RBGui/Widgets/TextWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"

namespace RBGui
{

//--------------------------------
static void buttonPressed( GuiElement& vElement, const Mocha::ValueList& vData )
{
	// Get button

	ButtonWidget& button = static_cast<ButtonWidget&>( vElement );

	// Get window

	Window* window = button.getWindow( );

	// Get callback object

	GuiCallback* cb = static_cast<GuiCallback*>( window->getObject( ) );

	// Do callback

	Mocha::ValueList v;
	v.push_back( button.getName( ) );

	cb->onGuiEvent( vElement, v );

	// Close window

	window->close( );
}

//--------------------------------
Window* GuiManager::createQuestionWindow( const Mocha::String& vTitle, const Mocha::String& vText, const Mocha::String& vButtons, GuiCallback* vCallback, const Mocha::Vector2& vSize )
{
	const float buttonwidth = 100.0f;
	const float buttonheight = 30.0f;

	// Create the window

	Window* window = createWindow( );
	window->setObject( vCallback );
	window->setResizeable( false );
	window->setCloseable( false );
	window->setModal( true );
	window->setText( vTitle );

	// Setup text label

	TextWidget* text = static_cast<TextWidget*>( window->createWidget( "Text" ) );
	text->setHorizontalTextAlignment( TEXTALIGN_CENTER );
	text->setVerticalTextAlignment( TEXTALIGN_CENTER );
	text->setName( "Text" );
	text->setText( vText );
	text->setWrap( true );

	// Get size of text region

	Font* f = text->getRenderFont( );
	if ( f )
	{
		Mocha::Vector2 size;
		f->getTextSize( vText, size );

		size = Mocha::Vector2( Mocha::max( vSize.x, size.x ), Mocha::max( vSize.y, size.y ) );
		window->setSize( size );
	}
	else
		window->setSize( vSize );

	// Center window

	window->centerX( );
	window->centerY( );

	const Mocha::Rectangle& client = window->getClientRectangle( );

	// Set text rectangle

	text->setRectangle( 0.0f, 0.0f, client.getWidth( ), client.getHeight( ) - buttonheight );

	// Get the list of buttons names

	Mocha::StringList tokens = Mocha::SplitString( vButtons, "," );
	const size_t count = tokens.size( );

	const float xpadding = 5.0f;
	const float ypadding = 5.0f;

	const float choiceWidth = (client.getWidth( ) - (xpadding*(count+1))) / count;
	const float choiceHeight = buttonheight;

	float xpos = xpadding;

	Mocha::StringList::const_iterator it;
	for ( it = tokens.begin( ); it != tokens.end( ); it++ )
	{
		const Mocha::String& text = (*it);

		// Setup the button

		ButtonWidget* button = static_cast<ButtonWidget*>( window->createWidget( "Button" ) );
		button->setRectangle( xpos, client.getHeight( ) - (choiceHeight+ypadding), choiceWidth, choiceHeight );
		//button->setRectangle( (r.getWidth( )/2) - (buttonwidth/2), r.getHeight( )-(buttonheight+ypadding), buttonwidth, buttonheight );
		button->setCallback( new StaticFunctionGuiCallback( &buttonPressed ) );
		button->setName( text );
		button->setText( text );

		// Add spacing between buttons

		xpos += choiceWidth + xpadding;
	}

	// All done!

	return window;
}

}
