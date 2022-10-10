/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.namespace.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:40:13 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 16:14:22 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <compare>

namespace ft {



#if defined(VECTOR_HPP) && !defined(FT_VECTOR)
# define FT_VECTOR

	template <
		class T,
		class Allocator
	> class vector;

#endif





#if defined(ITERATOR_HPP) && !defined(FT_ITERATOR)
# define FT_ITERATOR

	template < class T, class Diff >
	class iterator;

	template < class T, class Diff >
	constexpr iterator< T, Diff > operator + (
		Diff n,
		const iterator< T, Diff > & iter
	) noexcept;

	template < class Iter1, class Iter2 >
	constexpr bool operator < (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template < class Iter1, class Iter2 >
	constexpr bool operator > (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template < class Iter1, class Iter2 >
	constexpr bool operator <= (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template < class Iter1, class Iter2 >
	constexpr bool operator >= (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template < class Iter1, class Iter2 >
	constexpr bool operator == (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template < class Iter1, class Iter2 >
	constexpr bool operator != (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template< class Iter1, std::three_way_comparable_with< Iter1 > Iter2 >
	constexpr std::compare_three_way_result_t< Iter1, Iter2 > operator <=> (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	template < class T, class Diff >
	using pointer_const_iterator = iterator< const T*, Diff >;

	template < class T, class Diff >
	using pointer_iterator = iterator< T*, Diff >;

#endif





#if defined(REVERSE_ITERATOR_HPP) && !defined(FT_REVERSE_ITERATOR)
# define FT_REVERSE_ITERATOR

	template < class Iter >
	class reverse_iterator;

#endif





#if defined(ITERATOR_TRAITS_HPP) && !defined(FT_ITERATOR_TRAITS)
# define FT_ITERATOR_TRAITS

	template < class Iter >
	struct iterator_traits;

#endif





#if defined(ALLOCATOR_HPP) && !defined(FT_ALLOCATOR)
# define FT_ALLOCATOR

	template < class T >
	class allocator;

#endif



}
