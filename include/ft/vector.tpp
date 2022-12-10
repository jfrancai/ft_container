namespace ft {

template< class Type, class Allocator >
const typename vector< Type, Allocator >::size_type	vector< Type, Allocator >::_initialCapacity = 4;

template< class Type, class Allocator >
vector< Type, Allocator >::vector(void) :
	_capacity(_initialCapacity),
	_vectorSize(0),
	_elements(0)
{
	try
	{
		this->_elements = this->alloc.allocate(this->_capacity);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	std::memset(this->_elements, 0, this->_initialCapacity);
	return ;
}

/*
 * Member functions
 */

// Element access

template< class Type, class Allocator >
typename vector< Type, Allocator >::const_reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos) const
{
	std::cout << "\033[1;33mconst operator[] is called\033[0m" << std::endl;
	return (this->_elements[pos]);
}

template< class Type, class Allocator >
typename vector< Type, Allocator >::reference	vector< Type, Allocator >::operator[](typename vector< Type, Allocator >::size_type pos)
{
	std::cout << "\033[1;32mnon-const operator[] is called\033[0m" << std::endl;
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
	(void)value;
	this->_vectorSize++;
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
