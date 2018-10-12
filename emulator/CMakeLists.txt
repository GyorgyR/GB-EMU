cmake_minimum_required(VERSION 2.8.4)

project(gb-emulator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_custom_target(test-emulator COMMAND make -C ${gb-emulator_SOURCE_DIR}
                                    CLION_EXE_DIR=${PROJECT_BINARY_DIR})