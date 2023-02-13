#ifndef SET_HPP
#define SET_HPP

#include "../02_map/map.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../02_map/RedBlackTree.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/is_integral.hpp"

namespace ft {
    
    template <class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
    class set {
    
    public:
        //-- Types 
        typedef Key         key_type;
        typedef Key         value_type;
        typedef Compare     key_compare;
        typedef Compare     value_compare;
        typedef Allocator   allocator_type;

        typedef typename ft::RedBlackTree< key_type, value_type, key_compare, allocator_type>	tree_type;

        typedef typename tree_type::reference reference;
        typedef typename tree_type::const_reference const_reference;

        //-- Iterators
        typedef typename tree_type::iterator                    iterator;
        typedef typename tree_type::const_iterator              const_iterator;
        typedef typename tree_type::reverse_iterator            reverse_iterator;
        typedef typename tree_type::const_reverse_iterator      const_reverse_iterator;


        typedef typename tree_type::size_type                   size_type;
        typedef typename tree_type::difference_type             difference_type;
        typedef typename tree_type::pointer                     pointer;
        typedef typename tree_type::const_pointer               const_pointer;

        //--------------------------------------------------
	    //-- CONSTRUCTORS 
        explicit set(const Compare& comp = Compare(),const Allocator& alloc = Allocator()) : RB_Tree(comp, alloc)
        {}

        template <class InputIterator>
        set(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
        : RB_Tree(comp, alloc)
        {
            RB_Tree.insert(first, last);
        }

        set(const set<Key,Compare,Allocator>& x)
        {
            clear();
	    	RB_Tree.insert(x.begin(), x.end());
        }

        //--------------------------------------------------
	    //-- DESTRUCTOR 
        ~set()
        {}

        set<Key,Compare,Allocator>& operator= (const set<Key,Compare,Allocator>& x)
        { 
			if (this == &x)
				return *this;
			clear();
			insert(x.begin(), x.end());
			return (*this);
        }

        allocator_type get_allocator() const
        { 
            return allocator_type();
        }

        //--------------------------------------------------
	    //-- ITERATORS 

	    iterator begin() { return RB_Tree.begin();} 
	    const_iterator begin() const { return RB_Tree.begin(); }
	    iterator end() { return RB_Tree.end(); }
	    const_iterator end() const { return RB_Tree.end(); }
	    reverse_iterator rbegin() { return reverse_iterator(RB_Tree.end()); }
	    const_reverse_iterator  rbegin() const { return const_reverse_iterator(RB_Tree.end()); }
	    reverse_iterator rend() { return reverse_iterator(RB_Tree.begin()); }
	    const_reverse_iterator rend() const { return const_reverse_iterator(RB_Tree.begin()); }

        //--------------------------------------------------
	    //-- CAPACITY 
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

        //--------------------------------------------------
	    //-- MODIFIERS 

        pair<iterator,bool> insert(const value_type& x);
        iterator insert(iterator position, const value_type& x)
        { 
            return RB_Tree.insert(position, x);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
            RB_Tree.insert(first, last);
        }

        void erase(iterator position) 
        { 
            
        }

        size_type erase(const key_type& x)
        { }

        void erase(iterator first, iterator last)
        { }

        void swap(set<Key,Compare,Allocator>&)
        { }

		void clear()
		{
			if (size())
			    RB_Tree.clear();
		}

        //--------------------------------------------------
	    //-- OBSERVERS

       /* key_compare key_comp() const
        { 
            return key_compare();
        }

        value_compare value_comp() const;
        {
            value_compare(RB_Tree.key_comp());
        }

        // set operations:

        iterator find(const key_type& x) const
        { }

        size_type count(const key_type& x) const
        { }

        iterator lower_bound(const key_type& x) const
        { }

        iterator upper_bound(const key_type& x) const
        { }

        pair<iterator,iterator> equal_range(const key_type& x) const
        { }*/

    protected:
		tree_type	RB_Tree;
    };
    
   /* template <class Key, class Compare, class Allocator>
    bool operator==(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { }
    
    template <class Key, class Compare, class Allocator>
    bool operator< (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { }
    
    template <class Key, class Compare, class Allocator>
    bool operator!=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { }
    
    template <class Key, class Compare, class Allocator>
    bool operator> (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { }
    
    template <class Key, class Compare, class Allocator>
    bool operator>=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { }
    
    template <class Key, class Compare, class Allocator>
    bool operator<=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { }
    
    // specialized algorithms:
    template <class Key, class Compare, class Allocator>
    void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y)
    { }*/
}
#endif