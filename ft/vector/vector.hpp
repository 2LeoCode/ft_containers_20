/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Leo Suardi <lsuardi@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:38:31 by Leo Suardi        #+#    #+#             */
/*   Updated: 2022/10/10 01:21:24 by Leo Suardi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "../ft.namespace.hpp"
# include "../allocator/allocator.hpp"
# include "../iterator/iterator.hpp"
# include "../iterator/reverse_iterator.hpp"

# include <cstdint>
# include <initializer_list>
# include <algorithm>

template <
	class T,
	class Allocator = ft::allocator< T >
> class ft::vector {

public:

	typedef T											value_type;
	typedef Allocator									allocator_type;
	typedef std::size_t									size_type;
	typedef std::ptrdiff_t								difference_type;
	typedef T*											pointer;
	typedef const T*									const_pointer;
	typedef T&											reference;
	typedef const T&									const_reference;
	typedef pointer_iterator<T, difference_type>		iterator;
	typedef pointer_const_iterator<T, difference_type>	const_iterator;
	typedef ft::reverse_iterator< iterator >			reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;





	constexpr vector( void )
	noexcept(noexcept(allocator_type()))
	:		m_allocator(),
			m_size(0),
			m_capacity(0),
			m_data(m_allocator.allocate(0));
	{ }





	constexpr vector(
		const vector & other
	) :		m_size(other.m_size),
			m_capacity(other.m_capacity),
			m_allocator(other.m_allocator),
			m_data(m_allocator.allocate(m_capacity)) {
		auto src = other.begin();
		std::for_each(
			begin(),
			end(),
			[&src]( reference elem ) {
				allocator_traits< allocator_type >::construct(
					&elem,
					*src++
				);
			}
		);
	}

	constexpr vector(
		const vector & other,
		const allocator_type & alloc
	) :		m_size(other.m_size),
			m_capacity(other.m_capacity),
			m_allocator(alloc),
			m_data(m_allocator.allocate(m_capacity)) {
		auto src = other.begin();
		std::for_each(
			begin(),
			end(),
			[&src]( reference elem ) {
				allocator_traits< allocator_type >::construct(
					&elem,
					*src++
				);
			}
		);
	}





	constexpr vector(
		vector && other
	) noexcept
	:		m_size(other.m_size),
			m_capacity(other.m_capacity),
			m_allocator(other.m_allocator),
			m_data(other.m_data) {
		other.m_size = other.m_capacity = 0;
		other.m_data = nullptr;
	}

	constexpr vector(
		vector && other,
		const allocator_type & alloc
	) noexcept
	:		m_size(other.m_size),
			m_capacity(other.m_capacity),
			m_allocator(alloc),
			m_data(other.m_data) {
		other.m_size = other.m_capacity = 0;
		other.m_data = nullptr;
	}





	constexpr explicit vector(
		const allocator_type & alloc
	) :		m_size(0),
			m_capacity(0),
			m_allocator(alloc),
			m_data(m_allocator.allocate(0))
	{ }

	constexpr vector(
		size_type count,
		const_reference value,
		const allocator_type & alloc = allocator_type()
	) :		m_size(count),
			m_capacity(count),
			m_allocator(alloc),
			m_data(m_allocator.allocate(m_capacity)) {
		std::for_each(
			begin(),
			end(),
			[value]( reference elem ) {
				allocator_traits< allocator_type >::construct(
					&elem,
					value
				);
			}
		);
	}

	constexpr explicit vector(
		size_type count,
		const allocator_type & alloc = allocator_type()
	) :		m_size(count),
			m_capacity(count),
			m_allocator(alloc),
			m_data(m_allocator.allocate(m_capacity)) {
		std::for_each(
			begin(),
			end(),
			[]( reference elem ) {
				allocator_traits< allocator_type >::construct(
					&elem,
					value_type()
				);
			}
		);
	}

	template < class InputIt >
	constexpr vector(
		InputIt first,
		InputIt last,
		const allocator_type & alloc = allocator_type()
	) :		m_size(std::distance(first, last)),
			m_capacity(m_size),
			m_allocator(alloc),
			m_data(m_allocator.allocate(m_capacity)) {
		std::for_each(
			begin(),
			end(),
			[&first]( reference elem ) {
				allocator_traits< allocator_type >::construct(
					&elem,
					*first++
				);
			}
		);
	}

	constexpr vector(
		std::initializer_list< value_type > init,
		const allocator_type & alloc = allocator_type()
	) :		m_size(init.size()),
			m_capacity(init.size()),
			m_allocator(alloc),
			m_data(m_allocator.allocate(m_capacity)) {
		auto src = init.begin();
		std::for_each(
			begin(),
			end(),
			[&src]( reference elem ) {
				allocator_traits< allocator_type >::construct(
					&elem,
					*src++
				);
			}
		);
	}





	constexpr ~vector( void ) {
		std::for_each(
			begin(),
			end(),
			[]( reference elem ) {
				allocator_traits< allocator_type >::destroy(&elem);
			}
		);
		m_allocator.deallocate(m_data, m_capacity);
	}





	constexpr vector & operator = (
		const vector & other
	) {
		if (this == &other)
			return ;

		reserve(other.m_capacity);
		std::copy(other.begin(), other.begin() + m_size, begin());

		if (other.m_size > m_size) {
			auto src = other.begin() + m_size;
			std::for_each(
				end(),
				end() + other.m_size - m_size,
				[&src]( reference elem ) {
					allocator_traits< allocator_type >::construct(
						&elem,
						*src++
					);
				}
			)
		}
		m_size = other.m_size;
	}

	constexpr vector & operator = (
		vector && other
	) noexcept {
		if (this == &other)
			return ;

		clear();
		m_allocator.deallocate(m_data, m_capacity);
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_allocator = other.m_allocator;
		m_data = other.m_data;

		other.m_size = other.m_capacity = 0;
		other.m_data = nullptr;
	}

	constexpr vector & operator = (
		std::initializer_list< T > ilist
	) {
		reserve(ilist.size());
		if (m_size > ilist.size()) {
			std::copy(ilist.begin(), ilist.end(), begin());
			std::for_each(
				begin() + ilist.size(),
				end(),
				[]( reference elem ) {
					allocator_traits< allocator_type >::destroy(&elem);
				}
			);
		} else if (m_size < ilist.size()) {
			std::copy(ilist.begin(), ilist.begin() + m_size, begin());

			auto src = ilist.begin() + m_size;
			std::for_each(
				end(),
				end() + ilist.size() - m_size,
				[&src]( reference elem ) {
					allocator_traits< allocator_type >::construct(
						&elem,
						*src++
					);
				}
			);
		}
		m_size = ilist.size();
		
	}





private:

	size_type m_size, m_capacity;
	allocator_type m_allocator;
	pointer m_data;
};

#endif
