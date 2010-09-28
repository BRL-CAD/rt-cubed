INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_RA_LOCAL
	ra_plugin.c
	split_url.c
)

add_library(svn_ra_local SHARED ${LIBSVN_RA_LOCAL})
target_link_libraries(svn_ra_local svn_subr svn_repos)
install(TARGETS svn_ra_local LIBRARY DESTINATION lib)
