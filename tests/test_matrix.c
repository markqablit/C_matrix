#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
#include "complex_num.h"
#include "matrix_info.h"
#include "errors.h"

#ifdef _WIN32
    #include <windows.h>
    #include <locale.h>
#endif


START_TEST(test_double_matrix_create) {
    MatrixInfo* info = get_double_matrix_info();
    ErrorCode err = SUCCESS;
    Matrix* m = matrix_create(3, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    ck_assert_ptr_nonnull(m);

    double val = 5.5;
    matrix_set(m, 2, 2, &val, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    double* get_result = (double*)matrix_get(m, 2, 2, &err);
    ck_assert_ptr_nonnull(get_result);
    ck_assert_double_eq(*get_result, 5.5);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_double_matrix_set_get) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* m = matrix_create(3, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);

    double value = 5.5;
    matrix_set(m, 1, 1, &value, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    double* result = (double*)matrix_get(m, 1, 1, &err);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(err, SUCCESS);
    ck_assert_double_eq(*result, 5.5);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_double_matrix_set_out_of_bounds) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* m = matrix_create(3, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);

    double value = 5.5;
    matrix_set(m, 10, 10, &value, &err);
    ck_assert_int_eq(err, ERROR_OUT_OF_BOUNDS);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_double_matrix_add) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* m1 = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    Matrix* m2 = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    double val1 = 1.0, val2 = 2.0;
    matrix_set(m1, 0, 0, &val1, &err);
    matrix_set(m1, 0, 1, &val1, &err);
    matrix_set(m1, 1, 0, &val1, &err);
    matrix_set(m1, 1, 1, &val1, &err);
    
    matrix_set(m2, 0, 0, &val2, &err);
    matrix_set(m2, 0, 1, &val2, &err);
    matrix_set(m2, 1, 0, &val2, &err);
    matrix_set(m2, 1, 1, &val2, &err);
    
    Matrix* sum = matrix_add(m1, m2, &err);
    ck_assert_ptr_nonnull(sum);
    ck_assert_int_eq(err, SUCCESS);
    
    double* res = (double*)matrix_get(sum, 0, 0, &err);
    ck_assert_double_eq(*res, 3.0);
    
    matrix_free(m1, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(m2, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(sum, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_double_matrix_multiply) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* a = matrix_create(2, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    Matrix* b = matrix_create(3, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    double val = 1.0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            val = i * 3 + j + 1.0;
            matrix_set(a, i, j, &val, &err);
        }
    }
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            val = i * 2 + j + 7.0;
            matrix_set(b, i, j, &val, &err);
        }
    }
    
    Matrix* result = matrix_multiply(a, b, &err);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(err, SUCCESS);
    
    double* res00 = (double*)matrix_get(result, 0, 0, &err);
    double* res01 = (double*)matrix_get(result, 0, 1, &err);
    double* res10 = (double*)matrix_get(result, 1, 0, &err);
    double* res11 = (double*)matrix_get(result, 1, 1, &err);
    
    ck_assert_double_eq_tol(*res00, 58.0, 0.001);
    ck_assert_double_eq_tol(*res01, 64.0, 0.001);
    ck_assert_double_eq_tol(*res10, 139.0, 0.001);
    ck_assert_double_eq_tol(*res11, 154.0, 0.001);
    
    matrix_free(a, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(b, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(result, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST


START_TEST(test_complex_matrix_create) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_complex_matrix_info();
    Matrix* m = matrix_create(3, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    ck_assert_ptr_nonnull(m);
    
    Complex val = {1.0, 2.0};
    matrix_set(m, 2, 2, &val, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Complex* get_result = (Complex*)matrix_get(m, 2, 2, &err);
    ck_assert_ptr_nonnull(get_result);
    ck_assert_double_eq(get_result->real, 1.0);
    ck_assert_double_eq(get_result->imag, 2.0);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_complex_matrix_set_get) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_complex_matrix_info();
    Matrix* m = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Complex val = {1.5, 2.5};
    matrix_set(m, 0, 0, &val, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Complex* result = (Complex*)matrix_get(m, 0, 0, &err);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(err, SUCCESS);
    ck_assert_double_eq(result->real, 1.5);
    ck_assert_double_eq(result->imag, 2.5);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_complex_matrix_add) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_complex_matrix_info();
    Matrix* m1 = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    Matrix* m2 = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Complex val1 = {1.0, 2.0};
    Complex val2 = {3.0, 4.0};
    
    matrix_set(m1, 0, 0, &val1, &err);
    matrix_set(m2, 0, 0, &val2, &err);
    
    Matrix* result = matrix_add(m1, m2, &err);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(err, SUCCESS);
    
    Complex* sum = (Complex*)matrix_get(result, 0, 0, &err);
    ck_assert_double_eq(sum->real, 4.0);
    ck_assert_double_eq(sum->imag, 6.0);
    
    matrix_free(m1, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(m2, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(result, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_complex_matrix_multiply) {
    ErrorCode err = SUCCESS;
    Complex val;
    MatrixInfo* info = get_complex_matrix_info();
    Matrix* a = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    Matrix* b = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);

    val = (Complex){1, 2}; matrix_set(a, 0, 0, &val, &err);
    val = (Complex){3, 4}; matrix_set(a, 0, 1, &val, &err);
    val = (Complex){5, 6}; matrix_set(a, 1, 0, &val, &err);
    val = (Complex){7, 8}; matrix_set(a, 1, 1, &val, &err);

    val = (Complex){9, 10}; matrix_set(b, 0, 0, &val, &err);
    val = (Complex){11, 12}; matrix_set(b, 0, 1, &val, &err);
    val = (Complex){13, 14}; matrix_set(b, 1, 0, &val, &err);
    val = (Complex){15, 16}; matrix_set(b, 1, 1, &val, &err);
    
    Matrix* result = matrix_multiply(a, b, &err);
    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(err, SUCCESS);

    Complex* res00 = (Complex*)matrix_get(result, 0, 0, &err);
    ck_assert_double_eq_tol(res00->real, -28.0, 0.001);
    ck_assert_double_eq_tol(res00->imag, 122.0, 0.001);

    Complex* res01 = (Complex*)matrix_get(result, 0, 1, &err);
    ck_assert_double_eq_tol(res01->real, -32.0, 0.001);
    ck_assert_double_eq_tol(res01->imag, 142.0, 0.001);
    
    Complex* res10 = (Complex*)matrix_get(result, 1, 0, &err);
    ck_assert_double_eq_tol(res10->real, -36.0, 0.001);
    ck_assert_double_eq_tol(res10->imag, 306.0, 0.001);
    
    Complex* res11 = (Complex*)matrix_get(result, 1, 1, &err);
    ck_assert_double_eq_tol(res11->real, -40.0, 0.001);
    ck_assert_double_eq_tol(res11->imag, 358.0, 0.001);
    
    matrix_free(a, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(b, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(result, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST


START_TEST(test_null_pointer_errors) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* m = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Matrix* result = matrix_add(NULL, m, &err);
    ck_assert_ptr_null(result);
    ck_assert_int_eq(err, ERROR_NULL_POINTER);
    
    err = SUCCESS;
    result = matrix_multiply(NULL, m, &err);
    ck_assert_ptr_null(result);
    ck_assert_int_eq(err, ERROR_NULL_POINTER);
    
    err = SUCCESS;
    void* val = matrix_get(NULL, 0, 0, &err);
    ck_assert_ptr_null(val);
    ck_assert_int_eq(err, ERROR_NULL_POINTER);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_type_mismatch) {
    ErrorCode err = SUCCESS;
    MatrixInfo* double_info = get_double_matrix_info();
    MatrixInfo* complex_info = get_complex_matrix_info();
    
    Matrix* m_double = matrix_create(2, 2, double_info, &err);
    ck_assert_int_eq(err, SUCCESS);
    Matrix* m_complex = matrix_create(2, 2, complex_info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Matrix* result = matrix_add(m_double, m_complex, &err);
    ck_assert_ptr_null(result);
    ck_assert_int_eq(err, ERROR_TYPE_MISMATCH);
    
    matrix_free(m_double, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(m_complex, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_dimension_mismatch) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* m1 = matrix_create(2, 2, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    Matrix* m2 = matrix_create(3, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    Matrix* result = matrix_add(m1, m2, &err);
    ck_assert_ptr_null(result);
    ck_assert_int_eq(err, ERROR_DIMENSION_MISMATCH);
    
    matrix_free(m1, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(m2, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST

START_TEST(test_matrix_transpose) {
    ErrorCode err = SUCCESS;
    MatrixInfo* info = get_double_matrix_info();
    Matrix* m = matrix_create(2, 3, info, &err);
    ck_assert_int_eq(err, SUCCESS);
    
    double val = 1.0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            val = i * 3 + j + 1.0;
            matrix_set(m, i, j, &val, &err);
        }
    }
    
    Matrix* transposed = matrix_transpose(m, &err);
    ck_assert_ptr_nonnull(transposed);
    ck_assert_int_eq(err, SUCCESS);
    
    double* t00 = (double*)matrix_get(transposed, 0, 0, &err);
    double* t01 = (double*)matrix_get(transposed, 0, 1, &err);
    double* t10 = (double*)matrix_get(transposed, 1, 0, &err);
    
    ck_assert_double_eq(*t00, 1.0);
    ck_assert_double_eq(*t01, 4.0);
    ck_assert_double_eq(*t10, 2.0);
    
    matrix_free(m, &err);
    ck_assert_int_eq(err, SUCCESS);
    matrix_free(transposed, &err);
    ck_assert_int_eq(err, SUCCESS);
}
END_TEST


Suite* matrix_suite(void) {
    Suite* s = suite_create("Matrix");
    
    TCase* tc_double_basic = tcase_create("Double Basic");
    tcase_add_test(tc_double_basic, test_double_matrix_create);
    tcase_add_test(tc_double_basic, test_double_matrix_set_get);
    tcase_add_test(tc_double_basic, test_double_matrix_set_out_of_bounds);
    suite_add_tcase(s, tc_double_basic);
    
    TCase* tc_double_ops = tcase_create("Double Operations");
    tcase_add_test(tc_double_ops, test_double_matrix_add);
    tcase_add_test(tc_double_ops, test_double_matrix_multiply);
    suite_add_tcase(s, tc_double_ops);
    
    TCase* tc_complex = tcase_create("Complex");
    tcase_add_test(tc_complex, test_complex_matrix_create);
    tcase_add_test(tc_complex, test_complex_matrix_set_get);
    tcase_add_test(tc_complex, test_complex_matrix_add);
    tcase_add_test(tc_complex, test_complex_matrix_multiply);
    suite_add_tcase(s, tc_complex);
    
    TCase* tc_errors = tcase_create("Errors");
    tcase_add_test(tc_errors, test_null_pointer_errors);
    tcase_add_test(tc_errors, test_type_mismatch);
    tcase_add_test(tc_errors, test_dimension_mismatch);
    suite_add_tcase(s, tc_errors);
    
    TCase* tc_extra = tcase_create("Extra");
    tcase_add_test(tc_extra, test_matrix_transpose);
    suite_add_tcase(s, tc_extra);
    
    return s;
}

int main(void) {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        setlocale(LC_ALL, "ru_RU.UTF-8");
    #endif
    
    int number_failed;
    Suite* s = matrix_suite();
    SRunner* sr = srunner_create(s);
    
    srunner_run_all(sr, CK_VERBOSE);
    
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    printf("Result: %d tests failed\n", number_failed);
    
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}