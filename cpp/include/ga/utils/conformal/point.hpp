#ifndef __GA_UTILS_CONFORMAL_POINT_HPP__
#define __GA_UTILS_CONFORMAL_POINT_HPP__

namespace ga {

	// Initializes a multivector representation of a point using the given coordinates expressed in the base space.
	template<ndims_t N, typename... Types>
	constexpr decltype(auto) point(conformal_metric_space<N> const &mtr, Types &&... coords) {
		return vector(mtr, std::move(coords)..., c<1>, detail::sum(detail::square(std::move(coords))...) / c<2>);
	}

}

#endif // __GA_UTILS_CONFORMAL_POINT_HPP__
