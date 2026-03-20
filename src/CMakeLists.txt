set(LIB_SOURCES
    matrix.c
    matrix_info.c
    complex_num.c
    inout.c
)

set(LIB_PUBLIC_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/matrix.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/matrix_info.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/complex_num.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/errors.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/inout.h
)

add_library(matrix_lib STATIC ${LIB_SOURCES})

if(MINGW)
    target_compile_options(matrix_lib PRIVATE -Wall -Wextra)
endif()

target_include_directories(matrix_lib 
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS matrix_lib
    EXPORT MatrixLibraryTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(FILES ${LIB_PUBLIC_HEADERS} DESTINATION include)

install(EXPORT MatrixLibraryTargets
    FILE MatrixLibraryConfig.cmake
    DESTINATION lib/cmake/MatrixLibrary
)