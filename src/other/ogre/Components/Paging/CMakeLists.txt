#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

############################################################
# Paging optional component
############################################################

PROJECT(OgrePaging)

# define header and source files for the library
set (HEADER_FILES
	include/OgreGrid2DPageStrategy.h
	include/OgrePage.h
	include/OgrePageConnection.h
	include/OgrePageContent.h
	include/OgrePageContentCollection.h
	include/OgrePageContentCollectionFactory.h
	include/OgrePageContentFactory.h
	include/OgrePagedWorld.h
	include/OgrePagedWorldSection.h
	include/OgrePageFileFormats.h
	include/OgrePageLoadableUnit.h
	include/OgrePageManager.h
	include/OgrePageRequestQueue.h
	include/OgrePageStrategy.h
	include/OgrePaging.h
	include/OgrePagingPrerequisites.h
	include/OgreSimplePageContentCollection.h
)

set (SOURCE_FILES
	src/OgreGrid2DPageStrategy.cpp
	src/OgrePage.cpp
	src/OgrePageConnection.cpp
	src/OgrePageContent.cpp
	src/OgrePageContentCollection.cpp
	src/OgrePageContentCollectionFactory.cpp
	src/OgrePageContentFactory.cpp
	src/OgrePagedWorld.cpp
	src/OgrePagedWorldSection.cpp
	src/OgrePageLoadableUnit.cpp
	src/OgrePageManager.cpp
	src/OgrePageRequestQueue.cpp
	src/OgrePageStrategy.cpp
	src/OgreSimplePageContentCollection.cpp
)


# Add needed definitions 
add_definitions(-DOGRE_PAGING_EXPORTS -D_MT -D_USRDLL)

# include headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/OgreMain/include)


# setup target
add_library(OgrePaging ${OGRE_LIB_TYPE} ${HEADER_FILES} ${SOURCE_FILES} ${PLATFORM_HEADER_FILES} ${PLATFORM_SOURCE_FILES})
set_target_properties(OgrePaging PROPERTIES VERSION ${OGRE_VERSION} SOVERSION ${OGRE_VERSION_MAJOR})
target_link_libraries(OgrePaging OgreMain)
if (OGRE_CONFIG_THREADS)
  target_link_libraries(OgrePaging ${Boost_LIBRARIES})
endif ()

# install 
ogre_config_lib(OgrePaging)
install(FILES ${HEADER_FILES}
  DESTINATION include/OGRE/Paging
)

