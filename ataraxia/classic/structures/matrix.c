#include <stdio.h>
#include <stdlib.h>

struct _Matrix {
    double *raw;
    int m;
    int n;
} typedef Matrix;

Matrix *matrix_init(int m, int n);
double matrix_get(Matrix *, int i, int j);
int matrix_set(Matrix *matrix, int i, int j, double value);
Matrix *matrix_sum(Matrix *a, Matrix *b);
Matrix *matrix_mul(Matrix *a, Matrix *b);
Matrix *matrix_scalar_mul(Matrix *a, double t);
Matrix *matrix_zeros(int m, int n);
Matrix *matrix_init_raw(int m, int n, double raw[]);
void display_matrix(Matrix *matrix);
int matrix_equals(Matrix *a, Matrix *b);

void display_matrix(Matrix *matrix) {
    for (int i=0; i<matrix->m; i++) {
        for (int j=0; j<matrix->n; j++) {
            printf("%f\t", matrix_get(matrix, i, j));
        }
        printf("\n");
    }
    printf("\n");
}

Matrix *matrix_init(int m, int n) {
    Matrix *matrix;
    double *raw;
    matrix = (Matrix *)malloc(sizeof(Matrix));
    raw = (double *)malloc((m*n)*sizeof(double));
    
    matrix->raw = raw;
    matrix->m = m;
    matrix->n = n;
    return matrix;
}

Matrix *matrix_zeros(int m, int n) {
    Matrix *matrix;
    matrix = matrix_init(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix_set(matrix, i, j, 0);
        }
    }

    return matrix;
}

double matrix_get(Matrix *matrix, int i, int j) {
    return matrix->raw[i*matrix->n + j]; 
} 

int matrix_set(Matrix *matrix, int i, int j, double value) {
    matrix->raw[i*matrix->n + j] = value;
    return 0;
}

Matrix *matrix_sum(Matrix *a, Matrix *b) {
    Matrix *c;
    c = matrix_init(b->m, b->n);
    for (int i=0; i<a->m; i++) {
        for (int j=0; j<a->n; j++) {
            matrix_set(c, i, j, matrix_get(a, i, j)+matrix_get(b, i, j));
        }
    }
    return c;
}

Matrix *matrix_scalar_mul(Matrix *a, double t) {
    Matrix *c;
    c = matrix_init(a->m, a->n);
    for (int i=0; i<a->m; i++) {
        for (int j=0; j<a->n; j++) {
            matrix_set(c, i, j, t*matrix_get(a, i, j));
        }
    }
    return c;
}

Matrix *matrix_init_raw(int m, int n, double raw[]) {
    Matrix *matrix;
    matrix = matrix_init(m, n);
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            matrix_set(matrix, i, j, raw[i*n+j]);
        }
    }
    return matrix;
}

Matrix *matrix_mul(Matrix *a, Matrix *b) {
    Matrix *c;
    double d;
    int n, m, l;
    if (a->n != b->m) {
        return 0;
    }
    m = a->m;
    n = a->n;
    l = b->n;
    c = matrix_init(m, l);
    for (int i=0; i<m; i++) {
        for (int j=0; j<l; j++) {
            d = 0;
            for (int k=0; k<n; k++) {
                d += matrix_get(a, i, k)*matrix_get(b, k, j);
            }
            matrix_set(c, i, j, d);
        }
    }
    return c;
}

int matrix_equals(Matrix *a, Matrix *b) {
    double e = 0.000001;
    if (a->m != b->m || a->n != b->n) {
        return 0;
    }
    for (int i=0; i<a->m; i++) {
        for (int j=0; j<a->n; j++) {
            if (matrix_get(a, i, j)-matrix_get(b, i, j) > e) {
                return 0;
            }
        }
    }

    return 1;
}

int matrix_free(Matrix *a) {
    free(a->raw);
    free(a);
    return 0;
}
