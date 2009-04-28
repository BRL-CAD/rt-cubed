dnl                    C O N F I G U R E . A C
dnl rt^3
dnl
dnl Copyright (c) 2004-2009 United States Government as represented by
dnl the U.S. Army Research Laboratory.
dnl
dnl Redistribution and use in source and binary forms, with or without
dnl modification, are permitted provided that the following conditions
dnl are met:
dnl
dnl 1. Redistributions of source code must retain the above copyright
dnl notice, this list of conditions and the following disclaimer.
dnl
dnl 2. Redistributions in binary form must reproduce the above
dnl copyright notice, this list of conditions and the following
dnl disclaimer in the documentation and/or other materials provided
dnl with the distribution.
dnl
dnl 3. The name of the author may not be used to endorse or promote
dnl products derived from this software without specific prior written
dnl permission.
dnl
dnl THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
dnl OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
dnl WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
dnl ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
dnl DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
dnl DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
dnl GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
dnl INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
dnl WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
dnl NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
dnl SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
dnl
dnl NOTE: BRL-CAD as a collective work is distributed under the LGPL.
dnl       BRL-CAD's build system is under the BSD license.
dnl       See the COPYING file for more details.
dnl
dnl $Id$
dnl
dnl ******************************************************************
dnl ***                  rt^3's configure.ac                       ***
dnl ******************************************************************
dnl
dnl Herein lies the venerable GNU Build System configure template for
dnl BRL-CAD.  As best is reasonably possible, proper ordering and
dnl separation of tests and settings should be maintained per the
dnl recommended standard layout.  The tests should be added to the
dnl rather clearly labeled sections below so that they are as
dnl follows:
dnl
dnl     0) information on the package
dnl     1) check command-line arguments
dnl     2) check programs
dnl     3) check libraries
dnl     4) check headers
dnl     5) check types/structures
dnl     6) check compiler characteristics
dnl     7) check functions
dnl     8) check system services
dnl     9) output a summary
dnl
dnl Any useful build settings should be added to the output summary
dnl at the end.  Although it may be possible to check for certain
dnl features near the top in the command-line arguments section, any
dnl related tests should be delayed and placed into the appropriate
dnl check section.
dnl
dnl You should use enable/disable arguments for build settings and
dnl optional compilation components that are part of this package.
dnl You specify with/without arguments for components that are not a
dnl part of this package.
dnl
dnl Features of the GNU Autotools that would require an increase in
dnl the minimum version requirement are highly discouraged.  Likewise
dnl discouraged is rolling back support for versions released prior
dnl to the AC_PREREQ version shown below unless extensive testing has
dnl been performed.
dnl
dnl Let the finicky organized chaos begin.
dnl

AC_PREREQ(2.57)

dnl See HACKING for details on how to properly update the version
define([MAJOR_VERSION], [patsubst(esyscmd([cat include/conf/MAJOR]), [
])])
define([MINOR_VERSION], [patsubst(esyscmd([cat include/conf/MINOR]), [
])])
define([PATCH_VERSION], [patsubst(esyscmd([cat include/conf/PATCH]), [
])])
define([RT3___VERSION], [patsubst([MAJOR_VERSION.MINOR_VERSION.PATCH_VERSION], [
])])

dnl only needs major.minor version
AC_INIT(rt^3, [RT3___VERSION], [http://brlcad.org], rt3)
AC_REVISION($Revision$)
AC_CONFIG_AUX_DIR(misc)


dnl ***************************
dnl *** package information ***
dnl ***************************

RT3_VERSION=RT3___VERSION
AC_SUBST(MAJOR_VERSION)
AC_SUBST(MINOR_VERSION)
AC_SUBST(PATCH_VERSION)
AC_SUBST(RT3_VERSION)

dnl just in case
PACKAGE_NAME="rt^3"
AC_SUBST(PACKAGE_NAME)

# force locale setting to C so things like date output as expected
LC_ALL=C

CONFIG_DAY=`date +%d`
CONFIG_MONTH=`date +%m`
CONFIG_YEAR=`date +%Y`
CONFIG_DATE="${CONFIG_YEAR}${CONFIG_MONTH}${CONFIG_DAY}"
CONFIG_TIME="`date '+%H %M %S'`"
CONFIG_TS="`date`"
AC_SUBST(CONFIG_DAY)
AC_SUBST(CONFIG_MONTH)
AC_SUBST(CONFIG_YEAR)
AC_SUBST(CONFIG_DATE)
AC_SUBST(CONFIG_TIME)
AC_SUBST(CONFIG_TS)


# print out the title with a pretty box computed to wrap around
title="Configuring rt^3 Version $RT3_VERSION, Build $CONFIG_DATE"
length="`echo x${title}x | wc -c`"
separator=""
while test $length -gt 1 ; do
    separator="${separator}*"
    length="`expr $length - 1`"
done

BC_BOLD
AC_MSG_RESULT([***${separator}***])
AC_MSG_RESULT([*** ${title} ***])
AC_MSG_RESULT([***${separator}***])
BC_UNBOLD

# necessary for proper file creation on nfs volumes
umask 022

# override the default autoconf cflags if user has not modified them
if test "x$CFLAGS" = "x" ; then
	# an unset CFLAGS var is set to "-O2 -g" during AC_PROG_CC, so
	# set it to something benign instead like whitespace
	CFLAGS=" "
fi
if test "x$CXXFLAGS" = "x" ; then
	# an unset CXXFLAGS var is set to "-O2 -g" during AC_PROG_CXX, so
	# set it to something benign instead like whitespace
	CXXFLAGS=" "
fi

# override the default (empty) yflags (yacc) if user has not modified them
if test "x$YFLAGS" = "x" ; then
	YFLAGS="-d"
fi
AC_SUBST(YFLAGS)

# cannot override LD directly, so warn about that (configure sets it)
if test "x$LD" != "x" ; then
	AC_MSG_WARN([LD cannot be set directly yet it seems to be set ($LD)])
	sleep 1
fi

# classify this machine
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

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

AC_PREFIX_DEFAULT([/usr/brlcad])

# be explicit about our default directory
AC_MSG_CHECKING([where rt^3 is to be installed])
bc_prefix="$prefix"
eval "bc_prefix=\"$bc_prefix\""
eval "bc_prefix=\"$bc_prefix\""
if test "x$prefix" = "xNONE" ; then
    bc_prefix="$ac_default_prefix"
    # should be /usr/brlcad, but just in case
    eval "bc_prefix=\"$bc_prefix\""
    eval "bc_prefix=\"$bc_prefix\""
fi
AC_MSG_RESULT($bc_prefix)

# if this is not a checkout, disable dependency tracking for a faster
# build. it's not likely that the user is doing development from a
# source release. at least they really should not given the extra
# steps that are necessary for making a proper useful diff.
AC_MSG_CHECKING([whether dependency tracking should be enabled])
if test -d $srcdir/CVS -o -d $srcdir/.svn ; then
	if test "x$enable_maintainer_mode" = "x" ; then
		enable_maintainer_mode="yes"
	fi
	if test "x$enable_dependency_tracking" = "x" ; then
		enable_dependency_tracking="yes"
	fi
	AC_MSG_RESULT([yes])
else
	if test "x$enable_maintainer_mode" = "x" ; then
		enable_maintainer_mode="no"
	fi
	if test "x$enable_dependency_tracking" = "x" ; then
		enable_dependency_tracking="no"
	fi
	AC_MSG_RESULT([no])
fi

# init the venerable automake only _once_ or incur the wrath of
# several automake bugs (like "aclocal-" and install detection)
AM_INIT_AUTOMAKE([1.6 dist-zip dist-bzip2])

# disables the build system dependency tracking by default for the
# automake and autoconf template files.
AM_MAINTAINER_MODE

# write out all of our definitions to this header
AM_CONFIG_HEADER([include/rt3_config.h])

# automatically enable and load our configure cache file if available
BC_CONFIG_CACHE([config.cache.${host_os}.${ac_hostname}])


dnl ***************************
dnl *** Check for arguments ***
dnl ***************************

BC_CONFIGURE_STAGE([arguments], [1 of 9])

dnl *** enable options ***

# automatic flag updates
BC_ARG_ENABLE([auto_flags], [automatic-flags], [Automatically configure build flags], [yes])

# enable 64-bit builds
BC_ARG_ENABLE([build_64bit], [64bit-build], [Enable 64-bit compilation mode], [auto])

# optimized
BC_ARG_ENABLE([use_optimized], [optimized], [Enable optimized compilation], [no])

# warnings
BC_ARG_ENABLE([use_warnings], [warnings], [Enable verbose compilation warnings], [no])

# debug
BC_ARG_ENABLE([use_debug], [debug], [Enable debug symbols], [auto])

# profiling
BC_ARG_ENABLE([use_profiling], [profiling], [Enable profiling], [no])

dnl *** with options ***


###
# argument aliases
# they need to go below here in order for --help to consolidate the
# blank line that it inserts to exactly one line in the right place
###

# aliases for allowing configure to modify the flags automatically (help uses automatic-flags)
BC_ARG_ALIAS([auto_flags], [auto-flags])
BC_ARG_ALIAS([auto_flags], [auto-flag])
BC_ARG_ALIAS([auto_flags], [automatic-flag])

# 64-bit compilation (help uses 64bit-build)
BC_ARG_ALIAS([build_64bit], [64])
BC_ARG_ALIAS([build_64bit], [64bit])
BC_ARG_ALIAS([build_64bit], [64-bit])
BC_ARG_ALIAS([build_64bit], [64-build])
BC_ARG_ALIAS([build_64bit], [64-bit-build])

# optimized aliases (help uses optimized)
BC_ARG_ALIAS([use_optimized], [optimize])
BC_ARG_ALIAS([use_optimized], [optimization])
BC_ARG_ALIAS([use_optimized], [optimizations])

# verbose warning aliases (help uses warnings)
BC_ARG_ALIAS([use_warnings], [verbose])
BC_ARG_ALIAS([use_warnings], [warning])
BC_ARG_ALIAS([use_warnings], [verbose-warnings])
BC_ARG_ALIAS([use_warnings], [warnings-verbose])

# debug aliases (help uses debug)
BC_ARG_ALIAS([use_debug], [debugging])

# profiling aliases (help uses profiling)
BC_ARG_ALIAS([use_profiling], [profile])
BC_ARG_ALIAS([use_profiling], [profiled])

###
# argument summary printing
###

AC_MSG_CHECKING(whether to automatically set build flags)
AC_MSG_RESULT($bc_auto_flags)

AC_MSG_CHECKING(whether to compile in 64-bit mode)
AC_MSG_RESULT($bc_build_64bit)

AC_MSG_CHECKING(whether to enable optimized compilation)
AC_MSG_RESULT($bc_use_optimized)

AC_MSG_CHECKING(whether to enable verbose compilation warnings)
AC_MSG_RESULT($bc_use_warnings)

AC_MSG_CHECKING(whether to disable debug mode compilation)
AC_MSG_RESULT($bc_use_debug)

AC_MSG_CHECKING(whether to enable profile mode compilation)
AC_MSG_RESULT($bc_use_profiling)


dnl **************************
dnl *** Check for programs ***
dnl **************************

BC_CONFIGURE_STAGE([programs], [2 of 9])

# AC_LANG(C++)

AC_PROG_CC
AC_PROG_CC_C_O

AC_PROG_CPP
AC_REQUIRE_CPP

AC_PROG_CXX
AC_PROG_CXXCPP

AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_MKDIR_P

AM_PROG_LEX
AC_PROG_YACC

# libtool's configuration check has a bug that causes a /lib/cpp
# sanity check failure if a C++ compiler is not installed.  This makes
# the sanity test pass regardless of whether there is a c++ compiler.
if test "x$CXXCPP" = "x" ; then
	if test "x$CPP" = "x" ; then
		CXXCPP="cpp"
	else
		CXXCPP="$CPP"
	fi
fi

dnl disable unnecessary libtool test for fortran
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl

# libtool shouldn't be generated until after LD is set
# XXX went poof in libtool 1.9 -- AC_PROG_LIBTOOL
# LT_INIT
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

dnl verbose compilation progress
if test "x$bc_build_progress" != "xyes" ; then
	LIBTOOLFLAGS=--silent
	AC_SUBST(LIBTOOLFLAGS)
	# LIBTOOLFLAGS isn't often not enough;
	# tack --silent onto the LIBTOOL command.
	if test "x$LIBTOOL" != "x" ; then
		LIBTOOL="$LIBTOOL --silent"
	fi
fi

dnl Libtool may need AR so try to find it for it
AC_PATH_PROG(AR, ar, [], $PATH:/usr/bin:/usr/local/bin:/usr/ccs/bin)
AC_SUBST(AR)


dnl ***************************
dnl *** Check for libraries ***
dnl ***************************

BC_CONFIGURE_STAGE([libraries], [3 of 9])

AC_CHECK_LIB([c], [main])

dnl check if a math library links
m_link_works=no
LIBM=""
AC_CHECK_LIB(m, cos, m_link_works=yes ; LIBM="-lm")


dnl *************************
dnl *** Check for headers ***
dnl *************************

BC_CONFIGURE_STAGE([headers], [4 of 9])

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

BC_CONFIGURE_STAGE([types], [5 of 9])

AC_HEADER_STDBOOL
AC_HEADER_STAT
AC_HEADER_TIME
AC_TYPE_SIZE_T

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

BC_CONFIGURE_STAGE([compiler], [6 of 9])

if test ! "x$bc_auto_flags" = "xno" ; then

    dnl try to use -pipe to speed up the compiles
    BC_COMPILER_AND_LINKER_RECOGNIZES([-pipe])

    dnl check for -fno-strict-aliasing
    BC_COMPILER_AND_LINKER_RECOGNIZES([-fno-strict-aliasing])

    dnl check for -fno-common (libtcl needs it on darwin)
    BC_COMPILER_AND_LINKER_RECOGNIZES([-fno-common])

    dnl check for -search_paths_first linker flag.
    dnl prevent a false-positive where it can be treated as a -s and-e
    dnl linker option by adding a benign flag that should succeed.
    dnl this flag allows dylibs and archives to be found based on a
    dnl library path search order, not biasing a preference for dylibs.
    BC_LINKER_RECOGNIZES([-Wl,-search_paths_first -Wnewline-eof])

    dnl 64bit compilation flags
    if test "x$bc_build_64bit" = "xyes" ; then
	found_64bit_flag=no

	AC_MSG_CHECKING([if configure snuck on a 32bit flag to ld])
	PRELD="$LD"
	LD="`echo $LD | sed 's/32/64/'`"
	if test "x$LD" = "x$PRELD" ; then
		AC_MSG_RESULT(no)
	else
		AC_MSG_RESULT(yes)
	fi

	if test "x$found_64bit_flag" = "xno" ; then
		BC_COMPILER_AND_LINKER_RECOGNIZES([-64], [64_flag])
		if test "x$bc_64_flag_works" = "xyes" ; then
			found_64bit_flag=yes
		fi
	fi

	if test "x$found_64bit_flag" = "xno" ; then
		BC_COMPILER_AND_LINKER_RECOGNIZES([-mabi=64], [64_flag])
		if test "x$bc_64_flag_works" = "xyes" ; then
			found_64bit_flag=yes
		fi
	fi

	if test "x$found_64bit_flag" = "xno" ; then
		BC_COMPILER_AND_LINKER_RECOGNIZES([-m64], [64_flag])
		if test "x$bc_64_flag_works" = "xyes" ; then
			found_64bit_flag=yes
		fi
	fi

	if test "x$found_64bit_flag" = "xno" ; then
		BC_COMPILER_AND_LINKER_RECOGNIZES([-q64], [64_flag])
		if test "x$bc_64_flag_works" = "xyes" ; then
			found_64bit_flag=yes
		fi
	fi
    fi

# end check for automatic flags
fi
dnl profile flags
if test "x$bc_use_profiling" != "xno" ; then
	BC_COMPILER_AND_LINKER_RECOGNIZES([-pg], [profile_flag])
	if test "x$bc_debug_flag_works" = "xno" ; then
		if test "x$bc_use_profiling" = "xyes" ; then
			dnl profiling was requested, so abort
			AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
			AC_MSG_NOTICE([Profiling was enabled but -pg does not work])
			AC_MSG_ERROR([*** Don't know how to profile with this compiler ***])
		fi
		AC_MSG_WARN([Don't know how to profile with this compiler])
	else
		# convert 'auto' to 'no' even though it works
		bc_use_profiling=no
	fi
fi

dnl debug flags
if test "x$bc_use_debug" != "xno" ; then
	BC_COMPILER_AND_LINKER_RECOGNIZES([-g], [debug_flag])
	if test "x$bc_debug_flag_works" = "xno" ; then
		if test "x$bc_use_debug" = "xyes" ; then
			dnl debug was requested, so abort
			AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
			AC_MSG_NOTICE([Debug was enabled but -g does not work])
			AC_MSG_ERROR([*** Don't know how to debug with this compiler ***])
		fi
		AC_MSG_WARN([Do not know how to debug with this compiler])
	else
		# convert 'auto' to 'yes'
		bc_use_debug="yes"
	fi
fi

dnl optimization flags
if test "x$bc_use_optimized" != "xno" ; then
	BC_COMPILER_AND_LINKER_RECOGNIZES([-O3], [o3_flag])
	if test "x$bc_o3_flag_works" = "xno" ; then
		AC_MSG_WARN([Don't know how to compile optimized with this compiler])
	fi


# XXX -fast seems to provoke stack corruption in the shadow
# computations, possible that the corruption is indeed valid and
# there's something that needs to be checked/changed.
#
#	BC_COMPILER_AND_LINKER_RECOGNIZES([-fast], [mac_opt_flag])
#	if test "x$bc_mac_opt_flag_works" = "xno" ; then
#		BC_COMPILER_AND_LINKER_RECOGNIZES([-fast -mcpu=7450], [mac_opt_flag])
#	fi
	# don't set extra optimization flags if auto-flags was turned off
	if test ! "x$bc_auto_flags" = "xno" ; then
		if test "x$bc_mac_opt_flag_works" = "xno" ; then
			extra_optimization_flag="-ffast-math -fstrength-reduce -fexpensive-optimizations -finline-functions"
			if test "x$bc_use_debug" = "xno" ; then
				dnl non-debug can omit the frame pointer, debug cannot
				extra_optimization_flag="$extra_optimization_flag -fomit-frame-pointer"
			else
				extra_optimization_flag="$extra_optimization_flag -fno-omit-frame-pointer"
			fi
			BC_COMPILER_AND_LINKER_RECOGNIZES([$extra_optimization_flag])
		fi
	fi
fi

dnl verbose warning flags
if test "x$bc_use_warnings" != "xno" ; then
	BC_COMPILER_AND_LINKER_RECOGNIZES([-W -Wall -Wundef -Wfloat-equal -Wshadow -Wunreachable-code -Winline -Wconversion], [warning])
	# XXX also of interest
	# -Wmissing-declarations -Wmissing-prototypes -Wstrict-prototypes -pedantic -ansi -Werror

	if test "x$bc_warning_flag_works" = "xno" ; then
		AC_MSG_WARN([Don't know how to output verbose warnings with this compiler])
	fi
fi

AC_C_CONST
AC_C_INLINE
AC_C_VOLATILE
AM_C_PROTOTYPES

# figure out what size pointers the compiler is actually generating
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(void *, 4)
pointer_size="$ac_cv_sizeof_void_p"

# determine the minimum single-precision floating point tolerance
# value at compile time such that: 1.0 + value != 1.0
# ANSI defines this as FLT_EPSILON but float.h may not provide it.
BC_FLOAT_EPSILON

# determine the minimum double-precision floating point tolerance
# value at compile time such that: 1.0 + value != 1.0
# ANSI defines this as DBL_EPSILON but float.h may not provide it.
BC_DOUBLE_EPSILON

# determine whether the single-precision floating point implementation
# seems IEEE 754 compliant.
BC_COMPLIANT_FLOAT

# determine whether the double-precision floating point implementation
# seems IEEE 754 compliant.
BC_COMPLIANT_DOUBLE

# warn if either floating point compliance failed
if test "x$bc_compliant_float" = "xno" || test "x$bc_compliant_double" = "xno" ; then
    AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
    AC_MSG_WARN([The floating point implementation does not seem to be IEEE 754])
    AC_MSG_WARN([compliant.  The behavior or htond and htonf may be incorrect.])
    AC_MSG_NOTICE([{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{])
    sleep 1
fi

dnl Make sure that we can actually compile C code
BC_SANITY_CHECK([$CC compiler and flags for sanity])

dnl Make sure that we can actually compile C++ code
AC_LANG_PUSH([C++])
BC_SANITY_CHECK([$CXX compiler and flags for sanity])
AC_LANG_POP


dnl ***************************
dnl *** Check for functions ***
dnl ***************************

BC_CONFIGURE_STAGE([functions], [7 of 9])

AC_CHECK_FUNCS(\
)


dnl *********************************
dnl *** Check for system services ***
dnl *********************************

BC_CONFIGURE_STAGE([services], [8 of 9])

dnl *** libm ***
AC_MSG_CHECKING(whether to link with the math library)
AC_MSG_RESULT($m_link_works)
AC_SUBST(LIBM)


dnl *** 64-bit compilation ***
dnl figure out whether we are building 64-bit
build_brlcad_64bit="no"
if test "x$bc_build_64bit" = "xyes" ; then
	if test "x$pointer_size" != "x8" ; then
		AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
		AC_MSG_NOTICE([Try removing --enable-64bit-build or modifying the CFLAGS/LDFLAGS])
		AC_MSG_ERROR([*** Building 64-bit was requested, yet the build seems to be non-64-bit ***])
	fi
	build_brlcad_64bit=yes
else
	if test "x$bc_build_64bit" = "xno" ; then
		if test "x$pointer_size" = "x8" ; then
			AC_MSG_NOTICE([}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}])
			AC_MSG_NOTICE([Try removing --disable-64bit-build or modifying the CFLAGS/LDFLAGS])
			AC_MSG_ERROR([*** Building non-64-bit was requested, yet the build seems to be 64-bit ***])
		fi
	fi

	dnl automatic detection
	if test "x$pointer_size" = "x8" ; then
		build_brlcad_64bit="yes"
	elif test "x$pointer_size" = "x4" ; then
		build_brlcad_64bit="no (32-bit)"
	elif test "x$pointer_size" = "x2" ; then
		build_brlcad_64bit="no (16-bit)"
	elif test "x$pointer_size" = "x1" ; then
		build_brlcad_64bit="no (8-bit)"
	else
		AC_MSG_WARN([Unknown pointer size: $pointer_size])
	fi
fi

# XXX check for BRL-CAD

# make sure ECHO and ECHO_N got defined and substituted
if test "x$ECHO" = "x" ; then
    ECHO=echo
    AC_MSG_NOTICE([ECHO was not defined by configure so defining manually])
fi
AC_SUBST(ECHO)
AC_SUBST(ECHO_N)

dnl **************************************
dnl *** Configure Makefiles and output ***
dnl **************************************

BC_CONFIGURE_STAGE([output], [9 of 9])

# remove surrounding whitspace
CFLAGS="`echo $CFLAGS`"
CXXFLAGS="`echo $CXXFLAGS`"
CPPFLAGS="`echo $CPPFLAGS`"
LDFLAGS="`echo $LDFLAGS`"
LIBS="`echo $LIBS`"

dnl compile-time debug
if test "x$bc_use_debug" != "xno" ; then
	AC_DEFINE(DEBUG, 1, [Define to enable compile-time debug code])
else
	AC_DEFINE(NDEBUG, 1, [Define to indicate non-debug code (assert utilizes)])
fi

AC_CONFIG_FILES([
	Makefile
	include/Makefile
	include/conf/Makefile
	include/Image/Makefile
	include/Utility/Makefile
	include/Raytrace/Makefile
	m4/Makefile
	misc/Makefile
	src/Makefile
	src/date/Makefile
	src/GE/Makefile
	src/GS/Makefile
	src/iBME/Makefile
	src/libGeometry/Makefile
	src/libImage/Makefile
	src/libNetwork/Makefile
	src/libNumeric/Makefile
	src/libRaytrace/Makefile
	src/libUtility/Makefile
	src/rt^3/Makefile
	src/rt^3d/Makefile
	src/rt^3dbd/Makefile
	src/scratch/Makefile
	src/other/uuid/Makefile
])
AC_OUTPUT

# patch libtool if it has one of several common bugs and/or busted
# default configurations (e.g. Debian)
BC_PATCH_LIBTOOL


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
datadir=`eval "echo $datadir"`
datadir=`eval "echo $datadir"`


dnl
dnl Compute configuration time elapsed
dnl
if test -x "${srcdir}/misc/elapsed.sh" ; then
	time_elapsed="`${srcdir}/misc/elapsed.sh $CONFIG_TIME`"
else
	time_elapsed="unknown"
fi


dnl **********************
dnl *** Report Summary ***
dnl **********************

AC_MSG_RESULT([Done.])
AC_MSG_RESULT([])
BC_BOLD
AC_MSG_RESULT([rt^3 Version $RT3_VERSION, Build $CONFIG_DATE])
BC_UNBOLD
AC_MSG_RESULT([])
AC_MSG_RESULT([             Prefix: ${bc_prefix}])
AC_MSG_RESULT([           Binaries: ${bindir}])
AC_MSG_RESULT([       Manual pages: ${mandir}])
AC_MSG_RESULT([Configuration files: ${sysconfdir}])
AC_MSG_RESULT([Data resource files: ${bc_data_dir}])
if test ! "x$BC_ARGS" = "x" ; then
AC_MSG_RESULT([Options & variables: $BC_ARGS])
fi
AC_MSG_RESULT([])
AC_MSG_RESULT([CC       = ${CC}])
AC_MSG_RESULT([CXX      = ${CXX}])
if test ! "x$CFLAGS" = "x" ; then
AC_MSG_RESULT([CFLAGS   = ${CFLAGS}])
fi
if test ! "x$CXXFLAGS" = "x" ; then
AC_MSG_RESULT([CXXFLAGS = ${CXXFLAGS}])
fi
if test ! "x$CPPFLAGS" = "x" ; then
AC_MSG_RESULT([CPPFLAGS = ${CPPFLAGS}])
fi
if test ! "x$LDFLAGS" = "x" ; then
AC_MSG_RESULT([LDFLAGS  = ${LDFLAGS}])
fi
if test ! "x$LIBS" = "x" ; then
AC_MSG_RESULT([LIBS     = ${LIBS}])
fi
AC_MSG_RESULT([])
AC_MSG_RESULT([Build 64-bit release .................: $build_brlcad_64bit])
AC_MSG_RESULT([Build optimized release ..............: $bc_use_optimized])
AC_MSG_RESULT([Build debug release ..................: $bc_use_debug])
AC_MSG_RESULT([Build profile release ................: $bc_use_profiling])
AC_MSG_RESULT([Build static libraries ...............: $enable_static])
AC_MSG_RESULT([Build shared/dynamic libraries .......: $enable_shared])
AC_MSG_RESULT([Print verbose compilation warnings ...: $bc_use_warnings])
AC_MSG_RESULT([])
if test "x$time_elapsed" != "xunknown" ; then
AC_MSG_RESULT([Elapsed configuration time ...........: $time_elapsed])
fi
AC_MSG_RESULT([---])
AC_MSG_RESULT([$0 complete, type 'make' to begin building])
AC_MSG_RESULT([])

# Local Variables:
# tab-width: 8
# mode: autoconf
# sh-indentation: 4
# sh-basic-offset: 4
# indent-tabs-mode: t
# End:
# ex: shiftwidth=4 tabstop=8
