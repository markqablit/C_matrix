#pragma once

#include "matrix_info.h"

typedef struct Matrix Matrix; 

Matrix* matrix_create(int rows, int cols, MatrixInfo* field);
Matrix* Matrix_Add(Matrix* a, Matrix* b);
void matrix_free(Matrix* m);
void* matrix_get(Matrix* m, int r, int c);