#                     M A K E F I L E . A M
# BRL-CAD
#
# Copyright (c) 2006 United States Government as represented by
# the U.S. Army Research Laboratory.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above
# copyright notice, this list of conditions and the following
# disclaimer in the documentation and/or other materials provided
# with the distribution.
#
# 3. The name of the author may not be used to endorse or promote
# products derived from this software without specific prior written
# permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
# OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
# GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
###
# $Id$

# require automake version
AUTOMAKE_OPTIONS = 1.6 dist-zip dist-bzip2
ACLOCAL_AMFLAGS = -I m4

required_dirs = \
	include \
	src

SUBDIRS = \
	$(required_dirs)

DIST_SUBDIRS = \
	$(required_dirs)

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

DISTCLEANFILES = \
	$(CONFIG_CACHE) \
	aclocal.m4 \
	config.log \
	config.status \
	configure \
	libtool \
	so_locations

MAINTAINERCLEANFILES = Makefile.in

#############
# the rules #
#############

.PHONY : benchmark bench regression regress test

benchmark: all
	${ECHO} there is presently no benchmark suite

bench: benchmark

regression: all
	${ECHO} there is presently no test suite

regress: regression

test: regression



##########################
# summaries and warnings #
##########################

# make sure a dangerous umask will not prevent others from using an
# installed version by checking to make sure the exec mode is set.
# We minimally check only the binary and prefix directories.
install-data-local:
	@warn_umask=no ; \
	case `ls -ld $(DESTDIR)$(prefix)` in \
	  d????????-*) warn_umask=yes ;; \
	  d?????-???*) warn_umask=yes ;; \
	  d??-??????*) warn_umask=yes ;; \
	esac ; \
	if test "x$$warn_umask" = "xno" ; then \
	  case `ls -ld $(DESTDIR)$(bindir)` in \
	    d????????-*) warn_umask=yes ;; \
	    d?????-???*) warn_umask=yes ;; \
	    d??-??????*) warn_umask=yes ;; \
	  esac ; \
	fi ; \
	if test "x$$warn_umask" = "xyes" ; then \
	    $(ECHO) ; \
	    $(ECHO) "}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}" ; \
	    $(ECHO) "  WARNING: There is no execute permission on the" ; \
	    $(ECHO) "           install directory." ; \
	    $(ECHO) ; \
	    $(ECHO) "  Consider running \"umask 022\" before installing" ; \
	    $(ECHO) "  next time.  You should be able to repair this"; \
	    $(ECHO) "  installation's directory permissions with: " ; \
	    $(ECHO) ; \
	    $(ECHO) "    find $(DESTDIR)$(prefix)/. -type d -exec chmod go+x {} \;" ; \
	    if test -d "$(DESTDIR)$(bindir)" ; then \
	      if test "x$(DESTDIR)$(exec_prefix)/bin" != "x$(DESTDIR)$(bindir)" ; then \
	  	$(ECHO) "    find $(DESTDIR)$(bindir)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    if test -d "$(DESTDIR)$(sbindir)" ; then \
	      if test "x$(DESTDIR)$(exec_prefix)/sbin" != "x$(DESTDIR)$(sbindir)" ; then \
	  	$(ECHO) "    find $(DESTDIR)$(sbindir)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    if test -d "$(DESTDIR)$(libexecdir)" ; then \
	      if test "x$(DESTDIR)$(exec_prefix)/libexec" != "x$(DESTDIR)$(libexecdir)" ; then \
	  	$(ECHO) "    find $(DESTDIR)$(libexecdir)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    if test -d "$(DESTDIR)$(datadir)" ; then \
	      if test "x$(DESTDIR)$(prefix)/share" != "x$(DESTDIR)$(datadir)" ; then \
	   	$(ECHO) "    find $(DESTDIR)$(prefix)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    if test -d "$(DESTDIR)$(libdir)" ; then \
	      if test "x$(DESTDIR)$(exec_prefix)/lib" != "x$(DESTDIR)$(libdir)" ; then \
	   	$(ECHO) "    find $(DESTDIR)$(libdir)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    if test -d "$(DESTDIR)$(mandir)" ; then \
	      if test "x$(DESTDIR)$(prefix)/man" != "x$(DESTDIR)$(mandir)" ; then \
	   	$(ECHO) "    find $(DESTDIR)$(mandir)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    if test -d "$(DESTDIR)$(includedir)" ; then \
	      if test "x$(DESTDIR)$(prefix)/include" != "x$(DESTDIR)$(includedir)" ; then \
	   	$(ECHO) "    find $(DESTDIR)$(includedir)/. -type d -exec chmod go+x {} \;" ; \
	      fi ; \
	    fi ; \
	    $(ECHO) ; \
	    $(ECHO) "  Do not presume the find example is all that is" ; \
	    $(ECHO) "  needed.  VERIFY THE PERMISSIONS." ; \
	    $(ECHO) "{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{" ; \
	    $(ECHO) ; \
	fi ; \
	touch install.$(host_triplet).log ; \
	if test -w install.$(host_triplet).log ; then \
	    LC_ALL=C ; \
	    if test "x$USER" = "x" ; then \
		USER="unknown" ; \
	    fi ; \
	    $(ECHO) "Installed rt^3 Release @BRLCAD_VERSION@ Build @CONFIG_DATE@ by ${USER} to $(DESTDIR)$(prefix) on `date`" >> install.$(host_triplet).log ; \
	fi


# Print out an informative summary.  As just about everything seems to
# end up calling the all-am hook, which in turns calls the all-local
# hook.  The initial target goal is used to print out a custom summary
# message.  If the make being used doesn't set the MAKECMDGOALS
# variable, something generic is printed still.  For a make install,
# print out rule lines according to the size of the installation path
# to emphasize the achievement.
#
all-local:
	@$(ECHO) "Done."
	@$(ECHO)
	@$(ECHO) "rt^3 Release @BRLCAD_VERSION@, Build @CONFIG_DATE@"
	@$(ECHO)
	@if test "x$(MAKECMDGOALS)" = "xall-am" -o "x$(.TARGETS)" = "xall-am" -o "x$(MAKECMDGOALS)" = "xfast" -o "x$(.TARGETS)" = "xfast" ; then \
	  $(ECHO) $(ECHO_N) "Elapsed compilation time: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh `cat $(top_builddir)/include/brlcad_version.h | grep Compilation` ;\
	  $(ECHO) $(ECHO_N) "Elapsed time since configuration: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh @CONFIG_TIME@ ;\
	  $(ECHO) "---" ;\
	  $(ECHO) "Run 'make install' to begin installation into $(prefix)" ;\
	  $(ECHO) "Run 'make benchmark' to run the rt^3 Benchmark Suite" ;\
	elif test "x$(MAKECMDGOALS)" = "xinstall-am" -o "x$(.TARGETS)" = "xinstall-am" ; then \
	  $(ECHO) $(ECHO_N) "Elapsed installation time: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh `cat $(top_builddir)/include/brlcad_version.h | grep Compilation` ;\
	  $(ECHO) $(ECHO_N) "Elapsed time since configuration: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh @CONFIG_TIME@ ;\
	  $(ECHO) "---" ;\
	  $(ECHO) "Run 'make test' to run the rt^3 Test Suite" ;\
	  $(ECHO) "Run 'make benchmark' to run the rt^3 Benchmark Suite" ;\
	  $(ECHO) ;\
	  line1="  rt^3 @BRLCAD_VERSION@ is now installed into $(prefix)" ;\
	  line2="  Be sure to add $(prefix)/bin to your PATH" ;\
	  separator="`$(ECHO) $$line1 | tr '[a-zA-Z0-9.\-/ ]' '*'`" ;\
	  $(ECHO) "$${separator}****" ;\
	  $(ECHO) "$$line1" ;\
	  $(ECHO) "$$line2" ;\
	  $(ECHO) "$${separator}****" ;\
	elif test "x$(MAKECMDGOALS)" = "x" -a "x$(.TARGETS)" = "x" ; then \
	  $(ECHO) $(ECHO_N) "Elapsed time: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh `cat $(top_builddir)/include/brlcad_version.h | grep Compilation` ;\
	  $(ECHO) $(ECHO_N) "Elapsed time since configuration: " ;\
	  sh $(top_srcdir)/misc/elapsed.sh @CONFIG_TIME@ ;\
	  $(ECHO) "---" ;\
	  $(ECHO) "Run 'make benchmark' to run the rt^3 Benchmark Suite" ;\
	fi
	@$(ECHO)

include $(top_srcdir)/misc/Makefile.defs

# Local Variables:
# mode: Makefile
# tab-width: 8
# indent-tabs-mode: t
# End:
# ex: shiftwidth=8 tabstop=8
