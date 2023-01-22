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


		explicit stack(const Container& cont = Container()) : _container(cont) { }
		~stack(void) { }

		bool			empty(void) const { return (_container.empty()); }
		size_type		size(void) const { return (_container.size()); }
		reference		top(void) { return (_container.back()); }
		const_reference	top(void) const { return (_container.back()); }
		void			push(const value_type& value) { return (_container.push_back(value)); }
		void			pop(void) { return (_container.pop_back()); }

		friend bool operator==(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs._container == rhs._container); }
		friend bool operator!=(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs._container != rhs._container); }
		friend bool operator<(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs._container < rhs._container); }
		friend bool operator<=(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs._container <= rhs._container); }
		friend bool operator>(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs._container > rhs._container); }
		friend bool operator>=(const ft::stack< Type, Container > &lhs, const ft::stack< Type, Container > &rhs) { return (lhs._container >= rhs._container); }
		
	private:
		Container	_container;
};


} // namespace ft

#endif
