#include "matrix.h"
#include "errors.h"
#include "complex_num.h"
#include "matrix_info.h"
#include "stdio.h"

int main() {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_complex_matrix_info();
    Matrix* m = matrix_create(3, 5, info); 

    Complex val = {1.0, 2.0};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            val.real = i + 1.0;
            val.imag = j + 1.0;
            matrix_set(m, i, j, &val, &err);
            if (err != SUCCESS){
                printf("ERROR at [%d,%d]: %d\n", i, j, err);
                err = SUCCESS;  
            }
        }
    }
    
    err = SUCCESS;
    matrix_print(m, &err);
    
    matrix_free(m);
    
    while (1)
    {
        int a = 0;
        scanf_s("%d", &a);
    }

    return 0;
}
// int main() {
//     ErrorCode err = SUCCESS;
//     MatrixInfo* info = get_complex_matrix_info();
//     Matrix* m = matrix_create(3, 5, info); 

//     Complex val = {1.0, 2.0};
    
//     matrix_set(m, 10, 0, &val, &err);

//     if (err == ERROR_OUT_OF_BOUNDS) {
//         puts("Error: Index out of bounds");
//         err = SUCCESS;
//         matrix_print(m, &err);
//     }
//     matrix_print(m, &err);
//     matrix_free(m);
//     while (1)
//     {
//         int a = 0;
//         scanf_s("%d", &a);
//     }
    
//     return 0;
// }