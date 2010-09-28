INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_RA_SVN
	client.c
	cram.c
	cyrus_auth.c
	editorp.c
	internal_auth.c
	marshal.c
	streams.c
	version.c
)

add_library(svn_ra_svn SHARED ${LIBSVN_RA_SVN})
target_link_libraries(svn_ra_svn svn_subr svn_repos)
install(TARGETS svn_ra_svn LIBRARY DESTINATION lib)
