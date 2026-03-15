#include "matrix.h"
#include "matrix_info.h"



int main() {
    MatrixInfo* doubleType = GetDoubleFieldInfo();
    Matrix* m = matrix_create(2, 2, doubleType);
    int val = 5;
    matrix_set(m, 0, 0, &val);
    

    matrix_print(m);
    matrix_free(m);
    return 0;
}