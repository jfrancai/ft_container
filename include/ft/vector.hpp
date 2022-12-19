#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <sstream>

namespace ft {

template< class Type, class Allocator = std::allocator< Type > >
class vector
{
	public:
		// Member types (aliases)
		typedef Type 								value_type;
		typedef Allocator 							allocator_type;
		typedef std::size_t 						size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;

		/*
		 * Member functions
		 */

		// Constructors
		explicit vector( const Allocator& alloc = Allocator());
		vector( const vector& other);

		// Destructor
		~vector(void);

		// operator=
		vector&	operator=(const vector& other);

		// asssign
		void	assign(size_type count, const Type& value);

		// allocator_type
		allocator_type get_allocator(void) const;

		//// Element access ////

		// at
		const_reference at( size_type pos ) const;
		reference at( size_type pos );

		// operator[]
		const_reference operator[](size_type pos) const;
		reference operator[](size_type pos);

		// front
		reference front(void);
		const_reference front(void) const;

		// back
		reference back(void);
		const_reference back(void) const;

		// data
		pointer			data(void);
		const_pointer	data(void) const;

		//// Iterators ////

		//// Capacity ////

		// empty
		bool	empty(void);

		// size
		size_type	size(void) const;

		// max_size
		size_type max_size() const;

		// reserve
		void reserve( size_type new_cap );

		// capacity
		size_type	capacity(void) const;

		//// Modifiers ////
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
