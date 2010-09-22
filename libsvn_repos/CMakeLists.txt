INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(LIBSVN_REPOS
	authz.c
	commit.c
	delta.c
	deprecated.c
	dump.c
	fs-wrap.c
	hooks.c
	load.c
	log.c
	node_tree.c
	replay.c
	reporter.c
	repos.c
	rev_hunt.c
)

add_library(svn_repos SHARED ${LIBSVN_REPOS})
target_link_libraries(svn_repos svn_subr svn_delta svn_fs)
install(TARGETS svn_repos LIBRARY DESTINATION lib)
