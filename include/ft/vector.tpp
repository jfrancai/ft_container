namespace ft {

template<typename Type>
vector<Type>::vector(void)
{
	return ;
}

template<typename Type>
vector<Type>::~vector(void)
{
	return ;
}

template<typename Type>
vector<Type>::vector(vector const &src)
{
	*this = src;

	return ;
}

template<typename Type>
vector<Type>	&vector<Type>::operator=(vector const &rhs)
{
	(void)rhs;

	return (*this);
}

} //namespace
