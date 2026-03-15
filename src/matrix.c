#include "matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

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

Matrix* matrix_multiply(Matrix* a, Matrix* b, ErrorCode* err) {
    if (!a || !b) {
        if (err) *err = ERROR_NULL_POINTER;
        return NULL;
    }
    if (a->field != b->field) {
        if (err) *err = ERROR_TYPE_MISMATCH;
        return NULL;
    }
    if (a->cols != b->rows) {
        if (err) *err = ERROR_DIMENSION_MISMATCH;
        return NULL;
    }

    Matrix* res = matrix_create(a->rows, b->cols, a->field);

    if (!res) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            void* sum = NULL;
            for (int k = 0; k < a->cols; k++) {
                void* vA = matrix_get(a, i, k, err);
                if (*err != SUCCESS) {
                    matrix_free(res);
                    return NULL;
                }
                void* vB = matrix_get(b, k, j, err);
                if (*err != SUCCESS) {
                    matrix_free(res);
                    return NULL;
                }
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

    if (err) *err = SUCCESS;
    return res;
}

Matrix* matrix_add(Matrix* a, Matrix* b, ErrorCode* err) {
    if (!a || !b) {
        if (err) *err = ERROR_NULL_POINTER;
        return NULL;
    }
    if (a->field != b->field) {
        if (err) *err = ERROR_TYPE_MISMATCH; 
        return NULL;
    }
    if (a->rows != b->rows || a->cols != b->cols) {
        if (err) *err = ERROR_DIMENSION_MISMATCH;
        return NULL;
    }

    Matrix* res = matrix_create(a->rows, a->cols, a->field);

    if (!res) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    for (int i = 0; i < a->rows * a->cols; i++) {
        if (a->data[i] && b->data[i])
            res->data[i] = a->field->add(a->data[i], b->data[i]);
    }
    if (err) *err = SUCCESS;
    return res;
}

Matrix* matrix_transpose(Matrix* m, ErrorCode* err) {
    if (!m) {
        if (err) *err = ERROR_NULL_POINTER;
        return NULL;
    }

    Matrix* res = matrix_create(m->cols, m->rows, m->field);

    if (!res) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void* val = matrix_get(m, i, j, err);
            if (*err != SUCCESS) {
                matrix_free(res);
                return NULL;
            }
            if (val) {
                void* copy = malloc(m->field->size);
                memcpy(copy, val, m->field->size);
                res->data[j * m->rows + i] = copy;
            }
        }
    }
    if (err) *err = SUCCESS;
    return res;
}

int matrix_set(Matrix* m, int r, int c, void* value, ErrorCode* err) {
    if (!m || !value) {
        if (err) *err = ERROR_NULL_POINTER;
        return -1;
    }
    if (r < 0 || r >= m->rows || c < 0 || c >= m->cols) {
        if (err) *err = ERROR_OUT_OF_BOUNDS;
        return -1;
    }

    int index = r * m->cols + c;

    if (m->data[index] != NULL) {
        free(m->data[index]);
    }

    m->data[index] = malloc(m->field->size);

    if (!m->data[index]) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return -1;
    }

    memcpy(m->data[index], value, m->field->size);

    if (err) *err = SUCCESS;
    return 0;
}

void* matrix_get(Matrix* m, int r, int c, ErrorCode* err) {
    if (!m) {
        if (err) *err = ERROR_NULL_POINTER;
        return NULL;
    }
    if (r < 0 || r >= m->rows || c < 0 || c >= m->cols) {
        if (err) *err = ERROR_OUT_OF_BOUNDS;
        return NULL;
    }

    if (err) *err = SUCCESS;
    return m->data[r * m->cols + c];
}

void matrix_free(Matrix* m) {
    if (!m) return;
    for (int i = 0; i < m->rows * m->cols; i++) {
        if (m->data[i]) free(m->data[i]);
    }
    free(m->data);
    free(m);
}

void matrix_print(Matrix* m, ErrorCode* err) {
    if (!m) {
        if (err) *err = ERROR_NULL_POINTER;
        return;
    }

    ErrorCode temp_err = SUCCESS;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void* val = matrix_get(m, i, j, &temp_err);
            if (temp_err != SUCCESS) {
                if (err) *err = temp_err;
                return;
            }
            if (val) m->field->print(val);
            else printf("0");
            printf(" ");
        }
        puts("");
    }
    if (err) *err = SUCCESS;
}