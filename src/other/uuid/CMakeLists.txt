MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##               Configuring UUID             ##")
MESSAGE(STATUS "################################################\n")


set(UUID_SOURCES
	uuidcpp.cxx 
	uuid.c 
	uuid_cli.c 
	uuid_dce.c 
	uuid_mac.c 
	uuid_md5.c 
	uuid_prng.c 
	uuid_sha1.c 
	uuid_str.c 
	uuid_time.c 
	uuid_ui128.c 
	uuid_ui64.c
)

INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} )
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR}")

ADD_LIBRARY (uuid SHARED ${UUID_SOURCES})


