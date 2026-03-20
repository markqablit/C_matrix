find_package(PkgConfig REQUIRED)

if(MINGW)
    set(ENV{PKG_CONFIG_PATH} "C:/msys64/mingw64/bin;$ENV{PKG_CONFIG_PATH}")
    set(ENV{PKG_CONFIG_PATH} "C:/msys32/mingw32/bin;$ENV{PKG_CONFIG_PATH}")
endif()

pkg_check_modules(CHECK REQUIRED check)

add_executable(matrix_test test_matrix.c)

if(MINGW)
    target_compile_options(matrix_test PRIVATE -Wall -Wextra)
    target_link_libraries(matrix_test PRIVATE matrix_lib ${CHECK_LIBRARIES} pthread)
    
    file(GLOB CHECK_DLL_FILES "${CHECK_LIBRARY_DIRS}/../bin/libcheck*.dll")
    
else()
    target_link_libraries(matrix_test PRIVATE matrix_lib ${CHECK_LIBRARIES})
endif()

target_include_directories(matrix_test PRIVATE ${CHECK_INCLUDE_DIRS})
target_compile_options(matrix_test PRIVATE ${CHECK_CFLAGS_OTHER})
add_test(NAME MatrixTest COMMAND matrix_test)