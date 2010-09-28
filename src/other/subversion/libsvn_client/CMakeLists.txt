INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_CLIENT
	add.c
	blame.c
	cat.c
	changelist.c
	checkout.c
	cleanup.c
	client.h
	cmdline.c
	commit.c
	commit_util.c
	compat_providers.c
	copy.c
	ctx.c
	delete.c
	deprecated.c
	diff.c
	export.c
	externals.c
	info.c
	list.c
	locking_commands.c
	log.c
	merge.c
	mergeinfo.c
	mergeinfo.h
	prop_commands.c
	ra.c
	relocate.c
	repos_diff.c
	repos_diff_summarize.c
	resolved.c
	revert.c
	revisions.c
	status.c
	switch.c
	update.c
	url.c
	util.c
	version.c
)

add_library(svn_client SHARED ${LIBSVN_CLIENT})
target_link_libraries(svn_client svn_subr svn_ra svn_wc)
install(TARGETS svn_client LIBRARY DESTINATION lib)
