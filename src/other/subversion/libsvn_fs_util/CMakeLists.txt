SET(LIBSVN_FS_UTIL
	fs-util.c
)

add_library(svn_fs_util SHARED ${LIBSVN_FS_UTIL})
target_link_libraries(svn_fs_util svn_subr)
install(TARGETS svn_fs_util LIBRARY DESTINATION lib)
