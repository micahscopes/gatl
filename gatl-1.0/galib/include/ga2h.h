/*
 * Copyright (C) 2007 Leandro Augusto Frata Fernandes
 *
 * author   : Fernandes, Leandro A. F.
 * e-mail   : laffernandes@gmail.com
 * home page: http://www.inf.ufrgs.br/~laffernandes
 *
 * version  : Alpha 3.141592
 */

#ifndef _GA2H_MAIN_
#define _GA2H_MAIN_

#include "ga.h"

/*******************************************************************************************************
 * Model definition.
 *******************************************************************************************************/

/* Homogeneous model of 2D space. We define ga2h_model as a new class rather than a typedef from ga::homogeneous::model<base_space_dims,origin_vector> because we want to avoid operations between multivector from different models. Also, we declare the ga2h_model outside the ga2h namespace in order to be able to initialize the basis vectors.
   The basis blades are ordered as follow:

      basis blade: scalar  e0      e1      e0^e1   e2      e0^e2   e1^e2   e0^e1^e2
            index: 0       1       2       3       4       5       6       7
           bitmap: 000     001     010     011     100     101     110     111

   The metric matrix is:

         | e0 e1 e2
      ---+-----------
      e0 |  1  0  0
      e1 |  0  1  0
      e2 |  0  0  1
 */
class ga2h_model : public ga::homogeneous::model<2,0> {};

// The namespace of the 2D homogeneous geometric algebra model.
namespace ga2h
{

/*******************************************************************************************************
 * Model (re-)definition.
 *******************************************************************************************************/

// Geometric algebra model definition.
typedef ga2h_model model;

/*******************************************************************************************************
 * Some useful constant values for internal use only.
 *******************************************************************************************************/

// Bitmap representation of the scalar basis blade.
static const ga::bitmap_t _scalar = 0;

// Bitmap representation of e0.
static const ga::bitmap_t _e0 = ga::basis_vector<model,0>::bitmap;

// Bitmap representation of e1.
static const ga::bitmap_t _e1 = ga::basis_vector<model,1>::bitmap;

// Bitmap representation of e2.
static const ga::bitmap_t _e2 = ga::basis_vector<model,2>::bitmap;

/*******************************************************************************************************
 * Set of products/operations to be used within this model.
 *******************************************************************************************************/

#include "ga_operations.h"
#include "ga_homogeneous_operations.h"

/*******************************************************************************************************
 * Specialized multivectors definition.
 *******************************************************************************************************/

// A scalar value.
typedef ga::real_t real_t;

// A multivector having all the coefficients.
typedef ga::multivector<
		model,
		ga::store_all<model>::store_type
	> multivector_t;

// A null multivector.
typedef ga::multivector<
		model,
		ga::store_none
	> zero_t;

// Multivector representation of a scalar value.
typedef ga::multivector<
		model,
		ga::store<_scalar
	> > scalar_t;

// A multivector representation of a pseudoscalar.
typedef ga::multivector<
		model,
		ga::store_pseudoscalar<model>::store_type
	> pseudoscalar_t;

// A multivector representation of an Euclidean pseudoscalar.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2
	> > euclidean_pseudoscalar_t;

// Multivector representation of a vector e0.
typedef ga::multivector<
		model,
		ga::store<_e0
	> > e0_t;

// Multivector representation of a vector e1.
typedef ga::multivector<
		model,
		ga::store<_e1
	> > e1_t;

// Multivector representation of a vector e2.
typedef ga::multivector<
		model,
		ga::store<_e2
	> > e2_t;

// Multivector representation of a point.
typedef ga::multivector<
		model,
		ga::store<_e0,
		ga::store<_e1,
		ga::store<_e2
	> > > > point_t;

// Multivector representation of an improper point. An improper point can be interpreted as a direction (vector), or as a point at infinity.
typedef ga::multivector<
		model,
		ga::store<_e1,
		ga::store<_e2
	> > > improper_point_t;

// Multivector representation of a vector.
typedef improper_point_t vector_t;

// Multivector representation of a point at infinity.
typedef improper_point_t point_at_infinity_t;

// Multivector representation of a line.
typedef ga::multivector<
		model,
		ga::store<_e0^_e1,
		ga::store<_e0^_e2,
		ga::store<_e1^_e2
	> > > > line_t;

// Multivector representation of a hyperplane.
typedef line_t hyperplane_t;

// Multivector representation of an improper line. An improper line can be interpreted as a 2D direction (bivector), or as a line at infinity.
typedef ga::multivector<
		model,
		ga::store<_e1^_e2
	> > improper_line_t;

// Multivector representation of a bivector.
typedef improper_line_t bivector_t;

// Multivector representation of a line at infinity.
typedef improper_line_t line_at_infinity_t;

// Multivector representation of a rotor.
typedef ga::multivector<
		model,
		ga::store<_scalar,
		ga::store<_e1^_e2
	> > > rotor_t;

/*******************************************************************************************************
 * Matrices definition.
 *******************************************************************************************************/

// Matrix representation of a general multivector.
typedef la::dmatrix<real_t,model::basis_blades_count,1> multivector_matrix_t;

// Matrix representation of some linear operation.
typedef la::dmatrix<real_t,model::basis_blades_count,model::basis_blades_count> operation_matrix_t;

// 2nd-rank tensor representation some unary operation, for instance.
typedef la::dtensor2<real_t,model::basis_blades_count> rank2_tensor_t;

// 3rd-rank tensor representation some product, for instance.
typedef la::dtensor3<real_t,model::basis_blades_count> rank3_tensor_t;

/*******************************************************************************************************
 * Constant values declaration.
 *******************************************************************************************************/

// Unit point at origin.
extern const e0_t e0;

// Unit Euclidean vector e1.
extern const e1_t e1;

// Unit Euclidean vector e2.
extern const e2_t e2;

// Inverse of the unit vector e0.
extern const e0_t ie0;

// Unit pseudoscalar of homogeneous model.
extern const pseudoscalar_t I;

// Inverse of the unit pseudoscalar of homogeneous model.
extern const pseudoscalar_t iI;

// Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t Ie;

// Inverse of the Euclidean unit pseudoscalar.
extern const euclidean_pseudoscalar_t iIe;

}

#endif // !_GA2H_MAIN_
