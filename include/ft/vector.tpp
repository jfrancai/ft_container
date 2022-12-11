namespace ft {

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


// Operator=

/*
template< class Type, class Allocator >
typename ft::vector< Type, Allocator>	&vector< Type, Allocator >::operator=(const typename ft::vector< Type, Allocator >	&other)
{
	if (this != &other)
	{
	}
	return (*this);
}
*/

// Element access

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

// Capacity

template< class Type, class Allocator >
typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::size(void) const
{
	return (this->_vectorSize);
}

// Modifiers

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
