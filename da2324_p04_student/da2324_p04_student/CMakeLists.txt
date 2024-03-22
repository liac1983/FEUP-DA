cmake_minimum_required(VERSION 3.26)
project(da2324_p04_sol)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(TP4)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(da2324_p04_sol
        TP4/ex1.cpp
        TP4/ex2.cpp
        running_examples/closest_point_pair/ClosestPointPair.cpp
)

target_link_libraries(da2324_p04_sol gtest gtest_main)