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

#ifndef __GA_MODEL_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
#define __GA_MODEL_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_DEFINITION_HPP__

#define _GA_EUCLIDEAN_ALGEBRA_DEFINITION(SPACE, BASIS_VECTORS_NAMES, N, ...) \
	typedef euclidean_metric_space<N> space_t; \
	\
	static space_t const SPACE; \
	static std::array<std::string, N> const BASIS_VECTORS_NAMES = { __VA_ARGS__ }; \
	\
	static auto const I = pseudoscalar(SPACE); \
	static auto const Ie = I;

#endif // __GA_MODEL_SIGNED_EUCLIDEAN_MACRO_FOR_ALGEBRA_DEFINITION_HPP__
