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
	if (this->_vectorSize)
	{
		this->_elements = this->_alloc.allocate(this->_vectorCapacity);
	}
	else
		this->_elements = 0;
	for (size_type i = 0; i < this->_vectorSize; i++)
		this->_alloc.construct(this->_elements + i, rhs[i]);

	return ;
}

template< class Type, class Allocator >
vector< Type, Allocator >::vector(size_type count, const Type& value, const Allocator& alloc) :
	_alloc(alloc),
	_vectorCapacity(count),
	_vectorSize(count)
{
	if (count > this->max_size())
		throw std::length_error("cannot create std::vector larger than max_size()");
	this->_elements = this->_alloc.allocate(count);
	for (size_type i = 0; i < count; i++)
		this->_alloc.construct(this->_elements + i, value);
}

// Destructor
template< class Type, class Allocator >
vector< Type, Allocator >::~vector(void)
{
	for (size_type i = 0; i < this->_vectorSize; i++)
		this->_alloc.destroy(this->_elements + i);
	this->_alloc.deallocate(this->_elements, this->_vectorCapacity);

	return ;
}

// operator=
template< class Type, class Allocator >
typename ft::vector< Type, Allocator >	&vector< Type, Allocator >::operator=(const typename ft::vector< Type, Allocator >	&rhs)
{
	if (this != &rhs)
	{
		for (size_type i = 0; i < this->_vectorSize; i++)
			this->_alloc.destroy(this->_elements + i);
		if (this->_vectorCapacity != rhs.capacity())
		{
			pointer	pOrigin = this->_elements;
			this->_elements = this->_alloc.allocate(rhs.capacity());
			this->_alloc.deallocate(pOrigin, this->_vectorCapacity);
			/*
			 *
			 * This would be dangerous behaviour since we deallocate memory 
			 * of this object without knowing in advance if the allocation that
			 * come next is going to work or not...
			 *
			this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
			this->_elements = this->_alloc.allocate(rhs.capacity());
			*/
		}
		this->_vectorSize = rhs.size();
		for (size_type i = 0; i < this->_vectorSize; i++)
			this->_alloc.construct(this->_elements + i, rhs[i]);
		this->_vectorCapacity = rhs.capacity();
	}

	return (*this);
}

// assign
template< class Type, class Allocator >
void	vector< Type, Allocator >::assign(typename vector< Type, Allocator >::size_type count, const Type& value)
{
	if (count > this->_alloc.max_size())
	{
		throw std::invalid_argument("cannot create std::vector larger than max_size()");
		return ;
	}
	for (size_type i = 0; i < this->_vectorSize; i++)
		this->_alloc.destroy(this->_elements + i);
	if (this->_vectorCapacity < count)
	{
		this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
		if (this->_vectorCapacity == 0)
			this->_vectorCapacity = 1;
		while (this->_vectorCapacity < count)
			this->_vectorCapacity *= 2;
		this->_elements = this->_alloc.allocate(this->_vectorCapacity);
	}
	for (size_type i = 0; i < count; i++)
		this->_alloc.construct(this->_elements + i, value);
	this->_vectorSize = count;

	return ; 
}

// get_allocator
template< class Type, class Allocator >
typename ft::vector< Type, Allocator >::allocator_type	vector< Type, Allocator >::get_allocator(void) const
{
	return (this->_alloc);
}

//// Element access ////

// at
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_reference vector< Type, Allocator >::at( typename vector< Type, Allocator >::size_type pos ) const
{
	if (pos >= this->size())
	{
		std::ostringstream errorMsg;
		errorMsg << "vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << this->size() << ")";
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
	return (this->_elements[pos]);
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
	return ((*this)[this->_vectorSize - 1]);
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
	return (this->_elements);
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
	return (const_iterator(this->_elements));
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::iterator	vector< Type, Allocator >::begin(void)
{
	return (iterator(this->_elements));
}

// end
template< class Type, class Allocator >
typename vector< Type, Allocator >::const_iterator	vector< Type, Allocator >::end(void) const
{
	return (const_iterator(this->_elements + this->_vectorSize));
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::iterator	vector< Type, Allocator >::end(void)
{
	return (iterator(this->_elements + this->_vectorSize));
}

//// Capacity ////

// empty
template< class Type, class Allocator >
bool	vector< Type, Allocator >::empty(void)
{
	if (this->_vectorSize == 0)
		return (true);
	return (false);
}

// size
template< class Type, class Allocator >
typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::size(void) const
{
	return (this->_vectorSize);
}

// max_size
template< class Type, class Allocator >
typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::max_size(void) const
{
	return (this->_alloc.max_size());
}

// reserve
template< class Type, class Allocator >
void	vector< Type, Allocator >::reserve(typename vector< Type, Allocator >::size_type new_cap)
{
	if (new_cap <= this->_vectorCapacity)
		return ;
	if (new_cap > this->max_size())
		throw std::length_error("vector::reserve");
	pointer newElements = this->_alloc.allocate(new_cap);
	for (size_type i = 0; i < this->_vectorSize; i++)
	{
		this->_alloc.construct(newElements + i, (*this)[i]);
		this->_alloc.destroy(&(*this)[i]);
	}
	this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
	this->_vectorCapacity = new_cap;
	this->_elements = newElements;
	return ;
}

// capacity
template< class Type, class Allocator >
typename vector< Type, Allocator>::size_type	vector< Type, Allocator >::capacity(void) const
{
	return (this->_vectorCapacity);
}

//// Modifiers ////

// clear
template< class Type, class Allocator >
void	vector< Type, Allocator >::clear(void)
{
	for(size_type i = 0; i < this->_vectorSize; i++)
		this->_alloc.destroy(this->_elements + i);
	this->_vectorSize = 0;
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
	if (pos == this->end())
		return (pos);
	std::copy(pos + 1, this->end(), pos);
	resize(this->size() - 1);
	return (pos); 
}

// push_back
template< class Type, class Allocator >
void	vector< Type, Allocator >::push_back(const Type& value)
{
	if (this->_vectorSize == this->_vectorCapacity)
	{
		pointer newElements;
		if (this->_vectorCapacity == 0)
			newElements = this->_alloc.allocate(this->_initialCapacity);
		else
			newElements = this->_alloc.allocate(this->_vectorSize * 2);
		for (size_type i = 0; i < this->_vectorSize; i++)
		{
			this->_alloc.construct(newElements + i, (*this)[i]);
			this->_alloc.destroy(this->_elements + i);
		}
		this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
		this->_vectorCapacity = this->_vectorCapacity ? this->_vectorCapacity * 2 : this->_initialCapacity;
		this->_elements = newElements;
	}
	this->_alloc.construct(this->_elements + this->_vectorSize, value);
	this->_vectorSize++;
	return ;
}

// pop_back
template< class Type, class Allocator >
void	vector< Type, Allocator >::pop_back(void)
{
	if (this->_vectorSize == 0)
		return ;
	this->_vectorSize--;
	this->_alloc.destroy(this->_elements + this->_vectorSize);

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
		for (iterator i = begin() + count; i != end(); ++i)
			_alloc.destroy(i._ptr);
	}
	else if (count > size())
	{
		reserve(count);
		for (iterator i = end(); i != begin() + count; ++i)
			_alloc.construct(i._ptr, value);
	}
	_vectorSize = count;

	return ;
}

// swap
template< class Type, class Allocator >
void	vector< Type, Allocator >::swap(vector< Type, Allocator > &other)
{
	std::swap(_vectorSize, other._vectorSize);
	std::swap(_vectorCapacity, other._vectorCapacity);
	std::swap(_elements, other._elements);
	std::swap(_alloc, other._alloc);

	return ;
}

//insert
template< class Type, class Allocator >
typename vector< Type, Allocator >::iterator	vector< Type, Allocator>::insert(typename vector< Type, Allocator >::const_iterator pos, const Type &value)
{
	size_type	index = pos - begin();
	if (size() == capacity())
		reserve(capacity() ? 2 * capacity() : 1);
	for (size_type i = size(); i > index; --i)
		_elements[i] = _elements[i - 1];
	_elements[index] = value;
	++_vectorSize;
	return (iterator(_elements + index));
}

/*
 * Non-member functions
 */

} //namespace
