cmake_minimum_required(VERSION 3.20)
project(3lab_C__)

set(CMAKE_CXX_STANDARD 11)

add_executable(3lab_C__ main.cpp Blocks/Blocks.cpp Blocks/Blocks.h Utility/parser.h Utility/parser.cpp Blocks/readfile.cpp Blocks/readfile.h Utility/Applier.cpp Utility/Applier.h Blocks/writefile.cpp Blocks/writefile.h Blocks/grep.cpp Blocks/grep.h Blocks/example.cpp Blocks/example.h Blocks/sort.cpp Blocks/sort.h Blocks/replace.cpp Blocks/replace.h Blocks/dump.cpp Blocks/dump.h)
