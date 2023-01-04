#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft{
// definit sur la base d'une condition statitique de type void (par défaut)
	template<bool B, typename T = void> 
	struct enable_if
	{
		
	};

	template<typename T>
	struct	enable_if<true, T>{

		typedef T type;
	};
}
#endif