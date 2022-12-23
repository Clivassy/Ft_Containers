#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <stdexcept>

namespace ft
{
    template <class T, class Allocator = std::allocator <T> >
    class vector 
    {
        public:
            typedef typename Allocator::pointer 			        pointer;
            typedef Allocator                                       allocator_type;
            typedef typename allocator_type::size_type              size_type;
            typedef T										        value_type;
	        typedef typename Allocator::reference			        reference;
	        typedef typename Allocator::const_reference		        const_reference;
        // MEMBERS FUNCTIONS    
        // ( 1 ) Constructors  

            // Constructor by default
            // construct an empty container, with no element in it.
            // call of std::allocator : construct an allocator object. 
            explicit vector( const allocator_type& alloc = allocator_type()): 
            _alloc(alloc), _start(NULL), _end(NULL), _end_capacity(NULL)
            {
               // std::cout << "constructor by default called" << std::endl;
            }

            // fill constructor : construct a T vector object allocating memory for N elements
            explicit vector(size_type n, const T &val = T(), const allocator_type& alloc = allocator_type())
            {   
                // don't know if it is necessary
                _alloc = alloc;
                _start = NULL;
                _end_capacity = NULL;
                _end = NULL;
                // check here if N > max-size : reject exception if it is the case
                _start = _alloc.allocate( n ); 
                _end = _start;
                _end_capacity = _start + n;
                while (n--)
				{
					_alloc.construct(_end, val); //constructs a type T object in the allocated storage pointed by _end
					_end++;
				}
            }

            // constructor par copie
           /* vector (const vector& x)
            {
                // initialize values to null
                // allocate memory with allocator
                // copy each value in the new vector (from begin to end)
            }

            // constructor par range 
            template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr)
                    : _alloc(alloc)
            {

            }*/
        // ( 2 ) Destructor    
        ~vector() // destruct all element in the vector + liberate memory
	    {
		    // clear();
		    // allocator.deallocate(_start, capacity());
	    }

       // ( 3 ) Overload operator=    

       // ( 4 ) Iterators 
       /* iterator begin() { return (_start); };
        
        const_iterator begin() const { return (_start); }
        
        iterator end()
		{
			if (this->empty())
				return (this->begin());
            return (_end);
		}
        
        const_iterator end() const
		{
			if (this->empty())
				return (this->begin());
			return (_end);
		}*/
	    bool	empty()const{

				return (this->_start == this->_end);
			}
        // ( 5 ) Capacity  
        size_type capacity() const{ // returns current capacity of the vector
            return size_type(_end_capacity - _start); 
        }
	    void reserve(size_type n)
	    {
	    	//if (n > max_size())
	    	//	throw std::length_error("vector::reserve");
	    	if (n > capacity())
	    	{   
	    		pointer newStart = _alloc.allocate(n);
	    		pointer newFinish = newStart;
                for (pointer ptr = _start; ptr !=  _end; ++ptr)
                {
	    			_alloc.construct(newFinish, *ptr);
	    			newFinish++;
	    		}
	    		_alloc.destroy(--_end);
	    		_alloc.deallocate(_start, capacity());
	    		_start = newStart;
	    		_end = newFinish;
	    		_end_capacity = _start + n;
	    	}
	    }

        // ( 6 ) Element access    
        size_type size() const{ // returns current size of the vector
            return size_type(_end - _start);
        }

	    reference 
	    back()
	    { 
            //std::cout << *_end << std::endl;
            return *(_end - 1); 
        }

	    const_reference
	    back()
	    const
	    { return *(_end - 1); }
        // ( 7 ) Modifiers 

        void    clear()
        {
            // remove all elements from the vector
        }
        
        void        pop_back() // remove the last element from the vector
        {
            /* Step 1) : check is the vector is empty : we can throw an exception here
             or return a default
            Step 2 ) decrement the size of the vector by one and return the last element
            */
           _alloc.destroy(--_end);
        }

        void push_back (const value_type& val) 
        /* add an element at the end of the vector, after its current last element
            the content of val is copied to the new element. 
            This effectively increases the container size by one,
            which causes an automatic reallocation of the allocated storage space 
            if -and only if- the new vector size surpasses the current vector capacity */
        {
            if (_end >= _end_capacity)
			    reserve(size() > 0 ? size() * 2 : 1);
            _alloc.construct(_end, val);
            _end++;
            std::cout << *_end << std::endl;
        }
        // ( 8 ) Allocator     

        //protected:
            allocator_type _alloc; 
            pointer _start; // pointer to the first element of my vector
            pointer _end; 
            pointer _end_capacity; 
            
        // NON MEMBERS FUNTIONS OVERLOAD    
        };
}
#endif