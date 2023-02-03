#ifndef RBTREE_HPP
# define RBTREE_HPP

# include <stdint.h>
# include <iostream>
# include <stdlib.h>

# include "./pair.hpp"
# include "../utils/is_integral.hpp"

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
			typedef Node<Val>*				                                node_pointer;
			typedef const Node<Val>*			                            const_node_pointer;
    

        protected:
            typedef Node<Val>*  node;

            node_pointer    _root; // root of the tree
	        node_pointer	_leaf; // leaf
	        size_type		_size; // number of elements in the tree
            Compare         _compare;
	        node_allocator	_node_alloc; // allocation pour un noeud

	       
        
        public:
            // ----  Iterators TO DO 
            typedef ft::RBT_iterator<Val, node_pointer, Compare>        iterator;
            typedef ft::RBT_iterator<Val, node_pointer, Compare>        const_iterator;
            typedef ft::reverse_Iterator<iterator>			            reverse_iterator;
	        typedef ft::reverse_Iterator<const_iterator>	            const_reverse_iterator;

            RedBlackTree(const Compare& comp = Compare(), const node_allocator& alloc = node_allocator()) 
            : _compare(comp), _node_alloc(alloc)
            {
                (void)comp;
                _size = 0;
                _root = _node_alloc.allocate(1); // allocate memory for one node memory
                _node_alloc.construct(_root, Node<Val>()); // construct root node : create a new node object
                _root->parent = 0;
                _root->right = _root;
                _root->left = _root;
            }

            template <class InputIterator>
            RedBlackTree(InputIterator first, InputIterator last,
            const Compare& comp = Compare(), const node_allocator& alloc = node_allocator()) 
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
        void rotateLeft(node newNode)
        {
            node y = newNode->right;

            newNode->right = y->left;
            if (y->left != 0) {
              y->left->parent = newNode;
            }
            y->parent = newNode->parent;
            if (newNode->parent == nullptr) {
              this->_root = y;
            } else if (newNode == newNode->parent->left) {
              newNode->parent->left = y;
            } else {
              newNode->parent->right = y;
            }
            y->left = newNode;
            newNode->parent = y;
        }

        // Rotate Right
        void    rotateRight(node nodePtr)
        {         
            node y = nodePtr->left;

            nodePtr->left = y->right;
            if (y->right != 0) {
              y->right->parent = nodePtr;
            }
            y->parent = nodePtr->parent;
            if (nodePtr->parent == nullptr) {
              this->_root = y;
            } else if (nodePtr == nodePtr->parent->right) {
              nodePtr->parent->right = y;
            } else {
              nodePtr->parent->left = y;
            }
            y->right = nodePtr;
            nodePtr->parent = y;   
        }

        // insertfix
        void    checkInsertionNode(node newNode)
        {
            node ptr;
            // while the parent of newNode (p) is RED
            while (newNode->parent->color == RED)
            {         
                if (newNode->parent == newNode->parent->parent->right) 
                {
                    ptr = newNode->parent->parent->left;
                    if (ptr->color == 1) 
                    {
                        ptr->color = 0;
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        newNode = newNode->parent->parent;
                    } 
                    else 
                    {
                        if (newNode == newNode->parent->left) 
                        {
                            newNode = newNode->parent;
                            rotateRight(newNode);
                        }
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        rotateLeft(newNode->parent->parent);
                    }
                } 
                else 
                {
                    ptr = newNode->parent->parent->right;
                    if (ptr->color == 1) 
                    {
                        ptr->color = 0;
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        newNode = newNode->parent->parent;
                    } 
                    else 
                    {
                        if (newNode == newNode->parent->right) 
                        {
                            newNode = newNode->parent;
                            rotateLeft(newNode);
                        }
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        rotateRight(newNode->parent->parent);
                    }
                }
                if (newNode == _root) 
                    break;
            }
        _root->color = 0;
    }
        // delete fix
        // TO DO ----- 

        /*const key_type& at(const value_type &val)
        {
           // return val;
        }*/
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
                {
                    //std::cout << "Error: key already exists in the map" << std::endl;
                    return ft::make_pair(iterator(currentNode), false);
                }

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
            if (newNode->parent == 0 or newNode->parent == _root)
                newNode->color = BLACK;
            else
            {
               // std::cout << "Need to check RBT rules" << std::endl;
            }
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


        // erase 
        // swap 

        //-------------------------------------------------------------
        //-------------- LOOKUP -------------------------------------
        //-------------------------------------------------------------
        // count
        size_type count (const key_type& k) const
        {
            (void)k;
        }

        /*const_iterator find (const key_type& k) const
        {

        }*/

        //-- std::equal_range
        //-- Returns a range containing all elements with the given key in the container.
        //-- Returns a pair of iterators defining the wanted range :
        //-- Firt iterator: is pointing to the first element that is not less than the key
        //-- Second element: is pointing to the first element greater than key.
        std::pair<iterator,iterator> equal_range( const Key& key )
        {
            (void)key;
        }

        std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
        {
            (void)key;
        }

        //-- std::lower_bound
        //-- Returns an iterator pointing to the first element that is not less than key
        //-- (Greater or equal) 
        iterator lower_bound( const key_type& key )
        {
            node currentNode = _root->parent;
            node lowerBoundNode = _root; 

            while( currentNode != 0 and currentNode!= _root)
            {
                if ( !_compare(currentNode->value.first, key))
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
                if ( !_compare(currentNode->value.first, key))
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

        //-- std::upper_bound
        iterator upper_bound( const Key& key )
        {
            (void)key;
        }

        const_iterator upper_bound( const Key& key ) const
        {
            (void)key;
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
        //-------------------------------------------------------------
        //-------------- UTILS  ---------------------------------------
        //-------------------------------------------------------------
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
                _root->right = getMin(_root->parent);
                //-- sets the left child of the header node to be the maximum node in the tree.
                _root->left = getMax(_root->parent);
            }
        }

        // returns the minimum node in the RBT
        node getMin(const node &newNode) const
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
        }

        //-------------------------------------------------------------
        //-------------- ALLOCATOR  -----------------------------------
        //-------------------------------------------------------------

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
			std::string sColor = root->color ? "RED" : "BLACK";
			std::cout << root->value.second << "(" << sColor << ")" << std::endl;
			printTreeHelper(root->left, indent, false);
			printTreeHelper(root->right, indent, true);
		}
	}


    void printTree()
	{ 
        printTreeHelper(_root->parent, "", true); 
    }


    
    };
    //------------ NON MEMBER FUNCTIONS 
    


    //----------- RELATIONNAL OPERATORS 
}



#endif