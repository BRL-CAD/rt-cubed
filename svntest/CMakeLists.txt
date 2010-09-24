INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(SVNTEST_SRCS
	main.c
)

add_executable(svntest ${SVNTEST_SRCS})
target_link_libraries(svntest svn_repos)
install(TARGETS svntest RUNTIME DESTINATION bin)
