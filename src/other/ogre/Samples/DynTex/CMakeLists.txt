#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure DynTex demo build

set(SOURCE_FILES src/DynTex.cpp)

add_executable(Demo_DynTex WIN32 ${SOURCE_FILES} ${RESOURCE_FILES})

target_link_libraries(Demo_DynTex ${OGRE_LIBRARIES} ${OGRE_PLUGIN_LIBRARIES} ${OIS_LIBRARIES})
ogre_config_sample(Demo_DynTex)

if (SAMPLE_DEPENDENCIES)
  add_dependencies(Demo_DynTex ${SAMPLE_DEPENDENCIES})
endif ()
