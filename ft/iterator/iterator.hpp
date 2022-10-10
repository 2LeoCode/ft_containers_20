/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:34:23 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 16:14:31 by lsuardi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "../ft.namespace.hpp"
# include "../vector/vector.hpp"

# include <iterator>
# include <cstddef>

# include <iostream>

template < class T, class Diff >
class ft::iterator { };





template <
	class T,
	class Diff
> class ft::iterator< const T*, Diff > {

public:

	template < Class Allocator >
	friend class vector< T, Allocator >;

	template < class Iter1, class Iter2 >
	friend constexpr bool ft::operator < (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;

	typedef std::random_access_iterator_tag	iterator_category;
	typedef const T							value_type;
	typedef Diff							difference_type;
	typedef value_type*						pointer;
	typedef value_type&						reference;





	constexpr iterator( void )
	noexcept = default;





	constexpr iterator( const iterator & other )
	noexcept = default;




	constexpr iterator( iterator && other )
	noexcept = default;





	constexpr iterator & operator = ( const iterator & other )
	noexcept = default;

	constexpr iterator & operator = ( iterator && other )
	noexcept  = default;





	constexpr iterator & operator ++ ( void )
	noexcept {
		++m_data;
		return *this;
	}

	constexpr iterator operator ++ ( int )
	noexcept {
		iterator tmp(m_data);
		++m_data;
		return tmp;
	}

	constexpr iterator & operator -- ( void )
	noexcept {
		--m_data;
		return *this;
	}

	constexpr iterator operator -- ( int )
	noexcept {
		iterator tmp(m_data);
		--m_data;
		return tmp;
	}





	constexpr iterator & operator += ( difference_type n )
	noexcept {
		m_data += n;
		return *this;
	}

	constexpr iterator & operator -= ( difference_type n )
	noexcept {
		m_data -= n;
		return *this;
	}





	constexpr reference operator * ( void )
	const noexcept
	{ return *m_data; }

	constexpr pointer operator -> ( void )
	const noexcept
	{ return m_data; }

	constexpr reference operator [] ( difference_type n )
	const noexcept
	{ return m_data[n]; }





	constexpr iterator operator + ( difference_type n )
	const noexcept
	{ return iterator(m_data + n); }

	constexpr iterator operator - ( difference_type n )
	const noexcept
	{ return iterator(m_data - n); }

	constexpr iterator operator - ( const iterator & other )
	const noexcept
	{ return iterator(m_data - other.m_data); }


protected:

	pointer m_data;


private:

	constexpr explicit iterator( const pointer & ptr )
	noexcept
	:		m_data(ptr)
	{ }

	constexpr explicit iterator( pointer && ptr )
	noexcept
	:		m_data(ptr)
	{ }

};





template <
	class T,
	class Diff
> class ft::iterator< T*, Diff >
: public iterator< const T*, Diff > {

private:

	typedef iterator< const T*, Diff > super;

	using super::m_data;

	constexpr explicit iterator( const pointer & ptr )
	noexcept
	:		m_data(ptr)
	{ }

	constexpr explicit iterator( pointer && ptr )
	noexcept
	:		m_data(ptr)
	{ }


public:

	typedef T			value_type;
	typedef value_type*	pointer;
	typedef value_type&	reference;

	using super::super;

	template < Class Allocator >
	friend class vector< T, Allocator >;

	template < class Iter1, class Iter2 >
	friend constexpr bool ft::operator < (
		const Iter1 & lhs,
		const Iter2 & rhs
	) noexcept;





	constexpr iterator( const iterator & other )
	noexcept = default;





	constexpr reference operator * ( void )
	noexcept
	{ return const_cast< reference >(*m_data); }

	constexpr pointer operator -> ( void )
	noexcept
	{ return const_cast< pointer >(m_data); }

	constexpr reference operator [] ( difference_type n )
	noexcept
	{ return const_cast< reference >(m_data[n]); }





	constexpr iterator & operator = ( const iterator & other )
	noexcept = default;

	constexpr iterator & operator = ( iterator && other )
	noexcept = default;





	constexpr iterator & operator ++ ( void )
	noexcept {
		++m_data;
		return *this;
	}

	constexpr iterator operator ++ ( int )
	noexcept {
		iterator tmp(m_data);
		++m_data;
		return tmp;
	}

	constexpr iterator & operator -- ( void )
	noexcept {
		--m_data;
		return *this;
	}

	constexpr iterator operator -- ( int )
	noexcept {
		iterator tmp(m_data);
		--m_data;
		return tmp;
	}





	constexpr iterator & operator += ( difference_type n )
	noexcept {
		m_data += n;
		return *this;
	}

	constexpr iterator & operator -= ( difference_type n )
	noexcept {
		m_data -= n;
		return *this;
	}





	constexpr iterator operator + ( difference_type n )
	const noexcept
	{ return iterator(m_data + n); }

	constexpr iterator operator - ( difference_type n )
	const noexcept
	{ return iterator(m_data - n); }

	constexpr iterator operator - ( const iterator & other )
	const noexcept
	{ return iterator(m_data - other.m_data); }

};





template < class T, class Diff >
constexpr ft::iterator< T, Diff > ft::operator + (
	Diff n,
	const iterator< T, Diff > & iter
) noexcept
{ return iter + n; }





template < class Iter1, class Iter2 >
constexpr bool ft::operator < (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return lhs.m_data < rhs.m_data; }

template < class Iter1, class Iter2 >
constexpr bool ft::operator > (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return rhs < lhs; }

template < class Iter1, class Iter2 >
constexpr bool ft::operator <= (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return !(lhs > rhs); }

template < class Iter1, class Iter2 >
constexpr bool ft::operator >= (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return !(lhs < rhs); }

template < class Iter1, class Iter2 >
constexpr bool ft::operator == (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return lhs <= rhs && lhs >= rhs; }

template < class Iter1, class Iter2 >
constexpr bool ft::operator != (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return !(lhs == rhs); }

template< class Iter1, std::three_way_comparable_with< Iter1 > Iter2 >
constexpr std::compare_three_way_result_t< Iter1, Iter2 > ft::operator <=> (
	const Iter1 & lhs,
	const Iter2 & rhs
) noexcept
{ return lhs < rhs ? -1 : lhs != rhs; }

#endif
