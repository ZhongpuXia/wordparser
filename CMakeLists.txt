cmake_minimum_required(VERSION 2.8)
project(TABULAR_PARSER)
add_compile_options(-std=c++11)

#--------- compile -------------
include_directories("${PROJECT_SOURCE_DIR}/src")
set(SRC_LIST src/main.cpp  src/build_in.cpp)
add_executable(tabular_parser ${SRC_LIST})


#--------- install -------------
#install(TARGETS )
#install()


#--------- test ----------------
#add_test()


