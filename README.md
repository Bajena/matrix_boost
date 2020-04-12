# MatrixBoost

[![Build Status](https://travis-ci.com/Bajena/matrix_boost.svg?branch=master)](https://travis-ci.com/Bajena/matrix_boost)

This gem showcases usage of Ruby C extensions by reimplementing operations
from Ruby's [https://ruby-doc.org/stdlib-2.5.1/libdoc/matrix/rdoc/Matrix.html](Matrix) library.

### Performance comparison

```bash
irb(main):007:0> MatrixBoost.benchmark(dim: 3, n: 10000000)
                                                    user     system      total        real
Ruby matrix multiply:                          81.385777   0.190162  81.575939 ( 81.751942)
C matrix multiply:                             47.041961   0.081723  47.123684 ( 47.206611)
Ruby matrix multiply after monkey patch:       50.903808   0.222949  51.126757 ( 51.351058
```

as you can see Ruby's Matrix implementation is ~67% slower than the same operation
implemented in a C extension 🎉.

### Matrix class core extension
Even though this gem was created mainly for learning how to use C extensions in Ruby
you should still be able to use it in your production code.

You can either use `MatrixBoost.multiply(m1, m2)` or replace the original methods
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
