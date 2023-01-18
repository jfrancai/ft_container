#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <ft/random_access_iterator.hpp>
#include <ft/reverse_iterator.hpp>

// Testing purpose
//#include <vector>
namespace ft {

template< class Type >
class	LegacyRandomAccessIterator;

template< class Type, class Allocator = std::allocator< Type > >
class vector
{
	public:

		// Member types (aliases)
		typedef Type 										value_type;
		typedef Allocator 									allocator_type;
		typedef std::size_t 								size_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef LegacyRandomAccessIterator< Type >			iterator;
		typedef LegacyRandomAccessIterator< const Type >	const_iterator;
		typedef ft::reverse_iterator< iterator >			reverse_iterator;
//		typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;

		/*
		 * Member functions
		 */

		// Constructors
		explicit vector( const Allocator& alloc = Allocator());
		explicit vector(size_type count, const Type& value = Type(), const Allocator& alloc = Allocator());
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

		// begin
		const_iterator	begin(void) const;
		iterator	begin(void);

		// end
		const_iterator	end(void) const;
		iterator	end(void);

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

		// clear
		void	clear(void);

		// erase
		iterator	erase(iterator pos);
		iterator	erase(iterator first, iterator last);

		// push_back
		void	push_back(const Type& value);

		// pop_back
		void	pop_back(void);

		// resize
		void	resize(size_type count, Type value = Type());

		// swap
		void	swap(vector< Type, Allocator > &other);

		// insert
		iterator	insert(const_iterator pos, const Type &value);

	private:
		allocator_type			_alloc;
		static const size_type	_initialCapacity;
		size_type				_vectorCapacity;
		size_type				_vectorSize;
		pointer 				_elements;
};

} // namespace ft

#include "vector.tpp"

#endif
