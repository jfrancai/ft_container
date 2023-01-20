namespace ft {

/*
 * Statics
 */

template< class Type, class Allocator >
const typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::_initialCapacity = 1;

/*
 * Member functions
 */

// Constructors
template< class Type, class Allocator >
vector< Type, Allocator >::vector(const Allocator& alloc) :
	_alloc(alloc),
	_vectorCapacity(0),
	_vectorSize(0),
	_elements(0)
{
	return ;
}

template< class Type, class Allocator >
vector< Type, Allocator >::vector(const vector& rhs) :
	_vectorCapacity(rhs.capacity()),
	_vectorSize(rhs.size())
{
	if (_vectorSize)
		_elements = _alloc.allocate(_vectorCapacity);
	else
		_elements = 0;
	for (size_type i = 0; i < _vectorSize; i++)
		_alloc.construct(_elements + i, rhs[i]);

	return ;
}

template< class Type, class Allocator >
vector< Type, Allocator >::vector(size_type count, const Type& value, const Allocator& alloc) :
	_alloc(alloc),
	_vectorCapacity(count),
	_vectorSize(count)
{
	if (count > max_size())
		throw std::length_error("cannot create std::vector larger than max_size()");
	_elements = _alloc.allocate(count);
	for (size_type i = 0; i < count; i++)
		_alloc.construct(_elements + i, value);
}

// Destructor
template< class Type, class Allocator >
vector< Type, Allocator >::~vector(void)
{
	for (size_type i = 0; i < _vectorSize; i++)
		_alloc.destroy(_elements + i);
	_alloc.deallocate(_elements, _vectorCapacity);

	return ;
}

// operator=
template< class Type, class Allocator >
typename ft::vector< Type, Allocator >	&vector< Type, Allocator >::operator=(const typename ft::vector< Type, Allocator >	&rhs)
{
	if (this != &rhs)
	{
		for (size_type i = 0; i < _vectorSize; i++)
			_alloc.destroy(_elements + i);
		if (_vectorCapacity != rhs.capacity())
		{
			pointer	pOrigin = _elements;
			_elements = _alloc.allocate(rhs.capacity());
			_alloc.deallocate(pOrigin, _vectorCapacity);
			/*
			 *
			 * This would be dangerous behaviour since we deallocate memory 
			 * of this object without knowing in advance if the allocation that
			 * come next is going to work or not...
			 *
			_alloc.deallocate(_elements, _vectorCapacity);
			_elements = _alloc.allocate(rhs.capacity());
			*/
		}
		_vectorSize = rhs.size();
		for (size_type i = 0; i < _vectorSize; i++)
			_alloc.construct(_elements + i, rhs[i]);
		_vectorCapacity = rhs.capacity();
	}

	return (*this);
}

// assign
template< class Type, class Allocator >
void	vector< Type, Allocator >::assign(typename vector< Type, Allocator >::size_type count, const Type& value)
{
	if (count > _alloc.max_size())
	{
		throw std::invalid_argument("cannot create std::vector larger than max_size()");
		return ;
	}
	for (size_type i = 0; i < _vectorSize; i++)
		_alloc.destroy(_elements + i);
	if (_vectorCapacity < count)
	{
		_alloc.deallocate(_elements, _vectorCapacity);
		if (_vectorCapacity == 0)
			_vectorCapacity = 1;
		while (_vectorCapacity < count)
			_vectorCapacity *= 2;
		_elements = _alloc.allocate(_vectorCapacity);
	}
	for (size_type i = 0; i < count; i++)
		_alloc.construct(_elements + i, value);
	_vectorSize = count;

	return ; 
}

// get_allocator
template< class Type, class Allocator >
typename ft::vector< Type, Allocator >::allocator_type	vector< Type, Allocator >::get_allocator(void) const
{
	return (_alloc);
}

//// Element access ////

// at
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_reference vector< Type, Allocator >::at( typename vector< Type, Allocator >::size_type pos ) const
{
	if (pos >= size())
	{
		std::ostringstream errorMsg;
		errorMsg << "vector::_M_range_check: __n (which is " << pos << ") >= size() (which is " << size() << ")";
		throw std::out_of_range(errorMsg.str());
	}
	return ((*this)[pos]);
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::reference vector< Type, Allocator >::at( vector< Type, Allocator >::size_type pos )
{
	return (
		const_cast< reference >(
			static_cast< const ft::vector< Type, Allocator >& >(*this).at(pos)
		)
	);
}

// operator[]
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos) const
{
	return (_elements[pos]);
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos)
{
	return (
		const_cast< reference >(
			static_cast< const ft::vector< Type, Allocator >& >(*this)[pos]
		)
	);
}

// front
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::front(void) const
{
	return ((*this)[0]);
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::reference	vector< Type, Allocator >::front(void)
{
	return (
		const_cast< reference >(
			static_cast< const ft::vector< Type, Allocator >& >(*this).front()
		)
	);
}

// back
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::back(void) const
{
	return ((*this)[_vectorSize - 1]);
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::reference	vector< Type, Allocator >::back(void)
{
	return (
		const_cast< reference >(
			static_cast< const ft::vector< Type, Allocator >& >(*this).back()
		)
	);
}

// data
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_pointer	vector< Type, Allocator >::data(void) const
{
	return (_elements);
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::pointer	vector< Type, Allocator >::data(void)
{
	return (
		const_cast< pointer >(
			static_cast< const ft::vector< Type, Allocator >& >(*this).data()
		)
	);
}

//// Iterators ////

// begin

template< class Type, class Allocator >
typename vector< Type, Allocator >::const_iterator	vector< Type, Allocator >::begin(void) const
{
	return (const_iterator(_elements));
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::iterator	vector< Type, Allocator >::begin(void)
{
	return (iterator(_elements));
}

// end
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_iterator	vector< Type, Allocator >::end(void) const
{
	return (const_iterator(_elements + _vectorSize));
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::iterator	vector< Type, Allocator >::end(void)
{
	return (iterator(_elements + _vectorSize));
}

//// Capacity ////

// empty
template< class Type, class Allocator >
bool	vector< Type, Allocator >::empty(void)
{
	if (_vectorSize == 0)
		return (true);
	return (false);
}

// size
template< class Type, class Allocator >
typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::size(void) const
{
	return (_vectorSize);
}

// max_size
template< class Type, class Allocator >
typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::max_size(void) const
{
	return (_alloc.max_size());
}

// reserve
template< class Type, class Allocator >
void	vector< Type, Allocator >::reserve(typename vector< Type, Allocator >::size_type new_cap)
{
	if (new_cap <= capacity())
		return ;
	if (new_cap > max_size())
		throw std::length_error("vector::reserve");
	pointer newElements = _alloc.allocate(new_cap);
	for (size_type i = 0; i < _vectorSize; i++)
	{
		_alloc.construct(newElements + i, (*this)[i]);
		_alloc.destroy(&(*this)[i]);
	}
	_alloc.deallocate(_elements, _vectorCapacity);
	_vectorCapacity = new_cap;
	_elements = newElements;

	return ;
}

// capacity
template< class Type, class Allocator >
typename vector< Type, Allocator>::size_type	vector< Type, Allocator >::capacity(void) const
{
	return (_vectorCapacity);
}

//// Modifiers ////

// clear
template< class Type, class Allocator >
void	vector< Type, Allocator >::clear(void)
{
	for(size_type i = 0; i < _vectorSize; i++)
		_alloc.destroy(_elements + i);
	_vectorSize = 0;
	return ;
}

//insert
template< class Type, class Allocator >
typename vector< Type, Allocator >::iterator	vector< Type, Allocator>::insert(typename vector< Type, Allocator >::const_iterator pos, const Type &value)
{
	size_type	index = pos - begin();
	if (size() == capacity())
		reserve(capacity() ? 2 * capacity() : _initialCapacity);
	for (size_type i = size(); i > index; --i)
		_elements[i] = _elements[i - 1];
	_elements[index] = value;
	++_vectorSize;

	return (iterator(_elements + index));
}

template< class Type, class Allocator >
void	vector< Type, Allocator>::insert(typename vector< Type, Allocator >::const_iterator pos, typename vector< Type, Allocator >::size_type count, const Type &value)
{
	size_type	index = pos - begin();
	if (size() + count > capacity())
		reserve(std::max(capacity() * 2, size() + count));
	for (size_type i = size(); i > index; --i)
		_elements[i + count - 1] = _elements[i - 1];
	for (size_type i = 0; i < count; ++i)
		_elements[index + i] = value;
	_vectorSize += count;

	return ;
}

template< class Type, class Allocator >
template < typename  InputIt >
void	vector< Type, Allocator >::insert(typename vector< Type, Allocator >::const_iterator pos, InputIt first, InputIt last)
{
	size_type	index = pos - begin();
	size_type	count = 0;
	for (InputIt it = first; it != last; ++it)
		++count;
	if (count + size() > capacity())
	{
		size_type new_cap = std::max(capacity() * 2, size() + count);
		pointer newElements = _alloc.allocate(new_cap);
		for (size_type i = 0; i < _vectorSize; i++)
			_alloc.construct(newElements + i, (*this)[i]);
		for (size_type i = _vectorSize; i > index; --i)
			newElements[i + count - 1] = _elements[i - 1];
		for (size_type i = 0; i < count; ++i)
			newElements[index + i] = *(first++);
		for (size_type i = 0; i < _vectorSize; i++)
			_alloc.destroy(&(*this)[i]);
		_alloc.deallocate(_elements, _vectorCapacity);
		_vectorCapacity = new_cap;
		_elements = newElements;
	}
	else
	{
		for (size_type i = _vectorSize; i > index; --i)
			_elements[i + count - 1] = _elements[i - 1];
		for (size_type i = 0; i < count; ++i)
			_elements[index + i] = *(first++);
	}
	_vectorSize += count;

	return ;
}

// erase
template< class Type, class Allocator >
typename vector< Type, Allocator>::iterator	vector< Type, Allocator >::erase(typename vector< Type, Allocator >::iterator first, typename vector< Type, Allocator >::iterator last)
{
	if (first == last)
		return (first);
	size_type num_elements = std::distance(first, last);
	if (last != end())
		std::copy(last, end(), first);
	resize(size() - num_elements);
	return (first);
}

template< class Type, class Allocator >
typename vector< Type, Allocator>::iterator	vector< Type, Allocator >::erase(typename vector< Type, Allocator >::iterator pos)
{
	if (pos == end())
		return (pos);
	std::copy(pos + 1, end(), pos);
	resize(size() - 1);
	return (pos); 
}

// push_back
template< class Type, class Allocator >
void	vector< Type, Allocator >::push_back(const Type& value)
{
	if (_vectorSize == _vectorCapacity)
	{
		pointer newElements;
		newElements = _alloc.allocate(capacity() ? _vectorCapacity * 2 : _initialCapacity);
		for (size_type i = 0; i < _vectorSize; i++)
		{
			_alloc.construct(newElements + i, (*this)[i]);
			_alloc.destroy(_elements + i);
		}
		_alloc.deallocate(_elements, _vectorCapacity);
		_vectorCapacity = capacity() ? _vectorCapacity * 2 : _initialCapacity;
		_elements = newElements;
	}
	_alloc.construct(_elements + _vectorSize, value);
	_vectorSize++;
	return ;
}

// pop_back
template< class Type, class Allocator >
void	vector< Type, Allocator >::pop_back(void)
{
	if (_vectorSize == 0)
		return ;
	_vectorSize--;
	_alloc.destroy(_elements + _vectorSize);

	return ;
}

// resize
template< class Type, class Allocator >
void	vector< Type, Allocator >::resize(typename vector< Type, Allocator >::size_type count, Type value)
{
	if (count > max_size())
		throw std::length_error("vector::resize");
	if (count < size())
	{
		for (iterator it = begin() + count; it != end(); ++it)
			_alloc.destroy(it._ptr);
	}
	else if (count > size())
	{
		reserve(count);
		for (iterator it = end(); it != begin() + count; ++it)
			_alloc.construct(it._ptr, value);
	}
	_vectorSize = count;

	return ;
}

// swap
template< class Type, class Allocator >
void	vector< Type, Allocator >::swap(vector< Type, Allocator > &other)
{
	ft::swap(*this, other);
	return ;
}

/*
 * Non-member functions
 */

} //namespace
