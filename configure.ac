dnl *************************
dnl *** RT^3 configure.ac ***
dnl *************************


MAJOR_VERSION=0
MINOR_VERSION=1
PATCH_VERSION=0
RT3_VERSION="$MAJOR_VERSION.$MINOR_VERSION.$PATCH_VERSION"
AC_INIT(rt^3, 0.1.0, morrison@arl.army.mil)
AC_PREREQ(2.50)
AC_CONFIG_SRCDIR(src/Makefile.am)


dnl ***************************
dnl *** package information ***
dnl ***************************

CONFIGURE_DATE=`date +%Y%m%d`

AM_INIT_AUTOMAKE(rt^3, $RT3_VERSION)
AM_CONFIG_HEADER([include/config.h])

AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_DEFINE_UNQUOTED(RT_BUILD_OS, "$host_os", [Build operating system])
AC_DEFINE_UNQUOTED(RT_BUILD_USER, "`whoami`", [User who compiled])

echo "Configuring RT^3 $RT3_VERSION, Build $CONFIGURE_DATE"

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

if ! test "x$enable_doxygen" = "xno" ; then
	AC_PATH_PROG(DOXYGEN, doxygen, , $PATH)
	if test "x$DOXYGEN" = "x" ; then
		if test "x$enable_doxygen" = "xyes" ; then
			AC_MSG_ERROR([cound not find doxygen])
		fi
		enable_doxygen=no
	fi
fi
AM_CONDITIONAL(DOC, test "x$enable_doxygen" = "xyes")


dnl *****************************
dnl *** Check for environment ***
dnl *****************************

dnl autosearch fink paths
AC_MSG_CHECKING([for fink])
if test -d /sw ; then
	AC_MSG_RESULT([found, adding /sw to search paths])
	CFLAGS="$CFLAGS -I/sw/include"
	LDFLAGS="$LDFLAGS -L/sw/lib"
else
	AC_MSG_RESULT([not found])
fi

# manual sanity check
AC_MSG_CHECKING(compiler and flags for sanity)
AC_TRY_RUN([
#include <stdio.h>
int main(){exit(0);}
	],
	[	AC_MSG_RESULT(yes) ],
	[
		AC_MSG_RESULT(no)
		AC_MSG_ERROR([*** compiler cannot create working executables, check config.log ***])
	]
)


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


dnl ***************************
dnl *** Check for libraries ***
dnl ***************************

AC_CHECK_LIB([c], [main])
AC_CHECK_LIB([m], [main])
AC_CHECK_LIB([pthread], [main])
AC_CHECK_LIB([z], [main])


dnl ******************************
dnl *** Check for header files ***
dnl ******************************

AC_HEADER_STDC
AC_HEADER_DIRENT
AC_HEADER_SYS_WAIT
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_CHECK_HEADER( bitset,,
                 AC_MSG_ERROR( [[
Header <bitset> not found. This is probably caused by having an incomplete
C++ standard library implementation. Please upgrade to a compiler that is
ISO/IEC 14882 conformant.]]))
AC_CHECK_HEADERS([iostream string algorithm vector ctime])
AC_LANG_RESTORE
AC_CHECK_HEADERS([time.h ])


dnl ****************************************************
dnl *** Check for types, structures, and library goo ***
dnl ****************************************************

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


dnl *******************************************************
dnl *** Check for library functions and system services ***
dnl *******************************************************

AC_FUNC_ALLOCA
AC_FUNC_CHOWN
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_GETGROUPS
AC_PROG_GCC_TRADITIONAL
AC_FUNC_LSTAT
AC_FUNC_MALLOC
AC_FUNC_MEMCMP
AC_FUNC_MKTIME
AC_FUNC_MMAP
AC_FUNC_SETPGRP
AC_FUNC_SETVBUF_REVERSED
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_STRTOD
AC_FUNC_UTIME_NULL
AC_FUNC_VPRINTF
AC_FUNC_WAIT3
AC_CHECK_FUNCS([
	alarm 
	atexit 
	bzero 
	dup2 
	endgrent 
	endpwent 
	floor 
	ftime 
	ftruncate 
	getcwd 
	gethostbyaddr 
	gethostbyname 
	gethostname 
	getpagesize 
	gettimeofday 
	getwd 
	inet_ntoa 
	isascii 
	localtime_r 
	memchr 
	memmove 
	memset 
	mkdir 
	mkfifo 
	modf 
	munmap 
	nl_langinfo 
	pow putenv 
	re_comp 
	realpath 
	regcomp 
	rmdir 
	select 
	setlocale 
	socket 
	sqrt   
	strcasecmp 
	strchr 
	strcspn 
	strdup 
	strerror 
	strncasecmp 
	strpbrk 
	strrchr 
	strspn 
	strstr 
	strtol 
	strtoul 
	strtoull 
	tzset 
	uname 
	utime
])


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

dnl **********************
dnl *** Output summary ***
dnl **********************

echo
echo RT^3 $RT3_VERSION, Build $CONFIGURE_DATE
echo
echo            Binaries: ${prefix}
echo Configuration files: ${sysconfdir}
echo
echo CC       = ${CC}
echo CFLAGS   = ${CFLAGS}
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
echo ---
echo $0 complete, type \'make\' to begin building
echo
