#include "matrix.h"
#include "stdio.h"

struct Matrix {
    int rows;
    int cols;
    void** data;      
    MatrixInfo* field; 
};

Matrix* Matrix_Add(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;

    if (a->field != b->field) {
        fprintf(stderr, "Error: Type mismatch!\n"); // это попозже в io и убрать инклююд
        return NULL;
    }
}