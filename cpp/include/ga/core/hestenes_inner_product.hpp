#ifndef __GA_CORE_HESTENES_INNER_PRODUCT_HPP__
#define __GA_CORE_HESTENES_INNER_PRODUCT_HPP__

namespace ga {

	namespace detail {

		struct hip_mapping {
		private:

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades>
			struct _possible_grades_result {
			private:

				constexpr static default_bitset_t left_grade_bitset = rightmost_set_bit(LeftPossibleGrades);
				constexpr static default_bitset_t possible_grades = RightPossibleGrades / left_grade_bitset;

			public:

				constexpr static default_bitset_t value = _possible_grades_result<(possible_grades != default_bitset_t(0) ? LeftPossibleGrades ^ left_grade_bitset : default_bitset_t(0)), RightPossibleGrades>::value | possible_grades;
			};

			template<default_bitset_t RightPossibleGrades>
			struct _possible_grades_result<default_bitset_t(0), RightPossibleGrades> {
				constexpr static default_bitset_t value = default_bitset_t(0);
			};

		public:

			template<class LeftGrade, class RightGrade, class ResultGrade>
			struct are_valid_grades {
				typedef if_else_t<
					logical_or_t<equal_t<LeftGrade, constant_value<0> >, equal_t<RightGrade, constant_value<0> > >,
					std::false_type,
					if_else_t<
						less_or_equal_t<LeftGrade, RightGrade>,
						equal_t<ResultGrade, addition_t<RightGrade, product_t<constant_value<-1>, LeftGrade, value_mapping> > >,
						equal_t<ResultGrade, addition_t<LeftGrade, product_t<constant_value<-1>, RightGrade, value_mapping> > >
					>
				> type;
			};

			template<default_bitset_t LeftPossibleGrades, default_bitset_t RightPossibleGrades, ndims_t VectorSpaceDimensions>
			struct possible_grades_result {
			private:

				constexpr static default_bitset_t left_possible_grades = (LeftPossibleGrades | default_bitset_t(1)) ^ default_bitset_t(1);
				constexpr static default_bitset_t right_possible_grades = (RightPossibleGrades | default_bitset_t(1)) ^ default_bitset_t(1);

			public:

				constexpr static default_bitset_t value = _possible_grades_result<left_possible_grades, right_possible_grades>::value | _possible_grades_result<right_possible_grades, left_possible_grades>::value;
			};
		};

	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightExpression, class MetricSpaceType>
	constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &mtr) {
		auto lazy = make_lazy_context(lhs, rhs);
		return lazy.eval(clifford_expression<default_integral_t, detail::product_t<decltype(lazy)::argument_expression_t<0>, decltype(lazy)::argument_expression_t<1>, detail::metric_space_mapping_t<MetricSpaceType, detail::hip_mapping> > >());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightExpression>
	constexpr decltype(auto) hip(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return hip(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return hip(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftCoefficient, class RightCoefficientType, class RightCoefficient>
	constexpr decltype(auto) hip(scalar_clifford_expression<LeftCoefficientType, LeftCoefficient> const &lhs, scalar_clifford_expression<RightCoefficientType, RightCoefficient> const &rhs) {
		return hip(lhs, rhs, detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return hip(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftCoefficientType, class LeftExpression, class RightType, class = std::enable_if_t<!is_clifford_expression_v<RightType> > >
	constexpr decltype(auto) hip(clifford_expression<LeftCoefficientType, LeftExpression> const &lhs, RightType const &rhs) {
		return hip(lhs, scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class MetricSpaceType, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) hip(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs, metric_space<MetricSpaceType> const &) {
		return hip(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightCoefficientType, class RightExpression, class = std::enable_if_t<!is_clifford_expression_v<LeftType> > >
	constexpr decltype(auto) hip(LeftType const &lhs, clifford_expression<RightCoefficientType, RightExpression> const &rhs) {
		return hip(scalar(lhs), rhs, detail::real_metric_space());
	}

	template<class LeftType, class RightType, class MetricSpaceType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) hip(LeftType const &lhs, RightType const &rhs, metric_space<MetricSpaceType> const &) {
		return hip(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

	template<class LeftType, class RightType, class = std::enable_if_t<!(is_clifford_expression_v<LeftType> || is_clifford_expression_v<RightType>)> >
	constexpr decltype(auto) hip(LeftType const &lhs, RightType const &rhs) {
		return hip(scalar(lhs), scalar(rhs), detail::real_metric_space());
	}

}

#endif // __GA_CORE_HESTENES_INNER_PRODUCT_HPP__