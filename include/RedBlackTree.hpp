#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include <iostream>

namespace ft {

template< typename Type >
struct Node {
	Type			data;
	Node< Type >	*parent;
	Node< Type >	*left;
	Node< Type >	*right;
	bool			color;
};

template< typename Type >
class RedBlackTree
{
	public:
		typedef Type					value_type;
		typedef value_type				*pointer;
		typedef const value_type		*const_pointer;
		typedef value_type				&reference;
		typedef const value_type		&const_reference;
		typedef Node< Type >			node_type;
		typedef node_type				*node_pointer;
		typedef node_type				&node_reference;

		RedBlackTree(void)
		{
			_NILL = new Node< Type >;
			_NILL->color = false;
			_NILL->left = NULL;
			_NILL->right = NULL;
			_root = _NILL;
		}
		~RedBlackTree(void) {}

		void	rightRotate(node_pointer y)
		{
			node_pointer x = y->left;
			y->left = x->right;
			if (x->right != _NILL)
				x->right->parent = y;	
			x->parent = y->parent;
			if (y->parent == NULL)
				_root = x;
			else if (y == y->parent->right)
				y->parent->right = x;
			else
				y->parent->left = x;
			x->right = y;
			y->parent = x;
		}

		void	leftRotate(node_pointer x)
		{
			node_pointer y = x->right;
			x->right = y->left;
			if (y->left != _NILL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void	insert(const_reference key)
		{

			node_pointer node = new node_type;
			node->parent = NULL;
			node->data = key;
			node->left = _NILL;
			node->right = _NILL;
			node->color = true;

			node_pointer y = NULL;
			node_pointer x = _root;

			while (x != _NILL)
			{
				y = x;
				if (node->data < x->data)
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (node->data < y->data)
				y->left = node;
			else
				y->right = node;
			if (node->parent == NULL)
			{
				node->color = false;
				return ;
			}
			if (node->parent->parent == NULL)
				return;
		}

		node_pointer	getRoot(void) const {
			return (_root);
		}
		//RedBlackTree(RedBlackTree const &src);
		//RedBlackTree	&operator=(RedBlackTree const &rhs);
	private:
		node_pointer	_NILL;
		node_pointer	_root;
};

} //namespace

#endif
