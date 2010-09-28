INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_RA
	compat.c
	deprecated.c
	ra_loader.c
	ra_loader.h
	util.c
)

add_library(svn_ra SHARED ${LIBSVN_RA})
target_link_libraries(svn_ra svn_subr svn_delta svn_ra_local svn_ra_svn)
install(TARGETS svn_ra LIBRARY DESTINATION lib)
