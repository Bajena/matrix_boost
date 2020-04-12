require "extension"
require "matrix"
require "benchmark"

module MatrixBoost
  class << self
    # @param m1 [Matrix] Stdlib Matrix instance
    # @param m2 [Matrix] Stdlib Matrix instance
    # @return [Matrix] m1 x m2 Matrix
    def multiply(m1, m2)
      Matrix[*NativeHelpers.mul_matrix(m1.to_a, m2.to_a)]
    end

    def benchmark(dim: 3, n: 100000)
      m1 = Matrix[[1, 2, 3], [4, 5, 6]]
      m2 = Matrix[[9,8],[7,6],[5,4]]

      m1 = Matrix.build(dim) { rand }
      m2 = Matrix.build(dim) { rand }

      Benchmark.benchmark(Benchmark::CAPTION, 45, Benchmark::FORMAT) do |x|
        x.report("Ruby matrix multiply:") { n.times { m1 * m2 } }
        x.report("C matrix multiply:") { n.times { multiply(m1, m2) } }

        apply_core_extensions
        x.report("Ruby matrix multiply after monkey patch:") { n.times { m1 * m2 } }
      end
    end

    def apply_core_extensions
      require "matrix_boost/core_extensions"

      Matrix.prepend MatrixBoost::CoreExtensions::Multiply
    end
  end
end
