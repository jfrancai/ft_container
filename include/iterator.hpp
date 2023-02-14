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
	public:
		typedef	Iterator													iterator_type;
		typedef typename ft::iterator_traits< Iterator >::iterator_category	iterator_category;
		typedef typename ft::iterator_traits< Iterator >::value_type		value_type;
		typedef typename ft::iterator_traits< Iterator >::difference_type	difference_type;
		typedef typename ft::iterator_traits< Iterator >::pointer			pointer;
		typedef typename ft::iterator_traits< Iterator >::reference			reference;

		reverse_iterator(void) {}
		~reverse_iterator(void) {}
		explicit reverse_iterator(iterator_type x) : current_(x) { }
		template < class U >
		reverse_iterator(const reverse_iterator< U >&other) : current_(other.base()) { }

		template< class U >
		reverse_iterator	&operator=(const reverse_iterator< U > &other) { current_ = other.base(); return (*this); }
		iterator_type		base(void) const { return (current_); }
		reference			operator*(void) const { iterator_type tmp(current_); return (*--tmp); }
		pointer				operator->(void) const { return &(operator*()); }
		reference			operator[](difference_type n) const { return (*(*this + n)); }
		reverse_iterator	&operator++() { --current_; return (*this); }
		reverse_iterator	operator++(int) { reverse_iterator tmp(*this); --current_; return (tmp); }
		reverse_iterator	&operator--() {  ++current_; return (*this); }
		reverse_iterator	operator--(int) { reverse_iterator tmp(*this); ++current_; return (tmp); }
		reverse_iterator	operator+(difference_type n) const { iterator_type tmp(current_); while (n--) --tmp; return (reverse_iterator(tmp)); }
		reverse_iterator	operator-(difference_type n) const { iterator_type tmp(current_); while (n--) ++tmp; return (reverse_iterator(tmp)); }
		reverse_iterator	&operator+=(difference_type n) { current_ -= n; return (*this); }
		reverse_iterator	&operator-=(difference_type n) { current_ += n; return (*this); }

	protected:
		iterator_type	current_;
};

template< class Iterator1, class Iterator2 > inline bool operator==(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs) { return (lhs.base() == rhs.base()); }
template< class Iterator1, class Iterator2 > inline bool operator!=(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs) { return (lhs.base() != rhs.base()); }
template< class Iterator1, class Iterator2 > inline bool operator<(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs) { return (lhs.base() > rhs.base()); }
template< class Iterator1, class Iterator2 > inline bool operator>(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs) { return (lhs.base() < rhs.base()); }
template< class Iterator1, class Iterator2 > inline bool operator>=(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs) { return (lhs.base() <= rhs.base()); }
template< class Iterator1, class Iterator2 > inline bool operator<=(const ft::reverse_iterator< Iterator1 > &lhs, const ft::reverse_iterator< Iterator2 > &rhs) { return (lhs.base() >= rhs.base()); }

template< class Iterator >
reverse_iterator< Iterator >	operator+(std::ptrdiff_t n, const reverse_iterator< Iterator >& rhs)
{ return (reverse_iterator< Iterator >(rhs.base() - n)); }

template< class Iterator1, class Iterator2 >
std::ptrdiff_t	operator-(const reverse_iterator< Iterator1 >& lhs, const reverse_iterator< Iterator2 >& rhs)
{ return (rhs.base() - lhs.base()); }

} // namespace ft

#endif
