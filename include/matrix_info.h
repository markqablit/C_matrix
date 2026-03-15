#pragma once

#include "stdint.h"

typedef struct MatrixInfo {
    size_t size;
    void* (*add)(const void*, const void*);
    void* (*multiplication)(const void*, const void*);
    void (*print)(const void*);
} MatrixInfo;

MatrixInfo* GetDoubleFieldInfo();
MatrixInfo* GetComplexFieldInfo();