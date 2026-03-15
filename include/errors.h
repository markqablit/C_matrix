#pragma once

typedef enum {
    SUCCESS = 0,
    ERROR_MEMORY_ALLOCATION,    // Ошибка выделения памяти
    ERROR_NULL_POINTER,         // Передан NULL указатель
    ERROR_DIMENSION_MISMATCH,    // Несоответствие размеров матриц (для сложения/умножения) [cite: 13]
    ERROR_TYPE_MISMATCH,        // Попытка сложить разные типы (int и complex) [cite: 83, 90]
    ERROR_OUT_OF_BOUNDS         // Выход за границы индекса
} ErrorCode;