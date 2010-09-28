INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(SVNSERVE_SRCS
	cyrus_auth.c
	log-escape.c
	main.c
	serve.c
	winservice.c
)

add_executable(svnserve ${SVNSERVE_SRCS})
target_link_libraries(svnserve svn_repos svn_ra_svn)
install(TARGETS svnserve RUNTIME DESTINATION bin)
