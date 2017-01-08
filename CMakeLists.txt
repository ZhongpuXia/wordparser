cmake_minimum_required(VERSION 2.8)
project(TABULAR_PARSER)
add_compile_options(-std=c++11)

#--------- compile -------------
set(GLOG_INCLUDE_DIR "/usr/include/")
set(GLOG_LINK_DIR "/usr/lib/x86_64-linux-gnu/")
set(GLOG_LIBRARY "libglog.so")

include_directories("${PROJECT_SOURCE_DIR}/src" ${GLOG_INCLUDE_DIR})
link_directories(${GLOG_LINK_DIR})
set(SRC_LIST src/main.cpp  src/utils.cpp src/user.cpp src/parser.cpp)
add_executable(tabular_parser ${SRC_LIST})
target_link_libraries(tabular_parser ${GLOG_LIBRARY})

#--------- install -------------
#install(TARGETS )
#install()


#--------- test ----------------
#enable_testing()
#add_subdirectory(test)

#add_test()


