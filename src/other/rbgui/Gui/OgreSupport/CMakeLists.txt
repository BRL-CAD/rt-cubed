PROJECT(OgreSupport)

#Projects source files
SET(OGRESUPPORT_SRC_FILES
	Source/OgreBrush.cpp
	Source/OgreRenderQueueListener.cpp
	Source/OgreResourceManager.cpp
	Source/OgreTexture.cpp
	Source/OgreTextureManager.cpp
)

#Create the library
ADD_LIBRARY(RBGuiOgreSupport SHARED ${OGRESUPPORT_SRC_FILES}) #libRBGuiOgreSupport.so on unix, RBGuiOgreSupport.dll on Windows
#TARGET_LINK_LIBRARIES(RBGuiOgreSupport ${Mocha_LIBRARIES} ${FREETYPE_LIBRARIES} ${OGRE_LIBRARIES})
SET_TARGET_PROPERTIES(RBGuiOgreSupport PROPERTIES VERSION 0.1.3)

#Install the library
INSTALL(TARGETS RBGuiOgreSupport
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
