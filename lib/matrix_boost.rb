require "matrix_boost/extension"
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

    # @param m [Matrix] Stdlib Matrix instance
    # @return [Matrix] Inverted matrix
    def invert(m)
      Matrix[*NativeHelpers.inv_matrix(m.to_a)]
    end

    def apply_core_extensions
      require "matrix_boost/core_extensions"

      Matrix.prepend MatrixBoost::CoreExtensions::Multiply
      Matrix.prepend MatrixBoost::CoreExtensions::Inverse
    end
  end
end
