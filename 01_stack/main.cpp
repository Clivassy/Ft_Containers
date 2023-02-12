#include "stack.hpp"
#include <iostream>
#include <deque>
#include "../00_vector/vector.hpp"
#include "../utils/testeur.hpp"

#if 0 // create a real STL example
    #include <stack>
    namespace ft = std;
#else
    #include "stack.hpp" // create an example with my own vectp 
#endif

#include <chrono>
using namespace ft;
using namespace std::chrono;

int main()
{
    //-----------------------------------------------------------
    //-- CONSTRUCTORS
   /* printTitle("CONSTRUCTORS TESTS");
    printFunctionTest("Default Construtor");

    std::deque<int> mydeque(3,100);          // deque with 3 elements
    vector<int> myvector (2,200);        // vector with 2 eleme
    stack<int> first;                    // empty stack
    stack<int> second(mydeque);         // stack initialized to copy of deque
    stack<int,vector<int> > third;  // empty stack using vector
    stack<int,vector<int> > fourth (myvector);

    std::cout << "size of first: " << first.size() << '\n';
    std::cout << "size of second: " << second.size() << '\n';
    std::cout << "size of third: " << third.size() << '\n';
    std::cout << "size of fourth: " << fourth.size() << '\n';*/

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
        {
            stack<int> mystack;

            mystack.push(10);
            mystack.push(20);

            mystack.top() -= 5;

            std::cout << "mystack.top() is now " << mystack.top() << '\n';
        }
        //-------------------------------------------------------
        //-- Push()
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
    return (0);
    }
}