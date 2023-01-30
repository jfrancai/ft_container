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

		bool	checkerHelper(node_pointer node, bool &status)
		{
			if (status)
				return (status);
			if (node->color && (node->right->color || node->left->color))
			{
				status = true;
				return (status);
			}
			if (node != _NILL)
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
			if (node == _NILL)
			{
				if (depth != maxDepth)
					status = true;
				return (status);
			}
			if (node != _NILL)
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
			while(node != _NILL)
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
			insertFix(node);
		}

		node_pointer	getRoot(void) const {
			return (_root);
		}

		void	printTree(void)
		{
			if (_root)
				printHelper(_root, "", true);
		}
		//RedBlackTree(RedBlackTree const &src);
		//RedBlackTree	&operator=(RedBlackTree const &rhs);
	private:
		void	printHelper(node_pointer root, std::string indent, bool last)
		{
			if (root != _NILL)
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
				std::cout << root->data << "(" << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
		}
		node_pointer	_NILL;
		node_pointer	_root;
};

} //namespace

#endif
