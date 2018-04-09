#ifndef __GA_CLIFFORD_BASIC_ITERATORS_HPP__
#define __GA_CLIFFORD_BASIC_ITERATORS_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			class itr_end {
			};

			constexpr itr_end begin(empty_clifford_expression &) {
				return itr_end();
			}

			constexpr itr_end begin(empty_clifford_expression const &) {
				return itr_end();
			}

			constexpr itr_end obegin(empty_clifford_expression &) {
				return itr_end();
			}

			constexpr itr_end obegin(empty_clifford_expression const &) {
				return itr_end();
			}

			template<class ValueType>
			class itr_value {
			public:

				typedef ValueType value_type;

				typedef component<value_type, cbasis_blade<0> > element_type;

				constexpr itr_value() = default;

				constexpr itr_value(value_type const &value) :
					element_(make_component(value, cbasis_blade<0>())) {
				}

				constexpr decltype(auto) element() const {
					return element_;
				}

			protected:

				element_type const element_;

				static_assert(is_lazy_expression<ValueType>::value, "The ValueType template argument of ga::clifford::detail::itr_value<ValueType> should be a subclass of ga::lazy::lazy_expression<ExpressionType>.");
			};

			template<class ExpressionType, typename std::enable_if<!std::is_same<ExpressionType, constant<0> >::value, int>::type = 0>
			constexpr itr_value<ExpressionType> begin(lazy_expression<ExpressionType> const &arg) {
				return itr_value<ExpressionType>(arg());
			}

			template<class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
			constexpr decltype(auto) begin(ValueType const &arg) {
				return begin(value<ValueType>(arg));
			}

			constexpr itr_end begin(constant<0> const &) {
				return itr_end();
			}

			template<class ExpressionType>
			constexpr decltype(auto) obegin(lazy_expression<ExpressionType> const &arg) {
				return begin(arg);
			}

			template<class ValueType, typename std::enable_if<!(is_lazy_expression<ValueType>::value || is_clifford_expression<ValueType>::value), int>::type = 0>
			constexpr decltype(auto) obegin(ValueType const &arg) {
				return begin(arg);
			}

			template<class ValueType>
			constexpr itr_end next(itr_value<ValueType> const &) {
				return itr_end();
			}

		}

	}

}

#endif // __GA_CLIFFORD_BASIC_ITERATORS_HPP__
