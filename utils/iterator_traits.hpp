#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iterator>
# include <cstddef>

// https://en.cppreference.com/w/cpp/iterator/iterator_traits
// https://cplusplus.com/reference/iterator/iterator/

/*namespace ft {

    template <class Category, class T, class Distance = std::ptrdiff_t,
    class Pointer = T*, class Reference = T&>
    struct iterator 
    {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };

    template< class iterator > 
    struct iterator_traits{
    
        typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::pointer 				pointer;
		typedef typename iterator::reference 			reference;
		typedef typename iterator::iterator_category	iterator_category;
    };

    template< class T >
    struct iterator_traits<T*>
    {
        typedef std::ptrdiff_t	difference_type;
		typedef T	            value_type;
		typedef T	            *pointer;
		typedef	T	            &reference;
		typedef std::random_access_iterator_tag	iterator_category;
    };

    template< class T >
    struct iterator_traits< const T*>
    {
        typedef std::ptrdiff_t	difference_type;
		typedef const T	            value_type;
		typedef const T	            *pointer;
		typedef	const T	            &reference;
		typedef std::random_access_iterator_tag	iterator_category;
    };
}*/
#endif