#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

//-- random_access_iterator_tag -> used to identify iterators that belong to the random access category
//-- `T` -> value type of
template <typename T>
class random_access_iterator
{

    public:	
    //-- Iterators defined here -> iterators_traits -------------------------------------------------
    typedef typename ft::iterator<iterator_traits<T>, T >::iterator_category            iterator_category;
    typedef typename ft::iterator<iterator_traits<T>, T>::value_type                    value_type;
    typedef typename ft::iterator<iterator_traits<T>, T>::difference_type		        difference_type;
    typedef T *																		    pointer;
    typedef T &																			reference;
    
    //-- Default constructor 
    random_access_iterator() : element(NULL) { } 

    //-- Conctructor from pointer
    //-- Construct a random access iterator to the element passed in argument
    random_access_iterator(pointer elem) : element(elem) { }
    
    //-- Copy constructor
    random_access_iterator(const random_access_iterator &copy) : element(copy.element) { }

    //-- Overload operator
    random_access_iterator &operator=(const random_access_iterator &rhs)
    {
        if (this == &rhs)
		        return (*this);
        this->element = rhs.element;
        return (*this);
    }

    //-- Destructor
    virtual ~random_access_iterator() {}

    //-- Give a pointer to the element where the iterator point
    //-- Return the iterator
    pointer base() const 
    { 
        return this->element; 
    }

    //-- Dereference
    //-- Return the value pointed by the random access iterator
    reference operator*() const 
    { 
        return *this->element; 
    }
    
    //-- Return the pointer to the value 
    pointer operator->() 
    { 
        return &(this->operator*()); 
    }

    //-- Pre-increment iterator
    random_access_iterator &operator++()
    {
        this->element++;
        return (*this);
    }

    //-- Post-increment iterator
    random_access_iterator operator++(int)
    {
        random_access_iterator tmp(*this);
        operator++();
        return (tmp);
    }

    //-- Pre-decrement iterator
    random_access_iterator &operator--()
    {
        this->element--;
        return (*this);
    }

    //-- Post-decrement iterator
    random_access_iterator operator--(int)
    {
        random_access_iterator tmp(*this);
        operator--();
        return (tmp);
    }

    //-- Specific functionnality of random_access iterator:
    //      ---> which can access to any element in the container.
    // Return a random access iterator where element is point a this + n in memory
    random_access_iterator operator+(difference_type n) const
	{ return this->element + n; }

    // Return a random access iterator where element is point a this - n in memory
    random_access_iterator operator-(difference_type n) const
	{ return this->element - n; }

    //-- Return a random access iterator where the element pointed 
    //-- is at the actual pointer memory + n 
    random_access_iterator &operator+=(difference_type n)
    {
        this->element += n;
        return *this;
    }

    //-- Return a random access iterator where the element pointed 
    //-- is at the actual pointer memory - n 
    random_access_iterator &operator-=(difference_type n)
    {
        this->element -= n;
        return *this;
    }

    //-- Return a reference to the elements at an arbitrary offset position
    //-- relative to the element pointed by the random access iterator
    reference operator[](difference_type n)
	{ 
        return *(operator + (n)); 
    }

    operator random_access_iterator<const T>() const
    { 
        return random_access_iterator<const T>(this->element); 
    }

    protected:
        pointer element;
};

    //----------------------------------------------------------------------------------------------------------
    //-- RELATIONNAL OPERATORS    

    // Returns true if the pointer of lhs is equal at rhs, otherwise false. 
    template<typename T1, typename T2>
    inline bool operator==(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() == rhs.base(); }    

    template<typename T1, typename T2>
    inline bool operator!=(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() != rhs.base(); }    

    template<typename T1, typename T2>
    inline bool operator<(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() < rhs.base(); } 

    template<typename T1, typename T2>
    inline bool operator>(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() > rhs.base(); } 

    template<typename T1, typename T2>
    inline bool operator<=(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() <= rhs.base(); }    

    template<typename T1, typename T2>
    inline bool operator>=(const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() >= rhs.base(); }    

    // Returns a random access iterator pointing to n element after it pointed element
    template<typename T>
    inline ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n,
        	  typename ft::random_access_iterator<T> it)
    { return &(*it) + n; }  

    // Returns a random access iterator pointing to n element before it pointed element
    // Can only be used with iterators that operate on the same type of element.
    template<typename T1, typename T2>
    inline typename ft::random_access_iterator<T1>::difference_type operator-(const ft::random_access_iterator<T1> &lhs,
              const ft::random_access_iterator<T2> &rhs)
    { return lhs.base() - rhs.base(); }
}
#endif