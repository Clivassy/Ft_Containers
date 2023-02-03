#ifndef TESTEUR_HPP
#define TESTEUR_HPP

//-------- Colors ------------
#define CLEAR "\e[0m"
#define YELLOW "\e[33m"
#define REDCOLOR "\e[0;31m"
#define GREEN "\e[0;32m"
#define CYAN "\e[0;36m"
# define BLUE  "\x1B[34m"
# define MAGENTA  "\x1B[35m"
#include <iostream>


void    printTitle( std::string title)
{
    std::cout << std::endl;
    std::cout << CYAN "--------------------------------" CLEAR << std::endl;
    std::cout << GREEN "         " << title << "        " CLEAR << std::endl;
    std::cout << CYAN "--------------------------------" CLEAR << std::endl;
    std::cout << std::endl;
}

void    printFunctionTest( std::string functionName)
{
    std::cout << std::endl;
    std::cout << MAGENTA << "--  " << functionName << CLEAR<<  std::endl;
    std::cout << std::endl;
}

#endif