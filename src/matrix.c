#include "matrix.h"
#include "stdio.h"
#include "stdlib.h"

struct Matrix {
    int rows;
    int cols;
    void** data;      
    MatrixInfo* field; 
};

Matrix* matrix_create(int rows, int cols, MatrixInfo* field) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows; 
    m->cols = cols;
    m->field = field;
    m->data = (void**)calloc(rows * cols, sizeof(void*));
    return m;
}

Matrix* matrix_multiply(Matrix* a, Matrix* b) {
    if (a->cols != b->rows || a->field != b->field) return NULL;

    Matrix* res = matrix_create(a->rows, b->cols, a->field);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            void* sum = NULL;
            for (int k = 0; k < a->cols; k++) {
                void* vA = matrix_get(a, i, k);
                void* vB = matrix_get(b, k, j);
                if (!vA || !vB) continue;

                void* prod = a->field->multiplication(vA, vB);
                if (!sum) sum = prod;
                else {
                    void* old_sum = sum;
                    sum = a->field->add(old_sum, prod);
                    free(old_sum);
                    free(prod);
                }
            }
            if (sum) {
                res->data[i * b->cols + j] = sum;
            }
        }
    }
    return res;
}

Matrix* matrix_add(Matrix* a, Matrix* b) {
    if (a->rows != b->rows || a->cols != b->cols) return NULL;

    if (a->field != b->field) {
        fprintf(stderr, "Error: Type mismatch!\n"); // это попозже в io и убрать инклююд
        return NULL;
    }

    Matrix* res = matrix_create(a->rows, a->cols, a->field);
    for (int i = 0; i < a->rows * a->cols; i++) {
        if (a->data[i] && b->data[i])
            res->data[i] = a->field->add(a->data[i], b->data[i]);
    }
    return res;
}

Matrix* matrix_transpose(Matrix* m) {
    Matrix* res = matrix_create(m->cols, m->rows, m->field);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void* val = matrix_get(m, i, j);
            if (val) {
                void* copy = malloc(m->field->size);
                memcpy(copy, val, m->field->size);
                res->data[j * m->rows + i] = copy;
            }
        }
    }
    return res;
}

int matrix_set(Matrix* m, int r, int c, void* value) {
    if (r < 0 || r >= m->rows || c < 0 || c >= m->cols) return -1;
    int idx = r * m->cols + c;
    if (m->data[idx]) free(m->data[idx]);
    m->data[idx] = malloc(m->field->size);
    memcpy(m->data[idx], value, m->field->size);
    return 0;
}

void* matrix_get(Matrix* m, int r, int c) {
    if (r < 0 || r >= m->rows || c < 0 || c >= m->cols) return NULL;
    return m->data[r * m->cols + c];
}

void matrix_free(Matrix* m) {
    for (int i = 0; i < m->rows * m->cols; i++) {
        if (m->data[i]) free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void matrix_print(Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void* val = matrix_get(m, i, j);
            if (val) m->field->print(val);
            else printf(" 0 ");
            printf(" ");
        }
        printf("\n");
    }
}