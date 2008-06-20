
#ifndef GUI_DIRECTORYLISTWIDGET_H
#define GUI_DIRECTORYLISTWIDGET_H

#include "RBGui/Widgets/ListWidget.h"

namespace RBGui
{

class GUI_EXPORT DirectoryListWidget : public ListWidget
{
private:
	Mocha::String mPath;

	Mocha::String mFilter;

	bool mDirectoryOnly;

	bool mShowExtensions;

	bool matchFilter( const Mocha::StringList& vTokens, const Mocha::String& vName );

protected:
	virtual void onDoubleClick( MouseButtonID vID, const Mocha::Vector2& vPoint );

	virtual void onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint );

public:
	DirectoryListWidget( GuiManager* vManager );

	virtual ~DirectoryListWidget( );

	Mocha::String getFullPath( const Mocha::String& vPath );

	void setShowExtensions( bool vWhich );

	bool getShowExtensions( );

	void setDirectoryOnly( bool vWhich );

	bool getDirectoryOnly( );

	void setFilter( const Mocha::String& vFilter );

	const Mocha::String& getFilter( );

	void setPath( const Mocha::String& vPath );

	const Mocha::String& getPath( );

	void listDirectory( );

	static Widget* factory( GuiManager* vManager );
};

}

#endif
