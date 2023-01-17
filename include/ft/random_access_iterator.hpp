#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP
#include <iostream>

namespace ft {

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

		// LegacyIterator
		LegacyRandomAccessIterator< Type >(const iterator& other) : _ptr(other._ptr) {}
		~LegacyRandomAccessIterator< Type >(void) {}
		iterator		&operator=(const iterator& other) { this->_ptr = other._ptr; return (*this); }
		iterator		&operator++(void) { ++_ptr; return (*this); }
		reference		operator*(void) const { return (*_ptr); }

		// LegacyInputIterator
		iterator		operator++(int) { iterator it(_ptr); ++_ptr; return (it); }
		pointer			operator->(void) const { return (_ptr); }
		bool			operator==(const iterator& rhs) const { return (this->_ptr == rhs._ptr); }
		bool			operator!=(const iterator& rhs) const { return (this->_ptr != rhs._ptr); }

		// LegacyOutputIterator

		// LegacyForwardIterator
		operator	const_iterator(void) const { return  LegacyRandomAccessIterator< const Type >(_ptr); }
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
		iterator		operator+(difference_type n) const { iterator it(*this); return (it += n); }
		template< class IteType >
		friend LegacyRandomAccessIterator< IteType >
						operator+(difference_type n, const LegacyRandomAccessIterator< IteType >& rhs);
		iterator		&operator-=(difference_type n) {  return (*this += -n); }
		iterator		operator-(difference_type n) const { iterator	it(*this); return (it -= n); }
		difference_type	operator-(iterator rhs) { return (this->_ptr - rhs._ptr); }
		reference		operator[](difference_type n) const { return (*(this->_ptr + n)); };

	private:
		pointer	_ptr;
};

template< class IteType >
LegacyRandomAccessIterator< IteType >	operator+(std::ptrdiff_t n, const LegacyRandomAccessIterator< IteType >& rhs)
{
	LegacyRandomAccessIterator< IteType > it(rhs);
	it += n;
	return (it);
}

} // namespace ft

#endif
