/*
 * Copyright (C) 2008 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _LA_DETERMINANT_
#define _LA_DETERMINANT_

// The namespace of the linear algebra library.
namespace la
{

/*******************************************************************************************************
 * Determinant function implementations.
 *******************************************************************************************************/

// Computes the determinant of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
real_type
determinant(const matrix<real_type,1,1> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	return m(0,0);
}

// Computes the determinant of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
real_type
determinant(const matrix<real_type,2,2> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	return (m(0,0) * m(1,1)) - (m(0,1) * m(1,0));
}

// Computes the determinant of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type>
inline
real_type
determinant(const matrix<real_type,3,3> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	return (m(0,0) * m(1,1) * m(2,2)) + (m(0,1) * m(1,2) * m(2,0)) + (m(0,2) * m(1,0) * m(2,1)) − (m(0,0) * m(1,2) * m(2,1)) − (m(0,1) * m(1,0) * m(2,2)) − (m(0,2) * m(1,1) * m(2,0));
}

// Computes the determinant of the given matrix.
template<template<typename value_type, size_t rows, size_t cols> class matrix, typename real_type, size_t size>
inline
real_type
determinant(const matrix<real_type,size,size> &m, const real_type &tolerance _LA_DEFAULT_TOLERANCE)
{
	int pivot_col;
	real_type temp, scale, result = 1;
	matrix<real_type,size,size> copy( m );

	for (size_t k=0; k!=size; ++k)
	{
		if ((pivot_col = pivot( copy, k, tolerance )) == -1)
		{
			return 0;
		}

		if (pivot_col != 0)
		{
			result = -result;
		}
		result *= copy(k,k);

		scale = static_cast<real_type>( 1 ) / copy(k,k);
		for (size_t i=k+1; i!=size; ++i)
		{
			temp = scale * copy(i,k);
			for (size_t j=k+1; j!=size; ++j)
			{
				copy(i,j) -= temp * copy(k,j);
			}
		}
	}

	return result;
}

}

#endif // !_LA_DETERMINANT_
