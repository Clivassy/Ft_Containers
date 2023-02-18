#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "RedBlackTree.hpp"
#include "../utils/iterator_traits.hpp"

namespace ft {

	// 'T': the type of the element stored in the tree
	// 'node': the type of the node in the tree
	// 'Compare'
	template<typename T, typename node, class Compare>
	class RBT_iterator
	{ 
		private:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>	iterator;
		public:
			typedef T											value_type;
			typedef typename std::bidirectional_iterator_tag	iterator_category;
			typedef typename iterator::difference_type			difference_type;
			typedef typename iterator::pointer					pointer;
			typedef typename iterator::reference				reference;
			typedef node										node_pointer;

		protected:
			node_pointer _node;

		public:
			// CONSTRUCTORS 

			// Default constructor
			// Create an iterator object and initialize 'node' to NULL
			// Iterator will need to be assign to a valid node to be used.
			RBT_iterator() : _node() {}

			// Creates an iterator object and initialize the node with 'ptr' value.
			// Iterator will now point on 'ptr' (specific node in the tree)
			RBT_iterator(node_pointer ptr) : _node(ptr) {}

			// Copy constructor
			// Create new iterator intitialized with 'src' value.
			// /!\ both iterator will point to the same node in the tree.
			RBT_iterator(RBT_iterator const &src) : _node(src._node) {}

			//-- Overload operator
			RBT_iterator & operator=(RBT_iterator const & rhs) 
			{
				if (this == &rhs)
					return (*this);
				_node = rhs._node; 
				return *this;
			}
			
			// DESTRUCTOR
			~RBT_iterator() {}


			operator RBT_iterator<const T, node, Compare>() const 
			{
				return RBT_iterator<const T, node, Compare>(_node);
			}
			// ---------------------------------------------------------------------------

			// Post-increment operator
			RBT_iterator& operator++ (void) 
			{
				_node = increase(_node);
				return(*this);
			}

			// Pre-increment operator
			RBT_iterator operator++ (int) 
			{
				RBT_iterator temp = *this;
				_node = increase(_node);
				return(temp);
			}
			
			// Post-decrement operator
			RBT_iterator& operator-- (void) 
			{
				_node = decrease(_node);
				return(*this);
			}

			// Pre-decrement operator
			RBT_iterator operator-- (int) 
			{
				RBT_iterator temp = *this;
				_node = decrease(_node);
				return(temp);
			}

			reference operator*() const
			{
				return _node->value;
			}

			
			pointer operator->() const
			{
				return &_node->value;
			}

			node_pointer get_node()
			{
				return _node;
			}

			node_pointer get_node() const 
			{
				return _node;
			}
			//------------------------ Comparison Operators -----------------// 
			bool operator==(const RBT_iterator &rhs) const 
			{
				return (this->_node == rhs._node);
			}

			bool operator!=(const RBT_iterator &rhs) const 
			{
				return (this->_node != rhs._node);
			}

		// ------------------------------------------------------------------------------------
		protected:
			// If the current node has a right child:
			// the iterator goes to the leftmost node in the right subtree.
			// If the current node does not have a right child and has a parent, 
			// the iterator goes up the tree until it finds a parent node whose 
			// left child is the current node
			// else, current node is root 
			node increase(node &nodePos) 
			{
				if (nodePos->right != 0) 
				{
					nodePos = nodePos->right;
					while (nodePos->left != 0)
						nodePos = nodePos->left;
				}
				else
				{
					node tmp = nodePos->parent;
					while (nodePos == tmp->right)
					{
						nodePos = tmp;
						tmp = tmp->parent;
					}
					if (nodePos->right != tmp)
						nodePos = tmp;
				}
				return (nodePos);
			}


			// Same logic as increase in the reverse way	
			node decrease(node &nodePos) 
			{
				node tmp;
				if (nodePos->left != 0) 
				{
					tmp = nodePos->left;
					while (tmp->right != 0)
						tmp = tmp->right;
				}
				else
				{
					tmp = nodePos->parent;
					while (nodePos == tmp->left)
					{
						nodePos = tmp;
						tmp = tmp->parent;
					}
				}
				return (tmp);
			}
	};
}
#endif