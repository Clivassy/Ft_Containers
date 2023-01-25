#ifndef RBT_ITERATOR_HPP
# define RBT_ITERATOR_HPP

#include "map.hpp"

namespace ft {

	// 'T': the type of the element stored in the tree
	// 'node': the type of the node in the tree
	// 'Compare'
	template<typename T, typename node, class Compare>
	class RBT_iterator
	{ 
		public:
			typedef T									value_type;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef value_type*							pointer;
			typedef value_type&							reference;
			typedef const value_type*					const_pointer;
			typedef const value_type& 					const_reference;
			typedef node								node_pointer;

		protected:
			node_pointer node;

		public:
			// CONSTRUCTORS 

			// Default constructor
			// Create an iterator object and initialize 'node' to NULL
			// Iterator will need to be assign to a valid node to be used.
			RBT_iterator() : node(NULL) {}

			// Creates an iterator object and initialize the node with 'ptr' value.
			// Iterator will now point on 'ptr' (specific node in the tree)
			RBT_iterator(node_pointer ptr) : node(ptr) {}

			// Copy constructor
			// Create new iterator intitialized with 'src' value.
			// /!\ both iterator will point to the same node in the tree.
			RBT_iterator(RBT_iterator const & src) : node(src.node) {}

			RBT_iterator & operator=(RBT_iterator const & rhs) 
			{
				if (this == &rhs)
					return (*this);
				node = rhs.node; 
				return *this;
			}

			operator map_iterator<const T, node, Compare>() const 
			{
				return RBT_iterator<const T, node, Compare>(node);
			}
			
			// DESTRUCTOR
			~RBT_iterator() {}
			

			// Post-increment operator
			RBT_iterator& operator++ (void) {
				// need to check if tree is empty ? 
				// If the current node has a right child:
				// the iterator goes to the leftmost node in the right subtree.
				if (node && node->right)
				{
					node = node->right;
					while (node->left)
						node = node->left;
				}
				// If the current node does not have a right child and has a parent, 
				// the iterator goes up the tree until it finds a parent node whose 
				// left child is the current node
				else if (node && node->parent)
				{
					node_pointer save = node;
					node_pointer tmp = node->parent;
					while (tmp && node == tmp->right)
					{
						if (tmp->parent == NULL)
						{
							node = save->parent;
							return *this;
						}
						node = tmp;
						tmp = tmp->parent;
					}
					node = tmp;
				}
				// else, current node is root 
				return *this;
			}

			RBT_iterator operator++ (int) 
			{
				RBT_iterator it(*this);
				operator++();
				return it;
			}
			
			RBT_iterator& operator-- (void) {decrease(); return *this;}
			RBT_iterator operator-- (int) {RBT_iterator it = *this; --(*this); return it;}

			reference operator*() const {return node->data;}
			pointer operator->() const {return &node->data;}

			node_pointer get_node() {return node;}
			node_pointer get_node() const {return node;}

			template<typename it2>
			bool operator==(const RBT_iterator<it2, node, Compare>& b) const {return node == b.get_node();}
			template<typename it2>
			bool operator!=(const RBT_iterator<it2, node, Compare>& b) const {return node != b.get_node();}

		private:
			void increase() 
			{
				if (node && node->right)
				{
					node = node->right;
					while (node->left && node->left != NULL)
						node = node->left;
				}
				else if (node && node->parent)
				{
					node_pointer temp = node;
					node_pointer tmp_parent = node->parent;
					while ( tmp_parent && node == tmp_parent->right) 
					{
						if (node->parent == NULL) 
						{
							node = temp->parent;
							return ;
						}
						node = tmp_parent;
						tmp_parent = tmp_parent->parent;
					}
					node = tmp_parent;
				}
			}

			void decrease() 
			{
				if (node && _node->left)
				{
					node = node->left;
					while (node->right && node->right != NULL)
						node = node->right;
				}
				else if (node && node->parent)
				{
					node_pointer temp = node;
					node_pointer tmp_parent = node->parent;
					while ( tmp_parent && node == tmp_parent->left) 
					{
						if (node->parent == NULL) 
						{
							node = temp;
							break;
						}
						node = tmp_parent;
						tmp_parent = tmp_parent->parent;
					}
					node = tmp_parent;
				}
			}
	};

}
#endif