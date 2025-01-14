#include <stdio.h>
#include "../ataraxia/classic/structures/matrix.h"

void test_matrix_all();
int test_matrix_init();
int test_matrix_add();

int test_matrix_set_get() {
    Matrix *matrix;
    int n, m, ac;
    n = 3;
    m = 3;
    ac = 0;

    matrix = matrix_init(m, n);
    ac += matrix_set(matrix, 1, 1, 5);
    ac += !(matrix_get(matrix, 1, 1)==5);

    matrix_free(matrix);

    return ac; 
}

int test_matrix_init() {
    Matrix *matrix;
    int n, m, ac;
    ac = 0;
    n = 3;
    m = 3;

    matrix = matrix_init(m, n);

    ac += !(matrix->m == m) + !(matrix->n == n);
    matrix_free(matrix);

    return ac;
}

int test_matrix_zeros() {
    Matrix *a;
    int ac, m, n;
    m = 2;
    n = 3;
    ac = 0;

    a = matrix_zeros(m, n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            ac += !(matrix_get(a, i, j) == 0);
        }
    }
    ac += !(a->n == n);
    ac += !(a->m == m);

    matrix_free(a);

    return ac;
}

int test_matrix_add() {
    Matrix *a, *b, *c; 
    int m, n;
    m = 2;
    n = 3;
    a = matrix_zeros(m, n);
    b = matrix_init(m, n);
    for (int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            matrix_set(b, i, j, i+j);
        }
    }

    c = matrix_sum(a, b);

    for (int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if (!(matrix_get(c, i, j) == i+j)) {
                return 1;
            }
        }
    }

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);

    return 0;
}

int test_matrix_init_raw() {
    Matrix *a;
    int m, n, ac, c;
    ac = 0;
    double raw[] = {1, 2, 3, 4, 5, 6};
    m = 2;
    n = 3;
    a = matrix_init_raw(m, n, raw);
    c = 1;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            ac += !(matrix_get(a, i, j) == c++);
        }
    }

    matrix_free(a);

    return ac;
}

int main() {
    test_matrix_all();
}

int test_matrix_scalar_mul() {
    Matrix *a; 
    int m, n, ac;
    double raw[] = {1, 2, 3, 4, 5, 6};
    ac = 0;
    m = 2;
    n = 3;
    a = matrix_init_raw(m, n, raw);
    a = matrix_scalar_mul(a, -1);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            ac += !(matrix_get(a, i, j) == -1*raw[i*n+j]);
        }
    }

    matrix_free(a);

    return ac;
}

int test_matrix_mul() {
    Matrix *a, *b, *c, *d;
    int m, n, k, ac;
    ac = 0;

    double raw_a[] = {1, 2, 3, 4, 5, 6};
    double raw_b[] = {3, 4, 2, 5, 3, 1};
    double raw_d[] = {13, 10, 4, 29, 24, 10, 45, 38, 16};
    m = 3;
    n = 2;
    k = 3;

    a = matrix_init_raw(m, n, raw_a);
    b = matrix_init_raw(n, k, raw_b);
    d = matrix_init_raw(m, k, raw_d);

    c = matrix_mul(a, b);

    ac += !(matrix_equals(c, d));

    matrix_free(a);
    matrix_free(b);
    matrix_free(c);
    matrix_free(d);
    
    return ac;
}

int test_matrix_equals() {
    Matrix *a, *b;
    int m, n, ac;
    ac = 0;
    m = 2;
    n = 2;

    double raw_a[] = {1, 2, 3, 4};
    double raw_b[] = {1, 2, 3, 4};

    a = matrix_init_raw(m, n, raw_a);
    b = matrix_init_raw(m, n, raw_b);

    ac += !matrix_equals(a, b);

    matrix_free(a);
    matrix_free(b);
    return ac;
}

int test_matrix_equals_bad_dimentions() {
    Matrix *a, *b;
    int m, n, v, u, ac;
    ac = 0;
    m = 1;
    n = 4;
    v = 2;
    u = 2;

    double raw_a[] = {1, 2, 3, 4};
    double raw_b[] = {1, 2, 3, 4};

    a = matrix_init_raw(m, n, raw_a);
    b = matrix_init_raw(v, u, raw_b);

    ac += matrix_equals(a, b);

    matrix_free(a);
    matrix_free(b);
    return ac;
}

int test_matrix_equals_not_equal() {
    Matrix *a, *b;
    int m, n, v, u, ac;
    ac = 0;
    m = 1;
    n = 4;

    double raw_a[] = {1, 2, 4, 4};
    double raw_b[] = {1, 2, 3, 4};

    a = matrix_init_raw(m, n, raw_a);
    b = matrix_init_raw(m, n, raw_b);

    ac += matrix_equals(a, b);

    matrix_free(a);
    matrix_free(b);
    return ac;
}

void test_is_okey(char *text) {
    printf("\033[32m%s is okey\033[0m\n", text);
    fflush(stdout);
}

void test_is_fucked(char *text) {
    printf("\033[31m%s is fucked\033[0m\n", text);
    fflush(stdout);
}
void test_check(char *name, int (test)(void)) {
    if (test()) {
        test_is_fucked(name);
    } else {
        test_is_okey(name);
    }
}

void test_matrix_all() {
    test_check("matrix-init", test_matrix_init);
    test_check("matrix-set-get", test_matrix_set_get);
    test_check("matrix-add", test_matrix_add);
    test_check("matrix_zeros", test_matrix_zeros);
    test_check("matrix_init_raw", test_matrix_init_raw);
    test_check("matrix-scalar-mul", test_matrix_scalar_mul);
    test_check("matrix-mul", test_matrix_mul);
    test_check("matrix-equals", test_matrix_equals);
    test_check("matrix-equals-bad-dimentions", test_matrix_equals_bad_dimentions);
    test_check("matrix-equals-not-equal", test_matrix_equals_not_equal);
}
