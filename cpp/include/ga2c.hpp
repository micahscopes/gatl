#ifndef __GA2C_HPP__
#define __GA2C_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/macro_for_conformal_algebra_overload.hpp>

GA_CONFORMAL_ALGEBRA_OVERLOAD(ga2c, 2)

namespace ga2c {

	static auto const e1 = e(c<1>);
	static auto const e2 = e(c<2>);

	static auto const no = e(c<3>);
	static auto const ni = e(c<4>);

	static auto const ep = (ni / c<2>) - no;
	static auto const em = (ni / c<2>) + no;

	static auto const Ie = e1 ^ e2;
	static auto const I = pseudoscalar();

}

#endif // __GA2C_HPP__
