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
	bool			isNILL;

	Node(const Type &d = Type(), bool c = false, bool isN = false) : 
		data(d),
		parent(NULL),
		left(NULL),
		right(NULL),
		color(c),
		isNILL(isN)
	{}

	~Node()
	{
		if (left && !left->isNILL && !isNILL)
		{
			delete left;
			left = NULL;
		}
		if (right && !right->isNILL && !isNILL)
		{
			delete right;
			right = NULL;
		}
	}
};

template< typename Type, typename Compare = std::less< Type > >
class RedBlackTree
{
	public:
		typedef Type			value_type;
		typedef Type			*pointer;
		typedef const Type		*const_pointer;
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
			_NILL = getNewNode(Type(), false, true);
			_root = _NILL;
		}

		RedBlackTree(RedBlackTree const &src)
		{
			_NILL = getNewNode(Type(), false, true);
			_root = cloneBinaryTree(src.getRoot(), src._NILL);
		}

		node_pointer	getNewNode(Type data = Type(), bool color = true, bool isNILL = false)
		{
			node_pointer newNode = new node_type(data, color, isNILL);
			return (newNode);
		}

		node_pointer cloneBinaryTree(node_pointer node, node_pointer stop)
		{
			if (node->isNILL)
				return (_NILL);
			node_pointer newNode = getNewNode(node->data, node->color, node->isNILL);
			newNode->left = cloneBinaryTree(node->left, stop);
			newNode->right = cloneBinaryTree(node->right, stop);
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
			_root = cloneBinaryTree(rhs.getRoot(), rhs._NILL);
			return (*this);
		}

		bool	isIdentical(node_pointer root1, node_pointer root2) const
		{
			if (root1->isNILL && root2->isNILL)
				return (true);
			else if (root1->isNILL || root2->isNILL)
				return (false);
			else
			{
				if (root1->data == root2->data && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right))
					return (true);
				else
					return (false);
			}
		}

		bool	operator==(RedBlackTree const &rhs) const
		{
			return (isIdentical(this->getRoot(), rhs.getRoot()));
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

		std::pair< node_pointer, bool >	insert(const_reference key)
		{
			node_pointer node = searchTree(_root, key);
			if (!node->isNILL)
				return (std::make_pair(node, false));
			node = new node_type(key);
			node->left = _NILL;
			node->right = _NILL;
			node->color = true;

			node_pointer y = NULL;
			node_pointer x = _root;

			while (!x->isNILL)
			{
				y = x;
				if (_compare(node->data, x->data))
					x = x->left;
				else
					x = x->right;
			}

			node->parent = y;
			if (y == NULL)
				_root = node;
			else if (_compare(node->data, y->data))
				y->left = node;
			else
				y->right = node;
			if (node->parent == NULL)
			{
				node->color = false;
				return (std::make_pair(node, true));
			}
			if (node->parent->parent == NULL)
				return (std::make_pair(node, true));
			insertFix(node);
			return (std::make_pair(node, true));
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

		node_pointer minimum(node_pointer node) const
		{
			while (node && !node->left->isNILL)
				node = node->left;
			return (node);
		}

		node_pointer maximum(node_pointer node) const
		{
			while (!node->right->isNILL)
				node = node->right;
			return (node);
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

		void	deleteNode(value_type data)
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

		node_pointer	predecessor(node_pointer x) const
		{
			if (!x->left->isNILL)
				return (maximum(x->left));

			node_pointer y = x->parent;
			while (!y->isNILL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		node_pointer	successor(node_pointer x) const
		{
			if (!x->right->isNILL)
				return (minimum(x->right));

			node_pointer y = x->parent;
			while (!y->isNILL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return (y);
		}

		void	printTree(void)
		{
			if (_root)
				printHelper(_root, "", true);
		}

		node_pointer	searchTree(node_pointer node, value_type key)
		{
			if (node->isNILL || key == node->data)
				return (node);
			if (key < node->data)
				return (searchTree(node->left, key));
			return (searchTree(node->right, key));
		}
	private:
		void	printHelper(node_pointer root, std::string indent, bool last)
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
				std::cout << root->data << "(" << sColor << ")" << std::endl;
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
