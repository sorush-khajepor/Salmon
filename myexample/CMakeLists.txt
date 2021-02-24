cmake_minimum_required(VERSION 3.0.0)
project(Example VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 20)

add_executable(Example Example.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
 