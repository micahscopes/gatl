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

#ifndef __GA_EXTRA_DUALIZATION_HPP__
#define __GA_EXTRA_DUALIZATION_HPP__

namespace ga {

    template<typename CoefficientType, typename Expression, typename PseudoscalarCoefficientType, typename PseudoscalarExpression, typename MetricSpaceType>
    constexpr decltype(auto) dual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
        auto const lazy = make_lazy_context(arg, pseudoscalar);
        return lazy.eval(lcont(lazy.template argument<0>(), inv(lazy.template argument<1>(), mtr), mtr));
    }

    template<typename Type, typename PseudoscalarCoefficientType, typename PseudoscalarExpression, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<Type> > >
    constexpr decltype(auto) dual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) {
        return dual(scalar(arg), pseudoscalar, mtr);
    }

    template<typename CoefficientType, typename Expression, typename PseudoscalarCoefficientType, typename PseudoscalarExpression, typename MetricSpaceType>
    constexpr decltype(auto) undual(clifford_expression<CoefficientType, Expression> const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) noexcept {
        auto const lazy = make_lazy_context(arg, pseudoscalar);
        return lazy.eval(lcont(lazy.template argument<0>(), lazy.template argument<1>(), mtr));
    }

    template<typename Type, typename PseudoscalarCoefficientType, typename PseudoscalarExpression, typename MetricSpaceType, typename = std::enable_if_t<!is_clifford_expression_v<Type> > >
    constexpr decltype(auto) undual(Type const &arg, clifford_expression<PseudoscalarCoefficientType, PseudoscalarExpression> const &pseudoscalar, metric_space<MetricSpaceType> const &mtr) noexcept {
        return undual(scalar(arg), pseudoscalar, mtr);
    }

}

#endif // __GA_EXTRA_DUALIZATION_HPP__