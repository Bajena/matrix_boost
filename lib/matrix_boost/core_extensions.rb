require "matrix"

module MatrixBoost
  module CoreExtensions
    module Multiply
      # Overrides https://github.com/ruby/matrix/blob/master/lib/matrix.rb#L1057
      def *(m)
        case(m)
        when Matrix
          raise ErrDimensionMismatch if column_count != m.row_count

          MatrixBoost.multiply(self, m)
        else
          super
        end
      end
    end
  end
end
