#ifndef __GA_CLIFFORD_CLIFFORD_EXPRESSION_COPY_HPP__
#define __GA_CLIFFORD_CLIFFORD_EXPRESSION_COPY_HPP__

namespace ga {

	namespace clifford {

		namespace detail {

			template<class InputItrType, class OutputItrType>
			constexpr void copy(InputItrType const &in, OutputItrType const &out) {
				out.element() = in.element();
				copy(next(in), next(out));
			}

			constexpr void copy(itr_end const &in, itr_end const &out) {
			}

		}

	}

}

#endif // __GA_CLIFFORD_CLIFFORD_EXPRESSION_COPY_HPP__
