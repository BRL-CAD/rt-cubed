MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##        Configuring GeometryEngine          ##")
MESSAGE(STATUS "################################################\n")


set(GE_SOURCES
	GeometryEngine.cxx
	../iBME/Object.cxx
	io/DataStream.cxx
	io/ByteArrayInputStream.cxx
	io/ByteArrayOutputStream.cxx
	io/DataInputStream.cxx
	io/DataOutputStream.cxx
	io/FilterInputStream.cxx
	io/FilterOutputStream.cxx
	io/InputStream.cxx
	io/OutputStream.cxx
	io/PushbackInputStream.cxx
	exception/CloneNotSupportedException.cxx
	exception/Exception.cxx
	exception/NullPointerException.cxx
	exception/RuntimeException.cxx
	exception/Throwable.cxx
	exception/StreamEmptyException.cxx
	exception/EOFException.cxx
	exception/IOException.cxx
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

ADD_LIBRARY (ge SHARED ${GE_SOURCES})


ADD_SUBDIRECTORY(./libGeometry)
ADD_SUBDIRECTORY(./libImage)
ADD_SUBDIRECTORY(./libNumeric)
ADD_SUBDIRECTORY(./libRaytrace)
ADD_SUBDIRECTORY(./libUtility)
