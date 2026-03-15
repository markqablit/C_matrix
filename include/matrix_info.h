#pragma once

#include "stdint.h"

typedef struct MatrixInfo {
    size_t size;
    void* (*add)(const void*, const void*);
    void* (*deduct)(const void*, const void*);
    void* (*multiplication)(const void*, const void*);
    void (*print)(const void*);
} MatrixInfo;

MatrixInfo* get_double_matrix_info();
MatrixInfo* get_complex_matrix_info();