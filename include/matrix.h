#pragma once

#include "matrix_info.h"
#include "errors.h"

typedef struct Matrix Matrix; 

Matrix* matrix_create(int rows, int cols, MatrixInfo* field);
Matrix* matrix_multiply(Matrix* a, Matrix* b, ErrorCode* err);
Matrix* matrix_add(Matrix* a, Matrix* b, ErrorCode* err);
Matrix* matrix_transpose(Matrix* m, ErrorCode* err);
int matrix_set(Matrix* m, int r, int c, void* value, ErrorCode* err);
void* matrix_get(Matrix* m, int r, int c, ErrorCode* err);
void matrix_free(Matrix* m);
void matrix_print(Matrix* m, ErrorCode* err);