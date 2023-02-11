#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <sstream>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"

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
		typedef std::ptrdiff_t								difference_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef LegacyRandomAccessIterator< Type >			iterator;
		typedef LegacyRandomAccessIterator< const Type >	const_iterator;
		typedef ft::reverse_iterator< iterator >			reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;

		explicit vector( const Allocator& alloc = Allocator());
		explicit vector(size_type count, const Type& value = Type(), const Allocator& alloc = Allocator());
		vector( const vector& other);
		template< class InputIt >
		vector(InputIt first, InputIt last, const Allocator &alloc = Allocator());

		~vector(void);
		vector&					operator=(const vector& other);
		void					assign(size_type count, const Type& value);
		
		template< class InputIt >
		void assign(InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::value* =0);
		allocator_type			get_allocator(void) const;

		//// Element access ////
		const_reference			at( size_type pos ) const;
		reference				at( size_type pos );
		const_reference			operator[](size_type pos) const;
		reference				operator[](size_type pos);
		reference				front(void);
		const_reference			front(void) const;
		reference				back(void);
		const_reference			back(void) const;
		pointer					data(void);
		const_pointer			data(void) const;

		//// Iterators ////
		const_iterator			begin(void) const;
		iterator				begin(void);
		const_iterator			end(void) const;
		iterator				end(void);
		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void) ;
		const_reverse_iterator	rend(void) const;

		//// Capacity ////
		bool					empty(void) const;
		size_type				size(void) const;
		size_type				max_size() const;
		void					reserve( size_type new_cap );
		size_type				capacity(void) const;

		//// Modifiers ////
		void					clear(void);
		iterator				insert(const_iterator pos, const Type &value);
		void					insert(const_iterator pos, size_type count, const Type &value);
		template < class InputIt >
		void					insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::value* =0);
		iterator				erase(iterator pos);
		iterator				erase(iterator first, iterator last);
		void					push_back(const Type& value);
		void					pop_back(void);
		void					resize(size_type count, Type value = Type());
		void					swap(vector< Type, Allocator > &other);

	private:
		allocator_type			_alloc;
		static const size_type	_initialCapacity;
		size_type				_vectorCapacity;
		size_type				_vectorSize;
		pointer 				_elements;
};

template < typename Type > bool	operator==(const ft::vector< Type > &lhs, const ft::vector< Type > &rhs) { if (lhs.size() != rhs.size()) return (false); return (ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }
template < typename Type > bool	operator<(const ft::vector< Type > &lhs, const ft::vector< Type > &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
template < typename Type > bool	operator>(const ft::vector< Type > &lhs, const ft::vector< Type > &rhs) { return (rhs < lhs); }
template < typename Type > bool	operator>=(const ft::vector< Type > &lhs, const ft::vector< Type > &rhs) { return (!(lhs < rhs)); }
template < typename Type > bool	operator<=(const ft::vector< Type > &lhs, const ft::vector< Type > &rhs) { return (!(rhs < lhs)); }
template < typename Type > bool	operator!=(const ft::vector< Type > &lhs, const ft::vector< Type > &rhs) { return (!(lhs == rhs)); }

template< class Type, class Allocator >
void	swap(ft::vector< Type, Allocator > &x, ft::vector< Type, Allocator > &y) { return (y.swap(x)); }

template< class Type >
class	LegacyRandomAccessIterator
{
	public:
		template< class IteType, class AllocatorType >
		friend class vector;

		typedef std::random_access_iterator_tag				iterator_category;
		typedef Type 										value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef Type*										pointer;
		typedef Type&										reference;
		typedef LegacyRandomAccessIterator< Type >			iterator;
		typedef LegacyRandomAccessIterator< const Type >	const_iterator;

		LegacyRandomAccessIterator(const iterator& other) : _ptr(other.operator->()) {}
		~LegacyRandomAccessIterator(void) {}
		operator	const_iterator(void) const { return  (LegacyRandomAccessIterator< const Type >(_ptr)); }
		explicit	LegacyRandomAccessIterator(pointer ptr = NULL) : _ptr(ptr) {}

		iterator				operator++(int) { iterator it(_ptr); ++_ptr; return (it); }
		pointer					operator->(void) const { return (_ptr); }
		iterator				&operator=(const iterator& other) { this->_ptr = other.operator->(); return (*this); }
		iterator				&operator++(void) { ++_ptr; return (*this); }
		reference				operator*(void) const { return (*_ptr); }
		iterator				&operator--(void) { --_ptr; return (*this); }
		iterator				operator--(int) { iterator it(_ptr); --_ptr; return (it); }
		iterator				&operator+=(difference_type n) {  _ptr += n; return (*this); }
		iterator				operator+(difference_type n) const { return (iterator(_ptr + n)); }
		iterator				&operator-=(difference_type n) {  return (*this += -n); }
		iterator				operator-(difference_type n) const { return (iterator(_ptr - n)); }
		reference				operator[](difference_type n) const { return (*(_ptr + n)); };
	private:
		pointer	_ptr;
};

template < typename Type1, typename Type2 > bool	operator==(const LegacyRandomAccessIterator< Type1 > &lhs, const LegacyRandomAccessIterator< Type2 > &rhs) { return (lhs.operator->() == rhs.operator->()); }
template < typename Type1, typename Type2 > bool	operator!=(const LegacyRandomAccessIterator< Type1 > &lhs, const LegacyRandomAccessIterator< Type2 > &rhs) { return (lhs.operator->() != rhs.operator->()); }
template < typename Type1, typename Type2 > bool	operator<=(const LegacyRandomAccessIterator< Type1 > &lhs, const LegacyRandomAccessIterator< Type2 > &rhs) { return (lhs.operator->() <= rhs.operator->()); }
template < typename Type1, typename Type2 > bool	operator>=(const LegacyRandomAccessIterator< Type1 > &lhs, const LegacyRandomAccessIterator< Type2 > &rhs) { return (lhs.operator->() >= rhs.operator->()); }
template < typename Type1, typename Type2 > bool	operator<(const LegacyRandomAccessIterator< Type1 >  &lhs, const LegacyRandomAccessIterator< Type2 > &rhs) { return (lhs.operator->() < rhs.operator->()); }
template < typename Type1, typename Type2 > bool	operator>(const LegacyRandomAccessIterator< Type1 >  &lhs, const LegacyRandomAccessIterator< Type2 > &rhs) { return (lhs.operator->() > rhs.operator->()); }

template < typename Type1, typename Type2 >
std::ptrdiff_t	operator-(const LegacyRandomAccessIterator< Type1 >  &lhs, const LegacyRandomAccessIterator< Type2 > &rhs)
{ return (lhs.operator->() - rhs.operator->()); }

template< class Type >
LegacyRandomAccessIterator< Type > operator+(std::ptrdiff_t n, const LegacyRandomAccessIterator< Type > &rhs)
{ return (rhs + n); }

template< class Type >
void	swap(ft::LegacyRandomAccessIterator< Type > &x, ft::LegacyRandomAccessIterator< Type > &y)
{
	ft::LegacyRandomAccessIterator< Type > tmp(x);
	x = y;
	y = tmp;
}

} // namespace ft

#include "vector.tpp"

#endif
