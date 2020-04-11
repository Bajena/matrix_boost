#include "ruby/ruby.h"
#include "ruby/encoding.h"
#include "matrices.h"

void print_obj(VALUE o) {
  VALUE os = rb_funcall(o, rb_intern("to_s"), 0);
  puts(StringValuePtr(os));
}

VALUE matrix_to_rb_array(Matrix *matrix) {
  VALUE result = rb_ary_new();
  int row;
  int column;

  for (row = 0; row < matrix->rows; row++) {
    VALUE rb_row = rb_ary_new();
    rb_ary_push(result, rb_row);
    for (column = 0; column < matrix->columns; column++) {
      rb_ary_push(rb_row, DBL2NUM((matrix->numbers)[column][row]));
    }
  }

  return result;
}

Matrix* rb_array_to_matrix(VALUE a) {
  long rows = RARRAY_LEN(a);
  VALUE first_row = rb_ary_entry(a, 0);
  Check_Type(first_row, T_ARRAY);
  long columns = RARRAY_LEN(first_row);

  Matrix *matrix = constructor(rows, columns);
  int row;
  int column;

  for (row = 0; row < rows; row++) {
    VALUE rb_row = rb_ary_entry(a, row);
    for (column = 0; column < columns; column++) {
      VALUE rb_row = rb_ary_entry(a, row);
      (matrix->numbers)[column][row] = NUM2DBL(rb_ary_entry(rb_row, column));
    }
  }

  return matrix;
}

static VALUE mul_matrix(VALUE self, VALUE m1, VALUE m2) {
  Check_Type(m1, T_ARRAY);
  Check_Type(m2, T_ARRAY);

  Matrix *m1c = rb_array_to_matrix(m1);
  Matrix *m2c = rb_array_to_matrix(m2);

  Matrix *multiplied = multiply(m1c, m2c);

  destroy_matrix(m1c);
  destroy_matrix(m2c);

  if (multiplied) {
    VALUE result = matrix_to_rb_array(multiplied);
    destroy_matrix(multiplied);
    return result;
  } else {
    return Qnil;
  }
}

void Init_extension(void) {
  VALUE MatrixBoost = rb_define_module("MatrixBoost");
  VALUE NativeHelpers = rb_define_class_under(MatrixBoost, "NativeHelpers", rb_cObject);
  rb_define_singleton_method(NativeHelpers, "mul_matrix", mul_matrix, 2);
}
