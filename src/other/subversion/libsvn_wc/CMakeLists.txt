INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_WC
	adm_crawler.c
	adm_files.c
	adm_ops.c
	ambient_depth_filter_editor.c
	copy.c
	crop.c
	deprecated.c
	diff.c
	entries.c
	lock.c
	log.c
	merge.c
	props.c
	questions.c
	relocate.c
	revision_status.c
	status.c
	translate.c
	tree_conflicts.c
	update_editor.c
	util.c
	wc_db.c
)

add_library(svn_wc SHARED ${LIBSVN_WC})
target_link_libraries(svn_wc svn_subr svn_diff svn_delta)
install(TARGETS svn_wc LIBRARY DESTINATION lib)
