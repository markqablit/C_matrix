#include "complex_num.h"
#include "stdlib.h"

Complex* complex_add(const Complex* a, const Complex* b) {
    Complex* res = (Complex*)(malloc(sizeof(Complex)));
    res->real = a->real + b->real;
    res->imag = a->imag + b->imag;
    return res;
}

Complex* complex_deduct(const Complex* a, const Complex* b) {
    Complex* res = (Complex*)(malloc(sizeof(Complex)));
    res->real = a->real - b->real;
    res->imag = a->imag - b->imag;
    return res;
}