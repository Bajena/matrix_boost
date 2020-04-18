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
static int matrix_row_scalar_multiply(Matrix *m, int row, float factor);

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

/* enter 1s along the main diagonal */
Matrix *matrix_identity(int length){
  unsigned int i, j;
  Matrix *m;
  m = matrix_constructor(length, length);
  for(i = 0; i < length; i++){
    j = i;
    (m->numbers[i])[j] = 1;
  }
  return m;
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

/* matrix m will become the matrix_identity so the caller must save their matrix themselves  */
Matrix *matrix_invert(Matrix *m){
  Matrix *invert;
  unsigned int i, j, l;
  double factor;
  if(m == NULL)
    return NULL;
  if((m)->columns != (m)->rows)
    return NULL;
  invert = matrix_identity((m)->rows);

  /* matrix_reduce each of the rows to get a lower triangle */
  for(i = 0; i < (m)->columns; i++){
    for(j = i + 1; j < (m)->rows; j++){
      if((m)->numbers[i][i] == 0){
        for(l=i+1; l < m->rows; l++){
          if(m->numbers[l][l] != 0){
            matrix_row_swap(m, i, l);
            break;
          }
        }
        continue;
      }
      factor = (m)->numbers[i][j]/((m)->numbers[i][i]);
      matrix_reduce(invert, i, j, factor);
      matrix_reduce((m), i, j, factor);
    }
  }
  /* now finish the upper triangle  */
  for(i = (m)->columns - 1; i > 0; i--){
    for(j = i-1; j>=0; j--){
      if((m)->numbers[i][i] == 0)
        continue;
      if(j == -1)
        break;
      factor = (m)->numbers[i][j]/((m)->numbers[i][i]);
      matrix_reduce(invert, i, j, factor);
      matrix_reduce((m), i, j, factor);
    }
  }
  /* scale everything to 1 */
  for(i = 0; i < (m)->columns; i++){
    if((m)->numbers[i][i]==0)
      continue;
    factor = 1/((m)->numbers[i][i]);
    matrix_row_scalar_multiply(invert, i, factor);
    matrix_row_scalar_multiply((m), i, factor);
  }
  return invert;
}

int matrix_row_swap(Matrix *m, int a, int b){
  double temp;
  unsigned int i;
  if(m == NULL)
    return FAIL;
  if(m->rows <= a || m->rows <= b)
    return FAIL;
  for(i = 0; i < m->columns; i++){
    temp = m->numbers[i][a];
    m->numbers[i][a] = m->numbers[i][b];
    m->numbers[i][b] = temp;
  }
  return SUCC;
}

static int matrix_row_scalar_multiply(Matrix *m, int row, float factor){
  int i;
  if(m == NULL)
    return FAIL;
  if(m->rows <= row)
    return FAIL;
  for(i = 0; i < m->columns; i++)
    m->numbers[i][row] *= factor;
  return SUCC;
}

/* matrix_reduce row b by factor*a  */
int matrix_reduce(Matrix *m, int a, int b, float factor){
  int i;
  if(m == NULL)
    return FAIL;
  if(m->rows < a || m->rows < b)
    return FAIL;
  for(i = 0; i < m->columns; i++){
    m->numbers[i][b]  -= m->numbers[i][a]*factor;
  }

  return SUCC;
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

