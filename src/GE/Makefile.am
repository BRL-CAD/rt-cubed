SUBDIRS = \
        libGeometry \
        libNumeric \
        libImage \
        libRaytrace \
        libUtility 

AM_CPPFLAGS=-I${top_srcdir}/include

lib_LTLIBRARIES = libge.la

libge_la_SOURCES = \
	GeometryEngine.cxx \
	../iBME/Object.cxx \
	io/DataStream.cxx \
	io/ByteArrayInputStream.cxx \
	io/ByteArrayOutputStream.cxx \
	io/DataInputStream.cxx \
	io/DataOutputStream.cxx \
	io/FilterInputStream.cxx \
	io/FilterOutputStream.cxx \
	io/InputStream.cxx \
	io/OutputStream.cxx \
	io/PushbackInputStream.cxx \
	exception/CloneNotSupportedException.cxx \
	exception/Exception.cxx \
	exception/NullPointerException.cxx \
	exception/RuntimeException.cxx \
	exception/Throwable.cxx \
	exception/StreamEmptyException.cxx \
	exception/EOFException.cxx \
	exception/IOException.cxx
