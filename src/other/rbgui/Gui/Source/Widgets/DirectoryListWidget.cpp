
#include "Mocha/StringTools.h"

#include "RBGui/PlatformManager.h"
#include "RBGui/Core.h"

#include "RBGui/Widgets/DirectoryListWidget.h"

namespace RBGui
{

//--------------------------------
DirectoryListWidget::DirectoryListWidget( GuiManager* vManager )
: ListWidget( vManager ), mDirectoryOnly( false ), mShowExtensions( true ), mPath( "." )
{
	setDrawIcons( true );
	listDirectory( );
}

//--------------------------------
DirectoryListWidget::~DirectoryListWidget( )
{
	// ...
}

//--------------------------------
bool DirectoryListWidget::matchFilter( const Mocha::StringList& vTokens, const Mocha::String& vName )
{
	if ( mFilter == "" )
		return true;

	Mocha::String ext = Mocha::LowerString( Mocha::GetStringFileExtension( vName ) );
	
	Mocha::StringList::const_iterator it;
	for ( it = vTokens.begin( ); it != vTokens.end( ); it++ )
	{
		Mocha::String filter = Mocha::LowerString( (*it) );
		if ( (filter == ext) || (filter == "*") )
			return true;
	}

	return false;
}

//--------------------------------
void DirectoryListWidget::onDoubleClick( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	int selected = getSelected( );
	if ( selected < 0 )
		return;

	int type = (int)getEntryData( selected );
	if ( type == DIRENTRY_DIRECTORY )
	{
		// Switch directories...

		setPath( getEntryTextData( selected ) );

		// Call path changed signal

		Mocha::ValueList v;
		v.push_back( mPath );

		doCallback( v, "onDirectoryChanged" );
	}
	else
	{
		// Call file selected signal

		Mocha::ValueList v;
		v.push_back( getEntryText( selected ) );
		v.push_back( getEntryTextData( selected ) );

		doCallback( v, "onFileSelected" );
	}
}

//--------------------------------
void DirectoryListWidget::onMousePressed( MouseButtonID vID, const Mocha::Vector2& vPoint )
{
	// Do base list widget mouse handling

	int picked = pickEntry( vPoint );

	// See if we selected a file entry

	if ( picked < 0 )
		return;

	int type = (int)getEntryData( picked );
	if ( type == DIRENTRY_FILE )
	{
		Mocha::ValueList v;
		v.push_back( getEntryText( picked ) );
		v.push_back( getEntryTextData( picked ) );

		doCallback( v, "onFileClicked" );
	}
}

//--------------------------------
void DirectoryListWidget::listDirectory( )
{
	try
	{
		// Reset list widget

		clearEntries( );

		// Get current filter token list

		Mocha::StringList tokens = Mocha::SplitString( mFilter, "," );

		// Get directory listing

		PlatformManager& manager = Core::Get( ).getPlatformManager( );

		DirectoryEntryList entries;
		if ( manager.getDirectoryListing( mPath, entries, true, true ) == false )
		{
			// Directory listing failed. Use listing of root directory instead

			if ( manager.getDirectoryListing( ".", entries, true, true ) )
				mPath = ".";
			else
				return;
		}

		// Add parent entry

		if ( mPath != "." )
		{
			Mocha::String first;
			Mocha::String second;

			Mocha::SplitPath( mPath, first, second );

			if ( first == "" )
				first = ".";

			addEntry( "[parent]", (void*)DIRENTRY_DIRECTORY, first, "ParentIcon" );
		}

		// Add entries to list

		DirectoryEntryList::const_iterator it;
		for ( it = entries.begin( ); it != entries.end( ); it++ )
		{
			const DirectoryEntry& entry = (*it);
			
			// Make sure the entry matches the filter

			Mocha::String icon;
			if ( entry.type == DIRENTRY_FILE )
			{
				if ( (mDirectoryOnly == false) && matchFilter( tokens, entry.name ) )
				{
					if ( mShowExtensions )
						addEntry( entry.name, (void*)entry.type, Mocha::CombinePath( mPath, entry.name ), "FileIcon" );
					else
						addEntry( Mocha::GetStringFileName( entry.name ), (void*)entry.type, Mocha::CombinePath( mPath, entry.name ), "FileIcon" );
				}
			}
			else
				addEntry( entry.name, (void*)entry.type, Mocha::CombinePath( mPath, entry.name ), "FolderIcon" );
		}

		// Reset scroll value

		setScroll( 0.0f );
	}
	catch ( Mocha::Exception& )
	{
		//Compositor::Get( ).createMessageBox( "Error", e.getMessage( ) );
	}
}

//--------------------------------
Mocha::String DirectoryListWidget::getFullPath( const Mocha::String& vPath )
{
	return Mocha::CombinePath( mPath, vPath );
}

//--------------------------------
void DirectoryListWidget::setShowExtensions( bool vWhich )
{
	mShowExtensions = vWhich;
	listDirectory( );
}

//--------------------------------
bool DirectoryListWidget::getShowExtensions( )
{
	return mShowExtensions;
}

//--------------------------------
void DirectoryListWidget::setDirectoryOnly( bool vWhich )
{
	mDirectoryOnly = vWhich;
	listDirectory( );
}

//--------------------------------
bool DirectoryListWidget::getDirectoryOnly( )
{
	return mDirectoryOnly;
}

//--------------------------------
void DirectoryListWidget::setFilter( const Mocha::String& vFilter )
{
	mFilter = vFilter;
	listDirectory( );
}

//--------------------------------
const Mocha::String& DirectoryListWidget::getFilter( )
{
	return mFilter;
}

//--------------------------------
void DirectoryListWidget::setPath( const Mocha::String& vPath )
{
	mPath = vPath;
	listDirectory( );
}

//--------------------------------
const Mocha::String& DirectoryListWidget::getPath( )
{
	return mPath;
}

//--------------------------------
Widget* DirectoryListWidget::factory( GuiManager* vManager )
{
	return new DirectoryListWidget( vManager );
}

}
