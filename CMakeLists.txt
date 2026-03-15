cmake_minimum_required(VERSION 3.10)
project(MatrixLab)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")

set(SOURCES
    ${SRC_DIR}/main.c
    ${SRC_DIR}/matrix.c
    ${SRC_DIR}/matrix_info.c
    ${SRC_DIR}/complex_num.c
    ${SRC_DIR}/io.c
)

add_executable(MatrixLab ${SOURCES})

target_include_directories(MatrixLab PRIVATE ${INCLUDE_DIR})


if(MSVC)
    target_compile_options(MatrixLab PRIVATE /W4 /WX) 
else()
    target_compile_options(MatrixLab PRIVATE -Wall -Wextra -Werror)
endif()
