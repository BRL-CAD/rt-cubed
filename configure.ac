dnl rt^3
dnl Copyright (c) 2004 Christopher Sean Morrison
dnl $Id$
dnl
dnl This program is free software; you can redistribute it and/or
dnl modify it under the terms of the appropriate license described in
dnl the file named COPYING that should have accompanied this file.
dnl
dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY; without even the implied warranty of
dnl MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
dnl
dnl ******************************************************************
dnl ***                  rt^3's configure.ac                       ***
dnl ******************************************************************
dnl
dnl Herein lies a venerable GNU Build System configure template for
dnl this software package.  As best is reasonably possible, proper
dnl ordering and separation of tests and settings should be maintained
dnl per the recommended standard layout.  The tests should be added to
dnl the rather clearly labeled sections below so that they are as
dnl follows:
dnl
dnl      0) information on the package
dnl	 1) check command-line arguments
dnl	 2) check programs
dnl	 3) check libraries
dnl	 4) check headers
dnl	 5) check types/structures
dnl      6) check compiler characteristics
dnl	 7) check functions
dnl	 8) check system services
dnl	 9) output a summary
dnl
dnl Any useful build arguments should be added to the output summary
dnl at the end.  Although it may be possible to check for certain
dnl features of command line arguments near the top, related tests
dnl should be delayed and placed into the appropriate test section.
dnl 
dnl Let the finicky organized chaos begin.
dnl

AC_PREREQ(2.57)

dnl only needs major.minor version
AC_INIT(rt^3, 0.1, [brlcad@mac.com], rt3)
AC_REVISION($Revision$)
AC_CONFIG_AUX_DIR(misc)


dnl ***************************
dnl *** package information ***
dnl ***************************

MAJOR_VERSION=0
MINOR_VERSION=1
PATCH_VERSION=0
RT3_VERSION="$MAJOR_VERSION.$MINOR_VERSION.$PATCH_VERSION"
AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(PATCH_VERSION)
AC_SUBST(RT3_VERSION)

CONFIG_DATE=`date +%Y%m%d`

# print out the title with a pretty box computed to wrap around
title="Configuring rt^3 Version $RT3_VERSION, Build $CONFIG_DATE"
length="`echo x${title}x | wc -c`"
separator=""
while test $length -gt 1 ; do
      separator="${separator}*"
      length="`expr $length - 1`"
done
echo "***${separator}***"
echo "*** ${title} ***"
echo "***${separator}***"

# necessary for proper file creation on nfs volumes
umask 022

AC_CANONICAL_HOST
AC_CANONICAL_TARGET

CONFIG_TIME="`date '+%H %M %S'`"
CONFIG_USER="`whoami`"
CONFIG_HOST="$host_os"
AC_SUBST(CONFIG_DATE)
AC_SUBST(CONFIG_TIME)
AC_SUBST(CONFIG_USER)
AC_SUBST(CONFIG_HOST)

AC_DEFINE_UNQUOTED(RT3_VERSION, $RT3_VERSION, [Package version])
AC_DEFINE_UNQUOTED(RT3_CONFIG_DATE, $CONFIG_DATE, [Configuration date])
AC_DEFINE_UNQUOTED(RT3_CONFIG_TIME, $CONFIG_TIME, [Configuration time])
AC_DEFINE_UNQUOTED(RT3_CONFIG_USER, $CONFIG_USER, [Configuring user])
AC_DEFINE_UNQUOTED(RT3_CONFIG_HOST, $CONFIG_HOST, [Configuration system])

# am_init_automake performs a ac_prog_install check so need to handle
# problematic /usr/brl/bin/install on irix
if test "x$build_vendor" = "xsgi" ; then
	PATH="`echo $PATH | sed 's/\/brl\/bin/bin/g'`"
fi

AC_CONFIG_SRCDIR([src/Makefile.am])

AC_MSG_CHECKING([whether dependency tracking should be enabled])
if test -d $srcdir/CVS ; then
	AC_MSG_RESULT(it should)
	AM_INIT_AUTOMAKE
else
	AC_MSG_RESULT(it should not)
	AM_INIT_AUTOMAKE([no-dependencies])
fi
AM_CONFIG_HEADER([include/config.h])

# a secondary automated automake may blow away COPYING & INSTALL , so restore them
for file in COPYING INSTALL ; do
	if test -f "$srcdir/misc/${file}.backup" ; then
		AC_MSG_CHECKING([whether ${file} needs to be restored])
		content="`cat $srcdir/${file}`"
		backup="`cat $srcdir/misc/${file}.backup`"
		if test "x$content" = "x$backup" ; then
			AC_MSG_RESULT(no)
		else
			AC_MSG_RESULT(yes)
			cp -pr $srcdir/misc/${file}.backup $srcdir/${file}
		fi
	fi
done

# automatically enable and load our configure cache file if available
AC_MSG_CHECKING([whether a configure cache exists])
if test "x$cache_file" = "x/dev/null" ; then
	package_cache="config.cache.${host_os}.${ac_hostname}"
	CONFIG_CACHE=""
	if test -f "$package_cache"; then
		# if the configure script has been modified since
		# the last caching, assume it to be invalid.
		last_modified="`ls -Lt $package_cache configure`"
		case "x$last_modified" in
			xconfigure*)
				AC_MSG_RESULT([found but out of date])
				rm -f $package_cache
				;;
			*)
				AC_MSG_RESULT([found $package_cache])

				dnl go ahead and load our cache
				case $package_cache in
					[\\/]* | ?:[\\/]* )
						. $package_cache
						;;
					*)
						. ./$package_cache
						;;
				esac
		esac
	else
		AC_MSG_RESULT([not found])
	fi

	dnl if we are on sgi, bash may choke on sed syntax in the cache
	if test "x$host_os" != "xirix6.5" ; then
		AC_MSG_NOTICE([*** Automatically caching to $package_cache ***])
		>$package_cache
		cache_file="$package_cache"
		CONFIG_CACHE="$cache_file"
	else
		AC_MSG_NOTICE([Automatic caching is unavailable on IRIX])
	fi
	AC_SUBST(CONFIG_CACHE)
else
	AC_MSG_RESULT($cache_file)
fi


dnl ***************************
dnl *** Check for arguments ***
dnl ***************************

# Allow user to specify flags without relying on environment
AC_ARG_WITH(cflags, AC_HELP_STRING(--with-cflags,
		    [Specify additional flags to pass to the C compiler]) ,
	[
		if test "x$withval" != "xno" ; then
			CFLAGS="$CFLAGS $withval"
		fi
	]	
)
AC_ARG_WITH(cxxflags, AC_HELP_STRING(--with-cxxflags,
		    [Specify additional flags to pass to the C++ compiler]) ,
	[
		if test "x$withval" != "xno" ; then
			CXXFLAGS="$CXXFLAGS $withval"
		fi
	]	
)
AC_ARG_WITH(cppflags, AC_HELP_STRING(--with-cppflags,
		      [Specify additional flags to pass to C preprocessor]) ,
	[
		if test "x$withval" != "xno"; then
			CPPFLAGS="$CPPFLAGS $withval"
		fi
	]
)
AC_ARG_WITH(ldflags, AC_HELP_STRING(--with-ldflags,
		     [Specify additional flags to pass to linker]) ,
	[
		if test "x$withval" != "xno" ; then
			LDFLAGS="$LDFLAGS $withval"
		fi
	]	
)
AC_ARG_WITH(libs, AC_HELP_STRING(--with-libs,
		  [Specify additional libraries to link against]) ,
	[
		if test "x$withval" != "xno" ; then
			LIBS="$LIBS $withval"
		fi
	]	
)

# optimized
dnl optimized has aliases
use_optimized=no
AC_ARG_ENABLE(optimized, AC_HELP_STRING(--enable-optimized,
		[enable optimized compilation (default=no)]),
	[if test "x$enable_optimized" != "xno" ; then
		use_optimized=yes
	fi]
)

# warnings
dnl warnings has aliases
use_warnings=no
AC_ARG_ENABLE(warnings, AC_HELP_STRING(--enable-warnings,
		[enable verbose compilation warnings (default=no)]),
	[if test "x$enable_warnings" != "xno" ; then
		use_warnings=yes
	fi]
)

# debug
dnl debug has aliases
use_debug=yes
AC_ARG_ENABLE(debug, AC_HELP_STRING(--disable-debug,
		[disable debug symbols (default=no)]),
	[if test "x$disable_debug" != "xno" ; then
		use_debug=no
	fi]
)

# profiling
dnl profiling has aliases
use_profiling=no
AC_ARG_ENABLE(profiling, AC_HELP_STRING(--enable-profiling,
		[enable profiling (default=no)]),
	[if test "x$enable_profiling" != "xno" ; then
		use_profiling=yes
	fi]
)

# enable 64-bit builds
dnl has aliases
build_64bit=auto
AC_ARG_ENABLE(64bit-build, AC_HELP_STRING(--enable-64bit-build,
		[enable 64-bit compilation mode (default=auto)]),
	[if test "x$enableval" = "xno" ; then
		build_64bit=no
	elif test "x$enableval" = "xyes" ; then
		build_64bit=yes
	fi]
)

###
# argument aliases
# they need to go below here in order for --help to consolidate the
# blank line to exactly one line in the right place
###

# optimized alias
AC_ARG_ENABLE(optimization,,
	[if test "x$enable_optimization" != "xno" ; then
		use_optimized=yes
	fi]
)
AC_ARG_ENABLE(optimizations,,
	[if test "x$enable_optimizations" != "xno" ; then
		use_optimized=yes
	fi]
)
AC_MSG_CHECKING(whether to enable optimized compilation)
AC_MSG_RESULT($use_optimized)

# debug alias
AC_ARG_ENABLE(debugging,,
	[if test "x$disable_debug" != "xno" ; then
		use_debug=no
	fi]
)
AC_MSG_CHECKING(whether to disable debug mode compilation)
AC_MSG_RESULT($use_debug)

# profiling alias
AC_ARG_ENABLE(profile,,
	[if test "x$enable_profile" != "xno" ; then
		use_profiling=yes
	fi]
)
AC_ARG_ENABLE(profiled,,
	[if test "x$enable_profiled" != "xno" ; then
		use_profiling=yes
	fi]
)
AC_MSG_CHECKING(whether to enable profile mode compilation)
AC_MSG_RESULT($use_profiling)

# verbose warnings alias
AC_ARG_ENABLE(verbose-warnings,,
	[if test "x$enable_verbose_warnings" != "xno" ; then
		use_warnings=yes
	fi]
)
AC_ARG_ENABLE(warning,,
	[if test "x$enable_warning" != "xno" ; then
		use_warnings=yes
	fi]
)
AC_MSG_CHECKING(whether to enable verbose compilation warnings)
AC_MSG_RESULT($use_warnings)

# 64-bit compilation
AC_ARG_ENABLE(64bit,,
	[if test "x$enable_64bit" = "xno" ; then
		build_64bit=no
	elif test "x$enable_64bit" = "xyes" ; then
		build_64bit=yes
	fi]
)
AC_ARG_ENABLE(64-bit,,
	[if test "x$enable_64bit" = "xno" ; then
		build_64bit=no
	elif test "x$enable_64bit" = "xyes" ; then
		build_64bit=yes
	fi]
)
AC_ARG_ENABLE(64-bit-build,,
	[if test "x$enable_64bit" = "xno" ; then
		build_64bit=no
	elif test "x$enable_64bit" = "xyes" ; then
		build_64bit=yes
	fi]
)
AC_MSG_CHECKING(whether to compile in 64-bit mode)
AC_MSG_RESULT($build_64bit)


dnl **************************
dnl *** Check for programs ***
dnl **************************

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_CXXCPP
AC_PROG_MAKE_SET
AC_PROG_LN_S
AC_PROG_RANLIB
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_YACC
AM_PROG_LEX
AC_CHECK_PROG(ECHO, echo, echo)


dnl ***************************
dnl *** Check for libraries ***
dnl ***************************

AC_CHECK_LIB([c], [main])
AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([pthread], [main])
AC_CHECK_LIB([z], [main])


dnl *************************
dnl *** Check for headers ***
dnl *************************

AC_HEADER_STDC
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_CHECK_HEADER( bitset,,
		 AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
                 AC_MSG_ERROR( [[
Header <bitset> not found. This is probably caused by having an incomplete
C++ standard library implementation. Please upgrade to a compiler that is
ISO/IEC 14882 conformant.]]))
AC_CHECK_HEADERS( \
	algorithm \
	ctime \
	iostream \
	string \
	vector \
)
AC_LANG_RESTORE
AC_CHECK_HEADERS( \
	time.h \
)


dnl **********************************
dnl *** Check for types/structures ***
dnl **********************************

AC_HEADER_STAT
AC_C_CONST
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_ST_BLOCKS
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_CHECK_MEMBERS([struct stat.st_rdev])
AC_HEADER_TIME
AC_STRUCT_TM
AC_CHECK_TYPES(socklen_t)
# AC_CREATE_STDINT_H
AC_CHECK_TYPE(int8_t,, [AC_DEFINE_UNQUOTED(int8_t, signed char,	[Define to `signed char' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(int16_t,, [AC_DEFINE_UNQUOTED(int16_t, signed short, [Define to `signed short' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(int32_t,, [AC_DEFINE_UNQUOTED(int32_t, signed long, [Define to `signed long' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(int64_t,, [AC_DEFINE_UNQUOTED(int64_t, signed long long, [Define to `signed long long' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(uint8_t,, [AC_DEFINE_UNQUOTED(uint8_t, unsigned char, [Define to `unsigned char' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(uint16_t,, [AC_DEFINE_UNQUOTED(uint16_t, unsigned short, [Define to `unsigned short' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(uint32_t,, [AC_DEFINE_UNQUOTED(uint32_t, unsigned long, [Define to `unsigned long' if <sys/types.h> does not define.])])
AC_CHECK_TYPE(uint64_t,, [AC_DEFINE_UNQUOTED(uint64_t, unsigned long long, [Define to `unsigned long long' if <sys/types.h> does not define.])])


dnl ******************************************
dnl *** Check for compiler characteristics ***
dnl ******************************************

# manual sanity check
AC_MSG_CHECKING(compiler and flags for sanity)
AC_TRY_RUN([
#include <stdio.h>
int main(){exit(0);}
	],
	[	AC_MSG_RESULT(yes) ],
	[
		AC_MSG_RESULT(no)
		AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
		AC_MSG_ERROR([*** compiler cannot create working executables, check config.log ***])
	]
)


dnl ***************************
dnl *** Check for functions ***
dnl ***************************

AC_CHECK_FUNCS(\
	atexit \
)


dnl *********************************
dnl *** Check for system services ***
dnl *********************************


dnl ***********************
dnl *** Configure files ***
dnl ***********************

AC_CONFIG_FILES([Makefile
		 include/Makefile
		 include/Geometry/Makefile
		 include/Image/Makefile
		 include/Utility/Makefile
		 include/Raytrace/Makefile
		 src/Makefile
		 src/date/Makefile
		 src/libGeometry/Makefile
		 src/libImage/Makefile
		 src/libNetwork/Makefile
		 src/libNumeric/Makefile
		 src/libRaytrace/Makefile
		 src/libUtility/Makefile
		 src/rt^3/Makefile
		 src/rt^3d/Makefile
		 src/rt^3dbd/Makefile
		 src/scratch/Makefile])
AC_OUTPUT

dnl
dnl Expand the variables for summary reporting
dnl
prefix=`eval "echo $prefix"`
prefix=`eval "echo $prefix"`
bindir=`eval "echo $bindir"`
bindir=`eval "echo $bindir"`
sysconfdir=`eval "echo $sysconfdir"`
sysconfdir=`eval "echo $sysconfdir"`
mandir=`eval "echo $mandir"`
mandir=`eval "echo $mandir"`


dnl
dnl Compute configuration time elapsed
dnl
if test -x "${srcdir}/misc/elapsed.sh" ; then
	time_elapsed="`${srcdir}/misc/elapsed.sh $CONFIG_TIME`"
else
	time_elapsed="unknown"
fi


dnl **********************
dnl *** Output summary ***
dnl **********************

echo "Done."
echo
echo rt^3 Version $RT3_VERSION, Build $CONFIG_DATE
echo
echo "             Prefix: ${prefix}"
echo "           Binaries: ${bindir}"
echo "Configuration files: ${sysconfdir}"
echo "       Manual pages: ${mandir}"
echo
echo CC       = ${CC}
echo CFLAGS   = ${CFLAGS}
echo CXXFLAGS = ${CXXFLAGS}
echo CPPFLAGS = ${CPPFLAGS}
echo LDFLAGS  = ${LDFLAGS}
echo LIBS     = ${LIBS}
echo
echo Build static libraries ...............: $enable_static
echo Build shared/dynamic libraries .......: $enable_shared
echo Build debug release ..................: no
echo Build profile release ................: no
echo Print verbose compilation warnings ...: no
echo
echo Generate doxygen documentation .......: no
echo Run benchmark ........................: no
echo
if test "x$time_elapsed" != "xunknown" ; then
echo Elapsed configuration time ...........: $time_elapsed
fi
echo ---
echo "$0 complete, type 'make' to begin building"
echo
