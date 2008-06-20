PROJECT(OgreSample)

FIND_PACKAGE(OIS REQUIRED)

#Projects source files
SET(OGRESAMPLE_SRC_FILES
	Source/Application.cpp
	Source/Main.cpp
)

#Set include directories
INCLUDE_DIRECTORIES(${OIS_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Include)

#Create and link sample executable
ADD_EXECUTABLE(RBGuiOgreSample ${OGRESAMPLE_SRC_FILES})
TARGET_LINK_LIBRARIES(RBGuiOgreSample RBGui RBGuiOgreSupport ${OIS_LIBRARIES} ${OGRE_LIBRARIES})
SET_TARGET_PROPERTIES(RBGuiOgreSample PROPERTIES COMPILE_FLAGS "-DPOSIX") #SHOULDN'T BE NEEDED!

#Install executable, media, set paths and then install config files
INSTALL(TARGETS RBGuiOgreSample RUNTIME DESTINATION share/RBGuiOgreSample/bin)
INSTALL(DIRECTORY bin/Media DESTINATION share/RBGuiOgreSample)
CONFIGURE_FILE(bin/release/ogreplugins.cfg.linux ${CMAKE_CURRENT_BINARY_DIR}/ogreplugins.cfg)
INSTALL(FILES
	${CMAKE_CURRENT_BINARY_DIR}/ogreplugins.cfg
	bin/release/resources.cfg
	DESTINATION share/RBGuiOgreSample/bin
)
