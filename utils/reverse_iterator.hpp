#ifndef REVERSE_IterATOR_HPP
# define REVERSE_IterATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{
    template <typename Iterator>
    struct reverse_Iterator : public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
	    typename ft::iterator_traits<Iterator>::value_type,
	    typename ft::iterator_traits<Iterator>::difference_type,
	    typename ft::iterator_traits<Iterator>::pointer,
	    typename ft::iterator_traits<Iterator>::reference>
    {

    protected:
	    Iterator								element;
	    typedef ft::iterator_traits<Iterator>	traits_type;

    public:
	    typedef Iterator								Iterator_type;
	    typedef typename traits_type::difference_type	difference_type;
	    typedef typename traits_type::pointer			pointer;
	    typedef typename traits_type::reference			reference;

	    reverse_Iterator(): element() { }

	    explicit reverse_Iterator(Iterator_type it) : element(it) { }

	    reverse_Iterator(const reverse_Iterator &it) : element(it.element) { }

    // what is Iterator2?
	    template <typename Iterator2>
	    reverse_Iterator(const reverse_Iterator<Iterator2> &it) : element(it.base()) { }

	    Iterator_type base() const { return this->element; }

	    reference operator*() const
	    {
	    	Iterator tmp = this->element;
	    	return *--tmp;
	    }

	    pointer operator->() const { return &(operator*()); }

	    reverse_Iterator &operator++()
	    {
	    	--this->element;
	    	return *this;
	    }

	    reverse_Iterator operator++(int)
	    {
	    	reverse_Iterator tmp = *this;
	    	--this->element;
	    	return tmp;
	    }

	    reverse_Iterator &operator--()
	    {
	    	++this->element;
	    	return *this;
	    }

	    reverse_Iterator operator--(int)
	    {
	    	reverse_Iterator tmp = *this;
	    	++this->element;
	    	return tmp;
	    }

	    reverse_Iterator operator+(difference_type n) const
	    { return reverse_Iterator(this->element - n); }

	    reverse_Iterator &operator+=(difference_type n)
	    {
	    	this->element -= n;
	    	return *this;
	    }

	    reverse_Iterator operator-(difference_type n) const
	    { return reverse_Iterator(this->element + n); }

	    reverse_Iterator &operator-=(difference_type n)
	    {
	    	this->element += n;
	    	return *this;
	    }

	    reference operator[](difference_type n) const { return *(*this + n); }

};

// RELATIONAL OPERATORS 

// Returns true if the pointer of lhs is equal at rhs, otherwise false. 
template <typename Iterator>
inline bool operator==(const reverse_Iterator<Iterator> &lhs, const reverse_Iterator<Iterator> &rhs)
{ return lhs.base() == rhs.base(); }

template<typename Iterator1, typename Iterator2>
inline bool	operator==(const reverse_Iterator<Iterator1> &lhs, const reverse_Iterator<Iterator2> &rhs)
{ return (lhs.base() == rhs.base()); }

template<typename Iterator>
inline bool	operator!=(const reverse_Iterator<Iterator> &lhs, const reverse_Iterator<Iterator> &rhs){
	return (lhs.base() != rhs.base());
}

template<typename Iterator1, typename Iterator2>
inline bool	operator!=(const reverse_Iterator<Iterator1> &lhs, const reverse_Iterator<Iterator2> &rhs){
	return (lhs.base() != rhs.base());
}

template<typename Iterator>
inline bool	operator<(const reverse_Iterator<Iterator> &lhs, const reverse_Iterator<Iterator> &rhs){
	return (lhs.base() > rhs.base());
}

template<typename Iterator1, typename Iterator2>
inline bool	operator<(const reverse_Iterator<Iterator1> &lhs, const reverse_Iterator<Iterator2> &rhs){
	return (lhs.base() > rhs.base());
}

template<typename Iterator>
inline bool	operator<=(const reverse_Iterator<Iterator> &lhs, const reverse_Iterator<Iterator> &rhs){
	return (lhs.base() >= rhs.base());
}
template<typename Iterator1, typename Iterator2>
bool	operator<=(const reverse_Iterator<Iterator1> &lhs, const reverse_Iterator<Iterator2> &rhs){
	return (lhs.base() >= rhs.base());
}
template<typename Iterator>
bool	operator>(const reverse_Iterator<Iterator> &lhs, const reverse_Iterator<Iterator> &rhs){
	return (lhs.base() < rhs.base());
}

template<typename Iterator1, typename Iterator2>
inline bool	operator>(const reverse_Iterator<Iterator1> &lhs, const reverse_Iterator<Iterator2> &rhs){
	return (lhs.base() < rhs.base());
}

template<typename Iterator>
inline bool	operator>=(const reverse_Iterator<Iterator> &lhs, const reverse_Iterator<Iterator> &rhs){
	return (lhs.base() <= rhs.base());
}

template<typename Iterator1, typename Iterator2>
inline bool	operator>=(const reverse_Iterator<Iterator1> &lhs, const reverse_Iterator<Iterator2> &rhs){
	return (lhs.base() <= rhs.base());
}

template <typename Iterator>
inline reverse_Iterator<Iterator>
operator+(typename reverse_Iterator<Iterator>::difference_type n,
		  const reverse_Iterator<Iterator> &it){
	return (reverse_Iterator<Iterator>(it.base() - n));
}

template<typename Iterator1, typename Iterator2>
inline typename reverse_Iterator<Iterator1>::difference_type operator-(const reverse_Iterator<Iterator1>& lhs,
		  const reverse_Iterator<Iterator2>& rhs)
{ return rhs.base() - lhs.base(); }

}
#endif