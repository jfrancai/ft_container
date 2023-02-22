#ifndef MAP_HPP
#define MAP_HPP
#include <iostream>
#include <sstream>
#include <functional>
#include "iterator.hpp"
#include "type_traits.hpp"
#include "RedBlackTree.hpp"
#include "algorithm.hpp"
#include "utility.hpp"

namespace ft {

template< class DataType, class NodeType >
class	LegacyBidirectionalIterator;

template<
	class Key,
	class Type,
	class Compare = std::less< Key >,
	class Allocator = std::allocator< ft::pair< const Key, Type > >
> class map
{
	public:
		// Member types (aliases)
		typedef Key															key_type;
		typedef Type 														mapped_type;
		typedef ft::pair< const Key, Type >									value_type;
		typedef std::size_t 												size_type;
		typedef std::ptrdiff_t												Typedifference_type;
		typedef Compare														key_compare;
		typedef Allocator													allocator_type;
		typedef value_type&													reference;
		typedef const value_type&											const_reference;
		typedef typename Allocator::pointer									pointer;
		typedef typename Allocator::const_pointer							const_pointer;
		typedef LegacyBidirectionalIterator< value_type, value_type >					iterator;
		typedef LegacyBidirectionalIterator< const value_type, value_type >				const_iterator;
		typedef ft::reverse_iterator< iterator >							reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >						const_reverse_iterator;

		//// Member class ////
		class value_compare : public std::binary_function< value_type, value_type, bool >
		{
			public :
				bool	operator() (const value_type &lhs, const value_type &rhs) const { return (comp_(lhs.first, rhs.first)); }
			protected:
				Compare comp_;
				value_compare(Compare c) : comp_(c) {}
				friend class map;
		};

		map(void);
		explicit map( const Compare &comp, const Allocator& alloc = Allocator());
		template< class InputIt >
		map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator &alloc = Allocator());
		map(const map& other);
		~map(void);
		allocator_type										get_allocator(void) const;
		map													&operator=(const map& other);

		//// Element access ////
		Type												&at(const Key &key);
		Type												&operator[](const Key &key);

		//// Iterators ////
		const_iterator										begin(void) const;
		iterator											begin(void);
		const_iterator										end(void) const;
		iterator											end(void);
		reverse_iterator									rbegin(void);
		const_reverse_iterator								rbegin(void) const;
		reverse_iterator									rend(void) ;
		const_reverse_iterator								rend(void) const;

		//// Capacity ////
		bool												empty(void) const;
		size_type											size(void) const;
		size_type											max_size() const;

		//// Modifiers ////
		void												clear(void);
		ft::pair< iterator, bool >							insert(const value_type &value);
		iterator											insert(iterator pos, const value_type &value);
		template< class InputIt >
		void												insert(InputIt first, InputIt last);
		iterator											erase(iterator pos);
		iterator											erase(iterator first, iterator last);
		size_type											erase(const Key &key);
		void												swap(map &other);

		//// Lookup ////
		size_type											count(const Key &key) const;
		iterator											find(const Key &key);
		const_iterator										find(const Key &key) const;
		ft::pair< iterator, iterator >						equal_range( const Key &key);
		ft::pair< const_iterator, const_iterator >			equal_range( const Key &key) const;
		const_iterator										lower_bound(const Key &key) const;
		iterator											lower_bound(const Key &key);
		const_iterator										upper_bound(const Key &key) const;
		iterator											upper_bound(const Key &key);

		//// Observers ////
		key_compare								key_comp(void) const;
		value_compare							value_comp(void) const;

	private:
		key_compare									_comp;
		allocator_type								_alloc;
		size_type									_mapSize;
		RedBlackTree< Key, value_type, Compare >	_elements;
};

////// Non-Member Functions ////
template< typename Key, typename Type, typename Compare, typename Allocator >
bool	operator==(const ft::map< Key, Type, Compare, Allocator >&lhs, const ft::map< Key, Type, Compare, Allocator >&rhs) {  if (lhs.size() != rhs.size()) return (false); return (ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template< typename Key, typename Type, typename Compare, typename Allocator >
bool	operator!=(const ft::map< Key, Type, Compare, Allocator >&lhs, const ft::map< Key, Type, Compare, Allocator >&rhs) { return (!(lhs == rhs)); }

template< typename Key, typename Type, typename Compare, typename Allocator >
bool	operator>=(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (!(lhs < rhs)); }

template< typename Key, typename Type, typename Compare, typename Allocator >
bool	operator>(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (rhs < lhs); }

template< typename Key, typename Type, typename Compare, typename Allocator >
bool	operator<=(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (!(rhs < lhs)); }

template< typename Key, typename Type, typename Compare, typename Allocator >
bool	operator<(const ft::map< Key, Type, Compare, Allocator > &lhs, const ft::map< Key, Type, Compare, Allocator> &rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template< typename Key, typename Type, typename Compare, typename Allocator >
void	swap(ft::map< Key, Type, Compare, Allocator > &lhs, ft::map< Key, Type, Compare, Allocator > &rhs) { return (lhs.swap(rhs)); }

template< class DataType, class NodeType >
class	LegacyBidirectionalIterator
{
	private:
		typedef Node< NodeType >	*node_pointer;
		node_pointer	_node;
	public:
		template< class IteType, class AllocatorType >
		friend class vector;

		template< class IteType >
		friend class ConstLegacyBidirectionalIterator;

		typedef std::bidirectional_iterator_tag							iterator_category;
		typedef DataType												value_type;
		typedef std::ptrdiff_t											difference_type;
		typedef value_type*												pointer;
		typedef value_type&												reference;
		typedef LegacyBidirectionalIterator< DataType, NodeType >		iterator;
		typedef LegacyBidirectionalIterator< const DataType, NodeType >	const_iterator;

		// LegacyIterator
		LegacyBidirectionalIterator(const iterator& other) : _node(other._node) {}
		~LegacyBidirectionalIterator(void) {}
		iterator		&operator=(const iterator& other) { _node = other._node; return (*this); }
		iterator		&operator++(void) {  _node = _node->successor(_node); return (*this); }
		reference		operator*(void) const { return (*(_node->data)); }

		// LegacyInputIterator
		iterator		operator++(int) { iterator it(_node); _node = _node->successor(_node); return (it); }
		pointer			operator->(void) const { return (_node->data); }

		// LegacyForwardIterator
		explicit		LegacyBidirectionalIterator(node_pointer node = NULL) : _node(node) { }
		operator const_iterator(void) const { return (LegacyBidirectionalIterator< const DataType, NodeType >(_node)); }

		// LegacyBidirectionalIterator
		iterator		&operator--(void) { _node = _node->predecessor(_node); return (*this); }
		iterator		operator--(int) { iterator it(_node); _node = _node->predecessor(_node); return (it); }
};

template < typename DataType1, typename NodeType1, typename DataType2, typename NodeType2 >
bool	operator==(const LegacyBidirectionalIterator< DataType1, NodeType1 > &lhs, const LegacyBidirectionalIterator< DataType2, NodeType2 > &rhs)
{ return (lhs.operator->() == rhs.operator->()); }

template < typename DataType1, typename NodeType1, typename DataType2, typename NodeType2 >
bool	operator!=(const LegacyBidirectionalIterator< DataType1, NodeType1 > &lhs, const LegacyBidirectionalIterator< DataType2, NodeType2 > &rhs)
{ return (lhs.operator->() != rhs.operator->()); }

template < typename DataType1, typename NodeType1, typename DataType2, typename NodeType2 >
bool	operator<=(const LegacyBidirectionalIterator< DataType1, NodeType1 > &lhs, const LegacyBidirectionalIterator< DataType2, NodeType2 > &rhs)
{ return (lhs.operator->() <= rhs.operator->()); }

template < typename DataType1, typename NodeType1, typename DataType2, typename NodeType2 >
bool	operator>=(const LegacyBidirectionalIterator< DataType1, NodeType1 > &lhs, const LegacyBidirectionalIterator< DataType2, NodeType2 > &rhs)
{ return (lhs.operator->() >= rhs.operator->()); }

template < typename DataType1, typename NodeType1, typename DataType2, typename NodeType2 >
bool	operator<(const LegacyBidirectionalIterator< DataType1, NodeType1 >  &lhs, const LegacyBidirectionalIterator< DataType2, NodeType2 > &rhs)
{ return (lhs.operator->() < rhs.operator->()); }

template < typename DataType1, typename NodeType1, typename DataType2, typename NodeType2 >
bool	operator>(const LegacyBidirectionalIterator< DataType1, NodeType1 >  &lhs, const LegacyBidirectionalIterator< DataType2, NodeType2 > &rhs)
{ return (lhs.operator->() > rhs.operator->()); }


template< class DataType, class NodeType >
void	swap(ft::LegacyBidirectionalIterator< DataType, NodeType > &x, ft::LegacyBidirectionalIterator< DataType, NodeType > &y)
{
	ft::LegacyBidirectionalIterator< DataType, NodeType > tmp(x);
	x = y;
	y = tmp;
}

} // namespace ft

#include "map.tpp"

#endif
