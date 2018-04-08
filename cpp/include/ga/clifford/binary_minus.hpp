#ifndef __GA_CLIFFORD_BINARY_MINUS_HPP__
#define __GA_CLIFFORD_BINARY_MINUS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class LeftItrType, class RightItrType, typename std::enable_if<eq<typename LeftItrType::element_type, typename RightItrType::element_type>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(next(lhs), next(rhs)), binary_minus_element(lhs.element(), rhs.element()));
			}

			template<class LeftItrType, class RightItrType, typename std::enable_if<lt<typename LeftItrType::element_type, typename RightItrType::element_type>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(next(lhs), rhs), lhs.element());
			}

			template<class LeftItrType>
			constexpr decltype(auto) binary_minus(LeftItrType const &lhs, itr_end const &rhs) {
				return insert(binary_minus(next(lhs), rhs), lhs.element());
			}

			template<class LeftItrType, class RightItrType, typename std::enable_if<lt<typename RightItrType::element_type, typename LeftItrType::element_type>::value, int>::type = 0>
			constexpr decltype(auto) binary_minus(LeftItrType const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(lhs, next(rhs)), unary_minus_element(rhs.element()));
			}

			template<class RightItrType>
			constexpr decltype(auto) binary_minus(itr_end const &lhs, RightItrType const &rhs) {
				return insert(binary_minus(lhs, next(rhs)), unary_minus_element(rhs.element()));
			}

			constexpr empty_expression_tree binary_minus(itr_end const &, itr_end const &) {
				return empty_expression_tree();
			}

		}

		template<class LeftType, class RightType>
		constexpr decltype(auto) minus(LeftType const &lhs, RightType const &rhs) {
			return detail::binary_minus(detail::obegin(lhs), detail::obegin(rhs));
		}

		using lazy::operator-;

		template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
		constexpr decltype(auto) operator-(detail::expression_tree<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, detail::expression_tree<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
			return minus(lhs, rhs);
		}

		template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType>
		constexpr decltype(auto) operator-(detail::expression_tree<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, detail::empty_expression_tree const &rhs) {
			return minus(lhs, rhs);
		}

		template<class LeftElementType, class LeftLeftSubtreeType, class LeftRightSubtreeType, class RightExpressionType>
		constexpr decltype(auto) operator-(detail::expression_tree<LeftElementType, LeftLeftSubtreeType, LeftRightSubtreeType> const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return minus(lhs, rhs());
		}

		template<class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
		constexpr decltype(auto) operator-(detail::empty_expression_tree const &lhs, detail::expression_tree<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
			return minus(lhs, rhs);
		}

		constexpr decltype(auto) operator-(detail::empty_expression_tree const &lhs, detail::empty_expression_tree const &rhs) {
			return minus(lhs, rhs);
		}

		template<class RightExpressionType>
		constexpr decltype(auto) operator-(detail::empty_expression_tree const &lhs, lazy_expression<RightExpressionType> const &rhs) {
			return minus(lhs, rhs());
		}

		template<class LeftExpressionType, class RightElementType, class RightLeftSubtreeType, class RightRightSubtreeType>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, detail::expression_tree<RightElementType, RightLeftSubtreeType, RightRightSubtreeType> const &rhs) {
			return minus(lhs(), rhs);
		}

		template<class LeftExpressionType>
		constexpr decltype(auto) operator-(lazy_expression<LeftExpressionType> const &lhs, detail::empty_expression_tree const &rhs) {
			return minus(lhs(), rhs);
		}

	}

}

#endif // __GA_CLIFFORD_BINARY_MINUS_HPP__
