# MatrixBoost

[![Build Status](https://travis-ci.com/Bajena/matrix_boost.svg?branch=master)](https://travis-ci.com/Bajena/matrix_boost)

This gem showcases usage of Ruby C extensions by reimplementing operations
from Ruby's [https://ruby-doc.org/stdlib-2.5.1/libdoc/matrix/rdoc/Matrix.html](Matrix) library.

### Performance comparison

```bash
→ bin/rake benchmark_inverse benchmark_multiply
                                                    user     system      total        real
Ruby matrix inverse:                          137.841586   0.227272 138.068858 (138.278252)
C matrix inverse:                              40.402431   0.054922  40.457353 ( 40.506431)
Ruby matrix inverse after monkey patch:        42.565993   0.053962  42.619955 ( 42.662933)
>Ruby slower (%):                               3.411715   4.138087        NaN (  3.413736)
                                                    user     system      total        real
Ruby matrix multiply:                          62.837057   0.077940  62.914997 ( 62.985346)
C matrix multiply:                             61.969643   0.078727  62.048370 ( 62.111846)
Ruby matrix multiply after monkey patch:       63.094235   0.077695  63.171930 ( 63.234440)
>Ruby slower (%):                               1.013997   0.990003        NaN (  1.014063)
```

as you can see Ruby's Matrix implementation is ~67% slower than the same operation
implemented in a C extension 🎉.

### Matrix class core extension
Even though this gem was created mainly for learning how to use C extensions in Ruby
you should still be able to use it in your production code.

You can install the gem by adding `gem "matrix_boost"` to your gemfile.

Then you can either use `MatrixBoost.multiply(m1, m2)` or `MatrixBoost.invert(m)` or replace the original methods
from `Matrix` by calling `MatrixBoost.apply_core_extensions`.

### How do I play around?

```bash
$ bin/setup
$ bin/rake compile
```

And then run this play around:

```bash
$ bin/console
```

```bash
irb(main):001:0> m1 = Matrix[[1, 2, 3], [4, 5, 6]]
=> Matrix[[1, 2, 3], [4, 5, 6]]
irb(main):002:0> m2 = Matrix[[9, 8],[7, 6],[5, 4]]
=> Matrix[[9, 8], [7, 6], [5, 4]]
irb(main):003:0> MatrixBoost.multiply(m1, m2)
=> Matrix[[38.0, 32.0], [101.0, 86.0]]
```

Or run the tests:

```bash
bin/rake test
```
