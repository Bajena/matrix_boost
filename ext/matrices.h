#ifndef matrices_h
#define matrices_h

#ifdef __cplusplus
extern "C" {
#endif

/* current representation of a matrix in my mind  */
typedef struct Matrix{
  int rows;
  int columns;
  double **numbers;
} Matrix;

Matrix *matrix_constructor(int r, int c);
Matrix *matrix_identity(int length);
int matrix_destroy(Matrix *m);
int matrix_print(Matrix *m);
Matrix *matrix_transpose(Matrix *m);
Matrix *matrix_multiply(Matrix *m1, Matrix *m2);
Matrix *matrix_invert(Matrix *m);
int matrix_reduce(Matrix *m, int a, int b, float factor);
int matrix_row_swap(Matrix *m, int a, int b);

#ifdef __cplusplus
}
#endif

#endif /* matrices */
