#pragma once

typedef struct {
    double real;
    double imag;
} Complex;

Complex* c_add(const Complex* a, const Complex* b);
Complex* c_deduct(const Complex* a, const Complex* b);
Complex* c_muttiplication(const Complex* a, const Complex* b);
void c_print(const void* a);