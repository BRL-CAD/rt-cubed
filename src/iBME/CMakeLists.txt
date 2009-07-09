MESSAGE(STATUS "\n\n")
MESSAGE(STATUS "################################################")
MESSAGE(STATUS "##              Configuring iBME              ##")
MESSAGE(STATUS "################################################\n")


INCLUDE_DIRECTORIES (${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR})
MESSAGE(STATUS "Include Directories: ${RT3_INCLUDE_DIR} ${QT_INCLUDE_DIR}")

ADD_EXECUTABLE(gsph0 ../GS/gsph0.cxx)

TARGET_LINK_LIBRARIES(gsph0 ge)
TARGET_LINK_LIBRARIES(gsph0 gs)


ADD_EXECUTABLE(streamSerialTests ../tests/streamSerialTests.cxx)
TARGET_LINK_LIBRARIES(streamSerialTests ge)

ADD_EXECUTABLE(dataStreamTest ../tests/DataStreamTest.cxx)
TARGET_LINK_LIBRARIES(dataStreamTest ge)

ADD_EXECUTABLE(netMsgSerialTest ../tests/netMsgSerialTest.cxx)
TARGET_LINK_LIBRARIES(netMsgSerialTest ge)
TARGET_LINK_LIBRARIES(netMsgSerialTest gs)
