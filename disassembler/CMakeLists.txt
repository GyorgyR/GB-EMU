cmake_minimum_required(VERSION 2.8.4)

project(gb-disassembler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_custom_target(test-disassembler COMMAND make -C ${gb-disassembler_SOURCE_DIR}
                                    CLION_EXE_DIR=${PROJECT_BINARY_DIR})