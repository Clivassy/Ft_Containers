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
    template <typename Key, typename Val = Key , 
        class Compare = std::less<Key>, class Allocator = std::allocator<Val> >
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
            typedef typename Allocator::template rebind<Node<Val>>::other   node_allocator;

        public:
            typedef size_t				                                    size_type;
			typedef Key					                                    key_type;
			typedef Compare				                                    compare_type;
			typedef Allocator				                                allocator_type;
			typedef Val*			                                        pointer;
			typedef Node<Val>*				                                node_pointer;
			typedef const Node<Val>*			                            const_node_pointer;
			typedef Val&			                                        reference;
			typedef const Val&	                                            const_reference;
            

        protected:
            node_pointer    root; // root of the tree
	        node_pointer	leaf; // leaf
	        size_type		size; // number of elements in the tree 
	        node_allocator	node_alloc; // allocation pour un noeud
	        compare_type	compare;
        
        public:
            // ----  Iterators TO DO 
            typedef ft::RBT_iterator<Key, node_pointer>         iterator;
            typedef ft::RBT_iterator<Key, node_pointer>         const_iterator;
            typedef ft::reverse_Iterator<iterator>			    reverse_iterator;
	        typedef ft::reverse_Iterator<const_iterator>	    const_reverse_iterator;


            RedBlackTree(const compare_type& comp = compare_type(), 
                const node_allocator& alloc = node_allocator()) 
                : compare(comp), node_alloc(alloc)
            {
                size = 0;
                root = node_alloc.allocate(1); // allocate memory for one node memory
                node_alloc.construct(root, Node<Val>()); // construct root node : create a new node object
                root->parent = 0;
                root->right = root;
                root->left = root;

                //---- DEBEUG ---- 
                std::cout<< "red black tree is created" << std::endl;
                root->color = BLACK;
                std::cout<< "Root node is " ;
                if (root->color == BLACK)
                    std::cout << "Black" << std::endl;
                else
                    std::cout << "FAILED" << std::endl;
            }

            ~RedBlackTree()
            {
                //clear();
        		node_alloc.destroy(root);
		        node_alloc.deallocate(root, 1);
            } 

        //-- RED BLACK TREE OPERATIONS
        //--------------------------------

        // rotateLeft
        // rotateright
        // insertfix
        // delet fix
     
        //----------------------------------------------------------------
        //-------------- ELEMENT ACCESS ----------------------------------
        //----------------------------------------------------------------

        //----------------------------------------------
        //------ ITERATORS --- From RBT_Iterators
        //----------------------------------------------
	    iterator begin()
	    { 
            std::cout << "begin() function called" << std::endl;
            return iterator(root->right); 
        }

	    const_iterator begin()const
	    { 
            return const_iterator(root->right); 
        }

	    iterator end()
	    { 
            std::cout << "end() function called" << std::endl;
            return iterator(root); 
        }

	    const_iterator end() const 
        { 
            return const_iterator(root); 
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
            return size == 0;
        }

        //-- Returns number of elements present in the map
        size_type size() const {
            return size;
        }

        //-- Return maximum number of elements the map can hold
        size_type max_size() {
            return node_alloc.max_size(); 
        }

        //-------------------------------------------------------------
        //-------------- MODIFIERS -------------------------------------
        //-------------------------------------------------------------
        // Erase all elements from the container
        // Clear 

        // Insert
        // erase 
        // swap 

        //-------------------------------------------------------------
        //-------------- LOOKUP -------------------------------------
        //-------------------------------------------------------------
        // count
        // find
        // equal_range 
        // lower_bound
        // upper_bound

        //-------------------------------------------------------------
        //-------------- OBSERVERS  -------------------------------------
        //-------------------------------------------------------------
        // Key_comp
        // value_comp

    };
    //------------ NON MEMBER FUNCTIONS 
    


    //----------- RELATIONNAL OPERATORS 
}



#endif