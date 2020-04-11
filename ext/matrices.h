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

Matrix *constructor(int r, int c);
int destroy_matrix(Matrix *m);
int print(Matrix *m);
Matrix *transpose(Matrix *m);
Matrix *multiply(Matrix *m1, Matrix *m2);

#ifdef __cplusplus
}
#endif

#endif /* matrices */
