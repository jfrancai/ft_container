#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>

namespace ft {

template<typename Type>
class vector
{
	public:
		vector(void);
		~vector(void);
		vector(vector const &src);
		vector	&operator=(vector const &rhs);
	private:
};

} //namespace

#include "vector.tpp"

#endif
