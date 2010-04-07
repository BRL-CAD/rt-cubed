
bin_PROGRAMS = rt^3

rt_3_SOURCES = \
	RtApplication.cxx \
	RtApplication.h \
	main.cxx \
	main.h

AM_CPPFLAGS = -I${top_srcdir}/include
LDADD = \
	../GE/libutility/libUtility.a \
	../GE/libGeometry/libGeometry.a \
	../GE/libImage/libImage.a \
	../GE/libRaytrace/libRaytrace.a

rt_3_LDFLAGS = ../date/buildStamp.o
