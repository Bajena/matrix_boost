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
int matrix_destroy(Matrix *m);
int matrix_print(Matrix *m);
Matrix *matrix_transpose(Matrix *m);
Matrix *matrix_multiply(Matrix *m1, Matrix *m2);

#ifdef __cplusplus
}
#endif

#endif /* matrices */
