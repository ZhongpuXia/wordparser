# required: /usr/lib/x86_64-linux-gnu/libglog.a&libgtest.a


cmake_minimum_required(VERSION 2.8)
project(TABULAR_PARSER)
add_compile_options(-std=c++11)

set(GLOG_INCLUDE_DIR "/usr/include/")
set(GLOG_LINK_DIR "/usr/lib/x86_64-linux-gnu/")
set(GLOG_LIBRARY "glog")

set(GTEST_INCLUDE_DIR "/usr/include/")
set(GTEST_LINK_DIR "/usr/lib/x86_64-linux-gnu/")
set(GTEST_LIBRARY "gtest")

#--------- compile -------------
include_directories("${PROJECT_SOURCE_DIR}/src" ${GLOG_INCLUDE_DIR} ${GTEST_INCLUDE_DIR})
link_directories(${GLOG_LINK_DIR} ${GTEST_LINK_DIR})
set(SRC_LIST src/demo.cpp  src/utils.cpp src/user.cpp src/parser.cpp)
add_executable(demo ${SRC_LIST})
target_link_libraries(demo ${GLOG_LIBRARY} pthread)


#--------- test ----------------
set(SRC_TEST test/test_parser.cpp src/utils.cpp src/user.cpp src/parser.cpp)
add_executable(test_parser ${SRC_TEST})
target_link_libraries(test_parser ${GTEST_LIBRARY} ${GLOG_LIBRARY} pthread)
enable_testing()
##add_subdirectory(test)
add_test(NAME test_parser
	     COMMAND test_parser)


