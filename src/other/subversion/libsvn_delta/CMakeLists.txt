SET(LIBSVN_DELTA
	cancel.c
	compat.c
	compose_delta.c
	debug_editor.c
	default_editor.c
	depth_filter_editor.c
	path_driver.c
	svndiff.c
	text_delta.c
	version.c
	xdelta.c
)

add_library(svn_delta SHARED ${LIBSVN_DELTA})
target_link_libraries(svn_delta svn_subr)
install(TARGETS svn_delta LIBRARY DESTINATION lib)
