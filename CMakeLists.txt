cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_NAME "bezier")
project(${EXECUTABLE_NAME})

find_package(SFML REQUIRED COMPONENTS graphics window system)

include_directories("include")
file(GLOB SOURCES "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system)