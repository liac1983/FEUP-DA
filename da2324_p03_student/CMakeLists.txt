cmake_minimum_required(VERSION 3.26)
project(da2324_p03_student)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
include_directories(TP3)

set( CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_TMP} )

add_executable(da2324_p03_student
        data_structures/MutablePriorityQueue.h
        data_structures/UFDS.cpp
        data_structures/UFDS.h
        TP3/MSTTestAux.h
        TP3/ex1.cpp
        TP3/ex2.cpp
        TP3/ex3.cpp
)

target_link_libraries(da2324_p03_student gtest gtest_main)