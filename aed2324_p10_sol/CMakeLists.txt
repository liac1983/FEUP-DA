cmake_minimum_required(VERSION 3.10)
project(aed2324_p10_sol)

set(CMAKE_CXX_STANDARD 11)

set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(aed2324_p10_sol main.cpp Tests/tests.cpp Tests/Graph.h Tests/funWithDFS.cpp Tests/funWithBFS.cpp Tests/Person.cpp)

target_link_libraries(aed2324_p10_sol gtest gtest_main)
