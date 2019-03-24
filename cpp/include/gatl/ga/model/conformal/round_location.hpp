/**
Copyright (C) 2018 Leandro Augusto Frata Fernandes

author     : Fernandes, Leandro A. F.
e-mail     : laffernandes@ic.uff.br
home page  : http://www.ic.uff.br/~laffernandes
repository : https://github.com/laffernandes/gatl.git

This file is part of The Geometric Algebra Template Library (GATL).

GATL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

GATL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GATL. If not, see <https://www.gnu.org/licenses/>.
/**/

#ifndef __GA_MODEL_CONFORMAL_ROUND_LOCATION_HPP__
#define __GA_MODEL_CONFORMAL_ROUND_LOCATION_HPP__

namespace ga {

    // Returns the location parameter of a given round.
    template<typename CoefficientType, typename Expression, ndims_t D>
    constexpr decltype(auto) round_location(clifford_expression<CoefficientType, Expression> const &round, conformal_metric_space<D> const &mtr) {
        auto const lazy = make_lazy_context(round);
        return lazy.eval(gp(lazy.template argument<0>(), inv(lcont(-e(c<D + 2>), lazy.template argument<0>(), mtr), mtr), mtr));
    }

}

#endif // __GA_MODEL_CONFORMAL_ROUND_LOCATION_HPP__