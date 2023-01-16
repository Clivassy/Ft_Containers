#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

	template <class T, class Container = ft::vector<T> >
	class stack {	

	public:	
		typedef typename Container::value_type	value_type;	
		typedef typename Container::size_type	size_type;	
		typedef Container						container_type;	

	protected:	
		container_type container;	

	public:		
		explicit	
		stack(const Container & container = Container())	
			: container(container)	
		{}	

		bool	
		empty()	
		const	
		{ return container.empty(); }	

		size_type	
		size()	
		const	
		{ return container.size(); }	

		value_type &	
		top()	
		{ return container.back(); }	

		const	
		value_type &	
		top()	
		const	
		{ return container.back(); }	

		void	
		push(const value_type &x)	
		{ container.push_back(x); }	

		void	
		pop()	
		{ container.pop_back(); }	

		template <class _T, class _Container>	
		friend	
		bool	
		operator==(const stack<_T, _Container> &lhs,	
				   const stack<_T, _Container> &rhs);	

		template <class _T, class _Container>	
		friend	
		bool	
		operator<(const stack<_T, _Container> &lhs,	
				  const stack<_T, _Container> &rhs);	

		template <class _T, class _Container>	
		friend	
		bool	
		operator!=(const stack<_T, _Container> &lhs,	
				   const stack<_T, _Container> &rhs);	

		template <class _T, class _Container>	
		friend	
		bool	
		operator>(const stack<_T, _Container> &lhs,	
				  const stack<_T, _Container> &rhs);	

		template <class _T, class _Container>	
		friend	
		bool	
		operator>=(const stack<_T, _Container> &lhs,	
				   const stack<_T, _Container> &rhs);	

		template <class _T, class _Container>	
		friend bool operator<=(const stack<_T, _Container> &lhs,	
			   const stack<_T, _Container> &rhs);	

};

// RELATIONAL OPERATORS 
	template <class _T, class _Container>
	inline bool
	operator==(const ft::stack<_T, _Container>& lhs,
			   const ft::stack<_T, _Container>& rhs)
	{ return lhs.container == rhs.container; }

	template <class _T, class _Container>
	inline bool
	operator!=(const ft::stack<_T, _Container>& lhs,
			   const ft::stack<_T, _Container>& rhs)
	{ return lhs.container != rhs.container; }

	template <class _T, class _Container>
	inline bool
	operator<(const ft::stack<_T, _Container>& lhs,
			  const ft::stack<_T, _Container>& rhs)
	{ return lhs.container < rhs.container; }

	template <class _T, class _Container>
	inline bool
	operator<=(const ft::stack<_T, _Container>& lhs,
			   const ft::stack<_T, _Container>& rhs)
	{ return lhs.container <= rhs.container; }	

	template <class _T, class _Container>
	inline bool
	operator>(const ft::stack<_T, _Container>& lhs,
			  const ft::stack<_T, _Container>& rhs)
	{ return lhs.container > rhs.container; }

	template <class _T, class _Container>
	inline bool
	operator>=(const ft::stack<_T, _Container>& lhs,
			   const ft::stack<_T, _Container>& rhs)
	{ return lhs.container >= rhs.container; }	
	
}

#endif