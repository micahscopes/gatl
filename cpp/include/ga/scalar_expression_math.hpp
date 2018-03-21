#ifndef __GA_SCALAR_EXPRESSION_MATH_HPP__
#define __GA_SCALAR_EXPRESSION_MATH_HPP__

namespace ga {

	using detail::abs;

	constexpr detail::empty_expression abs(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) abs(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return abs(native(arg));
	}

	using detail::exp;

	template<class MetricSpaceType>
	constexpr decltype(auto) exp(detail::empty_expression const &) {
		return detail::make_expression(detail::make_component(detail::cvalue<1>(), detail::cbasis_blade<0>()), detail::empty_expression(), detail::empty_expression());
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType, typename std::enable_if<detail::may_cast_to_native<detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> >::value, int>::type = 0>
	constexpr decltype(auto) exp(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return exp(native(arg));
	}

	using detail::sqrt;

	constexpr detail::empty_expression sqrt(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) sqrt(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return sqrt(native(arg));
	}

	using detail::cos;

	constexpr decltype(auto) cos(detail::empty_expression const &) {
		return detail::make_expression(detail::make_component(detail::cvalue<1>(), detail::cbasis_blade<0>()), detail::empty_expression(), detail::empty_expression());
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) cos(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return cos(native(arg));
	}

	using detail::sin;

	constexpr decltype(auto) sin(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) sin(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return sin(native(arg));
	}

	using detail::tan;

	constexpr decltype(auto) tan(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) tan(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return tan(native(arg));
	}

	using detail::cosh;

	constexpr decltype(auto) cosh(detail::empty_expression const &) {
		return detail::make_expression(detail::make_component(detail::cvalue<1>(), detail::cbasis_blade<0>()), detail::empty_expression(), detail::empty_expression());
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) cosh(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return cosh(native(arg));
	}

	using detail::sinh;

	constexpr decltype(auto) sinh(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) sinh(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return sinh(native(arg));
	}

	using detail::tanh;

	constexpr decltype(auto) tanh(detail::empty_expression const &) {
		return detail::empty_expression();
	}

	template<class ElementType, class LeftSubtreeType, class RightSubtreeType>
	constexpr decltype(auto) tanh(detail::expression<ElementType, LeftSubtreeType, RightSubtreeType> const &arg) {
		return tanh(native(arg));
	}

}

#endif // __GA_SCALAR_EXPRESSION_MATH_HPP__
