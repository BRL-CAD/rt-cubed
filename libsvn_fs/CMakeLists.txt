INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_FS
	access.c
	fs-loader.c
)

add_library(svn_fs SHARED ${LIBSVN_FS})
target_link_libraries(svn_fs svn_subr svn_fs_util)
install(TARGETS svn_fs LIBRARY DESTINATION lib)
