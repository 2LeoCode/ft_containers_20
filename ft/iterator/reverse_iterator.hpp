/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:10:30 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 16:15:32 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "../ft.namespace.hpp"

# include <iterator>


template <
	class Iter,
	bool IsIteratorCategoryDerivedFromRandomAccessIteratorTag = false
> struct reverse_iterator__
{ typedef ft::iterator_traits<Iter>::iterator_category iterator_category; };

template < class Iter >
struct reverse_iterator__<
	Iter,
	true	// IsIteratorCategoryDerivedFromRandomAccessIteratorTag
>
{ typedef std::random_access_iterator_tag iterator_category; };






template <
	class Iter,
	bool IsRandomAccessIterator = false
> struct reverse_iterator_
:	public reverse_iterator__<
		Iter,
		std::derived_from<
			ft::iterator_traits< Iter >::iterator_category,
			std::random_access_iterator_tag
		>
	>
{ typedef std::bidirectional_iterator_tag iterator_concept; };

template < class Iter >
struct reverse_iterator_<
	Iter,
	true	// IsRandomAccessIterator
> :	public reverse_iterator__<
		Iter,
		std::derived_from<
			ft::iterator_traits< Iter >::iterator_category,
			std::random_access_iterator_tag
		>
	>
{ typedef std::random_access_iterator_tag iterator_concept; };






template < class Iter >
	requires std::bidirectional_iterator< Iter >
class ft::reverse_iterator : public reverse_iterator_<
		Iter,
		std::random_access_iterator< Iter >
	> {

public:

	typedef Iter									iterator_type;
	typedef std::iter_value_t< Iter >				value_type;
	typedef std::iter_difference_t< Iter >			difference_type;
	typedef ft::iterator_traits< Iter >::pointer	pointer;
	typedef std::iter_reference_t< Iter >			reference;

	constexpr reverse_iterator( void ) = default;





	constexpr explicit reverse_iterator( iterator_type x )
	:		current(x)
	{ }

	template < class U >
		requires ( !std::same_as< Iter, U > && std::convertible_to< const U&, Iter > )
	constexpr reverse_iterator( const reverse_iterator< U > & other )
	:		current(other.base())
	{ }





	template < class U >
		requires (
			!std::same_as<Iter, U>
			&& std::convertible_to<const U&, Iter>
			&& std::assignable_from<Iter&, const U&>
		)
	constexpr reverse_iterator & operator = (
		const reverse_iterator< U > & other
	) {
		current = other.base();
		return *this;
	}





	constexpr iterator_type base( void ) const
	{ return current; }





	constexpr reference operator * ( void ) const {
		iterator_type tmp = current;
		return *--tmp;
	}

	constexpr pointer operator -> ( void ) const
		requires (
			std::is_pointer_v<Iter>
			|| requires (const Iter i) { i.operator->(); }
		)
	{ return std::addressof(operator * ()); }





	constexpr reference operator [] ( difference_type n ) const
	{ return current[-n - 1]; }





	constexpr reverse_iterator & operator ++ ( void ) const {
		--current;
		return *this;
	}

	constexpr reverse_iterator operator ++ ( int ) const {
		reverse_iterator tmp = *this;
		--current;
		return tmp;
	}

	constexpr reverse_iterator & operator -- ( void ) const {
		++current;
		return *this;
	}

	constexpr reverse_iterator operator -- ( int ) const {
		reverse_iterator tmp = *this;
		++current;
		return tmp;
	}




	

protected:

	iterator_type	current;

};

#endif
