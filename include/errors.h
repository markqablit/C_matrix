#pragma once

typedef enum {
    SUCCESS = 0,
    ERROR_MEMORY_ALLOCATION,    
    ERROR_NULL_POINTER,        
    ERROR_DIMENSION_MISMATCH,    
    ERROR_TYPE_MISMATCH,        
    ERROR_OUT_OF_BOUNDS        
} ErrorCode;