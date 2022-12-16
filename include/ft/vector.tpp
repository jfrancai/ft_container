namespace ft {

/*
 * Testing
 */
////////////////////////////////////////////
// Accessors
template< class Type, class Allocator >
typename vector< Type, Allocator >::allocator_type	&vector< Type, Allocator >::getAlloc(void)
{
	return (this->_alloc);
}

template< class Type, class Allocator >
typename vector< Type, Allocator>::pointer	&vector< Type, Allocator >::getElements(void)
{
	return (this->_elements);
}

template< class Type, class Allocator >
typename vector< Type, Allocator>::size_type	vector< Type, Allocator >::getCapacity(void) const
{
	return (this->_vectorCapacity);
}
////////////////////////////////////////////

/*
 * Statics
 */

template< class Type, class Allocator >
const typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::_initialCapacity = 2;

/*
 * Member functions
 */

// Constructors

template< class Type, class Allocator >
vector< Type, Allocator >::vector(void) :
	_vectorCapacity(_initialCapacity),
	_vectorSize(0),
	_elements(0)
{
	try
	{
		this->_elements = this->_alloc.allocate(this->_initialCapacity);
	}
	catch (std::exception &e)
	{
		std::cout << "Default constructor : " << e.what() << std::endl;
	}

	return ;
}

template< class Type, class Allocator >
vector< Type, Allocator >::~vector(void)
{
	for (size_type i = 0; i < this->_vectorSize; i++)
		this->_alloc.destroy(this->_elements + i);
	this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
	return ;
}

// operator=
/*
template< class Type, class Allocator >
typename ft::vector< Type, Allocator >	&vector< Type, Allocator >::operator=(const typename ft::vector< Type, Allocator >	&other)
{
	if (this != &other)
	{
	}
	return (*this);
}
*/

// assign

template< class Type, class Allocator >
void	vector< Type, Allocator >::assign(typename vector< Type, Allocator >::size_type count, const Type& value)
{
	// Put max_size here when its done
	if (count > 9223372036854775807)
	{
		throw std::invalid_argument("cannot create std::vector larger than max_size()");
		return ;
	}
	for (size_type i = 0; i < this->_vectorSize; i++)
		this->_alloc.destroy(this->_elements + i);
	if (this->_vectorCapacity < count)
	{
		this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
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
			static_cast< const typename ft::vector< Type, Allocator >& >(*this)[pos]
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
			static_cast< const typename ft::vector< Type, Allocator >& >(*this).front()
		)
	);
}

//// Capacity ////

template< class Type, class Allocator >
typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::size(void) const
{
	return (this->_vectorSize);
}

//// Modifiers ////

template< class Type, class Allocator >
void	vector< Type, Allocator >::push_back(const Type& value)
{
		try
		{
			if (this->_vectorSize == this->_vectorCapacity)
			{
				pointer	newElements = this->_alloc.allocate(this->_vectorSize * 2);
				for (size_type i = 0; i < this->_vectorSize; i++)
				{
					this->_alloc.construct(newElements + i, (*this)[i]);
					this->_alloc.destroy(this->_elements + i);
				}
				this->_alloc.deallocate(this->_elements, this->_vectorCapacity);
				this->_vectorCapacity *= 2;
				this->_elements = newElements;
			}
			this->_alloc.construct(this->_elements + this->_vectorSize, value);
			this->_vectorSize++;
		}
		catch (std::exception &e)
		{
			std::cout << "push_back : " << e.what() << std::endl;
		}

	return ;
}

template< class Type, class Allocator >
void	vector< Type, Allocator >::pop_back(void)
{
	if (this->_vectorSize == 0)
		return ;
	this->_vectorSize--;
	this->_alloc.destroy(this->_elements + this->_vectorSize);
	return ;
}

/*
 * Non-member functions
 */

} //namespace
