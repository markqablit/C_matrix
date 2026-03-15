cmake_minimum_required(VERSION 3.10)
project(Matrix)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_C_STANDARD 11)

include_directories(${INCLUDE_DIR})
