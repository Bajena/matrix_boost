# MatrixBoost

This gem showcases usage of Ruby C extensions by reimplementing operations
from Ruby's [https://ruby-doc.org/stdlib-2.5.1/libdoc/matrix/rdoc/Matrix.html](Matrix) library.

```bash
irb(main):007:0> MatrixBoost.test_it(dim: 3, n: 10000000)
                           user     system      total        real
Ruby Matrix multiply: 76.065556   0.161843  76.227399 ( 76.378641)
MatrixBoost multiply: 45.243661   0.112737  45.356398 ( 45.474884)
```

as you can see Ruby's Matrix implementation is ~67% slower than the same operation
implemented in a C extension 🎉.


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
