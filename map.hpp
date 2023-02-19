#ifndef MAP_HPP
# define MAP_HPP

// Officials libraries
#include <iostream>

// Personnal librairies
#include "./utils/pair.hpp"
#include "./utils/random_access_iterator.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/RedBlackTree.hpp"
#include "./utils/enable_if.hpp"
#include "./utils/is_integral.hpp"

namespace ft {
	/*------------------------------------------------------------------------------------
		(1) 'Key': Type of the key in the map (used to sort and organize elements in the map)
		(2) 'T': Type of the value stored in the map.
		(3) 'Compare': use default std::less<Key> (built-in comparison object)
			-> Compare two key using '<'
			-> Map will be ordered in ascending order.
		(4) 'Alloc': Type of allocator object used to allocate memory. 
			-> by default here it is built-in allocator of std:: 
		NB: keys are 'const' (cannot be modified after insertion)
	-------------------------------------------------------------------------------------*/
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
	 		typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			
			// /!\ Not used to sort but only to compare elements in the tree and maintain the order.
			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				// Declaring 'map' as a friend of 'value_compare' class
				// 'map' has access to the private and protected members of 'value compare' class.
				// Specified parameters to clearly indicate which specific version of map class
				// we are referring to.iterator(c) {}
				friend class map<key_type, mapped_type, key_compare, allocator_type>;

				public:
					// Compares two pairs based on their fisrt element
					// Returns 'true' if first element of first pair is < first element of second pair
					// Returns 'false' otherwise.
					bool operator() (const value_type& lhs, const value_type& rhs) const 
					{
						return comp(lhs.first, rhs.first);
					}
					bool operator()(const key_type& lhs, const value_type& rhs) const
					{ 
						return comp(lhs, rhs.first); 
					}
					bool operator()(const value_type& lhs, const key_type& rhs) const
					{ 
						return comp(lhs.first, rhs); 
					}

				protected:
					Compare comp;
					value_compare(Compare c): comp(c) { }
			};

			typedef typename ft::RedBlackTree< key_type, value_type, value_compare, allocator_type>	tree_type;
			//-- Define RBT type ------------------------------------------------------
			//-- `key_type`: Key
			//-- `value_type`: pair of key and value
			//-- `key_compare`: Compare object 
			//		--> used to compare the value of the string object
			//-- `allocator_type`: allocation de memoire pour un type pair


			//-- Define iterators ------------------------------------------------------
			typedef typename tree_type::iterator													iterator;
			typedef typename tree_type::const_iterator												const_iterator;
			typedef typename tree_type::reverse_iterator											reverse_iterator;
			typedef typename tree_type::const_reverse_iterator										const_reverse_iterator;	

			//-- Define other types ------------------------------------------------------
			typedef typename tree_type::size_type													size_type;
			typedef typename tree_type::difference_type												difference_type;
			typedef typename tree_type::reference													reference;
			typedef typename tree_type::const_reference												const_reference;
			typedef typename tree_type::pointer														pointer;
			typedef typename tree_type::const_pointer												const_pointer;

			// CONSTRUCTORS 

			// Default constructor
			// Construct an empty map container object. 
			// Initialize the internal RB Tree.
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
			: RB_Tree(value_compare(comp), alloc)
			{ }

			// Initializes the internal red-black tree data member 
			// with the passed comp and alloc arguments.
			// Uses the insert function to insert elements 
			// from the range [first, last) into the map.
			template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: RB_Tree(first, last, value_compare(comp), alloc)
			{
				RB_Tree.insert(first, last);
			}

			// Copy constructor
			map(const map<Key, T, Compare, allocator_type> &rhs)
			:RB_Tree(rhs.begin(), rhs.end(), value_compare(rhs.value_comp()), rhs.RB_Tree.get_allocator())
			{ 
			}

			// DESTRUCTOR
			//-- No need to destroy anything because all is destroyed in Red Black Tree
			~map()
			{ }

			map& operator= (const map& rhs)
			{	
				if (this == &rhs)
					return *this;
				clear();
				insert(rhs.begin(), rhs.end());
				return (*this);
			}

			/*-------------------------------------------------------*/
			//------- ELEMENT ACCESS 
			//----------------------------------------------------------
			//-- If key matches tjhe key of an element : returns a reference to its map value
			//-- Else, insert a new element with that key and default value
			mapped_type& operator[](const key_type& k)
			{
				return (RB_Tree.insert(ft::make_pair(k, mapped_type())).first)->second;
			}

			//-------------------------------------------------------------
        	//-------------- CAPACITY -------------------------------------
        	//-------------------------------------------------------------

			bool empty() const 
			{ 
				return RB_Tree.empty(); 
			}

			size_type size() const
			{
				return RB_Tree.size();
			}

			size_type max_size() const
			{
				return RB_Tree.max_size();
			}

			//-------------------------------------------------------------
        	//-------------- ITERATORS  ------------------------------------
        	//-------------------------------------------------------------

			iterator begin() { return RB_Tree.begin(); }

			const_iterator begin() const { return RB_Tree.begin(); }

			iterator end() { return RB_Tree.end(); }

			const_iterator end() const { return RB_Tree.end(); }

			reverse_iterator rbegin() { return reverse_iterator(RB_Tree.rbegin()); }

			const_reverse_iterator  rbegin() const { return const_reverse_iterator(RB_Tree.rbegin()); }

			reverse_iterator rend() { return reverse_iterator(RB_Tree.rend()); }

			const_reverse_iterator rend() const { return const_reverse_iterator(RB_Tree.rend()); }

			//-------------------------------------------------------------
        	//-------------- MODIFIERS  ------------------------------------
        	//-------------------------------------------------------------
			void clear()
			{
				if (size())
					RB_Tree.clear();
			}

			//--- Inserts the given value into the map
			//--- Returns a pair.
			//--- `iterator`: pointing the the inserted element(or element that prevented insertion).
			//--- `bool`: wether the insertion succeed or not.
			// ft::pair<iterator, bool> insert( const_reference &value )
			ft::pair<iterator, bool> insert( const value_type &value )
			{
				return RB_Tree.insert(value);
			}


			iterator insert( iterator pos, const value_type& value )
			{
				return RB_Tree.insert(pos, value);
			}

			template< class InputIterator >
			void insert(InputIterator first, InputIterator last)
			{
				RB_Tree.insert(first, last);
			}

			void erase( iterator position )
			{
				RB_Tree.erase(position);
			}

			void erase( iterator first, iterator last )
			{
				RB_Tree.erase(first, last);
			}

			size_type erase( const Key& key )
			{
				return RB_Tree.erase(key);
			}

			void swap( map& x )
			{
				RB_Tree.swap(x.RB_Tree);
			}

			// LOOKUP 

			size_type count( const Key& key ) const
			{
				return (RB_Tree.count(key));
			}

			iterator find( const Key& key )
			{
				return (RB_Tree.find(key));
			}

			const_iterator find( const Key& key ) const
			{	
				return (RB_Tree.find(key));
			}

        	//-- std::equal_range
        	//-- Returns a range containing all elements with the given key in the container.
        	//-- Returns a pair of iterators defining the wanted range :
        	//-- Firt iterator: is pointing to the first element that is not less than the key
        	//-- Second element: is pointing to the first element greater than key.
			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
				return (RB_Tree.equal_range(key));
			}

			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				return (RB_Tree.equal_range(key));
			}

			iterator lower_bound( const key_type& key )
			{
				return (RB_Tree.lower_bound(key));
			}

			const_iterator lower_bound( const Key& key ) const
			{
				return (RB_Tree.lower_bound(key));
			}

			iterator upper_bound( const Key& key )
			{
				return (RB_Tree.upper_bound(key));
			}

			const_iterator upper_bound( const Key& key ) const
			{
				return (RB_Tree.upper_bound(key));
			}

			allocator_type get_allocator() const
			{
					return allocator_type();
			}

			//-------------------------------------------------------------
        	//-------------- OBSERVERS  -------------------------------------
        	//-------------------------------------------------------------
			key_compare key_comp() const
			{
				return key_compare();
			}

			//-- Returns a boolean value 
			//	--> Indicate wether the first argument is less than the second.
			value_compare value_comp() const
			{
				return value_compare(RB_Tree.key_comp());
			}
			//-----------------------------------------------------------
        	//-------------- DEBEUG  ------------------------------------
        	//-----------------------------------------------------------

			//----- RELATIONAL OPERATORS
			template <class _Key, class _T, class _Compare, class _Allocator>
			friend
			bool
			operator==(const map<_Key, _T, _Compare, _Allocator>& lhs,
					   const map<_Key, _T, _Compare, _Allocator>& rhs);
		
			template <class _Key, class _T, class _Compare, class _Allocator>
			friend
			bool
			operator<(const map<_Key, _T, _Compare, _Allocator>& lhs,
			  const map<_Key, _T, _Compare, _Allocator>& rhs);

		private:
			void	prinTree()
			{
				RB_Tree.printTree();
			}
		
		protected:
			tree_type	RB_Tree;
	};

	// NON MEMBERS FUNCTIONS 

	//-- Swap 
	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
	{
		return (lhs.swap(rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		typename map<Key, T, Compare, Alloc>::const_iterator itBegin1 = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator itBegin2 = rhs.begin();
		
		if (lhs.size() != rhs.size())
			return false;
		while (itBegin1 != lhs.end())
		{
			if (*itBegin1 != *itBegin2)
				return (false);
			itBegin1++;
			itBegin2++;
		}
		return (true);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end() );
	}

	template< class Key, class T, class Compare, class Alloc > 
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs > rhs));
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(lhs < rhs) && lhs != rhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs < rhs));
	}
}
#endif