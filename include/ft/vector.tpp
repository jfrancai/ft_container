namespace ft {

template<typename T>
vector<T>::vector(void)
{
	std::cout << "vector default constructor called" << std::endl;
	return ;
}

template<typename T>
vector<T>::~vector(void)
{
	std::cout << "vector destructor called" << std::endl;
	return ;
}

template<typename T>
vector<T>::vector(vector const &src)
{
	std::cout << "vector copy constructor called" << std::endl;
	*this = src;

	return ;
}

template<typename T>
vector<T>	&vector<T>::operator=(vector const &rhs)
{
	std::cout << "vector copy assignment operator called" << std::endl;
	(void)rhs;

	return (*this);
}

} //namespace
