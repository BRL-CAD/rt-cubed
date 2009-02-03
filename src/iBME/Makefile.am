bin_PROGRAMS = gsph0 streamSerialTests netMsgSerialTest DataStreamTest



streamSerialTests_SOURCES = \
	../tests/streamSerialTests.cxx

streamSerialTests_LDADD = \
	../GeometryEngine/libge.la



DataStreamTest_SOURCES = \
	../tests/DataStreamTest.cxx

DataStreamTest_LDADD = \
	../GeometryEngine/libge.la



netMsgSerialTest_SOURCES = \
	../tests/netMsgSerialTest.cxx

netMsgSerialTest_LDADD = \
	../GeometryEngine/libge.la \
	../GeometryService/libgs.la




gsph0_SOURCES = \
	../GeometryService/gsph0.cxx

gsph0_LDADD = \
	../GeometryEngine/libge.la \
	../GeometryService/libgs.la

gsph0_LDFLAGS =  -L/home/dloman/lib/ -lboost_system-gcc41-mt-1_37

