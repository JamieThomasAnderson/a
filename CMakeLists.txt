cmake_minimum_required(VERSION 3.0.0)
project(cas VERSION 0.1.0 LANGUAGES C)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


include_directories(${INCLUDE_DIR})
file(GLOB SOURCES "${SRC_DIR}/*.c")

add_executable(cas ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)