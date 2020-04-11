require "extension"
require "c_from_ruby_example/version"
require "matrix"
require 'benchmark'

module CFromRubyExample
  class << self
    def multiply(m1, m2)
      Matrix[*NativeHelpers.mul_matrix(m1.to_a, m2.to_a)]
    end

    def test_it(dim: 3, n: 100000)
      # m1 = Matrix[[1, 2, 3], [4, 5, 6]]
      # m2 = Matrix[[9,8],[7,6],[5,4]]

      m1 = Matrix.build(dim) { rand }
      m2 = Matrix.build(dim) { rand }

      Benchmark.benchmark(Benchmark::CAPTION, 22, Benchmark::FORMAT) do |x|
        x.report("Ruby matrix multiply:") { n.times { m1 * m2 } }
        x.report("C matrix multiply:") { n.times { multiply(m1, m2) } }
      end
    end
  end
end
