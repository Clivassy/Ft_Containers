#include <iostream>
#include "../utils/testeur.hpp"

#if 0 // create a real STL example
    #include <set>
    namespace ft = std;
#else
    #include "set.hpp" // create an example with my own vectp 
#endif

using namespace ft;
#include <chrono>
using namespace std::chrono;

int main() 
{
    //-----------------------------------------------------------
    //-- CONSTRUCTORS
    set<int> testConstructor;
    set<int>::iterator ite = testConstructor.begin();
	*ite = 42;
    return (0);
}