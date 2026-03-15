#include "complex_num.h"
#include "stdlib.h"
#include "stdio.h"

Complex* c_add(const Complex* a, const Complex* b) {
    Complex* res = (Complex*)(malloc(sizeof(Complex)));
    res->real = a->real + b->real;
    res->imag = a->imag + b->imag;
    return res;
}

Complex* c_deduct(const Complex* a, const Complex* b) {
    Complex* res = (Complex*)(malloc(sizeof(Complex)));
    res->real = a->real - b->real;
    res->imag = a->imag - b->imag;
    return res;
}

Complex* c_muttiplication(const Complex* a, const Complex* b) {
    Complex* res = (Complex*)malloc(sizeof(Complex));
    res->real = a->real * b->real - a->imag * b->imag;
    res->imag = a->real * b->imag + a->imag * b->real;
    return res;
}

void c_print(const Complex* a) {
    printf("%.2f + %.2fi", a->real, a->imag);
}