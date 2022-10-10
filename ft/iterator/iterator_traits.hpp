/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:21:06 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 14:27:54 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include "../ft.namespace.hpp"
# include <iterator>
# include <concepts>

template < class T >
concept has_difference_type = requires { typename T::difference_type; };

template < class T >
concept has_value_type = requires { typename T::value_type; };

template < class T >
concept has_pointer = requires { typename T::pointer; };

template < class T >
concept has_reference = requires { typename T::reference; };

template < class T >
concept has_iterator_category = requires { typename T::iterator_category; };

template < class T >
concept has_arrow_operator = requires { std::is_pointer_v<T> || std::declval<T&>().operator->(); };

template < class T >
concept is_referenceable = requires { !std::same_as< T, void >; };





template<class I>
concept LegacyIterator =
	requires (I i) {
		{   *i } -> is_referenceable;
		{  ++i } -> std::same_as<I&>;
		{ *i++ } -> is_referenceable;
	} && std::copyable<I>;

template<class I>
concept LegacyInputIterator =
	LegacyIterator<I> && std::equality_comparable<I> && requires (I i) {
		typename std::incrementable_traits<I>::difference_type;
		typename std::indirectly_readable_traits<I>::value_type;
		typename std::common_reference_t<std::iter_reference_t<I>&&,
					typename std::indirectly_readable_traits<I>::value_type&>;
		*i++;
		typename std::common_reference_t<decltype(*i++)&&,
					typename std::indirectly_readable_traits<I>::value_type&>;
		requires std::signed_integral<typename std::incrementable_traits<I>::difference_type>;
	};

template<class I>
concept LegacyForwardIterator =
	LegacyInputIterator<I> && std::constructible_from<I> &&
	std::is_lvalue_reference_v<std::iter_reference_t<I>> &&
	std::same_as<
		std::remove_cvref_t<std::iter_reference_t<I>>,
		typename std::indirectly_readable_traits<I>::value_type> &&
	requires (I it) {
		{  it++ } -> std::convertible_to<const I&>;
		{ *it++ } -> std::same_as<std::iter_reference_t<I>>;
	};

template<class I>
concept LegacyBidirectionalIterator =
	LegacyForwardIterator<I> && requires (I i) {
		{  --i } -> std::same_as<I&>;
		{  i-- } -> std::convertible_to<const I&>;
		{ *i-- } -> std::same_as<std::iter_reference_t<I>>;
	};

template<class I>
concept LegacyRandomAccessIterator =
	LegacyBidirectionalIterator<I> && std::totally_ordered<I> &&
	requires(I i, typename std::incrementable_traits<I>::difference_type n) {
		{ i += n } -> std::same_as<I&>;
		{ i -= n } -> std::same_as<I&>;
		{ i +  n } -> std::same_as<I>;
		{ n +  i } -> std::same_as<I>;
		{ i -  n } -> std::same_as<I>;
		{ i -  i } -> std::same_as<decltype(n)>;
		{  i[n]  } -> std::convertible_to<std::iter_reference_t<I>>;
	};





template <
	class Iter,
	bool IncrementableTraitsHaveDifferenceType = false
> struct iterator_traits___basic
{ typedef void difference_type; };

template < class Iter >
struct iterator_traits___basic<
	Iter,
	true	// IncrementableTraitsHaveDifferenceType
>
{ typedef typename std::incrementable_traits< Iter >::difference_type
	difference_type; };





template <
	class Iter,
	bool IsLegacyIterator = false
> struct iterator_traits___
{ };

template < class Iter >
struct iterator_traits___<
	Iter,
	true	// IsLegacyIterator
> : public iterator_traits___basic<
		Iter,
		has_difference_type< std::incrementable_traits< Iter > >
	> {
	typedef void						value_type;
	typedef void						pointer;
	typedef void						reference;
	typedef std::output_iterator_tag	iterator_category;
};





template <
	class Iter,
	bool IsLegacyForwardIterator = false
> struct iterator_traits__input______
{ typedef std::input_iterator_tag iterator_category; };

template < class Iter >
struct iterator_traits__input______<
	Iter,
	true	// IsLegacyForwardIterator
>
{ typedef std::forward_iterator_tag iterator_category; };





template <
	class Iter,
	bool IsLegacyBidirectionalIterator = false
> struct iterator_traits__input_____
:	public iterator_traits__input______<
		Iter,
		LegacyForwardIterator< Iter >
	>
{ };

template < class Iter >
struct iterator_traits__input_____<
	Iter,
	true	// IsLegacyBidirectionalIterator
>
{ typedef std::bidirectional_iterator_tag iterator_category; };





template <
	class Iter,
	bool IsLegacyRandomAccessIterator = false
> struct iterator_traits__input____
:	public iterator_traits__input_____<
		Iter,
		LegacyBidirectionalIterator< Iter >
	>
{ };

template < class Iter >
struct iterator_traits__input____<
	Iter,
	true	// IsLegacyRandomAccessIterator
>
{ typedef std::random_access_iterator_tag iterator_category; };




template <
	class Iter,
	bool HasIteratorCategory = false
> struct iterator_traits__input___
:	public iterator_traits__input____<
		Iter,
		LegacyRandomAccessIterator< Iter >
	>
{ };

template < class Iter >
struct iterator_traits__input___<
	Iter,
	true	// HasIteratorCategory
>
{ typedef typename Iter::iterator_category iterator_category; };





template <
	class Iter,
	bool HasReference = false
> struct iterator_traits__input__
:	public iterator_traits__input___<
		Iter,
		has_iterator_category< Iter >
	>
{ typedef std::iter_reference_t< Iter > reference; };

template < class Iter >
struct iterator_traits__input__<
	Iter,
	true	// HasReference
> :	public iterator_traits__input___<
		Iter,
		has_iterator_category< Iter >
	>
{ typedef typename Iter::reference reference; };





template <
	class Iter,
	bool HasArrowOperator = false
> struct iterator_traits__input_
:	public iterator_traits__input__<
		Iter,
		has_reference< Iter >
	>
{ typedef void pointer; };

template < class Iter >
struct iterator_traits__input_<
	Iter,
	true	// HasArrowOperator
> :	public iterator_traits__input__<
		Iter,
		has_reference< Iter >
	>
{ typedef decltype(std::declval<Iter&>().operator->()) pointer; };





template <
	class Iter,
	bool HasPointer = false
> struct iterator_traits__input
:	public iterator_traits__input_<
		Iter,
		has_arrow_operator< Iter >
	>
{ };

template < class Iter >
struct iterator_traits__input<
	Iter,
	true	// HasPointer
> :	public iterator_traits__input__<
		Iter,
		has_reference< Iter >
	>
{ typedef typename Iter::pointer pointer; };





template <
	class Iter,
	bool IsLegacyInputIterator = false
> struct iterator_traits__
:	public iterator_traits___<
		Iter,
		LegacyIterator< Iter >
	>
{ };

template < class Iter >
struct iterator_traits__<
	Iter,
	true	// IsLegacyInputIterator
> : public iterator_traits__input<
		Iter,
		has_pointer< Iter >
	> {
	typedef typename std::incrementable_traits<Iter>::difference_type
		difference_type;
	typedef typename std::indirectly_readable_traits<Iter>::value_type
		value_type;
};




template <
	class Iter,
	bool HasDifferenceType,
	bool HasValueType,
	bool HasPointer,
	bool HasReference,
	bool HasIteratorCategory
> struct iterator_traits_
:	public iterator_traits__<
		Iter,
		LegacyInputIterator< Iter >
	>
{ };

template < class Iter >
struct iterator_traits_<
	Iter,
	true,	// HasDifferenceType
	true,	// HasValueType
	false,	// HasPointer
	true,	// HasReference
	true	// HasIteratorCategory
> {
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef void								pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};

template < class Iter >
struct iterator_traits_<
	Iter,
	true,	// HasDifferenceType
	true,	// HasValueType
	true,	// HasPointer
	true,	// HasReference
	true	// HasIteratorCategory
> {
	typedef typename Iter::difference_type		difference_type;
	typedef typename Iter::value_type			value_type;
	typedef typename Iter::pointer				pointer;
	typedef typename Iter::reference			reference;
	typedef typename Iter::iterator_category	iterator_category;
};





template < class Iter >
struct ft::iterator_traits
:	public iterator_traits_<
		Iter,
		has_difference_type< Iter >,
		has_value_type< Iter >,
		has_pointer< Iter >,
		has_reference< Iter >,
		has_iterator_category< Iter >
	>
{ };

template < class T >
	requires requires { std::is_object_v<T>; }
struct ft::iterator_traits< T* > {
	typedef std::ptrdiff_t					difference_type;
	typedef ft::remove_cv_t< T >			value_type;
	typedef T*								pointer;
	typedef T&								reference;
	typedef std::random_access_iterator_tag	iterator_category;
	typedef std::contiguous_iterator_tag	iterator_concept;
}; 

#endif
