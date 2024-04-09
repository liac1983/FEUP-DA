cmake_minimum_required(VERSION 3.10)
project(WaterSupplyManager)

set(CMAKE_CXX_STANDARD 11)

set(SRC_DIR ./src)

include_directories(SYSTEM ${SRC_DIR})

set(
        SOURCE_FILES
        main.cpp
        ${SRC_DIR}/Node.cpp
        ${SRC_DIR}/Pipe.cpp
        ${SRC_DIR}/City.cpp
        ${SRC_DIR}/Station.cpp
        ${SRC_DIR}/Reservoir.cpp
        ${SRC_DIR}/Network.cpp
        ${SRC_DIR}/Parsing.cpp
        ${SRC_DIR}/MaxFlow.cpp
        ${SRC_DIR}/Menu.cpp
)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/output)

add_executable(WaterSupplyManager ${SOURCE_FILES})

# Doxygen Build

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)
