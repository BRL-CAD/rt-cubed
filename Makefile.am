# $Id$

# require automake version
AUTOMAKE_OPTIONS = 1.6

SUBDIRS = \
	include \
	src

DIST_SUBDIRS = \
	include \
	src

EXTRA_DIST = \
	AUTHORS \
	BUGS \
	BUILD \
	COPYING \
	DEVINFO \
	Makefile.am \
	PORTING \
	README \
	TODO \
	autogen.sh \
	configure.ac

CLOBBER_FILES = \
	aclocal.m4 \
	config.guess \
	config.sub \
	configure \
	Makefile.in

# Print out an informative summary.  As just about everything seems to
# end up calling the all-am hook, which in turns calls the all-local
# hook.  The initial target goal is used to print out a custom summary
# message.  If the make being used doesn't set the MAKECMDGOALS
# variable, something generic is printed still.  For a make install,
# print out rule lines according to the size of the installation path
# to emphasize the achievement.
#
all-local:
	@@ECHO@ "Done."
	@@ECHO@
	@@ECHO@ "rt^3 Version @RT3_VERSION@, Build @CONFIG_DATE@"
	@@ECHO@
	@if test "x$(MAKECMDGOALS)" = "xall-am" -o "x$(.TARGETS)" = "xall-am" ; then \
	  @ECHO@ @ECHO_N@ "Elapsed compilation time: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh `cat $(top_builddir)/include/rt^3_version.h | grep Compilation` ;\
	  @ECHO@ @ECHO_N@ "Elapsed time since configuration: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh @CONFIG_TIME@ ;\
	  @ECHO@ "---" ;\
	  @ECHO@ "Run 'make install' to begin installation into $(prefix)" ;\
	elif test "x$(MAKECMDGOALS)" = "xinstall-am" -o "x$(.TARGETS)" = "xinstall-am" ; then \
	  @ECHO@ @ECHO_N@ "Elapsed installation time: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh `cat $(top_builddir)/include/rt^3_version.h | grep Compilation` ;\
	  @ECHO@ @ECHO_N@ "Elapsed time since configuration: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh @CONFIG_TIME@ ;\
	  @ECHO@ "---" ;\
	  @ECHO@ ;\
	  line1="  rt^3 @RT3_VERSION@ is now installed into $(prefix)" ;\
	  line2="  Be sure to add $(prefix)/bin to your PATH" ;\
	  length="`@ECHO@ $(prefix)@RT3_VERSION@ | wc -c`" ;\
	  length="`expr $$length + 34`" ;\
	  separator="" ;\
	  while test $$length -gt 0  ; do \
	    separator="$${separator}***" ;\
	    length="`expr $$length - 3`" ;\
          done ;\
	  @ECHO@ "$$separator" ;\
	  @ECHO@ "$$line1" ;\
	  @ECHO@ "$$line2" ;\
	  @ECHO@ "$$separator" ;\
	elif test "x$(MAKECMDGOALS)" = "x" -a "x$(.TARGETS)" = "x" ; then \
	  @ECHO@ @ECHO_N@ "Elapsed time: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh `cat $(top_builddir)/include/rt^3_version.h | grep Compilation` ;\
	  @ECHO@ @ECHO_N@ "Elapsed time since configuration: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh @CONFIG_TIME@ ;\
	  @ECHO@ "---" ;\
	fi
	@@ECHO@
