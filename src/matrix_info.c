#include "matrix_info.h"
#include "complex_num.h"
#include "stdlib.h"
#include "stdio.h"


static void* double_add(const void* a, const void* b) {
    double* res = (double*)(malloc(sizeof(double)));
    *res = *(double*)a + *(double*)b;
    return res;
}

static void* double_deduct(const void* a, const void* b) {
    double* res = (double*)(malloc(sizeof(double)));
    *res = *(double*)a - *(double*)b;
    return res;
}

static void* double_multiplication(const void* a, const void* b) {
    double* res = (double*)(malloc(sizeof(double)));
    *res = *(double*)a * *(double*)b;
    return res;
}

static void double_print(const void* a) { printf("%f.2", *(double*)a); }

MatrixInfo* GetIntFieldInfo() {
    static MatrixInfo* setup = NULL;
    if (!setup) {
        setup = (MatrixInfo*)(malloc(sizeof(MatrixInfo)));
        setup->size = sizeof(double);
        setup->add = double_add;
        setup->deduct = double_deduct;
        setup->multiplication = double_multiplication;
        setup->print = double_print;
    }
    return setup;
}

static void* complex_add(const void* a, const void* b) {
    const Complex *c1 = (Complex*)a, *c2 = (Complex*)b;
    Complex* res = c_add(c1, c2);
    return res;
}

static void* complex_deduct(const void* a, const void* b) {
    const Complex *c1 = (Complex*)a, *c2 = (Complex*)b;
    Complex* res = c_deduct(c1, c2);
    return res;
}

static void* complex_muttiplication(const void* a, const void* b) {
    const Complex *c1 = (Complex*)a, *c2 = (Complex*)b;
    Complex* res = c_muttiplication(c1, c2);
    return res;
}

static void complex_print(const void* a) {
    Complex* c = (Complex*)a;
    c_print(c);
}

MatrixInfo* GetComplexFieldInfo() {
    static MatrixInfo* setup = NULL;
    if (!setup){
        setup = (MatrixInfo*)(malloc(sizeof(MatrixInfo)));
        setup->size = sizeof(Complex);
        setup->add = complex_add;
        setup->deduct = complex_deduct;
        setup->multiplication = complex_muttiplication;
        setup->print = complex_print;
    }
    return setup;
}