/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo Suardi <lsuardi@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:34:23 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 00:49:41 by Leo Suardi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "../ft.namespace.hpp"

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





	constexpr explicit iterator( const pointer & ptr )
	noexcept
	:		m_data(ptr)
	{ }

	constexpr explicit iterator( pointer && ptr )
	noexcept
	:		m_data(ptr)
	{ }





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





	constexpr iterator & operator += ( std::size_t n )
	noexcept {
		m_data += n;
		return *this;
	}

	constexpr iterator & operator -= ( std::size_t n )
	noexcept {
		m_data -= n;
		return *this;
	}





	constexpr bool operator == ( const iterator & other )
	const noexcept
	{ return m_data == other.m_data; }

	constexpr bool operator != ( const iterator & other )
	const noexcept
	{ return m_data != other.m_data; }

	constexpr bool operator < ( const iterator & other )
	const noexcept
	{ return m_data < other.m_data; }

	constexpr bool operator > ( const iterator & other )
	const noexcept
	{ return m_data > other.m_data; }

	constexpr bool operator <= ( const iterator & other )
	const noexcept
	{ return m_data <= other.m_data; }

	constexpr bool operator >= ( const iterator & other )
	const noexcept
	{ return m_data >= other.m_data; }





	constexpr reference operator * ( void )
	const noexcept
	{ return *m_data; }

	constexpr pointer operator -> ( void )
	const noexcept
	{ return m_data; }

	constexpr reference operator [] ( std::size_t n )
	const noexcept
	{ return m_data[n]; }





	constexpr iterator operator + ( std::size_t n )
	const noexcept
	{ return iterator(m_data + n); }

	constexpr iterator operator - ( std::size_t n )
	const noexcept
	{ return iterator(m_data - n); }

	constexpr iterator operator - ( const iterator & other )
	const noexcept
	{ return iterator(m_data - other.m_data); }


protected:

	pointer m_data;

};





template <
	class T,
	class Diff
> class ft::iterator< T*, Diff >
: public iterator< const T*, Diff > {

private:

	typedef iterator< const T*, Diff > super;
	using super::m_data;


public:

	typedef T			value_type;
	typedef value_type*	pointer;
	typedef value_type&	reference;

	using super::super;





	constexpr iterator( const iterator & other )
	noexcept = default;





	constexpr reference operator * ( void )
	noexcept
	{ return const_cast< reference >(*m_data); }

	constexpr pointer operator -> ( void )
	noexcept
	{ return const_cast< pointer >(m_data); }

	constexpr reference operator [] ( std::size_t n )
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





	constexpr iterator & operator += ( std::size_t n )
	noexcept {
		m_data += n;
		return *this;
	}

	constexpr iterator & operator -= ( std::size_t n )
	noexcept {
		m_data -= n;
		return *this;
	}





	constexpr iterator operator + ( std::size_t n )
	const noexcept
	{ return iterator(m_data + n); }

	constexpr iterator operator - ( std::size_t n )
	const noexcept
	{ return iterator(m_data - n); }

	constexpr iterator operator - ( const iterator & other )
	const noexcept
	{ return iterator(m_data - other.m_data); }

};





template < class T, class Diff >
constexpr ft::iterator< T, Diff > ft::operator + (
	std::size_t n,
	const ft::iterator< T, Diff > & iter
) noexcept
{ return iter + n; }

#endif
