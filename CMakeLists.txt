cmake_minimum_required(VERSION 2.8)
project(WORLD_PARSER)

#--------- compile -------------
include_directories("${PROJECT_SOURCE_DIR}/include")
set(SRC_LIST main.cpp)
add_executable(world_paser ${SRC_LIST})


#--------- install -------------
install(TARGETS )
install()


#--------- test ----------------
add_test()


