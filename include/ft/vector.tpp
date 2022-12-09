namespace ft {

template< class Type, class Allocator >
vector< Type, Allocator >::vector(void) : _vectorSize(0)
{
	try
	{
		this->_elements = this->alloc.allocate(2);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	this->_elements[0] = 0;
	this->_elements[1] = 0;
	return ;
}

/*
 * Member functions
 */

// Element access

template< class Type, class Allocator >
typename vector< Type, Allocator >::reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos)
{
	return (this->_elements[pos]);
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
	this->_vectorSize++;
	(void)value;
	return ;
}

template< class Type, class Allocator >
void	vector< Type, Allocator >::pop_back(void)
{
	if (this->_vectorSize == 0)
		return ;
	this->_vectorSize--;
	return ;
}

/* 
 * Non-member functions
 */

} //namespace
