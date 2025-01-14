#ifndef MATRIX_H

struct _Matrix {
    double **data;
    int m;
    int n;
} typedef Matrix;

Matrix *matrix_init(int n, int m);
double matrix_get(Matrix *, int i, int j);
int matrix_set(Matrix *matrix, int i, int j, double value);
Matrix *matrix_sum(Matrix *a, Matrix *b);
Matrix *matrix_mul(Matrix *a, Matrix *b);
Matrix *matrix_scalar_mul(Matrix *a, double t);
Matrix *matrix_zeros(int m, int n);
void display_matrix(Matrix *matrix);
Matrix *matrix_init_raw(int m, int n, double raw[]);
int matrix_equals(Matrix *a, Matrix *b);
int matrix_free(Matrix *a);

#endif
