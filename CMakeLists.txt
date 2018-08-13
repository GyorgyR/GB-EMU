cmake_minimum_required(VERSION 3.12)
project(GameBoy)

set(CMAKE_CXX_STANDARD 14)

include_directories(emulator/include)

add_executable(GameBoy
        emulator/bin/runner
        emulator/build/Main.o
        "emulator/data/Tetris (World).gb"
        emulator/src/Main.cpp
        emulator/LICENCE
        emulator/makefile
        emulator/README.md
        emulator/STYLEGUIDE)
