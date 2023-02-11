#ifndef ITERATOR
#define ITERATOR
#include <iostream>
#include "type_traits.hpp"

namespace ft {

template <typename Iterator>
struct iterator_traits {
	typedef typename Iterator::iterator_category	iterator_category;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
};

template <typename T>
struct iterator_traits<T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef T*								pointer;
	typedef T&								reference;
};

template <typename T>
struct iterator_traits<const T*> {
	typedef std::random_access_iterator_tag	iterator_category;
	typedef T								value_type;
	typedef std::ptrdiff_t					difference_type;
	typedef const T*						pointer;
	typedef const T&						reference;
};

template<class Iterator >
class reverse_iterator
{
	// Rhis is really weird to understand and not straight forware 
	// but it allows instances of reverse_iterator (so iterator< Type > under the hood)
	// to access inside const_reverse_iterator
	// (so iterator< const Type >) and vis&versa.
	template< class IteType >
	friend class reverse_iterator;

	public:
		typedef	Iterator													iterator_type;
		typedef typename ft::iterator_traits< Iterator >::iterator_category	iterator_category;
		typedef typename ft::iterator_traits< Iterator >::value_type		value_type;
		typedef typename ft::iterator_traits< Iterator >::difference_type	difference_type;
		typedef typename ft::iterator_traits< Iterator >::pointer			pointer;
		typedef typename ft::iterator_traits< Iterator >::reference			reference;

		// LegacyIterator

		reverse_iterator(void) {}
		~reverse_iterator(void) {}
		explicit reverse_iterator(iterator_type x) : current_(x) { }
		template < class U >
		reverse_iterator(const reverse_iterator< U >&other) : current_(other.base()) { }

		template< class U >
		reverse_iterator	&operator=(const reverse_iterator< U > &other) { this->current_ = other.current_; return (*this); }
		Iterator			base(void) const { return (this->current_); }
		reference			operator*(void) const { return (*(this->current_ - 1)); }
		pointer				operator->(void) const { return &(operator*()); }
		reference			operator[](difference_type n) const { return (*(*this + n)); }
		reverse_iterator	&operator++() { --this->current_; return (*this); }
		reverse_iterator	operator++(int) { reverse_iterator tmp(*this); --this->current_; return (tmp); }
		reverse_iterator	&operator--() { ++this->current_; return (*this); }
		reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++this->current_; return (tmp); }
		reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(this->current_ - n)); }
		reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(this->current_ + n)); }
		reverse_iterator	&operator+=(difference_type n) { this->current_ -= n; return (*this); }
		reverse_iterator	&operator-=(difference_type n) { this->current_ += n; return (*this); }

	protected:
		iterator_type	current_;
};

template< class Iterator1, class Iterator2 >
inline bool operator==(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs)
{
	return (lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator!=(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs)
{
	return (lhs.base() != rhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator<(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs)
{
	return (lhs.base() > rhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator>(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs)
{
	return (lhs.base() < rhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator>=(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs)
{
	return (lhs.base() <= rhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator<=(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs)
{
	return (lhs.base() >= rhs.base());
}

template< class Iterator >
reverse_iterator< Iterator >	operator+(std::ptrdiff_t n, const reverse_iterator< Iterator >& rhs)
{
	reverse_iterator< Iterator > it(rhs);
	it += n;
	return (it);
}

template< class Iterator1, class Iterator2 >
typename reverse_iterator< Iterator1 >::difference_type operator-(const reverse_iterator< Iterator1 >& lhs, const reverse_iterator< Iterator2 >& rhs)
{
	return (rhs.base() - lhs.base());
}

} // namespace ft

#endif
