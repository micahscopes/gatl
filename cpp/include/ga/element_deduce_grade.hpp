#ifndef __GA_ELEMENT_DEDUCE_GRADE__
#define __GA_ELEMENT_DEDUCE_GRADE__

namespace ga {

	template<class ValueType>
	class grade_result;

	namespace detail {

		template<default_integral_t CoefficientValue, default_bitset_t BasisBlade, class ToleranceType>
		constexpr decltype(auto) grade_element(component<cvalue<CoefficientValue>, cbasis_blade<BasisBlade> > const &, ToleranceType const &) {
			return grade_result<cvalue<_basis_blade_grade<cbasis_blade<BasisBlade> >::value> >(); // The coefficient is different than zero by construction.
		}

		template<default_integral_t CoefficientValue, default_bitset_t PossibleGrades, class ToleranceType>
		constexpr decltype(auto) grade_element(component<cvalue<CoefficientValue>, dbasis_blade<PossibleGrades> > const &arg, ToleranceType const &) {
			return grade_result<grade_t>(basis_blade_grade(arg.basis_blade())); // The coefficient is different than zero by construction.
		}

		template<class CoefficientType, class BasisBladeType, class ToleranceType>
		constexpr decltype(auto) grade_element(component<CoefficientType, BasisBladeType> const &arg, ToleranceType const &tol) {
			return grade_result<grade_t>(abs(arg.coefficient()) > tol ? basis_blade_grade(arg.basis_blade()) : -2);
		}

		template<class CoefficientType, default_bitset_t PossibleGrades, class ToleranceType>
		constexpr decltype(auto) grade_element(components<CoefficientType, PossibleGrades> const &arg, ToleranceType const &tol) {
			grade_t result = -2;
			for (auto itr = arg.begin(), end = arg.end(); itr != end; ++itr) {
				if (abs(itr->second) > tol) {
					grade_t curr = basis_blade_grade(itr->first);
					if (result != -2) {
						if (result != curr) {
							return grade_result<grade_t>(-1);
						}
					}
					else {
						result = curr;
					}
				}
			}
			return grade_result<grade_t>(result);
		}

	}

}

#endif // __GA_ELEMENT_DEDUCE_GRADE__
