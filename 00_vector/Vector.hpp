#ifndef VECTOR_HPP
# define VECTOR_HPP
 
// Officials libraries
# include <iostream>
# include <algorithm>
# include <cstddef>
# include <iterator>
# include <limits>
# include <memory>
# include <stdexcept>

// Personnal librairies
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "equal.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
    template <class T, class Allocator = std::allocator <T> >
    class vector 
    {
        public:
            typedef typename Allocator::pointer 			        pointer;
            typedef typename Allocator::const_pointer		        const_pointer;
            typedef Allocator                                       allocator_type;
            typedef std::ptrdiff_t							        difference_type;
            typedef typename allocator_type::size_type              size_type;
            typedef T										        value_type;
	        typedef typename Allocator::reference			        reference;
	        typedef typename Allocator::const_reference		        const_reference;
        
            // ITERATORS
            typedef ft::random_access_iterator<T>			iterator;
	        typedef ft::random_access_iterator<const T> 	const_iterator;
            typedef ft::reverse_Iterator<iterator>			reverse_iterator;
	        typedef ft::reverse_Iterator<const_iterator>	const_reverse_iterator;
        
        // MEMBERS FUNCTIONS    
        // ( 1 ) Constructors  

            // Constructor by default
            // construct an empty container, with no element in it.
            // call of std::allocator : construct an allocator object. 
            explicit vector( const allocator_type& alloc = allocator_type()): 
            _alloc(alloc), _start(NULL), _end(NULL), _end_capacity(NULL)
            { }

            // fill constructor : construct a T vector object allocating memory for N elements
            explicit vector(size_type n, const T &val = T(), const allocator_type& alloc = allocator_type())
            {   
                // check here if N > max-size : reject exception if it is the case
                if (n > max_size())
                    throw (std::length_error("cannot create std::vector larger than max_size()"));
                _start = _alloc.allocate( n ); 
                _end = _start;
                _end_capacity = _start + n;
                while (n--)
				{
					_alloc.construct(_end, val); //constructs a type T object in the allocated storage pointed by _end
					_end++;
				}
            }
// UTILS 
    template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type 
    distance(InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
		while (first != last)
		{
			first++;
			rtn++;
		}
		return (rtn);
	}

            // constructor par copie
            vector (const vector& x)
            /*initialize values to null
            allocate memory with allocator
            copy each value in the new vector (from begin to end)*/
            {
                _alloc = x._alloc;
                _start = NULL;
                _end_capacity = NULL;
                _end = NULL;
                this->insert(this->begin(), x.begin(), x.end());
            }

            // constructor par range 
            template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
                    : _alloc(alloc)
            { 
                size_type size = distance(first, last);
		        if (size > max_size())
			        throw std::length_error("cannot create std::vector larger than max_size()");
		        _start = _alloc.allocate(size);
		        _end = _start;
		        _end_capacity = _start + size;
		        while (size--)
		        {
		        	_alloc.construct(_end, *first++);
		        	_end++;
		        }
            }

        // ( 2 ) DESTRUCTOR 
        ~vector() // destruct all element in the vector + liberate memory
	    {
		    clear();
		    _alloc.deallocate(_start, capacity());
	    }

       // ( 3 ) Overload operator= 
       // Need iterators
        vector<T, Allocator> &operator=(const vector<T, Allocator> &rhs)
	    {
		    if (*this != rhs)
		    {
		    	clear();
		    	this->reserve(rhs.size());
		    	insert(begin(), rhs.begin(), rhs.end());
		    }
		    return (*this);
	    }

       // ( 4 ) Iterators 
        iterator    begin() { return (iterator(_start));}
        
        iterator	end(){ return (iterator(_end));}
        
        const_iterator begin() const { return (_start);}
        
        const_iterator end() const { return (_end); }
        
        // Reverse iterators
        reverse_iterator rbegin() { return reverse_iterator(end()); }

	    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

	    reverse_iterator rend() { return reverse_iterator(begin()); }

	    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
        
        // ( 5 ) CAPACITY
        size_type size() const{ // returns current size of the vector
            return size_type(_end - _start);
        }

        // max size : Return maximum size of the vector
        size_type max_size() const {
            return (_alloc.max_size());
        }

        void resize(size_type n, T val = T()) // resize : change sie of the vector 
        {
		    if (n > max_size())
		    	throw (std::length_error("vector::resize")); 
                // belong to std::class lenght error
                // https://en.cppreference.com/w/cpp/error/length_error 
            else if (n < size())
            {
                // content is reduce to its first n element
                // removing those beyond by destroying them.
              while (size() > n) 
		        {
		    	    _end--;
		    	    _alloc.destroy(_end);
		        }
            }
           // else
                // content is expandes by inserting at the end as many element
                // as needed to reach size of n. 
                // if val is specified, the new element are initialized as copies of val
		       // insert(end(), n - size(), val);
	    }

        size_type capacity() const{ // returns current capacity of the vector
            return size_type(_end_capacity - _start); 
        }

        bool	empty()const{
			return (this->_start == this->_end);
		}

	    void reserve(size_type n)
	    {
	    	if (n > max_size())
	    		throw std::length_error("vector::reserve");
                // belong to std::class lenght error
                // https://en.cppreference.com/w/cpp/error/length_error 
			else if (n > this->capacity())
			{
				pointer prev_start = _start;
				pointer prev_end = _end;
				size_type prev_size = size();
				size_type prev_capacity = capacity();
				
				_start = _alloc.allocate( n );
				_end_capacity = _start + n;
				_end = _start;
				while (prev_start != prev_end)
				{
					_alloc.construct(_end, *prev_start);
					_end++;
					prev_start++;
				}
				_alloc.deallocate(prev_start - prev_size, prev_capacity);
	        }
        }
        // ( 6 ) ELEMENT ACCESS   

	    reference back(){ return *(_end - 1); }
	    const_reference back() const{ return *(_end - 1); }
        
        // operator[]
        reference operator[](size_type n) { return *(_start + n); }
        const_reference operator[](size_type n) const { return *(_start + n); }
        
        // at

        reference at (size_type n)
        { 
            if (n >= this->size())
                throw(std::out_of_range("out of range"));
            return ((*this)[n]);
        }

        const reference at (size_type n) const
        {
            if (n >= this->size())
                throw(std::out_of_range("out of range"));
            return ((*this)[n]);
        }

        // front
        reference front(){ return *_start; }
        const_reference front() const { return *_start; }

        // ( 7 ) MODIFIERS
        
        // assign 
        /* std::enable_if is used to enable 
        the function overload that accepts an initializer list as an argument 
        only if the type of the elements in the initializer list can be assigned 
        to the elements of the vector. This is done to avoid ambiguities when the 
        function is called with an initializer list that contains elements of a type 
        that is different from the type of the elements in the vector.*/
        
        /* Takes two arguments of type InputIterator.
         Overload is enabled only if the type of InputIterator is not an integral type 
         (i.e., a type that is used to represent integers, such as int or long long).*/
        template <class InputIterator>  
        void assign (InputIterator first, InputIterator last
        , typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type * = 0)
        {
            // 1- clear notre ancien vector 
            clear();
            // 2 - Calculer la taille du nouveau vector
            size_type size = difference(first, last);
            // si notre capacity est > a la nouvelle taille
            // il faut désallouer pour réallouer le strict nécessaire en mémoire
            if (capacity() < size)
            {
                _alloc.deallocate(_start, capacity());
                _start = _alloc.allocate(size);
                // on initialize ici end au début du vector
                // on va lui faire prendre son emplacement exact après.
                _end = _start;
                _end_capacity = _start + size;
            }
            // On construit le nouveau vector avec la range de nombres
            // passée en paramètre.
            // On incrémente _end pour qu'il se situe à la fin du vector.
            for (InputIterator it = first; it != last; it++)
            {
                _alloc.construct(_end, *it);
                _end++;
            }
        }

        // fill the vector with a specified number of copies of a single value. 
        void assign (size_type n, const T &val) // fill version 
        {
		    clear();
		    if (capacity() >= n and n != 0)
		    	while (n--)
		    		_alloc.construct(_end++, val);
		    else if (n != 0)
		    {
		    	_alloc.deallocate(_start, capacity());
		    	_start = _alloc.allocate(n);
		    	_end = _start;
		    	_end_capacity = _start + n;
		    	while (n--)
		    	{
		    		_alloc.construct(_end, val);
		    		_end++;
		    	}
		    }
        }

        // push back()
        void push_back (const value_type& val) 
        /* add an element at the end of the vector, after its current last element
            the content of val is copied to the new element. 
            This effectively increases the container size by one,
            which causes an automatic reallocation of the allocated storage space 
            if -and only if- the new vector size surpasses the current vector capacity */
        {
        /*if (this->_end != this->_end_capacity)
        {
            _alloc.construct(_end++, val);
		}
		else
        {
          //  insert(end(), x);
		} */
            if (_end <= _end_capacity)
			{
				int next_capacity = (this->size() > 0) 
                ? (int)(this->size() * 2) 
                : 1;
				this->reserve(next_capacity);
			}
            _alloc.construct(_end, val);
            _end++;
        }

        // pop back
        void        pop_back() // remove the last element from the vector
        {
        // Decrement the size of the vector by one
        // If vector is empty : undefined behavior
           _alloc.destroy(--_end);
        }

        // insert
        iterator insert (iterator position, const value_type& val)
        {
            // 1- save l'emplacement où insérer le nouvel élément
            // -> on calcule la distance entre le début du vector et la position
            // où l'élément doit être insérer : on stocke la valeur.
            // 2 - Il faut réserver l'espace nécessaire en mémoire pour le vector + 1 elem
            // si le vector est vide, on a seulement besoin de la place pour un élément
		    difference_type offset = std::distance(begin(), position);
		    size_type offset2 = std::distance(position, end());
		    if (capacity() < size() + 1)
		    	reserve(size() > 0 ? capacity() * 2 : 1);
		    _alloc.construct(_end, val);
		    iterator it = end();
		    for (size_type i = 0; i < offset2; it--, i++)
		    	*it = *(it - 1);
		    *it = val;
		    _end++;
		    return begin() + offset;
        }

        void insert (iterator position, size_type n, const value_type& val)
        {
            ft::vector<value_type> tmp(n, val);
		    this->insert(position, tmp.begin(), tmp.end());
        }

        template <class InputIterator>    
        void insert (iterator position, InputIterator first, InputIterator last)
        {
		    size_type inputOffset = distance(first, last);
		    size_type posOffset = distance(position, end());
		    ft::vector<value_type> tmp(position, end());
		    if (capacity() < size() + inputOffset)
		    {
		    	if (this->size() == 0)
		    		reserve(this->size() + inputOffset);
		    	else
		    	{
		    		size_type i = 2;
		    		while (this->size() * i < inputOffset + this->size())
		    			i++;
		    		reserve(this->size() * i);
		    	}
		    }
		    for (size_type i = 0; i < posOffset; i++)
		    	erase(end() - 1);
		    for (size_type i = 0; i < inputOffset; i++)
		    {
		    	push_back(*first);
		    	first++;
		    }
		    for (iterator it = tmp.begin(); it < tmp.end(); it++)
		    	push_back(*it);
        }


        // erase 
        iterator erase (iterator position) // erase a single element from the vector
        {
			if (position + 1 != end()){
				for (pointer x = position.base() + 1, y = position.base(); x != this->_end; ++x, ++y){
					*y = *x;
				}
			}
			_alloc.destroy(--this->_end);
			return (position);
        }
        
        iterator erase (iterator first, iterator last) // erase a range of elements in the vector between "first" and "last"
        {
            pointer pos = first.base();
			for (pointer pos2 = last.base(); pos2 != this->_end; ++pos2, ++pos){
				*pos = *pos2;
			}
			pointer ptr = pos;
			while (ptr != this->_end){
			
				_alloc.destroy(ptr++);
			}
			this->_end = this->_end - (ptr - pos);
			return (first);
        }

        // swap 
        void	swap(vector &x)
        {
            if (x == *this)
			    return;	
			pointer save_start = x._start;
			pointer save_end = x._end;
			pointer save_end_capacity = x._end_capacity;
			allocator_type save_alloc = x._alloc;

			x._start = this->_start;
			x._end = this->_end;
			x._end_capacity = this->_end_capacity;
			x._alloc = this->_alloc;

			this->_start = save_start;
			this->_end = save_end;
			this->_end_capacity = save_end_capacity;
			this->_alloc = save_alloc;
		}

        // clear
        void    clear()
        {
		    while (_end > _start)
		    {
		    	_end--;
		    	_alloc.destroy(_end);
		    }
        }
        
        // ( 8 ) ALLOCATOR     
        allocator_type get_allocator()const { 

            return allocator_type(_alloc); 
        }
        protected:
            allocator_type _alloc; 
            pointer _start; // pointer to the first element of my vector
            pointer _end; 
            pointer _end_capacity; 
            
        // NON MEMBERS FUNTIONS OVERLOAD    
};



// RELATIONNAL OPERATORS
// Operator == 
template <class T, class Alloc>  
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
  if (lhs.size() != rhs.size()) // if size in not equal, for sure there are not equal
        return( false );
    return (equal(lhs.begin(), lhs.end(), rhs.begin()));
}

// Operator != 
template <class T, class Alloc>  
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    return(!(lhs == rhs));
}

// Operator <
template <class T, class Alloc>  
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{ 
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

// Operator <=
template <class T, class Alloc>  
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    return (!(lhs > rhs));    
}

// Operator >
template <class T, class Alloc>  
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    return (rhs < lhs);
}

// Operator =>
template <class T, class Alloc>  
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
    return (!(lhs < rhs));   
}	

// to swap content between two vectors
template <class T, class Alloc>
void swap(vector<T,Alloc>& lhs, vector<T,Alloc>& rhs )
{
	lhs.swap(rhs);
}
}
#endif