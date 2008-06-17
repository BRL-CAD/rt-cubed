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

# Get the executable pkg-config path, if exists
find_program(PKGCONFIG_EXECUTABLE NAMES pkg-config PATHS /usr/local/bin /usr/bin)


# Macro to check whether the package exist, with at least the given
# version
macro(PKGCONFIG_ATLEAST _package _atleast_version _found)
  # reset the variables at the beginning
  remove(${_return_var})

  # if pkg-config has been found
  if(PKGCONFIG_EXECUTABLE)
    exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_package} --atleast-version=${_atleast_version}
      RETURN_VALUE _exitCode OUTPUT_VARIABLE _pkgconfigDevNull )
    if(NOT _exitCode)
      set(${_found} 1)
    endif(NOT _exitCode)
  endif(PKGCONFIG_EXECUTABLE)
endmacro(PKGCONFIG_ATLEAST _package _atleast_version _return)


# Macro to simplify calls of pkg-config: it accepts arguments freely,
# and returns the output and the exit code
macro(PKGCONFIG_WRAPPER _args _output _exitCode)
  # reset the variables at the beginning
  remove(${_output})

  # if pkg-config has been found
  if(PKGCONFIG_EXECUTABLE)
    exec_program(${PKGCONFIG_EXECUTABLE} ARGS ${_args} RETURN_VALUE ${_exitCode} OUTPUT_VARIABLE ${_output} )
  endif(PKGCONFIG_EXECUTABLE)
endmacro(PKGCONFIG_WRAPPER _args _output _exitCode)


# Macro to get all useful variables at once for a package.  Better to
# get one kind of flags (CFLAGS, etc) for multiple packages (with the
# wrapper above): the output is merged so the final result is cleaner
# and optimized.
#
# !!!!!!!!!!!!!!!!!!!!!!! DEPRECATED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# !!!!!!!!!! USEFUL FOR IMPLEMENTING FUTURE MACROS, MAYBE !!!!!!!!!!
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
