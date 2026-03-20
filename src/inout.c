#include "inout.h"
#include "matrix.h"
#include "complex_num.h"
#include "matrix_info.h"
#include <stdio.h>
#include <stdlib.h>

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_error(ErrorCode err) {
    switch(err) {
        case SUCCESS:
            puts("Operation successful");
            break;
        case ERROR_MEMORY_ALLOCATION:
            puts("Error: Memory allocation failed");
            break;
        case ERROR_NULL_POINTER:
            puts("Error: Null pointer encountered");
            break;
        case ERROR_DIMENSION_MISMATCH:
            puts("Error: Matrix dimensions mismatch");
            break;
        case ERROR_TYPE_MISMATCH:
            puts("Error: Matrix types mismatch");
            break;
        case ERROR_OUT_OF_BOUNDS:
            puts("Error: Index out of bounds");
            break;
        default:
            puts("Error: Unknown error");
    }
}

int type_select() {
    char c;
    while (1) {
        puts("\nSelect matrix type:");
        puts("1 - double type");
        puts("2 - complex type");
        puts("Your choice:");
        
        c = getchar();
        clear_input_buffer();
        
        if (c == '1') return 1;
        if (c == '2') return 2;
        
        puts("Wrong selection. Try again");
    }
}

int action_select() {
    char c;
    while (1) {
        puts("Select action:");
        puts("1 - create matrix");
        puts("2 - delete matrix");
        puts("3 - set element");
        puts("4 - get element");
        puts("5 - input matrix");
        puts("6 - print matrix");
        puts("7 - exit");
        puts("Your choice:");
        
        c = getchar();
        clear_input_buffer();
        
        switch (c) {
            case '1': return 1;
            case '2': return 2;
            case '3': return 3;
            case '4': return 4;
            case '5': return 5;
            case '6': return 6;
            case '7': return 7;
            default: puts("Wrong selection. Try again");
        }
    }
}

static void read_double_value(void* value) {
    double* d = (double*)value;
    printf("Enter value: ");
    scanf("%lf", d);
    clear_input_buffer();
}

static void read_complex_value(void* value) {
    Complex* c = (Complex*)value;
    puts("Enter real part: ");
    scanf("%lf", &c->real);
    puts("Enter imaginary part: ");
    scanf("%lf", &c->imag);
    clear_input_buffer();
}

static void read_value(void* value, MatrixInfo* info) {
    if (info == get_double_matrix_info()) {
        read_double_value(value);
    } else {
        read_complex_value(value);
    }
}

static Matrix* create_matrix_interface() {
    int rows, cols;
    int type = type_select();
    
    MatrixInfo* info = (type == 1) ? get_double_matrix_info() : get_complex_matrix_info();
    
    puts("Enter number of rows:");
    scanf("%d", &rows);
    puts("Enter number of columns:");
    scanf("%d", &cols);
    clear_input_buffer();
    
    ErrorCode err = SUCCESS;
    Matrix* m = matrix_create(rows, cols, info, &err);
    if (!m || err != SUCCESS) {
        puts("Failed to create matrix");
        return NULL;
    }
    
    printf("Matrix created successfully (%d x %d)\n", rows, cols);
    return m;
}

static void input_matrix_interface(Matrix* m) {
    if (!m) {
        puts("No matrix selected");
        return;
    }
    
    ErrorCode err = SUCCESS;
    void* value = malloc(matrix_get_elem_size(m));
    if (!value) {
        puts("Memory allocation failed");
        return;
    }
    
    printf("Enter matrix elements (%d x %d):\n", matrix_get_rows(m), matrix_get_cols(m));
    
    for (int i = 0; i < matrix_get_rows(m); i++) {
        for (int j = 0; j < matrix_get_cols(m); j++) {
            printf("[%d][%d] = ", i, j);
            read_value(value, matrix_get_matrix_info(m));
            matrix_set(m, i, j, value, &err);
            if (err != SUCCESS) {
                print_error(err);
                free(value);
                return;
            }
        }
    }
    
    puts("Matrix input completed");
    free(value);
}

static void set_element_interface(Matrix* m) {
    if (!m) {
        puts("No matrix selected");
        return;
    }
    
    int r, c;
    ErrorCode err = SUCCESS;
    void* value = malloc(matrix_get_elem_size(m));
    
    if (!value) {
        puts("Memory allocation failed");
        return;
    }
    
    printf("Enter row index (0-%d): ", matrix_get_rows(m) - 1);
    scanf("%d", &r);
    printf("Enter column index (0-%d): ", matrix_get_cols(m) - 1);
    scanf("%d", &c);
    clear_input_buffer();
    
    printf("Enter value:\n");
    read_value(value, matrix_get_matrix_info(m));
    
    matrix_set(m, r, c, value, &err);
    if (err != SUCCESS) puts("Element set successfully");
    else print_error(err);
    
    free(value);
}

static void get_element_interface(Matrix* m) {
    if (!m) {
        puts("No matrix selected");
        return;
    }
    
    int r, c;
    ErrorCode err = SUCCESS;
    
    printf("Enter row index (0-%d): ", matrix_get_rows(m) - 1);
    scanf("%d", &r);
    printf("Enter column index (0-%d): ", matrix_get_cols(m) - 1);
    scanf("%d", &c);
    clear_input_buffer();
    
    void* value = matrix_get(m, r, c, &err);
    
    if (value && err == SUCCESS) {
        printf("Value at [%d][%d] = ", r, c);
        matrix_print_elem(m, r, c, &err);
        puts("");
    } else {
        print_error(err);
    }
}

static void print_matrix_interface(Matrix* m) {
    if (!m) {
        puts("No matrix to print");
        return;
    }
    
    ErrorCode err = SUCCESS;
    puts("\nCurrent matrix:");
    matrix_print(m, &err);
    if (err != SUCCESS) print_error(err);
}

static void delete_matrix_interface(Matrix* m) {
    ErrorCode err = SUCCESS;
    if (m) {
        matrix_free(m, &err);
        m = NULL;
        puts("Matrix deleted");
    } 
    else puts("No matrix to delete");
}

void interface(void) {
    Matrix* current_matrix = NULL;
    ErrorCode err = SUCCESS;
    int action;
    
    while (1) {
        action = action_select();
        
        switch(action) {
            case 1: 
                if (current_matrix)  puts("Matrix already exists. Delete first");
                else current_matrix = create_matrix_interface();
                break; 
            case 2: 
                delete_matrix_interface(current_matrix);
                break;
            case 3: 
                set_element_interface(current_matrix);
                break;
            case 4: 
                get_element_interface(current_matrix);
                break;
            case 5:
                input_matrix_interface(current_matrix);
                break;
            case 6: 
                print_matrix_interface(current_matrix);
                break;
            case 7: 
                if (current_matrix) {
                    matrix_free(current_matrix, &err);
                }
                puts("Program and");
                return;
                
            default:
                puts("Invalid action");
        }
    }
}