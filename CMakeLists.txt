cmake_minimum_required(VERSION 3.9)
project(hexcurses)

set(CMAKE_CXX_STANDARD 11)

add_executable(hexcurses main.cpp HexApplication.cpp HexApplication.h Window.cpp Window.h AddressWindow.cpp AddressWindow.h HexWindow.cpp HexWindow.h AsciiWindow.cpp AsciiWindow.h easylogging++.cc)
target_link_libraries(hexcurses ncursesw)