#ifndef SET_HPP
#define SET_HPP

#include "./map.hpp"
#include "./utils/random_access_iterator.hpp"
#include "./utils/reverse_iterator.hpp"
#include "./utils/RedBlackTree.hpp"
#include "./utils/enable_if.hpp"
#include "./utils/is_integral.hpp"

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
        typedef typename tree_type::const_iterator                  iterator;
        typedef typename tree_type::const_iterator                  const_iterator;
        typedef typename tree_type::const_reverse_iterator          reverse_iterator;
        typedef typename tree_type::const_reverse_iterator          const_reverse_iterator;


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
        :  RB_Tree(x.begin(), x.end(), x.value_comp(), x.RB_Tree.get_allocator())
        {

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

		iterator begin() { return RB_Tree.begin(); }
		const_iterator begin() const { return RB_Tree.begin(); }
		iterator end() { return RB_Tree.end(); }
		const_iterator end() const { return RB_Tree.end(); }
		reverse_iterator rbegin() { return reverse_iterator(RB_Tree.rbegin()); }
		const_reverse_iterator  rbegin() const { return const_reverse_iterator(RB_Tree.rbegin()); }
		reverse_iterator rend() { return reverse_iterator(RB_Tree.rend()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(RB_Tree.rend()); }

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

        pair<iterator,bool> insert(const value_type& x)
        { 
            return RB_Tree.insert(x);
        }
        
	    iterator insert(iterator position, const value_type& x)
	    { 
            (void)position;
            insert(x);
			iterator Found = begin();
            while( begin() != end())
            {
                if (*Found == x)
                    break;
                Found++;
            }
			return (Found);
        }

        template <class InputIterator>
        void insert(InputIterator first, InputIterator last)
        {
           RB_Tree.insert(first, last);
        }

        size_type erase(const value_type & x)
        { 
            return RB_Tree.erase(x);
        }

        void erase(iterator position) 
        { 
            const value_type &found = *position;
            RB_Tree.erase(found);
        }

        void erase(iterator first, iterator last)
        { 
            if (first == begin() && last == end())
			{
                this->clear();
                return;
			}
            else
            {
                while (first != last)
                {
                    erase(*first++);
                }
            }
            return;
        }

        void swap(set<Key,Compare,Allocator>& x)
        { 
            RB_Tree.swap(x.RB_Tree);
        }

		void clear()
		{
			if (size())
			    RB_Tree.clear();
		}

        //--------------------------------------------------
	    //-- OBSERVERS
        key_compare key_comp() const
        { 
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare(RB_Tree.key_comp());
        }

        // set operations:

        iterator find(const key_type& x)
        { 
            return (RB_Tree.find(x));
        }

        const_iterator find(const key_type& x) const
        { 
            return (RB_Tree.find(x));
        }

        size_type count(const key_type& x) const
        { 
            return (RB_Tree.count(x));
        }

        iterator lower_bound(const key_type& x)
        { 
            return (RB_Tree.lower_bound(x));
        }
        
        const_iterator lower_bound(const key_type& x) const
        { 
            return (RB_Tree.lower_bound(x));
        }

        iterator upper_bound(const key_type& x)
        { 
            return (RB_Tree.upper_bound(x));
        }

        const_iterator upper_bound(const key_type& x) const
        { 
            return (RB_Tree.upper_bound(x));
        }

        pair<iterator,iterator> equal_range(const key_type& x)
        { 
            return (RB_Tree.equal_range(x));
        }
        
        pair<const_iterator, const_iterator> equal_range(const key_type& x) const
        { 
            return (RB_Tree.equal_range(x));
        }

    protected:
		tree_type	RB_Tree;
    
	template <class _T, class _Compare, class _Allocator>
	friend
	bool
	operator==(const set<_T, _Compare, _Allocator>& lhs,
			   const set<_T, _Compare, _Allocator>& rhs);

	template <class _T, class _Compare, class _Allocator>
	friend
	bool
	operator<(const set<_T, _Compare, _Allocator>& lhs,
			  const set<_T, _Compare, _Allocator>& rhs);

    };
    
    template <class Key, class Compare, class Allocator>
    bool operator==(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { 
        return (x.RB_Tree == y.RB_Tree);
    }

    template <class Key, class Compare, class Allocator>
    bool operator< (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { 
        return (x.RB_Tree < y.RB_Tree);
    }
    
    template <class Key, class Compare, class Allocator>
    bool operator!=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { 
        return not (x == y);
    }

    template <class Key, class Compare, class Allocator>
    bool operator> (const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { 
        return (y < x);
    }
    
    template <class Key, class Compare, class Allocator>
    bool operator>=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { 
        return not (x < y);
    }
    
    template <class Key, class Compare, class Allocator>
    bool operator<=(const set<Key,Compare,Allocator>& x, const set<Key,Compare,Allocator>& y)
    { 
        return not (y < x);
    }
    
    // specialized algorithms:
    template <class Key, class Compare, class Allocator>
    void swap(set<Key,Compare,Allocator>& x, set<Key,Compare,Allocator>& y)
    { 
        x.swap(y);
    }
}
#endif