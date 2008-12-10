lib_LTLIBRARIES = libsocketcc.la

libsocketcc_la_CPPFLAGS = -DPLATFORM_linux

libsocketcc_la_SOURCES = \
	src/ipaddress.cxx \
	src/socketbase.cxx \
	src/socketexception.cxx \
	src/tcpsockets.cxx \
	src/udpsockets.cxx

libsocketcc_la_LIBADD = \
	../pthreadcc/libpthreadcc.la


bin_PROGRAMS = deamonapp echoapp

deamonapp_SOURCES = \
	sample/application.cxx \
	sample/deamon.cxx \
	sample/tcpserver.cxx

deamonapp_LDADD = \
	libsocketcc.la


echoapp_SOURCES = \
	sample/myecho.cxx

echoapp_LDADD = \
	libsocketcc.la

