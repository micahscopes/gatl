#ifndef __GA1M_HPP__
#define __GA1M_HPP__

#include <ga/core.hpp>
#include <ga/extra.hpp>
#include <ga/utils/macro_for_signed_algebra_overload.hpp>

GA_SIGNED_ALGEBRA_OVERLOAD(ga1m, 1 + 1, 1)

namespace ga1m {

	static auto const e1 = e(c<1>);

	static auto const ep = e(c<2>);
	static auto const em = e(c<3>);

	static auto const no = (em - ep) / c<2>;
	static auto const ni = ep + em;

	static auto const Ie = e1;
	static auto const I = pseudoscalar();

}

#endif // __GA1M_HPP__
