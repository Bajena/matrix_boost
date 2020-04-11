require "test_helper"

class MatrixBoostTest < Minitest::Test
  def test_multiplication
    m1 = Matrix[[1, 2, 3], [4, 5, 6]]
    m2 = Matrix[[9,8],[7,6],[5,4]]

    assert_equal MatrixBoost.multiply(1,2), m1 * m2
  end
end
