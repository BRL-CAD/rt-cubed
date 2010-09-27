INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(SVNSTRESS_SRCS
	main.c
)

add_executable(svnstress ${SVNSTRESS_SRCS})
target_link_libraries(svnstress svn_client svn_repos)
install(TARGETS svnstress RUNTIME DESTINATION bin)
