MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##             Configuring rbgui              ##")
MESSAGE(STATUS "################################################\n")

cmake_minimum_required(VERSION 2.2)
PROJECT(RBGUI)

#Find the requirements
MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

#SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
#FIND_PACKAGE(Freetype REQUIRED)
#FIND_PACKAGE(Mocha REQUIRED)
#FIND_PACKAGE(OGRE REQUIRED)


#Set the include search directories
INCLUDE_DIRECTORIES(${Mocha_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR} ${OGRE_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Include)

MESSAGE(STATUS "Include Paths: ${Mocha_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIR} ${OGRE_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Include")

ADD_SUBDIRECTORY(OgreSupport) #Build the OgreSupport module
ADD_SUBDIRECTORY(OgreSample) #Build the Ogre example

#Projects source files
SET(SRC_FILES
	Source/Window.cpp
	Source/Widget.cpp
	Source/ThemeManager.cpp
	Source/SimpleWindowFader.cpp
	Source/GuiManagerQuestionWindow.cpp
	Source/GuiManagerFileSelectWindow.cpp
	Source/FontManager.cpp
	Source/GuiManager.cpp
	Source/Win32CursorManager.cpp
	Source/GuiElement.cpp
	Source/BrushCursorManager.cpp
	Source/Win32PlatformManager.cpp
	Source/PosixPlatformManager.cpp
	Source/MacOSPlatformManager.cpp
	Source/GuiManagerMessageBox.cpp
	Source/Core.cpp
	Source/WobbleWindowAnimator.cpp
	Source/WindowFader.cpp
	Source/WindowAnimator.cpp
	Source/Theme.cpp
	Source/Font.cpp
	Source/Border.cpp
	Source/Widgets/AttributeEditWidget.cpp
	Source/Widgets/AttributeWidget.cpp
	Source/Widgets/AttributeWidgets
	Source/Widgets/ButtonWidget.cpp
	Source/Widgets/CheckWidget.cpp
	Source/Widgets/ColorRangeWidget.cpp
	Source/Widgets/ColorSelectWidget.cpp
	Source/Widgets/ContainerWidget.cpp
	Source/Widgets/DirectoryListWidget.cpp
	Source/Widgets/DropListWidget.cpp
	Source/Widgets/DropSplineWidget.cpp
	Source/Widgets/EvaluatorWidget.cpp
	Source/Widgets/GroupWidget.cpp
	Source/Widgets/HSVWidget.cpp
	Source/Widgets/ImageWidget.cpp
	Source/Widgets/ListWidget.cpp
	Source/Widgets/MenuEntryWidget.cpp
	Source/Widgets/MenuWidget.cpp
	Source/Widgets/OptionWidget.cpp
	Source/Widgets/ProgressWidget.cpp
	Source/Widgets/RectangleWidget.cpp
	Source/Widgets/ScrollWidget.cpp
	Source/Widgets/SplineWidget.cpp
	Source/Widgets/TextEntryWidget.cpp
	Source/Widgets/TextWidget.cpp
	Source/Widgets/AttributeWidgets/BoolAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/ButtonAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/ColorAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/EvaluatorAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/FileAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/FloatAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/IntAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/ListAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/SliderAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/SplineAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/TextAttributeWidget.cpp
	Source/Widgets/AttributeWidgets/Vector2AttributeWidget.cpp
	Source/Widgets/AttributeWidgets/Vector3AttributeWidget.cpp
)

#Create and link the RBGui library
ADD_LIBRARY(RBGui SHARED ${SRC_FILES}) #libRBGui.so on unix, RBGui.dll on Windows
TARGET_LINK_LIBRARIES(RBGui ${Mocha_LIBRARIES} ${FREETYPE_LIBRARIES} ${OGRE_LIBRARIES})
SET_TARGET_PROPERTIES(RBGui PROPERTIES VERSION 0.1.3)
SET_TARGET_PROPERTIES(RBGui PROPERTIES COMPILE_FLAGS "-DPOSIX") #SHOULDN'T BE NEEDED!

# pkg-config file
file(WRITE ${PROJECT_BINARY_DIR}/RBGui.pc "prefix=${CMAKE_INSTALL_PREFIX}
exec_prefix=\${prefix}
libdir=\${exec_prefix}/lib
includedir=\${prefix}/include

Name: RBGui
Description: Right Brain Games GUI
Version: 0.1.3
Libs: -L\${libdir} -lRBGui -lRBGuiOgreSupport
Cflags: -I\${includedir} -I\${includedir}/RBGui
")
set(PKGCONFIG_FILES ${PROJECT_BINARY_DIR}/RBGui.pc)


#Install the library and headers
INSTALL(TARGETS RBGui
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
INSTALL(DIRECTORY Include/RBGui DESTINATION include PATTERN ".svn" EXCLUDE)
install(FILES ${PKGCONFIG_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig/)
