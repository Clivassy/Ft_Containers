#ifndef STACK_HPP
#define STACK_HPP

//-- Test with other undelying containers
//#include <deque>
//#include <list>
//-----------------------------------------

//-- Default underlying container : vector
#include "./vector.hpp"

namespace ft 
{
	//template <class T, class Container = ft::vector<T> > 
	template <class T, class Container = ft::vector<T> > 
	class stack
	{
		public:
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_typE	size_type;
			typedef Container						container_type;

		protected:
			Container c;

		public:
			explicit stack(const Container& container = Container()) : c(container)
			{ }

			stack &operator=(const stack &other)
			{
				c = other.c;
				return (*this);
			};
			bool empty() const { return c.empty(); }

			size_type size() const { return c.size(); }

			value_type& top() { return c.back(); }

			const value_type& top() const { return c.back(); }

			void push(const value_type& x) { c.push_back(x); }

			void pop() { c.pop_back(); }

			//-------------------------------------------------------------
			//--------------	RELATIONNAL OPERATORS -----------------------
			//-------------------------------------------------------------
			//-- Need to access to private members of the stack such as vector elements.
			//-- Defining inside the class with friend keyword 
			// --> Allow comparison between elements stored in different vectors. 
			template <class X, class Y>
			friend bool operator==(const stack<X, Y> &x, const stack<X, Y> &y);

			template <class X, class Y>
			friend bool operator< (const stack<X, Y> &x, const stack<X, Y> &y);

			template <class X, class Y>
			friend bool operator!=(const stack<X, Y> &x, const stack<X, Y> &y);

			template <class X, class Y>
			friend bool operator> (const stack<X, Y>& x, const stack<X, Y> &y);

			template <class X, class Y>
			friend bool operator>=(const stack<X, Y>& x, const stack<X, Y> &y);

			template <class X, class Y>
			friend bool operator<=(const stack<X, Y>& x, const stack<X, Y> &y);
	};

	// -- Define relationnal operators inside the class could be sufficient
	// -- But defining them also outside provide a more flexible and maintainable implementation.
	template <class X, class Y>
	bool operator==(const ft::stack<X, Y>& lhs, const ft::stack<X, Y> &rhs)
	{
		return(lhs.c == rhs.c);
	}

	template <class X, class Y>
	bool operator!=(const ft::stack<X, Y>& lhs, const ft::stack<X, Y> &rhs)
	{
		return (lhs.c != rhs.c );
	}

	template <class X, class Y>
	bool operator<(const ft::stack<X, Y>& lhs, const ft::stack<X, Y> &rhs)
	{ 
		return (lhs.c < rhs.c);
	}
	
	template <class X, class Y>
	bool operator<=(const ft::stack<X, Y>& lhs, const ft::stack<X, Y> &rhs)
	{
		return (lhs.c <= rhs.c);
	}
	
	template <class X, class Y>
	bool operator>(const ft::stack<X, Y>& lhs, const ft::stack<X, Y> &rhs)
	{
		return (lhs.c > rhs.c);
	}
	
	template <class X, class Y>
	bool operator>=(const ft::stack<X, Y>& lhs, const ft::stack<X, Y> &rhs)
	{
		return (lhs.c >= rhs.c);
	}
}	
#endif
