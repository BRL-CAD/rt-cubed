INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_DIFF
	deprecated.c
	diff.c
	diff.h
	diff3.c
	diff4.c
	diff_file.c
	diff_memory.c
	lcs.c
	token.c
	util.c
)

add_library(svn_diff SHARED ${LIBSVN_DIFF})
target_link_libraries(svn_diff svn_subr)
install(TARGETS svn_diff LIBRARY DESTINATION lib)
