# $Id$

noinst_HEADERS = \
	rt^3_version.h

rt^3_version.h:
	@sh $(top_srcdir)/misc/vers.sh rt3_version "rt^3" > $@

DISTCLEANFILES = \
	rt^3_version.h \
	stamp-h1 \
	version

MAINTAINERCLEANFILES = \
	config.h.in \
	Makefile.in