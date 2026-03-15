#pragma once

#include "matrix_info.h"

typedef struct Matrix Matrix; 

Matrix* matrix_create(int rows, int cols, MatrixInfo* field);
Matrix* matrix_multiply(Matrix* a, Matrix* b);
Matrix* matrix_add(Matrix* a, Matrix* b);
Matrix* matrix_transpose(Matrix* m);
int matrix_set(Matrix* m, int r, int c, void* value);
void* matrix_get(Matrix* m, int r, int c);
void matrix_free(Matrix* m);
void matrix_print(Matrix* m);