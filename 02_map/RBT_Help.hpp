#include <iostream>
//#include "map_iterator.hpp"

namespace ft
{

	template <typename T>
	void swap_function(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <typename T, typename K, class Compare, class Alloc>
	class RedBlackTree 
	{
		private:
			typedef T value_type;

			
			struct Node 
			{
			  value_type		data;
			  bool				color;//  black = 0  | red = 1
			  Node				*left;
			  Node				*right;
			  Node				*parent;

			  //constructor for each node
			  Node(value_type const &data = value_type()) : data(data), left(NULL), right(NULL), parent(NULL){}
			};
  
			typedef size_t				size_type;
			typedef K					key_type;
			typedef Compare				compare_type;
			typedef Alloc				allocator_type;
			typedef value_type*			pointer;
			typedef Node*				node_pointer;
			typedef const Node*			const_node_pointer;
			typedef value_type&			reference;
			typedef const value_type&	const_reference;
			typedef typename allocator_type::template rebind<Node>::other node_allocator;

			node_pointer	_root;
			node_pointer	_end;
			size_type		_size;
			node_allocator	_node_alloc;
			compare_type	_comp;

		public:

			typedef typename ft::map_iterator<value_type, node_pointer, compare_type>				iterator;
			typedef typename ft::map_iterator<const value_type, node_pointer, compare_type>		const_iterator;
		  
		  
			RedBlackTree(const compare_type& comp = compare_type(), const node_allocator& node_alloc = node_allocator())
			{
				_node_alloc = node_alloc;
				_end = create_node();
				_root = _end;
				_size = 0;
				_comp = comp;
			}
		
			~RedBlackTree()
			{
				if (_size)
					clearAll();
				destroy_node(_root);
			}

			node_pointer	create_node(const_reference value = value_type())
			{
				node_pointer node = _node_alloc.allocate(1);

				_node_alloc.construct(node, Node(value));
				node->color = 1; 
				node->left = NULL;
				node->right = NULL;
				node->parent = NULL;
				return node;
			}

			bool	empty() const
			{
				return _size == 0;
			}

			size_type	size() const
			{
				return _size;
			}

			size_type	max_size() const
			{
				return _node_alloc.max_size();
			}

			iterator	begin()
			{
				return minimum();
			}

			const_iterator	begin() const
			{
				return minimum();
			}

			iterator	end()
			{
				return iterator(_end);
			}

			const_iterator	end() const
			{
				return const_iterator(_end);
			}

			compare_type	comp() const
			{
				return _comp;
			}

			
			/*************************************************/
			/*                  Operations                   */
			/*************************************************/

			iterator	find(const_reference value)
			{
				node_pointer pos = tree_search_helper(value);
				if (!pos)
					return (end());
				return iterator(pos);
			}

			const_iterator	find(const_reference value) const
			{
				node_pointer pos = tree_search_helper(value);
				if (!pos)
					return (end());
				return const_iterator(pos);
			}

			size_type	count(const_reference value) const
			{
				node_pointer pos = tree_search_helper(value);
				if(!pos)
					return 0;
				return 1;
			}

			iterator lower_bound(const_reference value)
			{
				iterator it = begin();
				iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (!(_comp(it->first, value.first)))
						return it;
				}
				return it;
			}

			const_iterator lower_bound(const_reference value) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (!(_comp(it->first, value.first)))
						return it;
				}
				return it;
			}

			iterator upper_bound(const_reference value)
			{
				iterator it = begin();
				iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (_comp(value.first, it->first))
						return it;
				}
				return it;
			}

			const_iterator upper_bound(const_reference value) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (_comp(value.first, it->first))
						return it;
				}
				return it;
			}
			
			/*************************************************/
			/*                  Modifiers                    */
			/*************************************************/
			
			ft::pair<iterator, bool>	insert(const_reference value)
			{
				node_pointer node = create_node(value);
				node_pointer tmp = _root;
				node_pointer parent = NULL;

				if (empty())
					return (insert_empty_node(node));
				while (tmp != NULL && tmp != _end)
				{
					parent = tmp;
					if (_comp(value.first, tmp->data.first))
					{
						tmp = tmp->left;
					}
					else if (_comp(tmp->data.first, value.first))
					{
						tmp = tmp->right;
					}
					else
					{
						destroy_node(node);
						update_end();
						return (ft::make_pair(iterator(tmp), false));
					}
				}
				node->parent = parent;
				if (_comp(value.first, parent->data.first))
				{
					parent->left = node;
				}
				else
				{
					parent->right = node;
				}
				node_insert_fix(node);
				update_end();
				_size++;
				return (ft::make_pair(iterator(node), true));
			}


			ft::pair<iterator, bool>	at(const_reference value)
			{
				node_pointer tmp = _root;
				node_pointer parent = NULL;

				if (empty())
					throw std::out_of_range("ft::map::at");
				while (tmp != NULL && tmp != _end)
				{
					parent = tmp;
					if (_comp(value.first, tmp->data.first))
					{
						tmp = tmp->left;
					}
					else if (_comp(tmp->data.first, value.first))
					{
						tmp = tmp->right;
					}
					else
					{

						return (ft::make_pair(iterator(tmp), false));
					}
				}
				throw std::out_of_range("ft::map::at");
			}

			const ft::pair<iterator, bool>	at(const_reference value) const
			{
				node_pointer tmp = _root;
				node_pointer parent = NULL;

				if (empty())
					throw std::out_of_range("ft::map::at");
				while (tmp != NULL && tmp != _end)
				{
					parent = tmp;
					if (_comp(value.first, tmp->data.first))
					{
						tmp = tmp->left;
					}
					else if (_comp(tmp->data.first, value.first))
					{
						tmp = tmp->right;
					}
					else
					{

						return (ft::make_pair(iterator(tmp), false));
					}
				}
				throw std::out_of_range("ft::map::at");
			}

			void clear(node_pointer node)
			{
				if (!node || node == _end)
					return;
				clear(node->left);
				clear(node->right);
				destroy_node(node);
			}
			
			void clearAll()
			{
				clear(_root);
				_root = _end;
				_size = 0;
			}

			void range_erase(iterator first, iterator last)
			{
				size_type i = 0;

				node_pointer tmp = first.get_node();
				if (first == begin() && last == end())
				{
					clearAll();
					return;
				}
				for (iterator it = first; it != last; it++)
					i++;
				while (i)
				{
					tmp = deleteNode(tmp);
					i--;
				}
			}

			size_type erase_node(value_type value)
			{
				node_pointer node;
				
				if (empty())
					return 0;
				node = tree_search_helper(value);
				if (!node)
					return 0;
				if (_size == 1)
				{
					clearAll();
					return 1;
				}
				deleteNode(node);
				return 1;
			}

			node_pointer deleteNode(node_pointer node)
			{
				node_pointer nextNode = replace(node);
				node_pointer parent = node->parent;
				node_pointer sibling = GetSibling(node);
				node_pointer ret = successor(node);
				
				if (nextNode == NULL)
				{
					if (node == _root)
						_root = NULL;
					else
					{
						if (nextNode == NULL || nextNode->color == 0)
							fixDoubleBlack(node);
						else if (sibling != NULL)
							sibling->color = 1;
						if (isonLeft(node))
							parent->left = NULL;
						else
							parent->right = NULL;
					}
					destroy_node(node);
					_size--;
					update_end();
					return ret;
				}
				if (node->left == NULL || node->right == NULL)
				{
					if (node == _root)
					{
						change_value(node, nextNode);
						destroy_node(nextNode);
						//node->data = nextNode->data;
						node->left = NULL;
						node->right = NULL;
					}
					else
					{
						if (isonLeft(node))
						{
							parent->left = nextNode;
						}
						else
						{
							parent->right = nextNode;
						}
						destroy_node(node);
						nextNode->parent = parent;
						if (nextNode == NULL || nextNode->color == 0)
							fixDoubleBlack(nextNode);
						else
							nextNode->color = 0;
					}
					_size--;
					update_end();
					return ret;
				}
				swap_value(nextNode, node);
				deleteNode(nextNode);
				return node;
			}

			void fixDoubleBlack(node_pointer node)
			{
				node_pointer sibling = GetSibling(node);
				node_pointer parent = node->parent;
				
				if (node == _root)
					return;
				if (sibling == NULL)
					fixDoubleBlack(parent);
				else
				{
					if (sibling->color == 1)
					{
						parent->color = 1;
						sibling->color = 0;
						if (isonLeft(sibling))
							rotateRight(parent);
						else
							rotateLeft(parent);
						fixDoubleBlack(node);
					}
					else
					{
						//if at least one child is red
						if ((sibling->left && sibling->left->color == 1) || (sibling->right && sibling->right->color == 1))
						{
							if (sibling->left && sibling->left->color == 1)
							{
								if (isonLeft(sibling))
								{
									sibling->left->color = sibling->color;
									sibling->color = parent->color;
									rotateRight(parent);
								}
								else
								{
									sibling->left->color = parent->color;
									rotateRight(sibling);
									rotateLeft(parent);
								}
							}
							else
							
								if (isonLeft(sibling))
								{
									sibling->right->color = parent->color;
									rotateLeft(sibling);
									rotateRight(parent);
								}
								else
								{
									sibling->right->color = sibling->color;
									sibling->color= parent->color;
									rotateLeft(parent);
								}
						}
						else
						{
							sibling->color = 1;
							if (parent->color == 0)
								fixDoubleBlack(parent);
							else
								parent->color = 0;
						}
					}
				}
			}


			bool isonLeft(node_pointer node)
			{
				return node == node->parent->left;
			}

			node_pointer GetSibling(node_pointer node)
			{
				if (node->parent == NULL)
					return NULL;
				if (isonLeft(node))
					return node->parent->right;
				else
					return node->parent->left;
			}

			/*************************************************/
			/*                    Helpers                    */
			/*************************************************/

			void 	change_value(node_pointer a, node_pointer b)
			{
				key_type* k1;
				key_type* k2;

				k1 = const_cast<key_type*>(&a->data.first);
				k2 = const_cast<key_type*>(&b->data.first);
				
				*k1 = *k2;
				a->data.second = b->data.second;
			}


			void swap_node(node_pointer *a, node_pointer *b)
			{
				node_pointer tmp = a;
				a = b;
				b = tmp;
			}

			void swap_tree(RedBlackTree &a)
			{
				ft::swap_function(_root, a._root);
				ft::swap_function(_end, a._end);
				ft::swap_function(_size, a._size);
				ft::swap_function(_node_alloc, a._node_alloc);
				ft::swap_function(_comp, a._comp);
			}

			//function to find in the tree
			node_pointer	tree_search_helper(const_reference to_find) const
			{
				node_pointer tmp = _root;

				while (tmp != NULL && tmp != _end)
				{
					if (_comp(tmp->data.first, to_find.first))
						tmp = tmp->right;
					else if (_comp(to_find.first, tmp->data.first))
						tmp = tmp->left;
					else
						return tmp;
				}
				return NULL;
			}

			//insert empty node
			ft::pair<iterator, bool>	insert_empty_node(node_pointer node)
			{
				_root = node;
				_root->left = NULL;
				_root->right = _end;
				_end->parent = _root;
				_root->color = 0; //black
				_size++;
				return ft::make_pair(iterator(_root), true);
			}

			// For balancing the tree after insertion
			void	node_insert_fix(node_pointer node)
			{
				while((node != _root) && (node->color != 0) && node->parent && node->parent->color == 1)
				{
					if(node->parent == node->parent->parent->left)
					{
						if (node->parent->parent->right != NULL && node->parent->parent->right->color == 1)
						{
							node->parent->parent->color = 1;
							node->parent->color = 0;
							node->parent->parent->right->color = 0;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								rotateLeft(node);
							}
						int tmpColor = node->parent->color;
						node->parent->color = node->parent->parent->color;
						node->parent->parent->color = tmpColor;
						//node = node->parent;
						rotateRight(node->parent->parent);
						}
					}
					else
					{
						if ((node->parent->parent->left != NULL) && (node->parent->parent->left->color == 1))
						{
							node->parent->parent->color = 1;
							node->parent->color = 0;
							node->parent->parent->left->color = 0;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								rotateRight(node);
							}
							int tmpColor = node->parent->color;
							node->parent->color = node->parent->parent->color;
							node->parent->parent->color = tmpColor;
							//node = node->parent;
							rotateLeft(node->parent->parent);
						}
					}
				}
				_root->color = 0;
			}

			node_pointer minimum() const
			{
				node_pointer min = _root;
				while (min && min->left != NULL) 
				{
					min = min->left;
				}
				return min;
			}

			node_pointer maximum() const
			{
				node_pointer max = _root;
				while (max && max->right != NULL && max->right != _end) 
				{
					max = max->right;
				}
				return max;
			}


			void destroy_node(node_pointer node)
			{
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
			}

			void update_end()
			{
				node_pointer max = maximum();
				max->right = _end;
				_end->parent = max;
				_end->left = NULL;
				_end->right = NULL;
				_end->color = 0;
			}

			void rotateLeft(node_pointer node) 
			{
				node_pointer parent = node->right;

				if (node == _root)
					_root = parent;
				if (node->parent != NULL)
				{
					if (node == node->parent->left)
						node->parent->left = parent;
					else 
						node->parent->right = parent;
				}
				parent->parent = node->parent;
				node->parent = parent;
				node->right = parent->left;
				if (parent->left != NULL) 
					parent->left->parent = node;
				parent->left = node;
			}

			void rotateRight(node_pointer node) 
			{
				node_pointer parent = node->left;

				if (node == _root)
					_root = parent;
				if (node->parent != NULL)
				{
					if (node == node->parent->right)
						node->parent->right = parent;
					else 
						node->parent->left = parent;
				}
				parent->parent = node->parent;
				node->parent = parent;
				node->left = parent->right;
				if (parent->right != NULL) 
					parent->right->parent = node;
				parent->right = node;
			}

			node_pointer successor(node_pointer node) 
			{
				if (node->right != NULL) 
				{
					node = node->right;
					while(node->left != NULL)
						node = node->left;
					return node;
				}
				node_pointer parent = node->parent;
				while (parent != NULL && parent != _end && node == parent->right) 
				{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}

			node_pointer predecessor(node_pointer node) 
			{
				if (node->left != NULL && node->left != _end) 
				{
					return maximum();
				}

				node_pointer child = node->parent;
				while (child != NULL && child != _end && node == child->left) 
				{
					node = child;
					child = child->parent;
				}

				return child;
			}

			node_pointer	replace(node_pointer node)
			{
				if (node->left != NULL && node->right != NULL && node->right != _end)
					return successor(node);
				if (!node->left && !node->right)
					return NULL;
				if (node->left != NULL)
					return node->left;
				return node->right;
			}

			void swap_value(node_pointer a,node_pointer b)
			{
				key_type tmp;
				key_type *keya = const_cast<key_type *>(&a->data.first);
				key_type *keyb = const_cast<key_type *>(&b->data.first);
				value_type	temp;

				tmp = *keya;
				*keya = *keyb;
				*keyb = tmp;

				temp.second= a->data.second;
				a->data.second = b->data.second;
				b->data.second = temp.second;

			}
	};
};
