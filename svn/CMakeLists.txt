INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(SVN_SRCS
	add-cmd.c
	blame-cmd.c
	cat-cmd.c
	changelist-cmd.c
	checkout-cmd.c
	cleanup-cmd.c
	commit-cmd.c
	conflict-callbacks.c
	copy-cmd.c
	delete-cmd.c
	diff-cmd.c
	export-cmd.c
	help-cmd.c
	import-cmd.c
	info-cmd.c
	list-cmd.c
	lock-cmd.c
	log-cmd.c
	main.c
	merge-cmd.c
	mergeinfo-cmd.c
	mkdir-cmd.c
	move-cmd.c
	notify.c
	propdel-cmd.c
	propedit-cmd.c
	propget-cmd.c
	proplist-cmd.c
	props.c
	propset-cmd.c
	resolve-cmd.c
	resolved-cmd.c
	revert-cmd.c
	status-cmd.c
	status.c
	switch-cmd.c
	tree-conflicts.c
	unlock-cmd.c
	update-cmd.c
	util.c
)

add_executable(svn ${SVN_SRCS})
target_link_libraries(svn svn_client)
install(TARGETS svn RUNTIME DESTINATION bin)
