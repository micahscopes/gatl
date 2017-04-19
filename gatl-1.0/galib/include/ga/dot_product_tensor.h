/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_DOT_PRODUCT_TENSOR_
#define _GA_DOT_PRODUCT_TENSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Dot product tensor.
 *******************************************************************************************************/

// Computes the dot product tensor for the given geometric algebra model.
template<typename model>
inline
const la::dtensor3<real_t,model::basis_blades_count>&
dot_tensor()
{
	return _private::product_tensor_dot<model>::run();
}

// Computes the dot product tensor for the given geometric algebra model (Euclidean metric).
template<typename model>
inline
const la::dtensor3<real_t,model::basis_blades_count>&
dot_tensor_em()
{
	return _private::product_tensor_dot_em<model>::run();
}

}

#endif // !_GA_DOT_PRODUCT_TENSOR_
