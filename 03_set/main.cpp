#include <iostream>
#include "../utils/testeur.hpp"

#if 0 // create a real STL example
    #include <set>
    namespace ft = std;
#else
    #include "set.hpp" // create an example with my own vectp 
#endif

using namespace ft;
bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main() 
{
    //-----------------------------------------------------------
    //-- CONSTRUCTORS
    {
        printTitle("CONSTRUCTORS TESTS");
        printFunctionTest("Default Construtor");
        set<int> first; 
        std::cout << GREEN << "<<<<<<<< SUCCESS >>>>>>>>>" << std::endl;
        //---------------------------------------------------------------

        int myints[]= {10,20,30,40,50};
        printFunctionTest("Range Construtor");
        set<int> second (myints,myints+5);
        std::cout << GREEN << "<<<<<<<< SUCCESS >>>>>>>>>" << std::endl;
        //---------------------------------------------------------------
        
        printFunctionTest("Copy Construtor");
        set<int> third (second);
        std::cout << GREEN << "<<<<<<<< SUCCESS >>>>>>>>>" << std::endl;

        printFunctionTest("Construtor with custom compare class");
        set<int> fourth (second.begin(), second.end());
        set<int,classcomp> fifth;
        std::cout << GREEN << "<<<<<<<< SUCCESS >>>>>>>>>" << std::endl;
        
        printFunctionTest("Construtor with function pointer as compare class");
        bool(*fn_pt)(int,int) = fncomp;
        set<int,bool(*)(int,int)> sixth (fn_pt);
        std::cout << GREEN << "<<<<<<<< SUCCESS >>>>>>>>>" << std::endl;
    }
    //-----------------------------------------------------------
    //-- ITERATORS
    {
        printTitle("ITERATORS TESTS");

    }

    //-----------------------------------------------------------
    //-- CAPACITY

    //-----------------------------------------------------------
    //-- MODIFIERS

    //-----------------------------------------------------------
    //-- OBSERVERS

    //-----------------------------------------------------------
    //-- OPERATIONS

    //-----------------------------------------------------------
    //-- ALLOCATOR

    return (0);
}