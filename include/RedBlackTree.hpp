#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP
#include <iostream>
#include "utility.hpp"

namespace ft {

template< typename Type >
struct Node {
	typedef Type				value_type;
	typedef Type				*pointer;
	typedef Type				&reference;
	typedef Node< Type >		*node_pointer;
	typedef Node< Type >		&node_reference;

	pointer			data;
	node_pointer	parent;
	node_pointer	left;
	node_pointer	right;
	bool			color;
	bool			isNILL;

	Node< Type >	&operator=(const Node< Type > &rhs)
	{
		if (data)
			data = new value_type(*rhs.data);
		parent = NULL;
		left = NULL;
		right = NULL;
		color = rhs.color;
		isNILL = rhs.isNILL;
	}

	Node(const Node< Type > &src) : 
		data(NULL),
		parent(NULL),
		left(NULL),
		right(NULL),
		color(src.color),
		isNILL(src.isNILL)
	{ if (src.data) data = new value_type(*src.data); }

	Node(void) : 
		data(NULL),
		parent(NULL),
		left(NULL),
		right(NULL),
		color(false),
		isNILL(true)
	{}

	Node(const Type &d, bool c = false, bool isN = false) : 
		data(NULL),
		parent(NULL),
		left(NULL),
		right(NULL),
		color(c),
		isNILL(isN)
	{ data = new value_type(d); }

	~Node()
	{
		if (data) { delete data; }
		if (left && !left->isNILL && !isNILL)
			delete left;
		if (right && !right->isNILL && !isNILL)
			delete right;
	}

	friend bool	operator==(const Node< Type > &lhs, const Node< Type > &rhs)
	{
		if (*lhs.data == *rhs.data &&
			lhs.color == rhs.color &&
			lhs.isNILL == rhs.isNILL)
			return (true);
		return (false);
	}

	node_pointer	predecessor(node_pointer node) const
	{
		node_pointer x = const_cast< node_pointer >(node);

		if (x->left && !x->left->isNILL)
		{
			x = x->left;
			while (x->right->isNILL == false)
				x = x->right;
			return (x);
		}

		node_pointer y = x->parent;
		while (!x->isNILL && y && !y->isNILL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return (y);
	}

	node_pointer	successor(node_pointer node) const
	{
		node_pointer x = const_cast< node_pointer >(node);

		if (x->right && !x->right->isNILL)
		{
			x = x->right;
			while (x->left->isNILL == false)
				x = x->left;
			return (x);
		}

		node_pointer y = x->parent;
		node_pointer nill = x->right;
		while (y && !y->isNILL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		if (y)
			return (y);
		return (nill);
	}
};

template < typename Type > bool	operator<(const Node< Type > &lhs, const Node< Type > &rhs) { if (!lhs.isNILL && !rhs.isNILL && *lhs.data < *rhs.data) { return (true); } return (false); }
template < typename Type > bool	operator<=(const Node< Type > &lhs, const Node< Type > &rhs) { return (!(rhs < lhs)); }
template < typename Type > bool	operator>=(const Node< Type > &lhs, const Node< Type > &rhs) { return (!(lhs < rhs)); }
template < typename Type > bool	operator>(const Node< Type > &lhs, const Node< Type > &rhs) { return (rhs < lhs); }
template < typename Type > bool	operator!=(const Node< Type > &lhs, const Node< Type > &rhs) {return (!(lhs == rhs)); }

template< typename Key, typename Type, typename Compare >
class RedBlackTree
{
	public:
		typedef Key				key_type;
		typedef Type			value_type;
		typedef Type			*pointer;
		typedef Type			&reference;
		typedef const Type		&const_reference;
		typedef Node< Type >	node_type;
		typedef node_type		*node_pointer;
		typedef node_type		&node_reference;
		typedef Compare			key_compare;

		~RedBlackTree(void) 
		{
			if (_root != _NILL)
				delete _root;
			delete _NILL;
		}

		RedBlackTree(void)
		{
			_NILL = new node_type();
			_root = _NILL;
		}

		RedBlackTree(RedBlackTree const &src)
		{
			_NILL = new node_type();
			_root = cloneBinaryTree(src.getRoot());
		}

		node_pointer	minimum(node_pointer node) const
		{
			while (node->left->isNILL == false)
				node = node->left;
			return (node);
		}

		node_pointer	maximum(node_pointer node) const
		{
			while (node->right->isNILL == false)
				node = node->right;
			return (node);
		}

		node_pointer cloneBinaryTree(node_pointer node)
		{
			if (node->isNILL)
				return (new node_type(*node));
			node_pointer newNode = new node_type(*node);
			newNode->left = cloneBinaryTree(node->left);
			newNode->left->parent = newNode;
			newNode->right = cloneBinaryTree(node->right);
			newNode->right->parent = newNode;
			return (newNode);
		}

		void	deleteNode(node_pointer node)
		{
			node->left = NULL;
			node->right = NULL;
			delete node;
		}

		RedBlackTree	&operator=(RedBlackTree const &rhs)
		{
			if (!_root->isNILL)
				delete _root;
			_root = cloneBinaryTree(rhs.getRoot());
			return (*this);
		}

		bool	checkerHelper(node_pointer node, bool &status)
		{
			if (status)
				return (status);
			if (node->color && (node->right->color || node->left->color))
			{
				status = true;
				return (status);
			}
			if (!node->isNILL)
			{
				checkerHelper(node->left, status);
				checkerHelper(node->right, status);
			}
			return (status);
		}

		bool	depthHelper(node_pointer node, bool &status, int &depth, int &maxDepth)
		{
			if (status)
				return (status);
			if (node->isNILL)
			{
				if (depth != maxDepth)
					status = true;
				return (status);
			}
			if (!node->isNILL)
			{
				if (node->color == false)
					depth++;
				depthHelper(node->left, status, depth, maxDepth);
				depthHelper(node->right, status, depth, maxDepth);
				if (node->color == false)
					depth--;
			}
			return (status);
		}

		int	maxDepthHelper(node_pointer node)
		{
			int depth = 0;
			while(!node->isNILL)
			{
				if (node->color == false)
					depth++;
				node = node->left;
			}
			return (depth);
		}

		bool	checker(node_pointer root)
		{
			if (root->color)
			{
				std::cout << "root is black" << std::endl;
				printTree();
				return (false);
			}
			if (_NILL->color)
			{
				std::cout << "_NILL is black" << std::endl;
				printTree();
				return (false);
			}
			bool status = false;
			if (checkerHelper(_root, status))
			{
				std::cout << "The children of red nodes are always black." << std::endl;
				printTree();
				return (false);
			}
			status = false;
			int maxDepth = maxDepthHelper(_root);
			int depth = 0;
			if (depthHelper(_root, status, depth, maxDepth))
			{
				std::cout << "Depth property violated." << std::endl;
				std::cout << "depth = " << depth << std::endl;
				std::cout << "maxDepth = " << maxDepth << std::endl;
				printTree();
				return (false);
			}

			return (true);
		}

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
			if (!y->left->isNILL)
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

		void	insertFix(node_pointer k)
		{
			node_pointer	u;

			while (k->parent->color)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color)
					{
						u->color = false;
						k->parent->color = false;
						k->parent->parent->color = true;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							rightRotate(k);
						}
						k->parent->color = false;
						k->parent->parent->color = true;
						leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color)
					{
						u->color = false;
						k->parent->color = false;
						k->parent->parent->color = true;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							leftRotate(k);
						}
						k->parent->color = false;
						k->parent->parent->color = 1;
						rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
					break;
			}
			_root->color = false;
		}

		ft::pair< node_pointer, bool >	insert(const_reference key)
		{
			node_pointer node = searchTree(_root, key.first);
			if (!node->isNILL)
				return (ft::make_pair(node, false));
			node = new node_type(key);
			node->left = _NILL;
			node->right = _NILL;
			node->color = true;

			node_pointer y = NULL;
			node_pointer x = _root;

			while (!x->isNILL)
			{
				y = x;
				if (_compare(node->data->first, x->data->first))
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (_compare(node->data->first, y->data->first))
				y->left = node;
			else
				y->right = node;
			if (node->parent == NULL)
			{
				node->color = false;
				return (ft::make_pair(node, true));
			}
			if (node->parent->parent == NULL)
				return (ft::make_pair(node, true));
			insertFix(node);
			return (ft::make_pair(node, true));
		}

		void	transplantNode(node_pointer x, node_pointer y)
		{
			if (x->parent == NULL)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->parent = x->parent;
		}

		void deleteFix(node_pointer x)
		{
			node_pointer	s;
			while (x != _root && x->color == false)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == true)
					{
						s->color = false;
						x->parent->color = true;
						leftRotate(x->parent);
						s = x->parent->right;
					}
					if (s->left->color == false && s->right->color == false)
					{
						s->color = true;
						x = x->parent;
					}
					else
					{
						if (s->right->color == false)
						{
							s->left->color = false;
							s->color = true;
							rightRotate(s);
							s = x->parent->right;
						}
						s->color = x->parent->color;
						x->parent->color = false;
						s->right->color = false;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == true)
					{
						s->color = false;
						x->parent->color = true;
						rightRotate(x->parent);
						s = x->parent->left;
					}
					if (s->right->color == false && s->right->color == false)
					{
						s->color = true;
						x = x->parent;
					}
					else
					{
						if (s->left->color == false)
						{
							s->right->color = false;
							s->color = true;
							leftRotate(s);
							s = x->parent->left;
						}
						s->color = x->parent->color;
						x->parent->color = 0;
						s->left->color = 0;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = false;
		}

		void	deleteNode(const_reference data)
		{
			node_pointer	node = searchTree(_root, data);

			if (node->isNILL)
			{
				std::cout << "Key is not in the tree" << std::endl;
				return ;
			}
			node_pointer	x;
			node_pointer	y;
			int	original_color = node->color;
			if (node->left->isNILL)
			{
				x = node->right;
				transplantNode(node, node->right);
			}
			else if (node->right->isNILL)
			{
				x = node->left;
				transplantNode(node, node->left);
			}
			else
			{
				y = minimum(node->right);
				original_color = y->color;
				x = y->right;
				if (y->parent == node)
					x->parent = y;
				else
				{
					transplantNode(y, y->right);
					y->right = node->right;
					y->right->parent = y;
				}
				transplantNode(node, y);
				y->left = node->left;
				y->left->parent = y;
				y->color = node->color;
			}
			deleteNode(node);
			if (original_color == false)
				deleteFix(x);
		}

		node_pointer	getRoot(void) const {
			return (_root);
		}

		node_pointer	getNill(void) const {
			return (_NILL);
		}


		void	printTree(void) const
		{
			if (_root)
				printHelper(_root, "", true);
		}

		node_pointer	searchTree(node_pointer node, key_type key)
		{
			while (!node->isNILL)
			{
				if (key == node->data->first)
					return (node);
				if (_compare(key, node->data->first))
					node = node->left;
				else
					node = node->right;
			}
			return (node);
		}

		void	setRoot(node_pointer node)
		{
			_root = node;
		}

	private:
		void	printHelper(node_pointer root, std::string indent, bool last) const
		{
			if (!root->isNILL)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "   ";
				}
				else
				{
					std::cout << "L----";
					indent += "|  ";
				}
				std::string sColor = root->color ? "RED" : "BLACK";
				std::cout << "(" << (*root->data).first << ", " << (*root->data).second << ", " << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}
		node_pointer	_NILL;
		node_pointer	_root;
		key_compare		_compare;
};

} //namespace

#endif
