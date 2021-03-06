#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# Configure DeferredShading demo build

set(HEADER_FILES 
  include/AmbientLight.h
  include/DeferredShading.h
  include/GeomUtils.h
  include/LightMaterialGenerator.h
  include/MaterialGenerator.h
  include/MLight.h
)
set(SOURCE_FILES 
  src/AmbientLight.cpp
  src/DeferredShading.cpp
  src/DeferredShadingDemo.cpp
  src/GeomUtils.cpp
  src/LightMaterialGenerator.cpp
  src/MaterialGenerator.cpp
  src/MLight.cpp
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_executable(Demo_DeferredShading ${HEADER_FILES} ${SOURCE_FILES} ${RESOURCE_FILES})

target_link_libraries(Demo_DeferredShading ${OGRE_LIBRARIES} ${OGRE_PLUGIN_LIBRARIES} ${OIS_LIBRARIES})
ogre_config_sample(Demo_DeferredShading)

if (SAMPLE_DEPENDENCIES)
  add_dependencies(Demo_DeferredShading ${SAMPLE_DEPENDENCIES})
endif ()
