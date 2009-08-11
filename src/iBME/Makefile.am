bin_PROGRAMS = gsph0 streamSerialTests netMsgSerialTest DataStreamTest

AM_CPPFLAGS=-I${top_srcdir}/include

streamSerialTests_SOURCES = \
	../tests/streamSerialTests.cxx

streamSerialTests_LDADD = \
	../GE/libge.la



DataStreamTest_SOURCES = \
	../tests/DataStreamTest.cxx

DataStreamTest_LDADD = \
	../GE/libge.la



netMsgSerialTest_SOURCES = \
	../tests/netMsgSerialTest.cxx

netMsgSerialTest_LDADD = \
	../GE/libge.la \
	../GS/libgs.la

gsph0_SOURCES = \
	../GS/gsph0.cxx

gsph0_LDADD = \
	../GE/libge.la \
	../GS/libgs.la
