#include "matrix.h"
#include "errors.h"
#include "complex_num.h"
#include "matrix_info.h"
#include "stdio.h"



int main() {
    ErrorCode* err = SUCCESS;
    MatrixInfo* info = get_complex_matrix_info();
    Matrix* m = matrix_create(3, 5, info); 

    Complex val = {1.0, 2.0};
    
    matrix_set(m, 10, 0, &val, err);

    if (*err == ERROR_OUT_OF_BOUNDS) {
        matrix_print(m, err);
    }

    matrix_free(m);
    while (1)
    {
        int a = 0;
        scanf_s("%d", &a);
    }
    
    return 0;
}