require "test_helper"

class MatrixBoostTest < Minitest::Test
  def test_multiplication
    m1 = Matrix[[1, 2, 3], [4, 5, 6]]
    m2 = Matrix[[9, 8],[7, 6],[5, 4]]

    assert_equal MatrixBoost.multiply(m1, m2), m1 * m2
  end

  def test_inverse
    m = Matrix.build(3) { rand }

    assert_equal MatrixBoost.invert(m).round(4), m.inverse.round(4)
  end
end
