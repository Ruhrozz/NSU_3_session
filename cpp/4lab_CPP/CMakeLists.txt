cmake_minimum_required(VERSION 3.20)
project(checkers)

set(CMAKE_CXX_STANDARD 14)

add_executable(checkers main.cpp Classes/Figure.cpp Classes/Figure.h Classes/Board.cpp Classes/Board.h Classes/Game.cpp Classes/Game.h Classes/Controller.cpp Classes/Controller.h Classes/Player.cpp Classes/Player.h)
