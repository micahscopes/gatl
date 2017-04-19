/*
 * Copyright (C) 2009 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA_CLIFFORD_CONJUGATION_TENSOR_
#define _GA_CLIFFORD_CONJUGATION_TENSOR_

// The namespace of the geometric algebra library.
namespace ga
{

/*******************************************************************************************************
 * Clifford conjugation operation tensor.
 *******************************************************************************************************/

// Computes the tensor representation of the Clifford conjugation operation.
template<typename model>
inline
const la::dtensor2<real_t,model::basis_blades_count>&
clifford_conjugation_tensor()
{
	typedef multivector<model,typename store_all<model>::store_type> multivector_t;

	static la::dtensor2<real_t,model::basis_blades_count> result;

	static bool first_time = true;
	if (first_time)
	{
		#pragma omp critical (GA_CLIFFORD_CONJUGATION_TENSOR)
		{
			if (first_time)
			{
				multivector_t blade_i;

				result = static_cast<real_t>( 0 );

				blade_i = multivector<model,store_none>();
				for (index_t i=0; i!=model::basis_blades_count; ++i)
				{
					blade_i[i] = 1;

					const multivector_t &aux = clifford_conjugation( blade_i );

					for (index_t k=0; k!=model::basis_blades_count; ++k)
					{
						result(k,i) += aux[k];
					}

					blade_i[i] = 0;
				}

				first_time = false;
			}
		}
	}

	return result;
}

}

#endif // !_GA_CLIFFORD_CONJUGATION_TENSOR_
