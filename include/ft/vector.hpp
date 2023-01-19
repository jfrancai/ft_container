#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <ft/random_access_iterator.hpp>
#include <ft/reverse_iterator.hpp>

namespace ft {

template< class Type, class Allocator = std::allocator< Type > >
class vector
{
	public:
		// Member types (aliases)
		typedef Type 										value_type;
		typedef Allocator 									allocator_type;
		typedef std::size_t 								size_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename Allocator::pointer					pointer;
		typedef typename Allocator::const_pointer			const_pointer;
		typedef LegacyRandomAccessIterator< Type >			iterator;
		typedef LegacyRandomAccessIterator< const Type >	const_iterator;
		typedef ft::reverse_iterator< iterator >			reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;

		explicit vector( const Allocator& alloc = Allocator());
		explicit vector(size_type count, const Type& value = Type(), const Allocator& alloc = Allocator());
		vector( const vector& other);
		~vector(void);

		vector&					operator=(const vector& other);
		void					assign(size_type count, const Type& value);
		allocator_type			get_allocator(void) const;

		//// Element access ////
		const_reference			at( size_type pos ) const;
		reference				at( size_type pos );
		const_reference			operator[](size_type pos) const;
		reference				operator[](size_type pos);
		reference				front(void);
		const_reference			front(void) const;
		reference				back(void);
		const_reference			back(void) const;
		pointer					data(void);
		const_pointer			data(void) const;

		//// Iterators ////
		const_iterator			begin(void) const;
		iterator				begin(void);
		const_iterator			end(void) const;
		iterator				end(void);

		//// Capacity ////
		bool					empty(void);
		size_type				size(void) const;
		size_type				max_size() const;
		void					reserve( size_type new_cap );
		size_type				capacity(void) const;

		//// Modifiers ////
		void					clear(void);
		iterator				insert(const_iterator pos, const Type &value);
		void					insert(const_iterator pos, size_type count, const Type &value);
		template < class InputIt >
		void					insert(const_iterator pos, InputIt first, InputIt last);

		iterator				erase(iterator pos);
		iterator				erase(iterator first, iterator last);
		void					push_back(const Type& value);
		void					pop_back(void);
		void					resize(size_type count, Type value = Type());
		void					swap(vector< Type, Allocator > &other);

	private:
		allocator_type			_alloc;
		static const size_type	_initialCapacity;
		size_type				_vectorCapacity;
		size_type				_vectorSize;
		pointer 				_elements;
};

} // namespace ft

#include "vector.tpp"

#endif
