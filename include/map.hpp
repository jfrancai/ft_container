#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <sstream>
#include <iterator.hpp>
#include <type_traits.hpp>
#include <RedBlackTree.hpp>

#include <utility> // replace with utility .hpp (make_pair and pair template should be inside this header)

namespace ft {

template< class Type >
class	LegacyBidirectionalIterator;

template<
	class Key,
	class Type,
	class Compare = std::less< Key >,
	class Allocator = std::allocator< std::pair< const Key, Type > > // update for ft::pair
> class map
{
	public:
		// Member types (aliases)
		typedef Key												key_type;
		typedef Type 											mapped_type;
		typedef std::pair< const Key, Type >					value_type; // update for ft::pair
		typedef std::size_t 									size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef LegacyBidirectionalIterator< Node< value_type > >		iterator;
		typedef LegacyBidirectionalIterator< const Node < value_type > >	const_iterator;
		typedef ft::reverse_iterator< iterator >				reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >			const_reverse_iterator;

		const RedBlackTree< value_type >	&getTree() const { return _elements; }
		explicit map( const Allocator& alloc = Allocator());
		//explicit vector(size_type count, const Type& value = Type(), const Allocator& alloc = Allocator());
		//vector( const vector& other);
		//template< class InputIt >
		//vector(InputIt first, InputIt last, const Allocator &alloc = Allocator());

		//~vector(void);
		//vector&					operator=(const vector& other);
		//void					assign(size_type count, const Type& value);
		//
		//template< class InputIt >
		//void assign(InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::value* =0);
		allocator_type			get_allocator(void) const;

		////// Element access ////
		//const_reference			at( size_type pos ) const;
		//reference				at( size_type pos );
		//const_reference			operator[](size_type pos) const;
		//reference				operator[](size_type pos);
		//reference				front(void);
		//const_reference			front(void) const;
		//reference				back(void);
		//const_reference			back(void) const;
		//pointer					data(void);
		//const_pointer			data(void) const;

		////// Iterators ////
		const_iterator			begin(void) const;
		iterator				begin(void);
		const_iterator			end(void) const;
		iterator				end(void);
		reverse_iterator		rbegin(void);
		const_reverse_iterator	rbegin(void) const;
		reverse_iterator		rend(void) ;
		const_reverse_iterator	rend(void) const;

		////// Capacity ////
		bool					empty(void) const;
		size_type				size(void) const;
		size_type				max_size() const;

		////// Modifiers ////
		//void					clear(void);
		std::pair< iterator, bool >				insert(const value_type &value); //remplacer par ft::pair
		//void					insert(const_iterator pos, size_type count, const Type &value);
		//template < class InputIt >
		//void					insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::value* =0);
		//iterator				erase(iterator pos);
		//iterator				erase(iterator first, iterator last);
		//void					push_back(const Type& value);
		//void					pop_back(void);
		//void					resize(size_type count, Type value = Type());
		//void					swap(vector< Type, Allocator > &other);

		////// Non-Member Functions ////
		friend bool	operator==(const ft::map< Key, Type, Compare, Allocator >&lhs, const ft::map< Key, Type, Compare, Allocator >&rhs) { return (lhs._elements == rhs._elements); }
		friend bool	operator!=(const ft::map< Key, Type, Compare, Allocator >&lhs, const ft::map< Key, Type, Compare, Allocator >&rhs) { return (lhs._elements != rhs._elements); }
		friend bool	operator>=(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (!(lhs._elements < rhs._elements)); }
		friend bool	operator>(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (rhs._elements < lhs._elements); }
		friend bool	operator<=(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (!(rhs._elements < lhs._elements)); }
		friend bool	operator<(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) {
			if (lhs.size() < rhs.size())
				return (true);
			if (rhs.size() < lhs.size())
				return (false);
			return (lhs._elements < rhs._elements);
		}
	private:
		allocator_type					_alloc;
		size_type						_mapSize;
		RedBlackTree< value_type >		_elements;

};

/*
template< class Type, class Allocator >
void	swap(ft::vector< Type, Allocator > &x, ft::vector< Type, Allocator > &y)
{
	return (y.swap(x));
}
*/

template< class Type >
class	LegacyBidirectionalIterator
{

	private:
		typedef Type	*node_pointer;
		node_pointer	_node;
		public:
		template< class IteType, class AllocatorType >
		friend class vector;

		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef typename Type::value_type					value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef value_type*									pointer;
		typedef value_type&									reference;
		typedef LegacyBidirectionalIterator< Type >			iterator;
		typedef LegacyBidirectionalIterator< const Type >	const_iterator;

		// LegacyIterator
		LegacyBidirectionalIterator(const iterator& other) : _node(other._node) {}
		~LegacyBidirectionalIterator(void) {}
		iterator		&operator=(const iterator& other) { _node = other._node; return (*this); }
		iterator		&operator++(void) { _node = _node->successor(); return (*this); }
		reference		operator*(void) const { return (_node->data); }

		// LegacyInputIterator
		iterator		operator++(int) { iterator it(_node); ++_node; return (it); }
		pointer			operator->(void) const { return (&_node->data); }
		bool			operator==(const iterator& rhs) const { return _node == rhs._node; }
		bool			operator!=(const iterator& rhs) const { return _node != rhs._node; }

		// LegacyOutputIterator

		// LegacyForwardIterator
		explicit		LegacyBidirectionalIterator(node_pointer node = NULL) : _node(node) { }
		operator const_iterator(void) const { return  (LegacyBidirectionalIterator< const Type >(_node)); }

		// LegacyBidirectionalIterator
		iterator		&operator--(void) { _node = _node->predecessor(); return (*this); }
		iterator		operator--(int) { iterator it(_node); --_node; return (it); }
};

template< class Type >
LegacyBidirectionalIterator< Type > operator+(std::ptrdiff_t n, const LegacyBidirectionalIterator< Type > &rhs)
{
	return (rhs + n);
}

template< class Type >
void	swap(ft::LegacyBidirectionalIterator< Type > &x, ft::LegacyBidirectionalIterator< Type > &y)
{
	ft::LegacyBidirectionalIterator< Type > tmp(x);
	x = y;
	y = tmp;
}


} // namespace ft

#include "map.tpp"

#endif
