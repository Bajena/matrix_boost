# MatrixBoost

[![Build Status](https://travis-ci.com/Bajena/matrix_boost.svg?branch=master)](https://travis-ci.com/Bajena/matrix_boost)

This gem showcases usage of Ruby C extensions by reimplementing operations
from Ruby's [https://ruby-doc.org/stdlib-2.5.1/libdoc/matrix/rdoc/Matrix.html](Matrix) library.

### Performance comparison

```bash
→ bin/rake benchmark_multiply; bin/rake benchmark_inverse
Benchmark multiplication (dim = 4, n = 1000000)...
                                                    user     system      total        real
Ruby matrix multiply:                          22.627594   0.180447  22.808041 ( 23.473300)
C matrix multiply:                             12.393963   0.124988  12.518951 ( 13.102763)
Ruby matrix multiply after monkey patch:       11.493074   0.073740  11.566814 ( 11.645836)
>Ruby slower (%):                               1.825695   1.443715        NaN (  1.791477)

Benchmark inversion (dim = 4, n = 1000000)...
                                                    user     system      total        real
Ruby matrix inverse:                           26.191386   0.067096  26.258482 ( 26.328944)
C matrix inverse:                               4.911581   0.005300   4.916881 (  4.920316)
Ruby matrix inverse after monkey patch:         5.180995   0.003944   5.184939 (  5.187873)
>Ruby slower (%):                               5.332577  12.659623        NaN (  5.351068)
```

- Ruby's multiplication of 4-dimensional martices is **~79%** slower than the same operation
implemented in a C extension 🎉.
- Ruby's inversion of 4-dimensional matrices is **~435%** slower than the same operation
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
