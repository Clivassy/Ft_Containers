#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft 
{
	//-- 'B': bolean value that determines whether specialization should be 
	//-- enable or not.
	//-- 'T' : type used if specialization is enabled
	template<bool B, typename T = void> 
	struct enable_if { };
	
	template<typename T> 
	struct	enable_if<true, T> { typedef T type; };
}
#endif