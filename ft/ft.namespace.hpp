/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.namespace.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo Suardi <lsuardi@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:40:13 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 00:49:06 by Leo Suardi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		std::size_t n,
		const iterator< T, Diff > & iter
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
