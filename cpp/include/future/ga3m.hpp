#ifndef __FUTURE_GA3M_HPP__
#define __FUTURE_GA3M_HPP__

#include "ga.hpp"
#include "ga/macro_for_algebra_overload.hpp"

GA_SIGNED_ALGEBRA_OVERLOAD(ga3m, 3 + 1, 1)

namespace ga3m {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);
	static auto const e3 = e(c<3>);

	static auto const ep = e(c<4>);
	static auto const em = e(c<5>);

	static auto const no = (em - ep) / c<2>;
	static auto const ni = ep + em;

	static auto const Ie = e1 ^ e2 ^ e3;
	static auto const I = pseudoscalar();

}

#endif // __FUTURE_GA3M_HPP__
