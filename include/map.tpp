namespace ft {

/*
 * Statics
 */

/*
 * Member functions
 */

//// Constructors ////
template< class Key, class Type, class Compare, class Allocator >
map< Key, Type, Compare, Allocator >::map(const Allocator& alloc) :
	_alloc(alloc),
	_mapSize(0)
{
	return ;
}

// get_allocator
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::allocator_type	map< Key, Type, Compare, Allocator >::get_allocator(void) const
{
	return (_alloc);
}

//// Element access ////

//// Iterators ////

// begin
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::const_iterator	map< Key, Type, Compare, Allocator>::begin(void) const
{
	if (empty())
		return (const_iterator(_elements.getNill()));
	return (const_iterator(_elements.minimum(_elements.getRoot())));
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::iterator	map< Key, Type, Compare, Allocator>::begin(void)
{
	if (empty())
		return (iterator(_elements.getNill()));
	return (iterator(_elements.minimum(_elements.getRoot())));
}

// end
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::const_iterator	map< Key, Type, Compare, Allocator>::end(void) const
{
	return (const_iterator(_elements.getNill()));
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::iterator	map< Key, Type, Compare, Allocator>::end(void)
{
	return (iterator(_elements.getNill()));
}


//// rbegin
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::const_reverse_iterator	map< Key, Type, Compare, Allocator>::rbegin(void) const
{
	return (const_reverse_iterator(end()));
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::reverse_iterator	map< Key, Type, Compare, Allocator>::rbegin(void)
{
	return (reverse_iterator(end()));
}

// rend
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::const_reverse_iterator	map< Key, Type, Compare, Allocator>::rend(void) const
{
	return (const_reverse_iterator(begin()));
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::reverse_iterator	map< Key, Type, Compare, Allocator>::rend(void)
{
	return (reverse_iterator(begin()));
}

//// Capacity ////

// empty
template< class Key, class Type, class Compare, class Allocator >
bool	map< Key, Type, Compare, Allocator >::empty(void) const
{
	if (_mapSize == 0)
		return (true);
	return (false);
}

// size
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::size_type	map< Key, Type, Compare, Allocator >::size(void) const
{
	return (_mapSize);
}

// max_size
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::size_type	map< Key, Type, Compare, Allocator >::max_size(void) const
{
	return (_alloc.max_size() / 5);
}

//// Modifiers ////

//insert
template< class Key, class Type, class Compare, class Allocator >
typename std::pair< typename map< Key, Type, Compare, Allocator >::iterator, bool >	map< Key, Type, Compare, Allocator >::insert(const typename map< Key, Type, Compare, Allocator >::value_type &value)
{
	std::pair< typename ft::RedBlackTree< Key, std::pair< const Key, Type >, Allocator >::node_pointer, bool > pair = _elements.insert(value);
	typename map< Key, Type, Compare, Allocator >::iterator	it(pair.first);
	if (pair.second)
	{
		_elements.getNill()->parent = _elements.maximum(_elements.getRoot());
		_mapSize++;
	}
	return (std::make_pair(it, pair.second));
}

//// Lookup ////
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::size_type	map< Key, Type, Compare, Allocator >::count(const Key &key)
{
	return (find(key) != end());
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::iterator	map< Key, Type, Compare, Allocator >::find(const Key &key)
{
	return (iterator(_elements.searchTree(_elements.getRoot(), key)));
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::const_iterator	map< Key, Type, Compare, Allocator >::find(const Key &key) const
{
	return (const_iterator(_elements.searchTree(_elements.getRoot(), key)));
}

} //namespace
