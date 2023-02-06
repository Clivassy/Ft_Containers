#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <stdint.h>
# include <iostream>
# include <stdlib.h>

# include "./pair.hpp"
# include "../utils/is_integral.hpp"
#include "./testeur.hpp"

#include "RBT_iterator.hpp"
# include "../utils/reverse_iterator.hpp"
# include "../utils/equal.hpp"
# include "../utils/lexicographical_compare.hpp"

//--------------------------------------------------
#define BLACK 0
#define RED 1

//---------------------------------------------------

namespace ft{
    template <typename Key, typename Val , class Compare = std::less<Key>, class Allocator = std::allocator<Val> >
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
                Node(): left(0), right(0), parent(0), color(RED){}
                Node(const T &data) : value(data), left(0), right(0), parent(0), color(RED){}
            };
            //-- create a new type of allocator that is bound to the 'Node' type nd uses the same 
            // memoryressource as the original 'allocator_type'.
            typedef typename Allocator::template rebind<Node<Val> >::other   node_allocator;

        public:
        	typedef Key					                                    key_type;
            typedef Compare											        key_compare;
			//typedef Compare				                                    compare_type;
            typedef Val												        value_type;
            typedef Val*			                                        pointer;
            typedef const value_type *								        const_pointer;
            typedef value_type &									        reference;
	        typedef const value_type &								        const_reference;    
            typedef size_t				                                    size_type;
			typedef Allocator				                                allocator_type;
			//typedef Node<Val>*				                                node_pointer;
			typedef const Node<Val>*			                            const_node_pointer;
    

        protected:
            typedef Node<Val>*  node;

            node    _root; // root of the tree
	       // node	_leaf; // leaf
	        size_type		_size; // number of elements in the tree
            Compare         _compare;
	        node_allocator	_node_alloc; // allocation pour un noeud

	       
        
        public:
            // ----  Iterators TO DO 
            typedef ft::RBT_iterator<Val, node, Compare>                iterator;
            typedef ft::RBT_iterator<const Val, node, Compare>          const_iterator;
            typedef ft::reverse_Iterator<iterator>			            reverse_iterator;
	        typedef ft::reverse_Iterator<const_iterator>	            const_reverse_iterator;

            RedBlackTree(const Compare& comp = Compare(), const node_allocator& alloc = node_allocator()) 
            : _compare(comp), _node_alloc(alloc)
            {
                _size = 0;
                _root = _node_alloc.allocate(1); // allocate memory for one node memory
                _node_alloc.construct(_root, Node<Val>()); // construct root node : create a new node object
                _root->parent = 0;
                _root->right = _root;
                _root->left = _root;
            }

            template <class InputIterator>
            RedBlackTree(InputIterator first, InputIterator last,
            const Compare& comp, const node_allocator& alloc = node_allocator()) 
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

        // rotateLeft
        void rotateLeft(node x)
        {
            node y = x->right;
		    x->right = y->left;
		    if (y->left != 0)
		    	y->left->parent = x;
		    y->parent = x->parent;
		    if (x->parent == 0 or x->parent == _root)
		    	_root->parent = y;
		    else if (x == x->parent->left)
		    	x->parent->left = y;
		    else
		    	x->parent->right = y;
		    y->left = x;
		    x->parent = y;
            /*node parent = newNode->right;
			if (newNode == _root)
				_root = parent;
			if (newNode->parent != NULL)
			{
				if (newNode == newNode->parent->left)
					newNode->parent->left = parent;
				else 
					newNode->parent->right = parent;
			}
			parent->parent = newNode->parent;
			newNode->parent = parent;
			newNode->right = parent->left;
			if (parent->left != NULL) 
				parent->left->parent = newNode;
			parent->left = newNode;*/

            /* node parent = newNode->right;

            newNode->right = parent->left;
            if (parent->left != 0) {
              parent->left->parent = newNode;
            }
            parent->parent = newNode->parent;
            if (newNode->parent == NULL) {
              this->_root = parent;
            } else if (newNode == newNode->parent->left) {
              newNode->parent->left = parent;
            } else {
              newNode->parent->right = parent;
            }
            parent->left = newNode;
            newNode->parent = parent;*/
        }

        // Rotate Right
        void rotateRight(node x)
	    {
	    	node y = x->left;
	    	x->left = y->right;
	    	if (y->right != 0)
	    		y->right->parent = x;
	    	y->parent = x->parent;
	    	if (x->parent == 0 or x->parent == _root)
	    		_root->parent = y;
	    	else if (x == x->parent->right)
	    		x->parent->right = y;
	    	else
	    		x->parent->left = y;
	    	y->right = x;
	    	x->parent = y;
	    }

            /*nodePtr->left = parent->right;
            if (parent->right != 0) 
                parent->right->parent = nodePtr;
            parent->parent = nodePtr->parent;
            if (nodePtr->parent == NULL)
                this->_root = parent;
            else if (nodePtr == nodePtr->parent->right)
                nodePtr->parent->right = parent;
            else 
                nodePtr->parent->left = parent;
            parent->right = nodePtr;
            nodePtr->parent = parent;   */

        // insertfix
        void    checkInsertionNode(node newNode)
        {
            node ptr;
            while (newNode->parent->color == RED)
            {
                if (newNode->parent == newNode->parent->parent->right) 
                {
                    ptr = newNode->parent->parent->left;
                    if (ptr)
                    {
                        if (ptr->color == RED)
                        {
                            ptr->color = BLACK;
                            newNode->parent->color = BLACK;
                            newNode->parent->parent->color = RED;
                            newNode = newNode->parent->parent;
                        }
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
                    if (ptr)
                    { 
                        if (ptr->color == RED)
                        {
                            ptr->color = BLACK;
                            newNode->parent->color = BLACK;
                            newNode->parent->parent->color = RED;
                            newNode = newNode->parent->parent;
                        }
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
        // delete fix
        // TO DO -----

        //----------------------------------------------
        //------ ACCESSORS 
        //----------------------------------------------
        ft::pair<iterator, bool> at(const value_type &value)
        {
            node traversal = _root;
            node parent;
            key_type key = value.first;

            if (empty())
                throw std::out_of_range("ft::map::at");
            while ( traversal != 0 && traversal != _root)
            {
                parent = traversal;
                if (traversal->value.first == key)
                    return(ft::make_pair(iterator(traversal), false));
                if (_compare(value.first, traversal->value.first))
                    traversal =  traversal->left;
                else if (_compare(traversal->value.first, value.first))
                    traversal =  traversal->right;
                else
                    return(ft::make_pair(iterator(traversal), false));
            }
            throw std::out_of_range("ft::map::at");
        }

        const ft::pair<iterator, bool> at(const value_type &value) const
        {
            node traversal = _root;
            node parent;
            key_type key = value.first;
            
            while ( traversal != 0 )
            {
                parent = traversal;
                if (traversal->value.first == key)
                    return(ft::make_pair(iterator(traversal), false));
                if (_compare(value.first, traversal->value.first))
                    traversal =  traversal->left;
                else if (_compare(traversal->value.first, value.first))
                    traversal =  traversal->right;
            }
            throw std::out_of_range("ft::map::at");          
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
                if (currentNode->value.first == val.first)
                    return ft::make_pair(iterator(currentNode), false);
                parentNode = currentNode;
                if (val.first < currentNode->value.first)
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
                if (newNode->value.first < parentNode->value.first)
                    parentNode->left = newNode;
                else
                    parentNode->right = newNode;
            }
            if (newNode->parent == 0)// or newNode->parent == _root)
                newNode->color = BLACK;
            else if (newNode->parent->parent != 0 && newNode->parent->parent != _root)
                checkInsertionNode(newNode);
            _size++;
            updateRootPos();

            // DEBEUG 
            // printRoot();
            //printOneNode(newNode);
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
			return Found;
        }

        template <class InputIterator>  
        void insert (InputIterator first, InputIterator last)
        {
            while ( first != last)
            {
                insert(*first);
                first++;
            }
        }

        

        node deleteNode (node nodePtr)
        {
            (void)nodePtr;
            // STEP 1 ) find node 

            // STEP 2) 
            // *** CASE 1 *** 
            // node to delete has two chlidren : 
            // ---> find its in order successor (the node with next largest value)
            // and replace the node to delete with its successor : will have at least one child
        
            // *** CASE  2 ***
            // If node tso delete has one or no children
            // ---> replace it with its child( or with nil if it has no children)
    
            // STEP 3) 
            //  --  Check RBT rules
    
        // erase position 
        }
        void erase (iterator position)
        {
			iterator tmp = position;
			while (tmp + 1 != end())
			{
				*tmp = *(tmp + 1);
				_node_alloc.destroy(tmp.base());
				_node_alloc.construct(tmp.base(), *(tmp + 1));
				tmp++;
			}
			_node_alloc.destroy(tmp.base());
			_size--;
			return (iterator(position));
        }

        // erase k
       /* size_type erase (const key_type& k)
        {

        }*/
        
        // erase first, last
        /*  void erase (iterator first, iterator last)
        {

        }*/

        // swap 
        void swap (RedBlackTree& x)
        {
            node            tmpRoot = NULL;
            size_type       tmpSize;
            Compare         tmpComp;
	        node_allocator	tmpNodeAlloc;

            tmpRoot = this->_root;
            this->_root = x._root;
            x._root = tmpRoot;

            tmpSize = this->_size;
            this->_size = x._size;
            x._size = tmpSize;

            tmpComp = this->_compare;
            this->_compare = x._compare;
            x._compare = tmpComp;

            tmpNodeAlloc = this->_node_alloc;
            this->_node_alloc = x._node_alloc;
            x._node_alloc = tmpNodeAlloc;
        
            /*node root = this->_root;
		    size_t size = this->_size;
		    RedBlackTree Alloc = this->_node_alloc;
		    this->_root = x._root;
		    this->_size = x._size;
		    this->_node_alloc = x._node_alloc;
		    x._root = root;
		    x._size = size;
		    x._node_alloc = Alloc;*/
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
        /*iterator lower_bound(const key_type& key)
			{
				iterator it = begin();
				iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (!(_compare(it->first, key)))
						return it;
				}
				return it;
			}

			const_iterator lower_bound(const key_type& key) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (!(_compare(it->first, key)))
						return it;
				}
				return it;
			}*/
        iterator lower_bound( const key_type& key )
        {
            node currentNode = _root->parent;
            node lowerBoundNode = _root; 

            while( currentNode != 0 and currentNode!= _root)
            {
                if (!_compare(currentNode->value.first, key))
                {
                    lowerBoundNode = currentNode;
                    currentNode = currentNode->left;
                    
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
            return iterator (lowerBoundNode);
        }


        const_iterator lower_bound( const Key& key ) const
        {
            node currentNode = _root->parent;
            node lowerBoundNode = _root; 

            while( currentNode != 0 and currentNode!= _root)
            {
                if (!_compare(currentNode->value.first, key))
                {
                    lowerBoundNode = currentNode;
                    currentNode = currentNode->left;
                    
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
            return const_iterator (lowerBoundNode);
        }

        //-- std::upper_bound
        iterator upper_bound( const Key& key )
        {
            node currentNode = _root->parent;
            node upperBoundNode = _root;

            while (currentNode != 0 and currentNode != _root)
            {
                if (_compare(key, currentNode->value.first))
                {
                    upperBoundNode = currentNode;
                    currentNode = currentNode->left;
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
            return iterator (upperBoundNode);
        }

        const_iterator upper_bound( const Key& key ) const
        {
            node currentNode = _root->parent;
            node upperBoundNode = _root;

            while (currentNode != 0 and currentNode != _root)
            {
                if (_compare(key, currentNode->value.first))
                {
                    upperBoundNode = currentNode;
                    currentNode = currentNode->left;
                }
                else
                {
                    currentNode = currentNode->right;
                }
            }
            return const_iterator (upperBoundNode);
        }
	       /* iterator upper_bound(const key_type& key)
			{
				iterator it = begin();
				iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (_compare(key, it->first))
						return it;
				}
				return it;
			}

			const_iterator upper_bound(const key_type& key) const
			{
				const_iterator it = begin();
				const_iterator ite = end();
				
				for (; it != ite; it++)
				{
					if (_compare(key, it->first))
						return it;
				}
				return it;
			}*/
        /*ft::pair<iterator, iterator> equal_range(const key_type& key)
	    { 
             return ft::make_pair(lower_bound(key), upper_bound(key));
        }

	    ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	    { 
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }*/

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
        //-------------------------------------------------------------
        //-------------- UTILS  ---------------------------------------
        //-------------------------------------------------------------
        node traverseTree(const node &current, const Key &search) const
	    {
	    	if (current == 0 || current == _root)
	    	    return _root;
            if (!_compare(current->value.first, search) && !_compare(search, current->value.first))
                return current;
            if (_compare(search, current->value.first))
            {
                return (traverseTree(current->left, search));
            }
            else
            {
                return (traverseTree(current->right, search));
            }
	    	/*if (not _compare(current->value.first, toFind) and not _compare(toFind, current->value.first))
	    		return nodePtr;
	    	return find_impl((_compare(toFind, current->value.first) ? current->left : current->right), toFind);*/
	    }

        void   inOrderSearch( node traversal)
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
    node getMin()
	const
	{ return getMinFrom(_root->parent); }

	node getMax()
	const
	{ return getMaxFrom(_root->parent); }

	node
	getMinFrom(const node &nodePtr)
	const
	{ return (nodePtr != 0 and nodePtr != _root and nodePtr->left != 0 and nodePtr->left != _root ? getMinFrom(nodePtr->left) : nodePtr); }

	
	node getMaxFrom(const node &nodePtr)
	const
	{ return (nodePtr != 0 and nodePtr != _root and nodePtr->right != 0 and nodePtr->right != _root ? getMaxFrom(nodePtr->right) : nodePtr); }
       /* node getMin(const node &newNode) const
        {
            if (newNode == 0 || newNode == _root)
                return (0);
            if (newNode->left == 0 || newNode->left == _root)
            {
                return newNode;
            }

            return (getMin(newNode->left));
        }

        node getMax(const node &newNode) const
        {
            if (newNode == 0 || newNode == _root)
                return (0);
            if (newNode->right == 0|| newNode->right == _root)
                return newNode;
            return (getMin(newNode->right));
        }*/

        //-------------------------------------------------------------
        //-------------- ALLOCATOR  -----------------------------------
        //-------------------------------------------------------------
	    allocator_type get_allocator() const
        { 
            return _node_alloc; 
        }
        ///////////////////// DEBUG //////////////////
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
       /* preOrderSearch(_root->parent);
        std::cout << std::endl;
        inOrderSearch(_root->parent);
        std::cout << std::endl;
        postOrderSearch(_root->parent);*/
    }


    
    };
    //------------ NON MEMBER FUNCTIONS 
    //-- swap 


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