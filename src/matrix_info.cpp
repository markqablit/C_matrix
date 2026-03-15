#include "matrix_info.h"
#include "stdlib.h"

static MatrixInfo* INT_FIELD_INFO = NULL; 

MatrixInfo* GetDoubleFieldInfo() {
    if (INT_FIELD_INFO == NULL) { 
        INT_FIELD_INFO = (MatrixInfo*)(malloc(sizeof(MatrixInfo)));
        INT_FIELD_INFO->size = sizeof(double);
        //INT_FIELD_INFO->add = int_add_func; тут типо функция под каждый тип
    }
    return INT_FIELD_INFO; 
}