#pragma once

typedef struct {
    double real;
    double imag;
} Complex;

Complex* complex_add(const Complex* a, const Complex* b);
Complex* complex_deduct(const Complex* a, const Complex* b);