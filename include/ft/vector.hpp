#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

namespace ft {

template< class Type, class Allocator = std::allocator<Type> >
class vector
{
	public:
		vector(void);

		// Member types : Basically they are just aliases.
		using value_type = Type;
		using allocator_type = Allocator;
		using size_type = std::size_t;
		using difference_type = std::ptrdiff_t;
		using reference = value_type&;
		using const_reference = const value_type&;
		using pointer = typename Allocator::pointer;
		using const_pointer = typename Allocator::const_pointer;

		// Element access
		reference operator[](size_type pos);
		const_reference operator[](size_type pos) const;

		// Iterators

		// Capacity
		size_type	size(void) const;

		// Modifiers
		void	push_back(const Type& value);
		void	pop_back(void);
	private:
		size_type		_vectorSize;
		pointer			_elements;
		allocator_type	alloc;
};

} //namespace

#include "vector.tpp"
#endif
