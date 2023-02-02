#ifndef MAP_HPP
# define MAP_HPP

// Officials libraries
#include <iostream>

// Personnal librairies
#include "./pair.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "newRBT.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"
//#include "./RedBlackTree.hpp"

namespace ft {
	/*--------------------------------------------------------
	1. 'KEY': Type of the key int he map (used to sort and organize elements in the map)
	2. 'T': Type of the value stored in the map.
	3. 'Compare': use default std::less<Key> (built-in comparison object)
		-> Compare two key using '<'
		-> Map will be ordered in ascending order.
	4. 'Alloc': Type of allocator object used to allocate memory. 
		-> by default here it is built-in allocator of std::. 
	NB: keys are 'const' (cannot be modified after insertion)
	--------------------------------------------------------*/
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<key_type, mapped_type>			value_type;
	 		typedef Compare									key_compare;
			typedef Alloc									allocator_type;
			
			// /!\ Not used to sort but only to compare elements 
			// in the tree and maintain the order.
			//class value_compare : public std::binary_function<value_type, value_type, bool>
			class value_compare : public std::less<value_type>
			{
				// Declaring 'map' as a friend of 'value_compare' class
				// 'map' has access to the private and protected members of 'value compare' class.
				friend class map<key_type, mapped_type, key_compare, allocator_type>;
				// Specified parameters to clearly indicate which specific version of map class
				// we are referring to.iterator(c) {}

				public:
					// Compares two pairs based on their fisrt element
					// Returns 'true' if first element of first pair is < firs element of second pair
					// Returns 'false' otherwise.
					bool operator() (const value_type& lhs, const value_type& rhs) const 
					{
						return comp(lhs.first, rhs.first);
					}

				protected:
					Compare comp;
					value_compare(Compare c): comp(c) { }
			};

			//-------------------------------------------------------

			public: 
				typedef typename ft::RedBlackTree< key_type, value_type, key_compare, allocator_type>	tree_type;
			// --- TO DO --- IN PROGRESS
				typedef typename tree_type::iterator													iterator;
				typedef typename tree_type::const_iterator												const_iterator;
				typedef typename tree_type::reverse_iterator											reverse_iterator;
				typedef typename tree_type::reverse_iterator											const_reverse_iterator;
				typedef typename tree_type::size_type													size_type;
				typedef typename allocator_type::difference_type										difference_type;
				typedef typename tree_type::reference													reference;
				typedef typename tree_type::const_reference												const_reference;
				typedef typename tree_type::pointer														pointer;
				typedef typename tree_type::const_pointer												const_pointer;
		
		protected:
			tree_type	RB_Tree;

		public:

		// CONSTRUCTORS 

		// Default constructor
		// Construct an empty map container object. 
		// Initialize the internal RB Tree.
		map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) 
		: RB_Tree(comp, alloc)
		{
			// Here need to initialize the Red black tree.
			std::cout<< "Default constructor called" << std::endl;
		}

		// Initializes the internal red-black tree data member 
		// with the passed comp and alloc arguments.
		// Uses the insert function to insert elements 
		// from the range [first, last) into the map.
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
		: RB_Tree(comp, alloc)
		{
			std::cout<< "Range constructor called" << std::endl;
			RB_Tree.insert(first, last);
		}

		// Copy constructor
		map (const map& rhs)
		{
			std::cout<< "Copy constructor called" << std::endl;
			clear();
			insert(rhs.begin(), rhs.end());
		}
		
		// DESTRUCTOR
		~map()
		{ 
			clear(); 
		}

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

		/*mapped_type& operator[](const key_type& key)
		{
			return (insert(ft::make_pair(key, mapped_type())).first)->second;
		}

		mapped_type& at(const key_type& key)
		{
			return (_tree.at(ft::make_pair(key, mapped_type())).first)->second;
		}

		const mapped_type& at(const key_type& key) const
		{
			return (_tree.at(ft::make_pair(key, mapped_type())).first)->second;

		}*/

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

		reverse_iterator rbegin() { return reverse_iterator(RB_Tree.end()); }
		
		const_reverse_iterator  rbegin() const { return const_reverse_iterator(RB_Tree.end()); }

		reverse_iterator rend() { return reverse_iterator(RB_Tree.begin()); }
		
		const_reverse_iterator rend() const { return const_reverse_iterator(RB_Tree.begin()); }
		

		//-------------------------------------------------------------
        //-------------- MODIFIERS  ------------------------------------
        //-------------------------------------------------------------
		void clear()
		{
			if (size())
				RB_Tree.clear();
		}

		//--- Inserts the given value into th map
		//--- Returns a pair.
		//--- 'iterator': pointing the the inserted element(or element htat prevented insertion).
		//--- 'bool': wether the insertion succeed or not.
		ft::pair<iterator, bool> insert( const_reference &value )
		{
			return RB_Tree.insert(value);
		}
		
		// DEBEUG 
		void	prinTree()
		{
			RB_Tree.printTree();
		}


		iterator insert( iterator pos, const value_type& value )
		{
			return RB_Tree.insert(pos, value);
		}

		template< class InputIterator >
		void insert(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			RB_Tree.insert(first, last);
		}

		/*void erase( iterator pos )
		{
			erase(pos->first);
		}

		void erase( iterator first, iterator last )
		{
			_tree.range_erase(first, last);
		}

		size_type erase( const Key& key )
		{
			return (_tree.erase_node(ft::make_pair(key, mapped_type())));
		}

		void swap( map& other )
		{
			_tree.swap_tree(other._tree);
		}*/

		// LOOKUP 

		/*size_type count( const Key& key ) const
		{
			return (_tree.count(ft::make_pair(key, mapped_type())));
		}

		iterator find( const Key& key )
		{
			return (_tree.find(ft::make_pair(key, mapped_type())));
		}

		const_iterator find( const Key& key ) const
		{	
			return (_tree.find(ft::make_pair(key, mapped_type())));
		}

		ft::pair<iterator,iterator> equal_range( const Key& key )
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
		{
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}*/
		
		iterator lower_bound( const key_type& key )
		{
			return (RB_Tree.lower_bound(key));
		}

		/*const_iterator lower_bound( const Key& key ) const
		{
			return (_tree.lower_bound(ft::make_pair(key, mapped_type())));
		}

		iterator upper_bound( const Key& key )
		{
			return (_tree.upper_bound(ft::make_pair(key, mapped_type())));
		}

		const_iterator upper_bound( const Key& key ) const
		{
			return (_tree.upper_bound(ft::make_pair(key, mapped_type())));
		}

		allocator_type get_allocator() const
		{
				return allocator_type();
		}*/

		//-------------------------------------------------------------
        //-------------- OBSERVERS  -------------------------------------
        //-------------------------------------------------------------
		key_compare key_comp() const
		{
			return key_compare();
		}

		// Returns a boolean value indicating wether 
		// the first argument is less than the second.
		value_compare value_comp() const
		{
			return value_compare(RB_Tree.key_comp());
		}
	};

	// NON MEMBERS FUNCTIONS 

	/*template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
	{
		typename map<Key, T, Compare, Alloc>::const_iterator it = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator it2 = rhs.begin();
		
		if (lhs.size() != rhs.size())
			return false;
		while (it != lhs.end())
		{
			if (*it != *it2)
				return false;
			it++;
			it2++;
		}
		return true;
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

	template< class Key, class T, class Compare, class Alloc >
	void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
	{
	return (lhs.swap(rhs));
	}*/
}

#endif