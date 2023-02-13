#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <stdint.h>
# include <iostream>
# include <stdlib.h>

# include "./pair.hpp"
# include "../utils/is_integral.hpp"
#include "../utils/testeur.hpp"

#include "RBT_iterator.hpp"
# include "../utils/reverse_iterator.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"

//--------------------------------------------------
#define BLACK 0
#define RED 1

//---------------------------------------------------

namespace ft {
    template <typename Key, typename Val = Key , class Compare = std::less<Key>, class Allocator = std::allocator<Val> >
    class RedBlackTree
    {
        private:
            template <typename T>
            struct Node 
            {
                T value;
                Node *left;
                Node *right;
                Node *parent;
                bool color;
                Node(): left(0), right(0), parent(0), color(RED){ }
                Node(const T &data) : value(data), left(0), right(0), parent(0), color(RED){ }
            };

            //-- Create a new type of allocator that is bound to the 'Node' type and uses the same 
            //   memory ressource as the original 'allocator_type'.
            typedef typename Allocator::template rebind<Node<Val> >::other   node_allocator;

        public:
        //-- NB: Need all types used in map since map is contructed on this Red Black Tree
        	typedef Key					                                    key_type;
            typedef Compare											        key_compare;
            typedef Val												        value_type;
            typedef Val*			                                        pointer;
            typedef const value_type *								        const_pointer;
            typedef value_type &									        reference;
	        typedef const value_type &								        const_reference;    
            typedef size_t				                                    size_type;
			typedef Allocator				                                allocator_type;
			typedef const Node<Val>*			                            const_node_pointer;
            typedef std::ptrdiff_t									        difference_type;

        protected:
            typedef Node<Val>*  node;

            node            _root;
	        size_type		_size;
            Compare         _compare;
	        node_allocator	_node_alloc;
        
        public:
            //-- Define iterators
            typedef ft::RBT_iterator<Val, node, Compare>                iterator;
            typedef ft::RBT_iterator<const Val, node, Compare>          const_iterator;
            typedef ft::reverse_Iterator<iterator>			            reverse_iterator;
	        typedef ft::reverse_Iterator<const_iterator>	            const_reverse_iterator;

            //-- RED BLACK TREE CONSTRUCTORS
            //--------------------------------

            //-- Defaut constructor
            RedBlackTree(const Compare& comp, const node_allocator& alloc) 
            : _compare(comp), _node_alloc(alloc)
            {
                _size = 0;
                _root = _node_alloc.allocate(1);
                _node_alloc.construct(_root, Node<Val>());
                _root->parent = 0;
                _root->right = _root;
                _root->left = _root;
            }

            //-- Range constructor 
            template <class InputIterator>
            RedBlackTree(InputIterator first, InputIterator last,
            const Compare& comp, const node_allocator& alloc) 
            : _compare(comp), _node_alloc(alloc)
            {
                _size = 0;
                _root = _node_alloc.allocate(1);
                _node_alloc.construct(_root, Node<Val>());
                _root->parent = 0;
                _root->right = _root;
                _root->left = _root;
                insert(first, last);
            }
	        
            RedBlackTree& operator= (const RedBlackTree& rhs)
		    {	
		    	if (this == &rhs)
		    		return *this;
		    	clear();
		    	insert(rhs.begin(), rhs.end());
		    	return (*this);
		    }

            ~RedBlackTree()
            {
                clear();
        		_node_alloc.destroy(_root);
		        _node_alloc.deallocate(_root, 1);
            } 

        //-- RED BLACK TREE OPERATIONS
        //--------------------------------

        //-- RotateLeft
        void rotateLeft(node current)
        {
            node newParent = current->right;
		    current->right = newParent->left;
		    if (newParent->left != 0)
		    	newParent->left->parent = current;
		    newParent->parent = current->parent;
		    if (current->parent == 0 or current->parent == _root)
		    	_root->parent = newParent;
		    else if (current == current->parent->left)
		    	current->parent->left = newParent;
		    else
		    	current->parent->right = newParent;
		    newParent->left = current;
		    current->parent = newParent;
        }

        //-- Rotate Right
        void rotateRight(node current)
	    {
	    	node newParent = current->left;
	    	current->left = newParent->right;
	    	if (newParent->right != 0)
	    		newParent->right->parent = current;
	    	newParent->parent = current->parent;
	    	if (current->parent == 0 or current->parent == _root)
	    		_root->parent = newParent;
	    	else if (current == current->parent->right)
	    		current->parent->right = newParent;
	    	else
	    		current->parent->left = newParent;
	    	newParent->right = current;
	    	current->parent = newParent;
	    }
	    
        void    checkInsertionNode(node newNode)
        {
            node ptr;
            while (newNode->parent->color == RED)
            {
                if (newNode->parent == newNode->parent->parent->right) 
                {
                    ptr = newNode->parent->parent->left;
                    if (ptr != 0 and ptr != _root and ptr->color == RED)
                    {
                        ptr->color = BLACK;
                        newNode->parent->color = BLACK;
                        newNode->parent->parent->color = RED;
                        newNode = newNode->parent->parent;
                    }
                    else
                    {
                        if (newNode == newNode->parent->left) 
                        {
                            newNode = newNode->parent;
                            rotateRight(newNode);
                        }
                        newNode->parent->color = BLACK;
                        newNode->parent->parent->color = RED;
                        rotateLeft(newNode->parent->parent);
                    }
                }
                else 
                {
                    ptr = newNode->parent->parent->right;
                    if (ptr != 0 and ptr != _root and ptr->color == RED)
                    { 
                        ptr->color = BLACK;
                        newNode->parent->color = BLACK;
                        newNode->parent->parent->color = RED;
                        newNode = newNode->parent->parent;
                    }
                    else 
                    {
                        if (newNode == newNode->parent->right) 
                        {
                            newNode = newNode->parent;
                            rotateLeft(newNode);
                        }
                        newNode->parent->color = BLACK;
                        newNode->parent->parent->color = RED;
                        rotateRight(newNode->parent->parent);
                    }
                }
                if (newNode == _root->parent) 
                    break;
            }
        _root->parent->color = BLACK;
        }

        void    checkNodeDeletion(node x)
        {
            node s;
	        while (x != 0 and x != _root and x->parent != 0 and x->color == BLACK)
	        {
	        	if (x == x->parent->left)
	        	{
	        		s = x->parent->right;
	        		if (s->color == RED)
	        		{
	        			s->color = BLACK;
	        			x->parent->color = RED;
	        			rotateLeft(x->parent);
	        			s = x->parent->right;
	        		}
	        		if (s->left->color == BLACK and s->right->color == BLACK)
	        		{
	        			s->color = RED;
	        			x = x->parent;
	        		}
	        		else
	        		{
	        			if (s->right->color == BLACK)
	        			{
	        				s->left->color = BLACK;
	        				s->color = RED;
	        				rotateRight(s);
	        				s = x->parent->right;
	        			}
                        s->color = x->parent->color;
	        			x->parent->color = BLACK;
	        			s->right->color = BLACK;
	        			rotateLeft(x->parent);
	        			x = _root->parent;
	        		}
	        	}
	        	else if (x == x->parent->right)
	        	{
	        		s = x->parent->left;
	        		if (s->color == RED)
	        		{
	        			s->color = BLACK;
	        			x->parent->color = RED;
	        			rotateRight(x->parent);
	        			s = x->parent->left;
                        break;
	        		}
	        		if (s->left->color == BLACK and s->right->color == BLACK)
	        		{
	        			s->color = RED;
	        			x = x->parent;
                        break;
	        		}
                    else
	        		{
	        			if (s->left->color == BLACK)
	        			{
	        				s->right->color = BLACK;
	        				s->color = RED;
	        				rotateLeft(s);
	        				s = x->parent->left;
                            break;
	        			}
                        s->color = x->parent->color;
	        			x->parent->color = BLACK;
	        			s->left->color = BLACK;
	        			rotateRight(x->parent);
	        			x = _root->parent;
	        		}
	        	}
	        if (x)
	        	x->color = BLACK;
	        if (_size == 0)
	        	clear();
            }
        }
        
        void remplaceSubtrees(node oldNode, node newNode)
	    {
	    	if (oldNode->parent == 0)
	    		_root->parent = newNode;
	    	else if (oldNode == oldNode->parent->left)
	    		oldNode->parent->left = newNode;
	    	else
	    		oldNode->parent->right = newNode;
	    	if (newNode != 0)
	    		newNode->parent = oldNode->parent;
	    }

        //----------------------------------------------
        //------ ITERATORS --- From RBT_Iterators
        //----------------------------------------------
	    iterator begin()
	    { 
            return iterator(_root->right); 
        }

	    const_iterator begin()const
	    { 
            return const_iterator(_root->right); 
        }

	    iterator end()
	    { 
            return iterator(_root); 
        }

	    const_iterator end() const 
        { 
            return const_iterator(_root); 
        }

	    reverse_iterator rbegin()
	    { 
            return reverse_iterator(end()); 
        }

	    const_reverse_iterator rbegin() const
	    { 
            return const_reverse_iterator(end()); 
        }

	    reverse_iterator rend()
        { 
            return reverse_iterator(begin()); 
        }

	    const_reverse_iterator rend() const
        { 
            return const_reverse_iterator(begin()); 
        }
        
        //-------------------------------------------------------------
        //-------------- CAPACITY -------------------------------------
        //-------------------------------------------------------------
        //-- Returns `true` if map is empty.
        //-- Returns `false` otherwise.
        bool empty () const{
            return _size == 0;
        }

        //-- Returns number of elements present in the map
        size_type size() const {
            return _size;
        }

        //-- Return maximum number of elements the map can hold
        size_type max_size() const {
            return _node_alloc.max_size(); 
        }

        //-------------------------------------------------------------
        //-------------- MODIFIERS -------------------------------------
        //-------------------------------------------------------------
        // Clear  
        void    clearEachNode( node oneNode)
        {
            if (!oneNode)
                return;
            clearEachNode(oneNode->left);
            clearEachNode(oneNode->right);
            _node_alloc.destroy(oneNode);
            _node_alloc.deallocate(oneNode, 1);
        }
        
        // Erase all elements from the container
        void    clear( )
        {
            if (_root)
            {
                clearEachNode(_root->parent);
                _root->parent = 0;
                _root->right = _root;
                _root->left = _root;
                _size = 0;
            }
        }

        // Insert
        ft::pair<iterator, bool> insert(const value_type &val)
        {
            node currentNode = _root->parent;
            node parentNode = 0;

            while (currentNode != 0 and currentNode != _root)
            {
                if (!_compare(val, currentNode->value) && !_compare(currentNode->value, val))
                    return ft::make_pair(iterator(currentNode), false);
                parentNode = currentNode;
                if (_compare(val,currentNode->value))
                    currentNode = currentNode->left;
                else
                    currentNode = currentNode->right;
            }
            node    newNode = _node_alloc.allocate(1);
		    _node_alloc.construct(newNode, Node<Val>(val));
            newNode->parent = parentNode;
            if (parentNode == 0)
                _root->parent = newNode;
            else
            {
                if (_compare(newNode->value, parentNode->value))
                    parentNode->left = newNode;
                else
                    parentNode->right = newNode;
            }
            if (newNode->parent == 0 or newNode->parent == _root)
                newNode->color = BLACK;
            else if (newNode->parent->parent != 0 && newNode->parent->parent != _root)
                checkInsertionNode(newNode);
            _size++;
            updateRootPos();
            return ft::make_pair(iterator(newNode), true);
        }

        //-- Insert `val` at given `position` in the map
        //-- Returns an iterator pointing to the newly inserted element.
        iterator insert (iterator position, const value_type& val)
        {
            (void)position;
            insert(val);
			iterator Found = begin();
            while( begin() != end())
            {
                if (*Found == val)
                    break;
                Found++;
            }
			return (Found);
        }

        template <class InputIterator>  
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last)
            {
                insert(*first);
                first++;
            }
        }

        void erase(iterator position)
        {
            erase(position->first);
        }

        //------------------------------------------------------------------------------------
        // STEP 1 ) find node 
        // STEP 2) 
        // *** CASE 1 *** 
        // node to delete has two children : 
        // ---> find its in order successor (the node with next largest value)
        // and replace the node to delete with its successor : will have at least one child
    
        // *** CASE  2 ***
        // If node tso delete has one or no children
        // ---> replace it with its child( or with nil if it has no children)

        // STEP 3) 
        //  --  Check RBT rules
        //-----------------------------------------------------------------------------------
        size_type erase(const key_type &key)
	    {

	    	node current = traverseTree(_root->parent, key);
	    	if (current == _root)
	    		return 0;
	    	if (_root->parent)
	    		_root->parent->parent = 0;
	    	node x, y = current;
	    	int saveColor = y->color;

	    	if (current->left == 0)
	    	{
	    		x = current->right;
	    		remplaceSubtrees(current, current->right);
	    	}
	    	else if (current->right == 0)
	    	{
	    		x = current->left;
	    		remplaceSubtrees(current, current->left);
	    	}
	    	else
	    	{
	    		y = getMinFrom(current->right);
	    		saveColor = y->color;
	    		x = y->right;
	    		if (x and y->parent == current)
	    			x->parent = y;
	    		else
	    		{
	    			remplaceSubtrees(y, y->right);
	    			y->right = current->right;
	    			if (y->right)
	    				y->right->parent = y;
	    		}
	    		remplaceSubtrees(current, y);
	    		y->left = current->left;
	    		if (y->left)
	    			y->left->parent = y;
	    		y->color = current->color;
	    	}
	    	_node_alloc.destroy(current);
	    	_node_alloc.deallocate(current, 1);
	    	_size--;
	    	if (saveColor == BLACK and x)
            {
	    	    checkNodeDeletion(x);
            }
	    	updateRootPos();
	    	return (1);
	    }
		    
        //-- Range erase
        void erase (iterator first, iterator last)
        {
            if (first == begin() && last == end())
			{
                	this->clear();
                    return;
			}
            else
            {
                while (first != last)
                    erase(first++);
            }
            return;
        }

        // swap 
        void swap (RedBlackTree& x)
        {
            node            tmpRoot = NULL;
            size_type       tmpSize;
	        node_allocator	tmpNodeAlloc;

            tmpRoot = this->_root;
            this->_root = x._root;
            x._root = tmpRoot;

            tmpSize = this->_size;
            this->_size = x._size;
            x._size = tmpSize;

            tmpNodeAlloc = this->_node_alloc;
            this->_node_alloc = x._node_alloc;
            x._node_alloc = tmpNodeAlloc;
        }

        //-------------------------------------------------------------
        //-------------- LOOKUP -------------------------------------
        //-------------------------------------------------------------

        // count()
        size_type count( const Key& key ) const
        {
            node foundNode = traverseTree(_root->parent, key);
            if (foundNode == 0 or foundNode == _root)
                return (0);
            return (1);
        }
        
        // find()
        iterator find (const key_type& key)
        {
            iterator isFound = traverseTree(_root->parent, key);
            return(isFound);
        }

        // const find()
        const_iterator find (const key_type& key) const
        {   
            const_iterator isFound = traverseTree(_root->parent, key);
            return (isFound);
        }

        //-- std::lower_bound
        //-- Returns an iterator pointing to the first element that is not less than key
        //-- (== first element greater or equal to key) 
        iterator lower_bound(const key_type& key)
		{
            node nodePtr = _root->parent, ret = _root;
		    while (nodePtr != 0 and nodePtr != _root)
		    {
		    	if (!_compare(nodePtr->value, key))
		    	{
		    		ret = nodePtr;
		    		nodePtr = nodePtr->left;
		    	}
		    	else
		    		nodePtr = nodePtr->right;
		    }
		    return iterator(ret);
		/*	iterator it = begin();
			iterator ite = end();
			
			while ( it != ite )
			{
				if (!(_compare(it->first, key)))
					return it;
                it++;
			}
			return it;*/
		}

		const_iterator lower_bound(const key_type& key) const
		{
			/*const_iterator it = begin();
			const_iterator ite = end();
			
			while (it != ite)
			{
				if (!(_compare(it->first, key)))
					return it;
                it++;
			}
			return it;*/
            node nodePtr = _root->parent, ret = _root;
		    while (nodePtr != 0 and nodePtr != _root)
		    {
		    	if (!_compare(nodePtr->value, key))
		    	{
		    		ret = nodePtr;
		    		nodePtr = nodePtr->left;
		    	}
		    	else
		    		nodePtr = nodePtr->right;
		    }
		    return const_iterator(ret);
		}

        //-- std::upper_bound
	    iterator upper_bound(const key_type& key)
		{

        node nodePtr = _root->parent, ret = _root;
		while (nodePtr != 0 and nodePtr != _root)
		{
			if (_compare(key, nodePtr->value))
			{
				ret = nodePtr;
				nodePtr = nodePtr->left;
			}
			else
				nodePtr = nodePtr->right;
		}
		return iterator(ret);
			/*iterator it = begin();
			iterator ite = end();
			
            while ( it != ite )
			{
				if (_compare(key, it->first))
					return (it);
                it++;
			}
			return (it);*/
		}

		const_iterator upper_bound(const key_type& key) const
		{
            node nodePtr = _root->parent, ret = _root;
		    while (nodePtr != 0 and nodePtr != _root)
		    {
		    	if (_compare(key, nodePtr->value))
		    	{
		    		ret = nodePtr;
		    		nodePtr = nodePtr->left;
		    	}
		    	else
		    		nodePtr = nodePtr->right;
		    }
		    return const_iterator(ret);

			/*const_iterator it = begin();
			const_iterator ite = end();

			while ( it != ite )
			{
				if (_compare(key, it->first))
					return (it);
                it++;
			}
			return (it);*/
		}

        //-- Equal_range
        ft::pair<iterator, iterator> equal_range(const key_type& key)
	    { 
             return ft::make_pair(lower_bound(key), upper_bound(key));
        }

	    ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	    { 
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        //-------------------------------------------------------------
        //-------------- OBSERVERS  -----------------------------------
        //-------------------------------------------------------------
        // Returns the comparison object used to compare the keys in the map
        // Used for example :
        // ---> To check if a given key is less than or equal to another key.
        // ---> To sort a rangeof keys.
        key_compare key_comp() const{
            return _compare;
        }

        void    updateRootPos()
        {
            // Need to update the header node here
            //!\\ Root->value is stocked in root->parent 
            if (_root->parent)
            {   
                //-- sets the parent of the header's parent to be the header node, 
                //-- ensuring that the header node is always a valid parent node.
                _root->parent->parent = _root;
                //-- sets the right child of the header node to be the minimum node in the tree.
                _root->right = getMinFrom(_root->parent);
                //-- sets the left child of the header node to be the maximum node in the tree.
                _root->left = getMaxFrom(_root->parent);
            }
        }

        // returns the minimum node in the RBT

        //-------------------------------------------------------------
        //-------------- ALLOCATOR  -----------------------------------
        //-------------------------------------------------------------
	    allocator_type get_allocator() const
        { 
            return _node_alloc; 
        }

        //-------------------------------------------------------------
        //-------------- UTILS  ---------------------------------------
        //-------------------------------------------------------------
        private:
            node getMin() const
	        { 
                return getMinFrom(_root->parent); 
            }
    
	        node getMax() const
	        { 
                return getMaxFrom(_root->parent); 
            }
    
            node getMinFrom (const node &nodePtr) const
            {
                if (nodePtr != 0 && nodePtr != _root && nodePtr->left != 0 && nodePtr->left != _root)
                    return getMinFrom(nodePtr->left);
                else
                    return (nodePtr);
            }
    
	        node getMaxFrom(const node &nodePtr) const
            {
                if (nodePtr != 0 && nodePtr != _root && nodePtr->right != 0 && nodePtr->right != _root)
                    return getMaxFrom(nodePtr->right);
                else
                    return (nodePtr);
            }
            
            node traverseTree(const node &current, const Key &search) const
	        {
	        	if (current == 0 || current == _root)
	        	    return _root;
                if (!_compare(current->value, search) && !_compare(search, current->value))
                    return current;
                if (_compare(search, current->value))
                {
                    return (traverseTree(current->left, search));
                }
                else
                {
                    return (traverseTree(current->right, search));
                }
	        }

            /*void   inOrderSearch( node traversal)
            {
                if (traversal == NULL)
                    return;
                inOrderSearch(traversal->left);
                std::cout << traversal->value.first << " " << std::endl;
                inOrderSearch(traversal->right);
            }

            void   preOrderSearch( node traversal)
            {
                if (traversal == NULL)
                    return;
                std::cout << traversal->value.first << " " << std::endl;
                inOrderSearch(traversal->left);
                inOrderSearch(traversal->right);
            }

            void   postOrderSearch( node traversal)
            {
                if (traversal == NULL)
                    return;
                inOrderSearch(traversal->left);
                inOrderSearch(traversal->right);
                std::cout << traversal->value.first << " " << std::endl;
            }*/
        
            void    printOneNode( node oneNode)
            {
                std::cout << std::endl;
                std::cout << "| ------------------------------------ |"<< std::endl;
                std::cout << "   Node color : " ;
                if (oneNode->color == BLACK) 
                    std::cout << "   Black" << std::endl;
                else
                    std::cout << " Red" << std::endl;
                std::cout << "   Node value : " << oneNode->value.first << std::endl;
                std::cout << "| ------------------------------------ |"<< std::endl;
            }

            void    printRoot( void )
            {
                std::cout << std::endl;
                std::cout << "| ------------------------------------ |"<< std::endl;
                std::cout << "   ROOT: " << _root->parent->value.first << std::endl;
                std::cout << "| ------------------------------------ |"<< std::endl;
            }

            void printTreeHelper(node root, std::string indent, bool last)
	        {
                if (empty())
                {
                    std::cout << "MAP IS EMPTY" << std::endl;
                    return;
                }
	        	if (root != 0 and root != _root)
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
                    if (root->color == RED)
                        std::cout << root->value.second << REDCOLOR << "(RED)" << CLEAR << std::endl;
                    else
                        std::cout << root->value.second << "(BLACK)" << std::endl;	
	        		printTreeHelper(root->left, indent, false);
	        		printTreeHelper(root->right, indent, true);
	        	}
	        }

            void printTree()
	        { 
                printTreeHelper(_root->parent, "", true);
            }

};
    
    //----------- RELATIONNAL OPERATORS
    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator==(const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &rhs)
    {
    	return lhs.size() == rhs.size()
    		   and ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator<(const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &lhs,
    		  const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator!=(const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return not (lhs == rhs); }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator>(const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &lhs,
    		  const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return rhs < lhs; }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator>=(const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return not (lhs < rhs); }

    template <typename _Key, typename _Val, class _Compare, class _Allocator>
    inline bool
    operator<=(const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &lhs,
    		   const ft::RedBlackTree<_Key, _Val, _Compare, _Allocator> &rhs)
    { return not (rhs < lhs); }
}
#endif