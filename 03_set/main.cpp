#include <iostream>
#include "../utils/testeur.hpp"
#include <time.h>

#if  0// create a real STL example
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
    clock_t t;
    t = clock();
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
        set<int> testIterator;
        testIterator.insert(10);
        testIterator.insert(15);
        testIterator.insert(17);
        testIterator.insert(7);
        testIterator.insert(8);
        testIterator.insert(5);

        std::cout << "<<<<<< TREE >>>>>>>" << std::endl;
        for (set<int>::iterator it = testIterator.begin() ; it != testIterator.end(); it++)
        {
            std::cout << *it << " | " ;
        }

        std::cout << std::endl;
        set<int>::iterator test;
        test = testIterator.find(17);
        std::cout << *test << std::endl;
        test++;
        if (test == testIterator.end())
            std::cout << GREEN << "<<<<<< SUCCESS >>>>>>>" << CLEAR << std::endl;
    }

    //-----------------------------------------------------------
    //-- CAPACITY
    printTitle("CAPACITY TESTS");

    //-----------------------------------------------------------
    {
        printFunctionTest("empty");
        set<int> myset;
        myset.insert(20);
        myset.insert(30);
        myset.insert(10);

        std::cout << "myset contains:";
        while (!myset.empty())
        {
           std::cout << ' ' << *myset.begin();
           myset.erase(myset.begin());
        }
        std::cout << '\n';
    }
    //-----------------------------------------------------------
    {
        printFunctionTest("size");
        set<int> myints;
        std::cout << "0. size: " << myints.size() << '\n';

        for (int i=0; i<10; ++i) myints.insert(i);
        std::cout << "1. size: " << myints.size() << '\n';

        myints.insert (100);
        std::cout << "2. size: " << myints.size() << '\n';

        myints.erase(5);
        std::cout << "3. size: " << myints.size() << '\n';
    }
    //-----------------------------------------------------------
    {
        printFunctionTest("Max size");
        int i;
        set<int> myset;

        if (myset.max_size()>1000)
        {
          for (i=0; i<1000; i++) myset.insert(i);
          std::cout << "The set contains 1000 elements.\n";
        }
        else std::cout << "The set could not hold 1000 elements.\n";
    }
    //-----------------------------------------------------------
    //-- MODIFIERS
    printTitle("MODIFIERS TESTS");
    {
        printFunctionTest("Insert");
        set<int> myset;
        set<int>::iterator it;
        pair<set<int>::iterator,bool> ret;
        for (int i=1; i<=5; ++i) myset.insert(i*10);
        
        ret = myset.insert(20);

        if (ret.second==false) it=ret.first;

        myset.insert (it,25);        
        myset.insert (it,24); 
        myset.insert (it,26);                 

        int myints[]= {5,10,15}; 
        myset.insert (myints,myints+3);

        std::cout << "myset contains:";
        for (it=myset.begin(); it!=myset.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
    }
    {
        printFunctionTest("Erase");
        set<int> myset;
        set<int>::iterator it;

        for (int i=1; i<10; i++) myset.insert(i*10);

        it = myset.begin();
        ++it; 

        myset.erase (it);

        myset.erase (40);

        it = myset.find (60);
        myset.erase (it, myset.end());

        std::cout << "myset contains:";
        for (it=myset.begin(); it!=myset.end(); ++it)
          std::cout << ' ' << *it;
        std::cout << '\n';
    }
    {
        printFunctionTest("Swap");
        int myints[]={12,75,10,32,20,25};
        set<int> first (myints,myints+3);     // 10,12,75
        set<int> second (myints+3,myints+6);  // 20,25,32

        first.swap(second);

        std::cout << "first contains:";
        for (set<int>::iterator it=first.begin(); it!=first.end(); ++it)
          std::cout << ' ' << *it;
        std::cout << '\n';

        std::cout << "second contains:";
        for (set<int>::iterator it=second.begin(); it!=second.end(); ++it)
          std::cout << ' ' << *it;
        std::cout << '\n';

    }

    {
        printFunctionTest("Clear");
        set<int> myset;

        myset.insert (100);
        myset.insert (200);
        myset.insert (300);

        std::cout << "myset contains:";
        for (set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
          std::cout << ' ' << *it;
        std::cout << '\n';

                myset.clear();
        myset.insert (1101);
        myset.insert (2202);

        std::cout << "myset contains:";
        for (set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
          std::cout << ' ' << *it;
        std::cout << '\n';
    }

    //-----------------------------------------------------------
    //-- OBSERVERS
    {
        printTitle("OBSERVERS TESTS");

    }


    //-----------------------------------------------------------
    //-- OPERATIONS
    printTitle("OPERATIONS TESTS");

    //-----------------------------------------------------------
    //-- ALLOCATOR
    printTitle("ALLOCATOR TESTS");
    
    
    
    //-----------------------------------------------------------
    //-- COMPLEXITY

    //t = clock() - t;
    //double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    //printTitle("COMPLEXITY TESTS");
    //std::cout << YELLOW <<  "Programm took  = " << time_taken << " seconds to execute \n" << CLEAR << std::endl;
    return (0);
}