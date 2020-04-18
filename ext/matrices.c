#include<math.h>
#include<stdlib.h>
#include"matrices.h"
#include<stdio.h>
#include<time.h>

#define SUCC 1
#define FAIL -1
/*
* This library was originaly posted at https://github.com/nhomble/yasML
*
* A matrix is
    columns
  pointer   .   .   .   .
rows    |
    |
    V
    .
    .
    .
the matrix is an array of array pointers where each array pointer corresponds to a vector
*/

static double matrix_vector_multiply(double *col, double *row, int length);

/* make a zero matrix of given dimensions */
Matrix *matrix_constructor(int r, int c){
  unsigned int i;
  Matrix *m;
  if(r <= 0 || c <= 0){
    perror("Give me positive values for dimensions genius");
    return NULL;
  }
  m = malloc(sizeof(Matrix));
  m->rows = r;
  m->columns = c;
  m->numbers = malloc(sizeof(double *)*c);
  for(i = 0; i < c; i++)
    m->numbers[i] = calloc(sizeof(double), r);
  return m;
}

/* free memory associated with the matrix  */
int matrix_destroy(Matrix *m){
  unsigned int i;
  if(m == NULL)
    return FAIL;
  for(i = 0; i < m->columns; i++)
    free(m->numbers[i]);
  free(m->numbers);
  free(m);
  return SUCC;
}

/* print the matrix  */
int matrix_print(Matrix *m){
  unsigned int i, j;
  if(m == NULL)
    return FAIL;
  for(i = 0; i < m->rows; i++){
    for(j = 0; j < m->columns; j++){
      printf("%f ", m->numbers[j][i]);
    }
    printf("\n");
  }
  return SUCC;
}

Matrix *matrix_transpose(Matrix *m){
  Matrix *trans;
  unsigned int i, j;
  if(m == NULL)
    return NULL;
  trans = matrix_constructor(m->columns, m->rows);
  for(i = 0; i < trans->columns; i++){
    for(j = 0; j < trans->rows; j++)
      trans->numbers[i][j] = m->numbers[j][i];
  }
  return trans;
}

/* m1 x m2  */
Matrix *matrix_multiply(Matrix *m1, Matrix *m2){
  Matrix *product, *trans;
  unsigned int i, j;
  if(m1 == NULL || m2 == NULL)
    return NULL;
  if(m1->columns != m2->rows)
    return NULL;
  trans = matrix_transpose(m1);
  product = matrix_constructor(m1->rows, m2->columns);
  for(i = 0; i < product->columns; i++){
    for(j = 0; j < product->rows; j++){
      product->numbers[i][j] = matrix_vector_multiply(trans->numbers[j], m2->numbers[i], m2->rows);
    }
  }
  matrix_destroy(trans);
  return product;
}

/* v1 x v2  -- simply a helper function -- computes dot product between two vectors*/
static double matrix_vector_multiply(double *col, double *row, int length){
  double sum;
  unsigned int i;
  sum = 0;
  for(i = 0; i < length; i++){
    sum += col[i] * row[i];
  }
  return sum;
}

