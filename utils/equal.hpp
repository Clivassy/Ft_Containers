#ifndef EQUAL_HPP
#define EQUAL_HPP

/*
** std::equal compares two ranges of elements for equality
** It returns true if the elements in the two ranges are equal,
** false otherwise.
*/
# include <cstring>
namespace ft{

	template <typename T>
	bool equal(const T *first1, const T *last1, const T *first2)
	// this function can be used only with a signe type T, it operates on raw pointers
	{
		while (first1 != last1) // pointers to the first and last element in the first range
		{
			if (*first1 != *first2) // if the element pointed are not equal, it will return false
				return (false);
			++first1;
			++first2;
		}
		return (true); // otherwise, it will return true
	}
	
	//still need to understand the difference between first fct and the second//
	// use of different type : use specified range for the firt and iterators on object for the second i guess
	template< typename InputIt1, typename InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
			while (first1 != last1)
			{
				if (*first1 != *first2)
					return (false);
				++first1;
				++first2;
			}
			return (true);
	}
}
#endif