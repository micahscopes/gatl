#ifndef __GA_CORE_EXPRESSION_ADDITION_HPP__
#define __GA_CORE_EXPRESSION_ADDITION_HPP__

namespace ga {

	namespace detail {

		// Specialization of _addition_level5<LeftExpression, RightExpression> with simple bind or sort-and-bind patterns.
		template<typename LeftExpression, typename RightExpression>
		struct _addition_level5 {
			typedef std::conditional_t<
				lt_v<LeftExpression, RightExpression>,
				add_t<LeftExpression, RightExpression>, // bind
				add_t<RightExpression, LeftExpression> // sort and bind
			> type;
		};
		
		// Specializations of _addition_level5<LeftExpression, RightExpression> with at least one constant argument (simplify).
		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level5<constant_value<LeftValue>, constant_value<RightValue> > {
			typedef constant_value<LeftValue + RightValue> type; // A + B = C (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level5<constant_value<LeftValue>, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<LeftValue * RightValue + 1>, power_t<constant_value<RightValue>, constant_value<-1> >, value_mapping> type; // A + 1 / B = (A * B + 1) / B (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level5<power<constant_value<LeftValue>, constant_value<-1> >, constant_value<RightValue> > {
			typedef product_t<constant_value<1 + RightValue * LeftValue>, power_t<constant_value<LeftValue>, constant_value<-1> >, value_mapping> type; // 1 / A + B = (1 + B * A) / A (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightValue>
		struct _addition_level5<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<LeftLeftValue * RightValue + LeftRightValue>, power_t<constant_value<LeftRightValue * RightValue>, constant_value<-1> >, value_mapping> type; // A / B + 1 / C = (A * C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct _addition_level5<power<constant_value<LeftValue>, constant_value<-1> >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
			typedef product_t<constant_value<RightRightValue + LeftValue * RightLeftValue>, power_t<constant_value<LeftValue * RightRightValue>, constant_value<-1> >, value_mapping> type; // 1 / C + A / B = (B + C * A) / (C * B) (simplify)
		};

		template<default_integral_t LeftValue, default_integral_t RightValue>
		struct _addition_level5<power<constant_value<LeftValue>, constant_value<-1> >, power<constant_value<RightValue>, constant_value<-1> > > {
			typedef product_t<constant_value<RightValue + LeftValue>, power_t<constant_value<LeftValue * RightValue>, constant_value<-1> >, value_mapping> type; // 1 / B + 1 / C = (C + B) / (B * C) (simplify)
		};

		template<default_integral_t LeftLeftValue, default_integral_t LeftRightValue, default_integral_t RightLeftValue, default_integral_t RightRightValue>
		struct _addition_level5<mul<constant_value<LeftLeftValue>, power<constant_value<LeftRightValue>, constant_value<-1> > >, mul<constant_value<RightLeftValue>, power<constant_value<RightRightValue>, constant_value<-1> > > > {
			typedef product_t<constant_value<LeftLeftValue * RightRightValue + LeftRightValue * RightLeftValue>, power_t<constant_value<LeftRightValue * RightRightValue>, constant_value<-1> >, value_mapping> type; // A / B + C / D = (A * D + B * C) / (B * D) (simplify)
		};

		// Specializations of _addition_level4<LeftExpression, RightExpression> with some patterns to simplify (simplify).
		template<typename LeftExpression, typename RightExpression, typename Enable = void>
		struct _addition_level4 {
			typedef typename _addition_level5<LeftExpression, RightExpression>::type type;
		};

		template<typename LeftLeftArgument, typename CommonArgument>
		struct _addition_level4<mul<LeftLeftArgument, CommonArgument>, CommonArgument, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument> > > > {
			typedef product_t<addition_t<LeftLeftArgument, constant_value<1> >, CommonArgument, value_mapping> type; // (P * A) + A = (P + 1) * A (simplify)
		};

		template<typename LeftLeftArgument, typename... CommonArguments>
		struct _addition_level4<mul<LeftLeftArgument, CommonArguments...>, mul<CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, constant_value<1> >, add_t<LeftLeftArgument, constant_value<1> >, add_t<constant_value<1>, LeftLeftArgument > > > > {
			typedef product_t<addition_t<LeftLeftArgument, constant_value<1> >, mul_t<CommonArguments...>, value_mapping> type; // (P * A * ...) + (A * ...) = (P + 1) * (A * ...) (simplify)
		};

		template<typename CommonArgument, typename RightLeftArgument>
		struct _addition_level4<CommonArgument, mul<RightLeftArgument, CommonArgument>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
			typedef product_t<addition_t<constant_value<1>, RightLeftArgument>, CommonArgument, value_mapping> type; // A + (P * A) = (1 + P) * A (simplify)
		};

		template<typename... CommonArguments, typename RightLeftArgument>
		struct _addition_level4<mul<CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<constant_value<1>, RightLeftArgument>, add_t<constant_value<1>, RightLeftArgument>, add_t<RightLeftArgument, constant_value<1> > > > > {
			typedef product_t<addition_t<constant_value<1>, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping> type; // A * ... + (P * A * ...) = (1 + P) * (A * ...) (simplify)
		};

		template<typename LeftLeftArgument, typename CommmonArgument, typename RightLeftArgument>
		struct _addition_level4<mul<LeftLeftArgument, CommmonArgument>, mul<RightLeftArgument, CommmonArgument>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
			typedef product_t<addition_t<LeftLeftArgument, RightLeftArgument>, CommmonArgument, value_mapping> type; // (P * A) + (Q * A) = (P + Q) * A (simplify)
		};

		template<typename LeftLeftArgument, typename... CommonArguments, typename RightLeftArgument>
		struct _addition_level4<mul<LeftLeftArgument, CommonArguments...>, mul<RightLeftArgument, CommonArguments...>, std::enable_if_t<!is_any_v<addition_t<LeftLeftArgument, RightLeftArgument>, add_t<LeftLeftArgument, RightLeftArgument>, add_t<RightLeftArgument, LeftLeftArgument> > > > {
			typedef product_t<addition_t<LeftLeftArgument, RightLeftArgument>, mul_t<CommonArguments...>, value_mapping> type; // (P * A * ...) + (Q * A * ...) = (P + Q) * (A * ...) (simplify)
		};

		// Specialization of _addition_level3<LeftExpression, RightExpression>.
		template<typename LeftExpression, typename RightExpression>
		struct _addition_level3 {
			typedef typename _addition_level4<LeftExpression, RightExpression>::type type;
		};

		template<typename CommonExpression>
		struct _addition_level3<CommonExpression, CommonExpression> {
			typedef product_t<constant_value<2>, CommonExpression, value_mapping> type; // A + A = 2 * A (simplify)
		};

		// Specialization of _addition_level2<LeftExpression, RightExpression>.
		template<typename LeftExpression, typename RightExpression>
		struct _addition_level2 {
			typedef typename _addition_level3<LeftExpression, RightExpression>::type type;
		};

		template<typename LeftArgument>
		struct _addition_level2<LeftArgument, constant_value<0> > {
			typedef LeftArgument type; // simplify
		};

		template<typename RightExpression>
		struct _addition_level2<constant_value<0>, RightExpression> {
			typedef RightExpression type; // simplify
		};

		template<>
		struct _addition_level2<constant_value<0>, constant_value<0> > {
			typedef constant_value<0> type; // simplify
		};

		// Specialization of _addition_level1<LeftExpression, RightExpression> (merge add<...>).
		template<typename LeftExpression, typename RightExpression, typename Enable = void>
		struct _addition_level1;

		template<typename LeftExpression, typename RightExpression>
		struct _addition_level1<LeftExpression, RightExpression, std::enable_if_t<!(is_function_v<name_t::add, LeftExpression> || is_function_v<name_t::add, RightExpression>)> > {
			typedef typename _addition_level2<LeftExpression, RightExpression>::type type;
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<le_v<LeftArgument, RightArgument> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, add<RightArgument, RightNextArguments...> > > type; // merge
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightArgument, typename... RightNextArguments>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, add<RightArgument, RightNextArguments...>, std::enable_if_t<lt_v<RightArgument, LeftArgument> > > {
			typedef addition_t<RightArgument, addition_t<add<LeftArgument, LeftNextArguments...>, add_t<RightNextArguments...> > > type; // merge
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && lt_v<RightArgument, LeftExpression> > > {
			typedef addition_t<RightArgument, addition_t<LeftExpression, add_t<RightNextArguments...> > > type; // merge
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && le_v<LeftExpression, RightArgument> && !std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
			typedef addition_t<addition_t<LeftExpression, RightArgument>, add_t<RightNextArguments...> > type; // simplification found (simplify-and-merge)
		};

		template<typename LeftExpression, typename RightArgument, typename... RightNextArguments>
		struct _addition_level1<LeftExpression, add<RightArgument, RightNextArguments...>, std::enable_if_t<!is_function_v<name_t::add, LeftExpression> && le_v<LeftExpression, RightArgument> && std::is_same_v<addition_t<LeftExpression, RightArgument>, add<LeftExpression, RightArgument> > > > {
			typedef add_t<LeftExpression, RightArgument, RightNextArguments...> type; // no simplification found (bind)
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::add, RightExpression> && le_v<LeftArgument, RightExpression> > > {
			typedef addition_t<LeftArgument, addition_t<add_t<LeftNextArguments...>, RightExpression> > type; // merge
		};

		template<typename LeftArgument, typename... LeftNextArguments, typename RightExpression>
		struct _addition_level1<add<LeftArgument, LeftNextArguments...>, RightExpression, std::enable_if_t<!is_function_v<name_t::add, RightExpression> && lt_v<RightExpression, LeftArgument> > > {
			typedef addition_t<RightExpression, add<LeftArgument, LeftNextArguments...> > type; // merge
		};

		// Specialization of _addition<LeftExpression, RightExpression> (add components).
		template<typename LeftExpression, typename RightExpression>
		struct _addition {
			typedef typename _addition_level1<LeftExpression, RightExpression>::type type;
		};

		template<typename LeftCoefficient, default_integral_t LeftBasisVectors, typename RightCoefficient, default_integral_t RightBasisVectors>
		struct _addition<component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, component<RightCoefficient, constant_basis_blade<RightBasisVectors> > > {
			typedef std::conditional_t<
				std::is_same_v<LeftCoefficient, constant_value<0> >,
				component<RightCoefficient, constant_basis_blade<RightBasisVectors> >, // 0 * 1 + A * Ej = A * Ej (simplify)
				std::conditional_t<
					std::is_same_v<RightCoefficient, constant_value<0> >,
					component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, // A * Ei + 0 * 1 = A * Ei (simplify)
					std::conditional_t<
						LeftBasisVectors == RightBasisVectors,
						component_t<addition_t<LeftCoefficient, RightCoefficient>, constant_basis_blade<LeftBasisVectors> >, // A * Ei + B * Ei = (A + B) * Ei (simplify)
						std::conditional_t<
							lt_v<component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, component<RightCoefficient, constant_basis_blade<RightBasisVectors> > >,
							add_t<component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, component<RightCoefficient, constant_basis_blade<RightBasisVectors> > >, // bind
							add_t<component<RightCoefficient, constant_basis_blade<RightBasisVectors> >, component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> > > // sort and bind
						>
					>
				>
			> type;
		};

		template<typename LeftCoefficient, default_integral_t LeftBasisVectors, typename RightCoefficient, default_bitset_t RightPossibleGrades, typename RightBitset>
		struct _addition<component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> > > {
			typedef std::conditional_t<
				std::is_same_v<LeftCoefficient, constant_value<0> >,
				component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> >, // 0 * 1 + A * Ej = A * Ej (simplify)
				std::conditional_t<
					lt_v<component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> > >,
					add_t<component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> >, component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> > >, // bind
					add_t<component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> >, component<LeftCoefficient, constant_basis_blade<LeftBasisVectors> > > // sort and bind
				>
			> type;
		};

		template<typename LeftCoefficient, default_bitset_t LeftPossibleGrades, typename LeftBitset, typename RightCoefficient, default_integral_t RightBasisVectors>
		struct _addition<component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, component<RightCoefficient, constant_basis_blade<RightBasisVectors> > > {
			typedef std::conditional_t<
				std::is_same_v<RightCoefficient, constant_value<0> >,
				component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, // A * Ei + 0 * 1 = A * Ei (simplify)
				std::conditional_t<
					lt_v<component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, component<RightCoefficient, constant_basis_blade<RightBasisVectors> > >,
					add_t<component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, component<RightCoefficient, constant_basis_blade<RightBasisVectors> > >, // bind
					add_t<component<RightCoefficient, constant_basis_blade<RightBasisVectors> >, component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> > > // sort and bind
				>
			> type;
		};

		template<typename LeftCoefficient, default_bitset_t LeftPossibleGrades, typename LeftBitset, typename RightCoefficient, default_bitset_t RightPossibleGrades, typename RightBitset>
		struct _addition<component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> > > {
			typedef std::conditional_t<
				lt_v<component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> > >,
				add_t<component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> >, component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> > >, // bind
				add_t<component<RightCoefficient, dynamic_basis_blade<RightPossibleGrades, RightBitset> >, component<LeftCoefficient, dynamic_basis_blade<LeftPossibleGrades, LeftBitset> > > // sort and bind
			> type;
		};

	}

}

#endif // __GA_CORE_EXPRESSION_ADDITION_HPP__
