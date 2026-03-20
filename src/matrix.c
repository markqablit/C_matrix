#include "matrix.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct Matrix {
    int rows;
    int cols;
    void* data;      
    MatrixInfo* field; 
};

int matrix_get_elem_size(Matrix * m){
    if(!m || !m->field){
        return -1;
    }
    return m->field->size;
}

MatrixInfo* matrix_get_matrix_info(Matrix* m){
    if(!m || !m->field){
        return NULL;
    }
    return m->field;
}

int matrix_get_rows(Matrix * m){
    if(!m ){
        return -1;
    }
    return m->rows;
}

int matrix_get_cols(Matrix * m){
    if(!m){
        return -1;
    }
    return m->cols;
}

Matrix* matrix_create(int rows, int cols, MatrixInfo* field, ErrorCode* err) {
    Matrix* m = (Matrix*)malloc(sizeof(Matrix));
    m->rows = rows; 
    m->cols = cols;
    m->field = field;
    m->data = calloc(rows * cols, field->size);

    if (!m) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        free(m);
        return NULL;
    }

    if (err) *err = SUCCESS;
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

    Matrix* res = matrix_create(a->rows, b->cols, a->field, err);

    if (err == NULL || *err != SUCCESS){
        return NULL;
    }
    if (!res) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    size_t size = a->field->size;
    char* a_data = (char*)a->data;
    char* b_data = (char*)b->data;
    char* res_data = (char*)res->data;

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            void* sum = NULL;
            for (int k = 0; k < a->cols; k++) {
                void* vA = a_data + (i * a->cols + k) * size;
                void* vB = b_data + (k * b->cols + j) * size;

                void* prod = a->field->multiplication(vA, vB);
                
                if (!sum) {
                    sum = prod;
                } else {
                    void* old_sum = sum;
                    sum = a->field->add(old_sum, prod);
                    free(old_sum);
                    free(prod);
                }
            }
            if (sum) {
                memcpy(res_data + (i * b->cols + j) * size, sum, size);
                free(sum);
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

    Matrix* res = matrix_create(a->rows, a->cols, a->field, err);


    if (*err != SUCCESS) return NULL;
    if (!res) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    char* a_data = (char*)a->data;
    char* b_data = (char*)b->data;
    char* res_data = (char*)res->data;
    size_t size = a->field->size;

    for (int i = 0; i < a->rows * a->cols; i++) {
        void* sum = a->field->add(a_data + i * size, b_data + i * size);
        memcpy(res_data + i * size, sum, size);
        free(sum);
    }

    if (err) *err = SUCCESS;
    return res;
}

Matrix* matrix_transpose(Matrix* m, ErrorCode* err) {
    if (!m) {
        if (err) *err = ERROR_NULL_POINTER;
        return NULL;
    }

    Matrix* res = matrix_create(m->cols, m->rows, m->field, err);


    if (*err != SUCCESS) return NULL;
    if (!res) {
        if (err) *err = ERROR_MEMORY_ALLOCATION;
        return NULL;
    }

    size_t size = m->field->size;
    char* src_data = (char*)m->data;
    char* targer_data = (char*)res->data;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void* src = src_data + (i * m->cols + j) * size;
            void* targer = targer_data + (j * m->rows + i) * size;
            memcpy(targer, src, size);
        }
    }

    if (err) *err = SUCCESS;
    return res;
}

void matrix_set(Matrix* m, int r, int c, void* value, ErrorCode* err) {
    if (!m || !value) {
        if (err) *err = ERROR_NULL_POINTER;
        return;
    }
    if (r < 0 || r >= m->rows || c < 0 || c >= m->cols) {
        if (err) *err = ERROR_OUT_OF_BOUNDS;
        return;
    }

    char* data_ptr = (char*)m->data;
    void* target = data_ptr + (r * m->cols + c) * m->field->size;
    
    memcpy(target, value, m->field->size);

    if (err) *err = SUCCESS;
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

    char* data_ptr = (char*)m->data;
    return data_ptr + (r * m->cols + c) * m->field->size;
}

void matrix_free(Matrix* m, ErrorCode* err) {
    if (!m){
        if (err) *err = ERROR_NULL_POINTER;
        return;
    } 
    free(m->data);
    free(m);
    if (err) *err = SUCCESS;
}

void matrix_print(Matrix* m, ErrorCode* err) {
    if (!m) {
        if (err) *err = ERROR_NULL_POINTER;
        return;
    }
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            void* val = matrix_get(m, i, j, err);
            if (*err != SUCCESS) {
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


void matrix_print_elem(Matrix* m, int r, int c, ErrorCode* err){
    if (!m) {
        if (err) *err = ERROR_NULL_POINTER;
        return;
    }

    if (r < 0 || r >= m->rows || c < 0 || c >= m->cols) {
        if (err) *err = ERROR_OUT_OF_BOUNDS;
        return;
    }

    if (err) *err = SUCCESS;

    char* data_ptr = (char*)m->data;
    m->field->print(data_ptr + (r * m->cols + c) * m->field->size);
}