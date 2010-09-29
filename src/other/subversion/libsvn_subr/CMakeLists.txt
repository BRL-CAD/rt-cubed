SET(LIBSVN_SUBR
	atomic.c
	auth.c
	cache-inprocess.c
	cache-memcache.c
	cache.c
	checksum.c
	cmdline.c
	compat.c
	config.c
	config_auth.c
	config_file.c
	config_win.c
	constructors.c
	ctype.c
	date.c
	deprecated.c
	dirent_uri.c
	dso.c
	error.c
	hash.c
	io.c
	iter.c
	kitchensink.c
	lock.c
	log.c
	macos_keychain.c
	md5.c
	mergeinfo.c
	nls.c
	opt.c
	path.c
	pool.c
	prompt.c
	properties.c
	quoprint.c
	sha1.c
	simple_providers.c
	skel.c
	sorts.c
	sqlite.c
	ssl_client_cert_providers.c
	ssl_client_cert_pw_providers.c
	ssl_server_trust_providers.c
	stream.c
	subst.c
	svn_base64.c
	svn_string.c
	target.c
	time.c
	user.c
	username_providers.c
	utf.c
	utf_validate.c
	validate.c
	version.c
	win32_crashrpt.c
	win32_crypto.c
	win32_xlate.c
	xml.c
)

IF(APPLE)
	SET(APPLE_LINKS "-framework Security -framework CoreFoundation -framework CoreServices")
ENDIF(APPLE)

add_library(svn_subr SHARED ${LIBSVN_SUBR})
target_link_libraries(svn_subr ${ZLIB_LIBRARIES} ${EXPAT_LIBRARIES} ${APR_LIBRARY} ${APU_LIBRARY} ${SQLITE3_LIBRARIES} ${APPLE_LINKS})
install(TARGETS svn_subr LIBRARY DESTINATION lib)
IF(SUBVERSION_BUILD_LOCAL_APR)
	add_dependencies(svn_subr apr)
ENDIF(SUBVERSION_BUILD_LOCAL_APR)
IF(SUBVERSION_BUILD_LOCAL_APU)
	add_dependencies(svn_subr apr-util)
ENDIF(SUBVERSION_BUILD_LOCAL_APU)
