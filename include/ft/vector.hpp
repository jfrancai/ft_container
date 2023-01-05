#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <sstream>
#include <iterator>

// Testing purpose
#include <vector>

namespace ft {

template< class Type >
class LegacyRandomAccessIterator;

template< class Type, class Allocator = std::allocator< Type > >
class vector
{
	public:
		// Member types (aliases)
		typedef Type 								value_type;
		typedef Allocator 							allocator_type;
		typedef std::size_t 						size_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef LegacyRandomAccessIterator< Type >	iterator;
	
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

		iterator	begin(void);
		//const_iterator begin(void) const;

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

template< class Type >
class	LegacyRandomAccessIterator
{
	public:
		typedef std::random_access_iterator_tag		iterator_category;
		typedef Type 								value_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Type*								pointer;
		typedef Type&								reference;
		typedef LegacyRandomAccessIterator< Type >	iterator;


		// LegacyIterator
		LegacyRandomAccessIterator< Type >(const iterator& other) : _ptr(other._ptr) {}
		~LegacyRandomAccessIterator< Type >(void) {}
		iterator		&operator=(const iterator& other) { this->_ptr = other._ptr; return (*this); }
		iterator		&operator++(void) { ++_ptr; return (*this); }
		value_type		operator*(void) const { return (*_ptr); }

		// LegacyInputIterator
		iterator		operator++(int) { iterator it(_ptr); ++_ptr; return (it); }
		pointer			operator->(void) const { return (_ptr); }
		bool			operator==(const iterator& rhs) const { return (this->_ptr == rhs._ptr); }
		bool			operator!=(const iterator& rhs) const { return (this->_ptr != rhs._ptr); }

		// LegacyOutputIterator

		// LegacyForwardIterator
		explicit	LegacyRandomAccessIterator< Type >(pointer ptr = NULL) : _ptr(ptr) {}

		// LegacyBidirectionalIterator
		iterator		&operator--(void) { --_ptr; return (*this); }
		iterator		operator--(int) { iterator it(_ptr); --_ptr; return (it); }

		// LegacyRandomAccessIterator
		bool			operator<(const iterator& rhs) const { return (this->_ptr < rhs._ptr); }
		bool			operator>(const iterator& rhs) const { return (this->_ptr > rhs._ptr); }
		bool			operator<=(const iterator& rhs) const { return (this->_ptr <= rhs._ptr); }
		bool			operator>=(const iterator& rhs) const { return (this->_ptr >= rhs._ptr); }
		iterator		&operator+=(difference_type n) {  if (n >= 0) { while (n--) ++_ptr; } else { while(n++) --_ptr; } return (*this); }
		iterator		operator+(difference_type n) { iterator it(*this); return (it += n); }
		friend iterator	operator+(difference_type n, const iterator& rhs);

		/*
		iterator	&operator-=(difference_type n) {  if (n >= 0) { return (*this += -n); }
		iterator	operator+(difference_type n) { iterator	temp; return (temp += n); }
		*/

	private:
		pointer	_ptr;
};

LegacyRandomAccessIterator< std::string >	operator+(std::ptrdiff_t n, const LegacyRandomAccessIterator< std::string >& rhs)
{
	LegacyRandomAccessIterator< std::string > it(rhs);
	it += n;
	return (it);
}

} //namespace

#include "vector.tpp"

#endif
