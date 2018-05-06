#ifndef __GA2M_HPP__
#define __GA2M_HPP__

#include <ga.hpp>
#include <ga/macro_for_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga2m, 2 + 1, 1)

namespace ga2m {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);

	static auto const ep = e(c<3>);
	static auto const em = e(c<4>);

	static auto const no = (em - ep) / c<2>;
	static auto const ni = ep + em;

	static auto const Ie = e1 ^ e2;
	static auto const I = pseudoscalar();

	GA_USE_LAZY_VARK_FUNCTIONS()

}

#endif // __GA2M_HPP__