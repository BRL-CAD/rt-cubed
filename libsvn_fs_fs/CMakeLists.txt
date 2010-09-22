INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/rep-cache-db.h
   COMMAND ${SH_EXEC} ${CMAKE_SOURCE_DIR}/scripts/transform_sql.sh ${CMAKE_SOURCE_DIR}/libsvn_fs_fs/rep-cache-db.sql < ${CMAKE_SOURCE_DIR}/libsvn_fs_fs/rep-cache-db.sql > ${CMAKE_CURRENT_BINARY_DIR}/rep-cache-db.h
)

SET(LIBSVN_FS_FS
	caching.c
	dag.c
	err.c
	fs.c
	fs_fs.c
	id.c
	key-gen.c
	lock.c
	rep-cache.c
	tree.c
)

add_library(svn_fs_fs SHARED ${LIBSVN_FS_FS})
add_dependencies(svn_fs_fs ${CMAKE_CURRENT_BINARY_DIR}/rep-cache-db.h)
target_link_libraries(svn_fs_fs svn_subr svn_delta svn_fs_util)
install(TARGETS svn_fs_fs LIBRARY DESTINATION lib)
