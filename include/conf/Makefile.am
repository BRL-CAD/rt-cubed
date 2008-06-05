# $Id: Makefile.am 31210 2008-05-29 06:08:26Z brlcad $

COUNT: DATE HOST PATH USER
	test -f $@ && expr `cat COUNT` + 1 > $@ || echo "1" > $@

DATE: HOST PATH USER $(top_builddir)/include/rt3_config.h
	echo "\"`date`\"" > $@

HOST: $(top_builddir)/include/rt3_config.h
	echo "\"`hostname`\"" > $@

PATH: $(top_builddir)/include/rt3_config.h
	echo "\"$(DESTDIR)$(prefix)\"" > $@

USER: $(top_builddir)/include/rt3_config.h
	echo "\"`whoami`\"" > $@

# this causes them to be dependencies on the 'all' target
BUILT_SOURCES = \
	COUNT \
	DATE \
	HOST \
	PATH \
	USER

EXTRA_DIST = \
	$(BUILT_SOURCES) \
	MAJOR \
	MINOR \
	PATCH

# remove all except COUNT
CLEANFILES = \
	DATE \
	HOST \
	PATH \
	USER

DISTCLEANFILES = \
	$(CLEANFILES) \
	COUNT

all-am: $(BUILT_SOURCES)

include $(top_srcdir)/misc/Makefile.defs
