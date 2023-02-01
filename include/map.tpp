namespace ft {

/*
 * Statics
 */

/*
 * Member functions
 */

//// Constructors
template< class Key, class Type, class Compare, class Allocator >
map< Key, Type, Compare, Allocator >::map(const Allocator& alloc) :
	_alloc(alloc),
	_mapSize(0),
	_elements(0)
{
	return ;
}

//template< class Type, class Allocator >
//vector< Type, Allocator >::vector(const vector &rhs) :
//	_alloc(rhs.get_allocator()),
//	_vectorCapacity(0),
//	_vectorSize(0),
//	_elements(0)
//{
//	insert(begin(), rhs.begin(), rhs.end());
//
//	return ;
//}
//
//template< class Type, class Allocator >
//template< class InputIt >
//vector< Type, Allocator >::vector(InputIt first, InputIt last, const Allocator &alloc) :
//	_alloc(alloc),
//	_vectorCapacity(0),
//	_vectorSize(0),
//	_elements(0)
//{
//	insert(begin(), first, last);
//
//	return ;
//}
//
//template< class Type, class Allocator >
//vector< Type, Allocator >::vector(size_type count, const Type& value, const Allocator& alloc) :
//	_alloc(alloc),
//	_vectorCapacity(0),
//	_vectorSize(0),
//	_elements(0)
//{
//	if (count > max_size())
//		throw std::length_error("cannot create std::vector larger than max_size()");
//	insert(begin(), count, value);
//}
//
//// Destructor
//template< class Type, class Allocator >
//vector< Type, Allocator >::~vector(void)
//{
//	for (size_type i = 0; i < _vectorSize; i++)
//		_alloc.destroy(_elements + i);
//	_alloc.deallocate(_elements, _vectorCapacity);
//
//	return ;
//}
//
//// operator=
//template< class Type, class Allocator >
//typename ft::vector< Type, Allocator >	&vector< Type, Allocator >::operator=(const typename ft::vector< Type, Allocator >	&rhs)
//{
//	if (this != &rhs)
//		assign(rhs.begin(), rhs.end());
//
//	return (*this);
//}
//
//// assign
//template< class Type, class Allocator >
//void	vector< Type, Allocator >::assign(typename vector< Type, Allocator >::size_type count, const Type& value)
//{
//	if (count > _alloc.max_size())
//		throw std::invalid_argument("cannot create std::vector larger than max_size()");
//	clear();
//	resize(count, value);
//
//	return ; 
//}
//
//// assign
//template< class Type, class Allocator >
//template< class InputIt >
//void	vector< Type, Allocator >::assign(InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::value*)
//{
//	clear();
//	insert(begin(), first, last);
//
//	return ;
//}
//
// get_allocator
template< class Key, class Type, class Compare, class Allocator >
typename map< Key, Type, Compare, Allocator >::allocator_type	map< Key, Type, Compare, Allocator >::get_allocator(void) const
{
	return (_alloc);
}

//// Element access ////

//// at
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_reference vector< Type, Allocator >::at( typename vector< Type, Allocator >::size_type pos ) const
//{
//	if (pos >= size())
//	{
//		std::ostringstream errorMsg;
//		errorMsg << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << size() << ")";
//		throw std::out_of_range(errorMsg.str());
//	}
//	return ((*this)[pos]);
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::reference vector< Type, Allocator >::at( vector< Type, Allocator >::size_type pos )
//{
//	return (
//		const_cast< reference >(
//			static_cast< const ft::vector< Type, Allocator >& >(*this).at(pos)
//		)
//	);
//}
//
//// operator[]
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos) const
//{
//	return (_elements[pos]);
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos)
//{
//	return (
//		const_cast< reference >(
//			static_cast< const ft::vector< Type, Allocator >& >(*this)[pos]
//		)
//	);
//}
//
//// front
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::front(void) const
//{
//	return ((*this)[0]);
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::reference	vector< Type, Allocator >::front(void)
//{
//	return (
//		const_cast< reference >(
//			static_cast< const ft::vector< Type, Allocator >& >(*this).front()
//		)
//	);
//}
//
//// back
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::back(void) const
//{
//	return ((*this)[_vectorSize - 1]);
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::reference	vector< Type, Allocator >::back(void)
//{
//	return (
//		const_cast< reference >(
//			static_cast< const ft::vector< Type, Allocator >& >(*this).back()
//		)
//	);
//}
//
//// data
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_pointer	vector< Type, Allocator >::data(void) const
//{
//	return (_elements);
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::pointer	vector< Type, Allocator >::data(void)
//{
//	return (
//		const_cast< pointer >(
//			static_cast< const ft::vector< Type, Allocator >& >(*this).data()
//		)
//	);
//}
//
////// Iterators ////
//
//// begin
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_iterator	vector< Type, Allocator >::begin(void) const
//{
//	return (const_iterator(_elements));
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::iterator	vector< Type, Allocator >::begin(void)
//{
//	return (iterator(_elements));
//}
//
//// end
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_iterator	vector< Type, Allocator >::end(void) const
//{
//	return (const_iterator(_elements + _vectorSize));
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::iterator	vector< Type, Allocator >::end(void)
//{
//	return (iterator(_elements + _vectorSize));
//}
//
//// rbegin
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_reverse_iterator	vector< Type, Allocator >::rbegin(void) const
//{
//	return (const_reverse_iterator(end()));
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::reverse_iterator	vector< Type, Allocator >::rbegin(void)
//{
//	return (reverse_iterator(end()));
//}
//
//// rend
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::reverse_iterator	vector< Type, Allocator >::rend(void)
//{
//	return (reverse_iterator(begin()));
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator >::const_reverse_iterator	vector< Type, Allocator >::rend(void) const
//{
//	return (const_reverse_iterator(begin()));
//}
////// Capacity ////

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
	return (_alloc.max_size());
}

////// Modifiers ////

//// clear
//template< class Type, class Allocator >
//void	vector< Type, Allocator >::clear(void)
//{
//	for(size_type i = 0; i < _vectorSize; i++)
//		_alloc.destroy(_elements + i);
//	_vectorSize = 0;
//	return ;
//}

//insert
template< class Key, class Type, class Compare, class Allocator >
typename std::pair< iterator, bool >	map< Key, Type, Compare, Allocator >::insert(const typename map< Key, Type, Compare, Allocator >::value_type &value);
{
	return ();
}

//template< class Type, class Allocator >
//void	vector< Type, Allocator>::insert(typename vector< Type, Allocator >::const_iterator pos, typename vector< Type, Allocator >::size_type count, const Type &value)
//{
//	size_type	index = pos - begin();
//	if (size() + count > capacity())
//		reserve(capacity() + count);
//	for (size_type i = size(); i > index; --i)
//		_elements[i + count - 1] = _elements[i - 1];
//	for (size_type i = 0; i < count; ++i)
//		_elements[index + i] = value;
//	_vectorSize += count;
//
//	return ;
//}
//
//template< class Type, class Allocator >
//template < typename  InputIt >
//void	vector< Type, Allocator >::insert(typename vector< Type, Allocator >::const_iterator pos, InputIt first, InputIt last, typename ft::enable_if< !ft::is_integral< InputIt >::value, InputIt >::value*)
//{
//	size_type	index = pos - begin();
//	size_type	count = std::distance(first, last);
//	if (count + size() > capacity())
//	{
//		size_type new_cap = size() + count;
//		pointer newElements = _alloc.allocate(new_cap);
//		for (size_type i = 0; i < _vectorSize; i++)
//			_alloc.construct(newElements + i, (*this)[i]);
//		for (size_type i = _vectorSize; i > index; --i)
//			newElements[i + count - 1] = _elements[i - 1];
//		for (size_type i = 0; i < count; ++i)
//			newElements[index + i] = *(first++);
//		for (size_type i = 0; i < _vectorSize; i++)
//			_alloc.destroy(&(*this)[i]);
//		_alloc.deallocate(_elements, _vectorCapacity);
//		_vectorCapacity = new_cap;
//		_elements = newElements;
//	}
//	else
//	{
//		for (size_type i = _vectorSize; i > index; --i)
//			_elements[i + count - 1] = _elements[i - 1];
//		for (size_type i = 0; i < count; ++i)
//			_elements[index + i] = *(first++);
//	}
//	_vectorSize += count;
//
//	return ;
//}
//
//// erase
//template< class Type, class Allocator >
//typename vector< Type, Allocator>::iterator	vector< Type, Allocator >::erase(typename vector< Type, Allocator >::iterator first, typename vector< Type, Allocator >::iterator last)
//{
//	if (first == last)
//		return (last);
//	size_type num_elements = std::distance(first, last);
//	if (last != end())
//		std::copy(last, end(), first);
//	resize(size() - num_elements);
//	return (first);
//}
//
//template< class Type, class Allocator >
//typename vector< Type, Allocator>::iterator	vector< Type, Allocator >::erase(typename vector< Type, Allocator >::iterator pos)
//{
//	if (pos == end())
//		return (pos);
//	std::copy(pos + 1, end(), pos);
//	resize(size() - 1);
//	return (pos); 
//}
//
//// push_back
//template< class Type, class Allocator >
//void	vector< Type, Allocator >::push_back(const Type& value)
//{
//	if (_vectorSize == _vectorCapacity)
//		reserve(capacity() ? _vectorCapacity * 2 : _initialCapacity);
//	_alloc.construct(_elements + _vectorSize, value);
//	_vectorSize++;
//	return ;
//}
//
//// pop_back
//template< class Type, class Allocator >
//void	vector< Type, Allocator >::pop_back(void)
//{
//	if (_vectorSize == 0)
//		return ;
//	_vectorSize--;
//	_alloc.destroy(_elements + _vectorSize);
//
//	return ;
//}
//
//// resize
//template< class Type, class Allocator >
//void	vector< Type, Allocator >::resize(typename vector< Type, Allocator >::size_type count, Type value)
//{
//	if (count > max_size())
//		throw std::length_error("vector::resize");
//	if (count < size())
//	{
//		for (iterator it = begin() + count; it != end(); ++it)
//			_alloc.destroy(it._ptr);
//	}
//	else if (count > size())
//	{
//		reserve(count);
//		for (iterator it = end(); it != begin() + count; ++it)
//			_alloc.construct(it._ptr, value);
//	}
//	_vectorSize = count;
//
//	return ;
//}
//
//// swap
//template< class Type, class Allocator >
//void	vector< Type, Allocator >::swap(vector< Type, Allocator > &other)
//{
//	ft::vector< Type, Allocator >::pointer d(data());
//	ft::vector< Type, Allocator >::size_type c(capacity());
//	ft::vector< Type, Allocator >::size_type s(size());
//	ft::vector< Type, Allocator >::allocator_type a(get_allocator());
//
//	_vectorCapacity = other.capacity();
//	_vectorSize = other.size();
//	_elements = other.data();
//	_alloc = other.get_allocator();
//
//	other._vectorCapacity = c;
//	other._vectorSize = s;
//	other._alloc = a;
//	other._elements = d;
//
//	return ;
//}
//
///*
// * Non-member functions
// */
//
} //namespace
