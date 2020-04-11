#include "ruby/ruby.h"
#include "ruby/encoding.h"
#include "library.h"
#include "matrices.h"

static VALUE string(VALUE self, VALUE value) {
  Check_Type(value, T_STRING);

  char* pointer_in = RSTRING_PTR(value);
  char* pointer_out = string_from_library(pointer_in);
  return rb_str_new2(pointer_out);
}

static VALUE number(VALUE self, VALUE value) {
  Check_Type(value, T_FIXNUM);

  int number_in = NUM2INT(value);
  int number_out = number_from_library(number_in);
  return INT2NUM(number_out);
}

static VALUE boolean(VALUE self, VALUE value) {
  int boolean_in = RTEST(value);
  int boolean_out = boolean_from_library(boolean_in);
  if (boolean_out == 1) {
    return Qtrue;
  } else {
    return Qfalse;
  }
}

void print_obj(VALUE o) {
  VALUE os = rb_funcall(o, rb_intern("to_s"), 0);
  puts(StringValuePtr(os));
}

// double* rb_array_to_c_array(VALUE a) {
//   VALUE l = RARRAY_LEN(a);
//   double *result = ALLOC_N(double, l);
//   int i;

//   for (i = 0; i < l; i++) {
//     result[i] = rb_ary_entry(a, i);
//   }

//   return result;
// }

// VALUE c_array_to_rb_array(double *a) {
//   VALUE l = RARRAY_LEN(a);
//   double *result = ALLOC_N(double, l);
//   int i;

//   for (i = 0; i < l; i++) {
//     result[i] = rb_ary_entry(a, i);
//   }

//   return result;
// }

VALUE matrix_to_rb_array(Matrix *matrix) {
  VALUE result = rb_ary_new();
  int row;
  int column;

  for (row = 0; row < matrix->rows; row++) {
    VALUE rb_row = rb_ary_new();
    rb_ary_push(result, rb_row);
    for (column = 0; column < matrix->columns; column++) {
      rb_ary_push(rb_row, DBL2NUM((matrix->numbers)[row][column]));
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
  print_obj(m1);
  print_obj(m2);

  Check_Type(m1, T_ARRAY);
  Check_Type(m2, T_ARRAY);

  Matrix *m1c = rb_array_to_matrix(m1);
  Matrix *m2c = rb_array_to_matrix(m2);

  print(m1c);
  print(m2c);

  Matrix *multiplied = multiply(m1c, transpose(m2c));

  printf("Multiplied: (%d, %d): %ld\n", multiplied->rows, multiplied->columns, multiplied->numbers[0][0]);
  // print(multiplied);

  if (multiplied) {
    return matrix_to_rb_array(multiplied);
  } else {
    return Qnil;
  }

  // VALUE result = matrix_to_rb_array(m1c);

  // destroy_matrix(m1c);
  // xfree(m2c);
  // xfree(multiplied);

  return Qnil;
}

void Init_extension(void) {
  VALUE CFromRubyExample = rb_define_module("CFromRubyExample");
  VALUE NativeHelpers = rb_define_class_under(CFromRubyExample, "NativeHelpers", rb_cObject);

  rb_define_singleton_method(NativeHelpers, "string", string, 1);
  rb_define_singleton_method(NativeHelpers, "number", number, 1);
  rb_define_singleton_method(NativeHelpers, "boolean", boolean, 1);
  rb_define_singleton_method(NativeHelpers, "mul_matrix", mul_matrix, 2);
}
