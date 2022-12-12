#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <cstring>

namespace ft {

template< class Type, class Allocator = std::allocator<Type> >
class vector
{
	public:
		// Member types (aliases)
		typedef Type value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		/*
		 * Member functions
		 */
		// Constructors
		vector(void);
		~vector(void);

		// Operator=
		//vector&	operator=(const vector& other);

		// Element access
		const_reference operator[](size_type pos) const;
		reference operator[](size_type pos);

		// Iterators

		// Capacity
		size_type	size(void) const;

		// Modifiers
		void	push_back(const Type& value);
		void	pop_back(void);
	private:
		allocator_type			_alloc;
		static const size_type	_initialCapacity;
		size_type				_vectorCapacity;
		size_type				_vectorSize;
		pointer 				_elements;
};

} //namespace

#include "vector.tpp"

#endif
