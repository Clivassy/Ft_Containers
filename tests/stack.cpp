#include <iostream>
#include "../utils/testeur.hpp"

#if 0 // create a real STL example
    #include <stack>
    namespace ft = std;
#else
    #include "../stack.hpp" // create an example with my own vectp 
#endif

using namespace ft;


int main()
{
    //-----------------------------------------------------------
    //-- CONSTRUCTORS
    {
        printTitle("CONSTRUCTORS TESTS");
        printFunctionTest("Default Construtor");
        stack<int>test1;
        std::cout << GREEN << " <<<<<<< SUCCESS >>>>>>>>>" << std::endl;
        printFunctionTest("Copy Construtor");
        stack<int>test2(test1);
        std::cout << GREEN << " <<<<<<< SUCCESS >>>>>>>>>" << std::endl;
    }

    printTitle("MEMBERS FUNCTIONS TESTS");
    //-----------------------------------------------------------
    //-- MEMBER FUNCTIONS
    {
        //-- Empty()
        printFunctionTest("Empty");
        stack<int> mystack;
        int sum (0);
        for (int i=1;i<=10;i++) mystack.push(i);
        while (!mystack.empty())
        {
           sum += mystack.top();
           mystack.pop();
        }
        std::cout << "total: " << sum << '\n';
        //-------------------------------------------------------

        //-- Size()
        printFunctionTest("Size");
        stack<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<5; i++) myints.push(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.pop();
        std::cout << "2. size: " << myints.size() << '\n';

        //-------------------------------------------------------
        //-- Top()
        printFunctionTest("Top");
        {
            stack<int> mystack;

            mystack.push(10);
            mystack.push(20);

            mystack.top() -= 5;

            std::cout << "mystack.top() is now " << mystack.top() << '\n';
        }
        //-------------------------------------------------------
        //-- Push()
        printFunctionTest("Push");
        {
            stack<int> mystack;

            for (int i=0; i<5; ++i) mystack.push(i);

            std::cout << "Popping out elements...";
            while (!mystack.empty())
            {
               std::cout << ' ' << mystack.top();
               mystack.pop();
            }
            std::cout << '\n';
        }
        //-------------------------------------------------------
        //-- Pop()
        printFunctionTest("Pop");
        {
            stack<int> mystack;

            for (int i=0; i<5; ++i) mystack.push(i);
            std::cout << "Popping out elements...";
            while (!mystack.empty())
            {
               std::cout << ' ' << mystack.top();
               mystack.pop();
            }
            std::cout << '\n';
        }

        //-------------------------------------------------------
        //-- TESTING STACK CANNOT BE ITERATE 
        //    stack<int>::iterator;

    return (0);
    }
}