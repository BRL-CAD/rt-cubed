# Originally from:
#	https://wiki-flowvr.imag.fr/browser/trunk/flowvr-render/cmake/UsePkgConfig.cmake?rev=1793&format=raw
#
# - pkg-config module for CMake
#
# Defines the following macros:
#
# PKGCONFIG(package includedir libdir linkflags cflags)
#
# Calling PKGCONFIG will fill the desired information into the 4 given arguments,
# e.g. PKGCONFIG(libart-2.0 LIBART_INCLUDE_DIR LIBART_LINK_DIR LIBART_LINK_FLAGS LIBART_CFLAGS)
# if pkg-config was NOT found or the specified software package doesn't exist, the
# variable will be empty when the function returns, otherwise they will contain the respective information
#

find_program(PKGCONFIG_EXECUTABLE NAMES pkg-config PATHS /usr/local/bin /usr/bin)


macro(PKGCONFIG_ATLEAST _package _atleast_version _return_var)
  # reset the variables at the beginning
  remove(${_return_var})

  # if pkg-config has been found
  if(PKGCONFIG_EXECUTABLE)
    # check --atleast-version
    exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --atleast-version=${_atleast_version} RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _pkgconfigDevNull )
    if(NOT _return_VALUE)
      set(${_return_var} 1)
    endif(NOT _return_VALUE)
  endif(PKGCONFIG_EXECUTABLE)
endmacro(PKGCONFIG_ATLEAST _return_var _package _atleast_version)


macro(PKGCONFIG_WRAPPER _args _output)
  # reset the variables at the beginning
  remove(${_output})

  # if pkg-config has been found
  if(PKGCONFIG_EXECUTABLE)
    exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_args} RETURN_VALUE _return_VALUE OUTPUT_VARIABLE ${_output} )
  endif(PKGCONFIG_EXECUTABLE)
endmacro(PKGCONFIG_WRAPPER _package _args _output)


macro(PKGCONFIG _package _atleast_version _include_DIR _link_DIR _link_FLAGS _cflags)
  # reset the variables at the beginning
  remove(${_package}_FOUND)
  set(${_include_DIR})
  set(${_link_DIR})
  set(${_link_FLAGS})
  set(${_cflags})

  # if pkg-config has been found
  if(PKGCONFIG_EXECUTABLE)
    # check --atleast-version
    exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --atleast-version=${_atleast_version} RETURN_VALUE _return_VALUE OUTPUT_VARIABLE _pkgconfigDevNull )
    if(NOT _return_VALUE)
      set(${_package}_FOUND 1)

      # if exists, get the variables
      exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --variable=includedir OUTPUT_VARIABLE ${_include_DIR} )
      exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --variable=libdir OUTPUT_VARIABLE ${_link_DIR} )
      exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --libs OUTPUT_VARIABLE ${_link_FLAGS} )
      exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --cflags OUTPUT_VARIABLE ${_cflags} )
    endif(NOT _return_VALUE)
  endif(PKGCONFIG_EXECUTABLE)
endmacro(PKGCONFIG _package _atleast_version _include_DIR _link_DIR _link_FLAGS _cflags)



mark_as_advanced(PKGCONFIG_EXECUTABLE)
