
lib_LTLIBRARIES = libge.la

libge_la_SOURCES = \
	AbstractDbObjectSource.cxx \
	BrlcadDb.cxx \
	CommandResult.cxx \
	DbObject.cxx \
	GED.cxx \
	GeometryEngine.cxx \
	GeoCollection.cxx \
	GeoRegion.cxx \
	GeoSolid.cxx \
	NonGeo.cxx \
	DbObjectCache.cxx \
	SourceDiskLink.cxx \
	SourceSvnLink.cxx \
	DbObjectManager.cxx \
	DbObjectManifest.cxx \
	../io/ByteArrayInputStream.cxx \
	../io/ByteArrayOutputStream.cxx \
	../io/DataInputStream.cxx \
	../io/DataOutputStream.cxx \
	../io/EOFException.cxx \
	../io/FilterInputStream.cxx \
	../io/FilterOutputStream.cxx \
	../io/InputStream.cxx \
	../io/IOException.cxx \
	../io/OutputStream.cxx \
	../io/PushbackInputStream.cxx \
	../lang/CloneNotSupportedException.cxx \
	../lang/Exception.cxx \
	../lang/NullPointerException.cxx \
	../lang/Object.cxx \
	../lang/RuntimeException.cxx \
	../lang/Throwable.cxx 


bin_PROGRAMS = serialtest

serialtest_SOURCES = \
	../io/sstest.cxx

serialtest_LDADD = \
	libge.la
