/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancai <jfrancai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:47:07 by jfrancai          #+#    #+#             */
/*   Updated: 2023/01/18 12:39:36 by jfrancai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR
#define REVERSE_ITERATOR
#include <iostream>
#include <ft/iterator_traits.hpp>

namespace ft {

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

		// LegacyIterator

		reverse_iterator(void) {}
		~reverse_iterator(void) {}
		explicit reverse_iterator(iterator_type x) : current_(x) { }
		reverse_iterator(const reverse_iterator &other) : current_(other.base()) { }

		reverse_iterator	&operator=(const reverse_iterator< Iterator > &other) { this->current_ = other.current_; return (*this); }
		Iterator			base(void) const { return (this->current_); }
		reference			operator*(void) const { Iterator tmp(this->current_); return (*(--tmp)); }
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

template< class Iterator >
inline bool operator==(const ft::reverse_iterator< Iterator > &lhs, const ft::reverse_iterator< Iterator > &rhs)
{
	return (lhs.base() == rhs.base());
}

template< class Iterator >
inline bool operator!=(const ft::reverse_iterator< Iterator > &lhs, const ft::reverse_iterator< Iterator > &rhs)
{
	return (lhs.base() != rhs.base());
}

template< class Iterator >
inline bool operator<(const ft::reverse_iterator< Iterator > &lhs, const ft::reverse_iterator< Iterator > &rhs)
{
	return (lhs.base() > rhs.base());
}

template< class Iterator >
inline bool operator>(const ft::reverse_iterator< Iterator> &lhs, const ft::reverse_iterator< Iterator > &rhs)
{
	return (lhs.base() < rhs.base());
}

template< class Iterator >
inline bool operator>=(const ft::reverse_iterator< Iterator> &lhs, const ft::reverse_iterator< Iterator > &rhs)
{
	return (lhs.base() <= rhs.base());
}

template< class Iterator >
inline bool operator<=(const ft::reverse_iterator< Iterator > &lhs, const ft::reverse_iterator< Iterator > &rhs)
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

} // namespace ft

#endif
