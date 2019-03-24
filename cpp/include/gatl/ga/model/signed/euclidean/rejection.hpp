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

#ifndef __GA_MODEL_SIGNED_EUCLIDEAN_REJECTION_HPP__
#define __GA_MODEL_SIGNED_EUCLIDEAN_REJECTION_HPP__

namespace ga {

    // Rejection of a subspace (lhs) by another subspace (rhs).
    template<typename LeftCoefficientType, typename LeftExpression, typename RightCoefficientType, typename RightExpression, ndims_t N>
    constexpr decltype(auto) reject(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, euclidean_metric_space<N> const &mtr) {
        auto const lazy = make_lazy_context(lhs, rhs);
        return lazy.eval(lazy.template argument<0>() - project(lazy.template argument<0>(), lazy.template argument<1>(), mtr));
    }

}

#endif // __GA_MODEL_SIGNED_EUCLIDEAN_REJECTION_HPP__