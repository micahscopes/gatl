#ifndef __GA_UTILS_CONFORMAL_ROUND_SIZE_SQR_HPP__
#define __GA_UTILS_CONFORMAL_ROUND_SIZE_SQR_HPP__

namespace ga {

	// Returns the squared size parameter of a given round.
	template<typename CoefficientType, typename Expression, ndims_t N>
	constexpr decltype(auto) round_size_sqr(clifford_expression<CoefficientType, Expression> const &round, conformal_metric_space<N> const &mtr) {
		auto const lazy = make_lazy_context(round);
		auto aux = lcont(e(c<N + 2>), lazy.argument<0>(), mtr);
		return lazy.eval(sp(sp(lazy.argument<0>(), involution(lazy.argument<0>()), mtr), inv(sp(aux, aux, mtr), mtr), mtr));
	}

}

#endif // __GA_UTILS_CONFORMAL_ROUND_SIZE_SQR_HPP__
