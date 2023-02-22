#ifndef STACK_HPP
#define STACK_HPP
#include <vector.hpp>

namespace ft {

template < class Type, class Container = ft::vector< Type > >
class stack
{
	public:
		// Member types
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;


		explicit stack(const Container& cont = Container()) : c(cont) { }
		~stack(void) { }

		bool			empty(void) const { return (c.empty()); }
		size_type		size(void) const { return (c.size()); }
		reference		top(void) { return (c.back()); }
		const_reference	top(void) const { return (c.back()); }
		void			push(const value_type& value) { return (c.push_back(value)); }
		void			pop(void) { return (c.pop_back()); }

		friend bool operator==(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs.c == rhs.c); }
		friend bool operator!=(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs.c != rhs.c); }
		friend bool operator<(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs.c < rhs.c); }
		friend bool operator<=(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs.c <= rhs.c); }
		friend bool operator>(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs.c > rhs.c); }
		friend bool operator>=(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs.c >= rhs.c); }
		
	protected:
		Container	c;
};


} // namespace ft

#endif
