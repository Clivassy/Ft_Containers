#ifndef UTILS_HPP
#define UTILS_HPP

#include "iterators.hpp"
#include <typeinfo>

namespace ft{

	template<typename Iter>
	typename iterator_traits<Iter>::difference_type distance(Iter first, Iter last){

		typename iterator_traits<Iter>::difference_type n = 0;
		while (first++ != last){

			++n;
		}
		return (n);
	}

	template<typename Tp>
	struct less{

		bool	operator()(const Tp &lhs, const Tp &rhs)const{

			return (lhs < rhs);
		}
	};

	template<typename Tp>
	void	swap(Tp &x, Tp &y){

		Tp	tmp(x);
		x = y;
		y = tmp;
	}

	template<typename Tp>
	const Tp	&max(const Tp &x, const Tp &y){

		return ((x < y) ? y : x);
	}

	template<typename T>
	class avlNode{

		public:
			typedef T	value_type;
			int			bf;
			value_type	*data;
			avlNode<T>	*left;
			avlNode<T>	*right;
			avlNode<T>	*parent;
			int			height;
			
			avlNode() : data(NULL), left(NULL), right(NULL), parent(NULL), height(0) 
			{}
			avlNode(value_type val) : data(val), left(NULL), right(NULL), parent(NULL), height(0) 
			{}
			avlNode(const avlNode &nd) : data(nd.data), left(nd.left), right(nd.right), parent(nd.parent)/* , height(nd.height), bf(nd.bf) */ 
			{}
			~avlNode() {}
			avlNode	&operator=(const avlNode &cp){

				this->bf = cp.bf;
				this->data = cp.data;
				this->left = cp.left;
				this->right = cp.right;
				this->parent = cp.parent;
				this->height = cp.height;
				
				return (*this);
			}
	};
	
	template<typename T>
	bool	operator==(const avlNode<T> &x, const avlNode<T> &y){

		if (x.data == NULL && y.data == NULL)
			return (true);
		return (x.data == y.data);
	}
	
	template<typename T>
	bool	operator!=(const avlNode<T> &x, const avlNode<T> &y){
		
		return (!(x.data == y.data));
	}

	// template<typename T>
	// struct less : std::binary_function<T, T, bool>{

	// 	bool	operator()(const T &x, const T &y)const{

	// 		return (x < y);
	// 	}
	// };	
}

#endif