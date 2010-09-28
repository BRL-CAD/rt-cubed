INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

SET(SVNADMIN_SRCS
	main.c
)

add_executable(svnadmin ${SVNADMIN_SRCS})
target_link_libraries(svnadmin svn_repos)
install(TARGETS svnadmin RUNTIME DESTINATION bin)
