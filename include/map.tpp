namespace ft {
/*
 * Statics
 */

/*
 * Member functions
 */

//// Constructors ////

template< class Key, class Type, class Compare, class Allocator >
map< Key, Type, Compare, Allocator >::map(void) :
	_comp(Compare()),
	_alloc(Allocator()),
	_mapSize(0)
{
	return ;
}

template< class Key, class Type, class Compare, class Allocator >
map< Key, Type, Compare, Allocator >::map(const Compare &comp, const Allocator& alloc) :
	_comp(comp),
	_alloc(alloc),
	_mapSize(0)
{
	return ;
}

template< class Key, class Type, class Compare, class Allocator >
template< class InputIt >
map< Key, Type, Compare, Allocator >::map(InputIt first, InputIt last, const Compare &comp, const Allocator &alloc) :
	_comp(comp),
	_alloc(alloc),
	_mapSize(0)
{
	insert(first, last);

	return ;
}

// get_allocator
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::allocator_type	map< Key, Type, Compare, Allocator >::get_allocator(void) const
{
	return (_alloc);
}

template< class Key, class Type, class Compare, class Allocator >
map< Key, Type, Compare, Allocator >	&map< Key, Type, Compare, Allocator>::operator=(const map& other)
{
	_comp = other._comp;
	_alloc = other._alloc;
	_mapSize = other._mapSize;
	_elements = other._elements;

	return (*this);
}

//// Destructor ////

template< class Key, class Type, class Compare, class Allocator >
map< Key, Type, Compare, Allocator >::~map(void)
{
	return ;
}
//// Element access ////

// at
template< class Key, class Type, class Compare, class Allocator >
Type	&map< Key, Type, Compare, Allocator >::at(const Key &key)
{
	typename RedBlackTree< Key, value_type, Compare >::node_pointer node = _elements.searchTree(_elements.getRoot(), key);
	if (node->isNILL)
	{
		std::ostringstream errorMsg;
		errorMsg << "map::at";
		throw std::out_of_range(errorMsg.str());
	}
	return (node->data->second);
}

// operator[]
template< class Key, class Type, class Compare, class Allocator >
Type	&map< Key, Type, Compare, Allocator >::operator[](const Key &key)
{
	typename RedBlackTree< Key, value_type, Compare >::node_pointer node = _elements.searchTree(_elements.getRoot(), key);
	if (node->isNILL)
	{
		ft::pair< iterator, bool> pair = insert(ft::make_pair(key, Type()));
		map< Key, Type, Compare, Allocator >::iterator it = pair.first;
		return (it->second);
	}
	return (node->data->second);
}

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

// clear

template< class Key, class Type, class Compare, class Allocator >
void	map< Key, Type, Compare, Allocator >::clear(void)
{
	delete _elements.getRoot();
	_elements.setRoot(_elements.getNill());
	_mapSize = 0;
}

// insert
template< class Key, class Type, class Compare, class Allocator >
typename ft::pair< typename map< Key, Type, Compare, Allocator >::iterator, bool >	map< Key, Type, Compare, Allocator >::insert(const typename map< Key, Type, Compare, Allocator >::value_type &value)
{
	ft::pair< typename ft::RedBlackTree< Key, ft::pair< const Key, Type >, Compare >::node_pointer, bool > pair = _elements.insert(value);
	if (pair.second)
	{
		_elements.getNill()->parent = _elements.maximum(_elements.getRoot());
		_mapSize++;
	}
	return (pair);
}

template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::iterator	map< Key, Type, Compare, Allocator >::insert(typename map< Key, Type, Compare, Allocator >::iterator pos, const typename map< Key, Type, Compare, Allocator >::value_type &value)
{
	(void)pos;
	return (insert(value).first);
}


template< class Key, class Type, class Compare, class Allocator >
template< class InputIt >
void	map< Key, Type, Compare, Allocator >::insert(InputIt first, InputIt last) 
{
	for (InputIt it = first; it != last; ++it)
		insert(*it);
}


template< class Key, class Type, class Compare, class Allocator >
void	map< Key, Type, Compare, Allocator >::swap(map< Key, Type, Compare, Allocator > &other)
{
	typename RedBlackTree< Key, value_type, Compare >::node_pointer	root = _elements.getRoot();
	typename RedBlackTree< Key, value_type, Compare >::node_pointer	nill = _elements.getNill();
	typename RedBlackTree< Key, value_type, Compare >::key_compare	c = _elements.getComp();
	map< Key, Type, Compare, Allocator >::size_type s(size());
	map< Key, Type, Compare, Allocator >::allocator_type a(get_allocator());
	map< Key, Type, Compare, Allocator >::key_compare k(key_comp());

	_elements.setRoot(other._elements.getRoot());
	_elements.setNill(other._elements.getNill());
	_elements.setComp(other._elements.getComp());
	_alloc = other.get_allocator();
	_comp = other.key_comp();
	_mapSize = other.size();

	other._elements.setRoot(root);
	other._elements.setNill(nill);
	other._elements.setComp(c);
	other._mapSize = s;
	other._alloc = a;
	other._comp = k;

	return ;
}

//// Lookup ////

// count
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::size_type	map< Key, Type, Compare, Allocator >::count(const Key &key)
{
	return (find(key) != end());
}

// find
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::iterator	map< Key, Type, Compare, Allocator >::find(const Key &key)
{
	return (iterator(_elements.searchTree(_elements.getRoot(), key)));
}

// find
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::const_iterator	map< Key, Type, Compare, Allocator >::find(const Key &key) const
{
	return (const_iterator(_elements.searchTree(_elements.getRoot(), key)));
}

//equal range
template< class Key, class Type, class Compare, class Allocator >
ft::pair< typename map< Key, Type, Compare, Allocator>::iterator, typename map< Key, Type, Compare, Allocator >::iterator >	map< Key, Type, Compare, Allocator >::equal_range( const Key &key)
{
	typedef typename map< Key, Type, Compare, Allocator >::iterator iterator;

	return (ft::pair< iterator, iterator >(lower_bound(key), upper_bound(key)));
}

template< class Key, class Type, class Compare, class Allocator >
ft::pair< typename map< Key, Type, Compare, Allocator>::const_iterator, typename map< Key, Type, Compare, Allocator >::const_iterator >	map< Key, Type, Compare, Allocator >::equal_range( const Key &key) const
{
	typedef typename map< Key, Type, Compare, Allocator >::const_iterator const_iterator;

	return (ft::pair< const_iterator, const_iterator >(lower_bound(key), upper_bound(key)));
}

// lower_bound const
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::const_iterator	map< Key, Type, Compare, Allocator >::lower_bound(const Key &key) const
{
	typedef typename RedBlackTree< Key, value_type, Compare >::node_pointer node_pointer; 

	node_pointer node = _elements.minimum(_elements.getRoot());
	while (node && !node->isNILL)
	{
		if (key <= node->data->first)
			return (const_iterator(node));
		node = node->successor(node);
	}
	return (const_iterator(node));
}


// lower_bound
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::iterator	map< Key, Type, Compare, Allocator >::lower_bound(const Key &key)
{
	typedef typename RedBlackTree< Key, value_type, Compare >::node_pointer node_pointer; 

	node_pointer node = _elements.minimum(_elements.getRoot());
	while (node && !node->isNILL)
	{
		if (key <= node->data->first)
			return (iterator(node));
		node = node->successor(node);
	}
	return (iterator(node));
}


// upper_bound const
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::const_iterator	map< Key, Type, Compare, Allocator >::upper_bound(const Key &key) const
{
	typedef typename RedBlackTree< Key, value_type, Compare >::node_pointer node_pointer; 

	node_pointer node = _elements.minimum(_elements.getRoot());
	while (node && !node->isNILL)
	{
		if (key < node->data->first)
			return (const_iterator(node));
		node = node->successor(node);
	}
	return (const_iterator(node));
}


// upper_bound
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::iterator	map< Key, Type, Compare, Allocator >::upper_bound(const Key &key)
{
	typedef typename RedBlackTree< Key, value_type, Compare >::node_pointer node_pointer; 

	node_pointer node = _elements.minimum(_elements.getRoot());
	while (node && !node->isNILL)
	{
		if (key < node->data->first)
			return (iterator(node));
		node = node->successor(node);
	}
	return (iterator(node));
}//// Observers ////

// key_comp
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator>::key_compare	map< Key, Type, Compare, Allocator >::key_comp(void) const
{
	return (_comp);
}

// value_comp
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::value_compare	map< Key, Type, Compare, Allocator >::value_comp(void) const
{
	return (typename ft::map< Key, Type, Compare, Allocator >::value_compare(_comp));
}
//// Observers ////

} //namespace
