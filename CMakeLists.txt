cmake_minimum_required(VERSION 3.12)

# Paths
set(TGAME_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TGAME_THIRDPARTY_DIR ${TGAME_ROOT_DIR}/thirdparty)

project(tgame CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

# Thirdparty librariies
include(${TGAME_THIRDPARTY_DIR}/libs.cmake)

add_subdirectory(src)