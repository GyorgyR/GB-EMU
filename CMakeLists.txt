cmake_minimum_required(VERSION 3.12)
project(GameBoy)

set(CMAKE_CXX_STANDARD 14)

include_directories(disassembler/include)

add_executable(GameBoy
        disassembler/bin/runner
        disassembler/build/Main.o
        "disassembler/data/Tetris (World).gb"
        disassembler/src/Main.cpp
        disassembler/LICENCE
        disassembler/makefile
        disassembler/README.md
        disassembler/STYLEGUIDE)
