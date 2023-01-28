#ifndef PAIR_HPP
# define PAIR_HPP

# include <iostream>
# include <memory>

namespace ft {
	template <class T1, class T2>
	struct pair
	{
		
		typedef T1	first_type;
		typedef T2	second_type;
	
		first_type	first;
		second_type	second;
	
		pair() : first(T1()), second(T2()) {};
		
		pair(const T1& a, const T2& b) : first(a), second(b) {};
	
		template<class U, class V>
		pair(const pair< U, V >& pr) : first(pr.first), second(pr.second) {};
		
		//~pair() {};


		pair& operator= (const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		};
	};
	
	template< class T1, class T2 >
	pair<T1,T2>		make_pair( T1 t, T2 u )
	{
		return pair<T1, T2>(t, u);
	};

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) 
	{
		return ( lhs.first == rhs.first && lhs.second == rhs.second );
	};

	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs==rhs);
	};

	template <class T1, class T2>
        bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        {
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	};

	template <class T1, class T2>
	bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(rhs<lhs);
	};

	template <class T1, class T2>
	bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return rhs<lhs;
	};

	template <class T1, class T2>
	bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs<rhs);
	};
}



/*--------------------------------------------------------
PAIR: 
¨¨¨¨
	Container olding two objects of potential 
	differents types called 'first' and 'second.
----------------------------------------------------------
MAKE_PAIR:
¨¨¨¨¨¨¨¨¨
	Enable create an object of type pair< T1, T2 >
	initialized with values passed in argument.  

-----------------------------------------------------------
 TYPEDEFS:
 ¨¨¨¨¨¨¨
 	Typedefs are used by the standard template library 
	in STL to make the code more consistent and reusable.
-----------------------------------------------------------*/

/*namespace ft {

	template <class T1, class T2>
	struct pair
	{
		
		typedef T1	first_type;
		typedef T2	second_type;
	
		first_type	first;
		second_type	second;

		// Constructor by default of pair 
		pair() : first(), second() {};
		
		// Constructor with two objects passed in argument whatever there are
		pair(const T1& a, const T2& b) : first(a), second(b) {};

		// Copy constructor
		// The pair is initialized with the content of "pr".
		// The "pr" first is passed to this first
		// The "pr" second is passed to this second
		// copy constructor is only used when the type of the object
		// being copied is the same as the type of the object being initialized. 
		//template<class U, class V>
		//pair(const pair< U, V >& pr) : first(pr.first), second(pr.second) {};
		
		// Why no destructor? 

		// Overload operator
		pair& operator= (const pair& pr)
		{
			if (*this == pr)
                return (*this);
			this->first = pr.first;
			this->second = pr.second;
			return (*this);
		};
	};
	
	// Takes two arguments of type T1 and T2 
	// Returns a pair of those types
	// with the values of the arguments as the values
	// of the 'first' and 'second' members of the pair. 
	
	template< class T1, class T2 >
	pair<T1,T2>		make_pair( T1 x, T2 y )
	{
		return pair<T1, T2>(x, y);
	};

	//	RELATIONAL OPERATORS 

	// Checks if two 'pair' objects have the same value of theirs 'first' and 'second' members.
	// Returns 'true' if there are equal and 'false' if there are not. 
	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs ) 
	{
		return ( lhs.first == rhs.first && lhs.second == rhs.second );
	};

	// Returns 'true' if the 'first' and 'second' members
	// of the two 'pair' objects are not equal, returns 'false' otherwise. 
	template <class T1, class T2>
	bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs==rhs);
	};

	// Check if the first element of the left-hand side pair is 
	// smaller than the first element of the right-hand side pair
	// If true : return true 
	// -> left and side pair should come first in the sorted order. 
	// second check is here to stop comparison if there first elems are not equal.
	// If firsts eleme are equal => comparison of second to determine order.
	template <class T1, class T2>
    bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
		return ((lhs.first < rhs.first) || (!(rhs.first < lhs.first) 
			&& lhs.second < rhs.second));
	};

	// Returns true if left-hand side pair <= to the right-hand side pair
	// Returns true if both the first and second element of the left-hand side pair
	// are equal to the first and second elements og the right-hand side pair. 
	template <class T1, class T2>
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(rhs < lhs);
	};

	// Same as < in the other sens
	template <class T1, class T2>
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	};

	// Same as <= in the other sens
	template <class T1, class T2>
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) 
	{
		return !(lhs<rhs);
	};
}*/

#endif