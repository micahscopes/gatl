#ifndef __GA_EXTRA_VERSOR_INVERSE_HPP__
#define __GA_EXTRA_VERSOR_INVERSE_HPP__

namespace ga {

	template<typename CoefficientType, typename Expression, typename MetricSpaceType>
	constexpr decltype(auto) inv(clifford_expression<CoefficientType, Expression> const &arg, metric_space<MetricSpaceType> const &mtr) {
		auto const lazy = make_lazy_context(arg);
		return lazy.eval(gp(reversion(lazy.argument<0>()), inv(rnorm_sqr(lazy.argument<0>(), mtr))));
	}

	template<typename CoefficientType, typename Coefficient>
	constexpr decltype(auto) inv(scalar_clifford_expression<CoefficientType, Coefficient> const &arg) {
		return pow(arg, c<-1>);
	}

	template<typename Type, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) inv(Type const &arg, metric_space<MetricSpaceType> const &) {
		return pow(scalar(arg), c<-1>);
	}

	template<typename Type, typename = std::enable_if_t<!is_clifford_expression_v<Type> > >
	constexpr decltype(auto) inv(Type const &arg) {
		return pow(scalar(arg), c<-1>);
	}

}

#endif // __GA_EXTRA_VERSOR_INVERSE_HPP__
