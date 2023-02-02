#include "testeur.hpp"

#include "map.hpp"
using namespace ft;

//#include <iostream>
//#include <map>
//using namespace std;

int main() {

    //-----------------------------------------------------------
    //-- CONSTRUCTORS
    {
        printTitle("CONSTRUCTORS TESTS");
        printFunctionTest("Default Construtor");

        map<char, int> defaultConstructor;
        defaultConstructor.insert(pair<const int, int>('A', 12));
        defaultConstructor.insert(pair<const int, int>('B', 6));
        defaultConstructor.insert(pair<const int, int>('C', 30));
        
        map<char,int>::iterator it;
        for (it=defaultConstructor.begin(); it!=defaultConstructor.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';

        printFunctionTest("Range Construtor");
        map<char,int> rangeConstructor (defaultConstructor.begin(),defaultConstructor.end());


        printFunctionTest("Copy Construtor");
        map<char,int> copyConstructor (rangeConstructor);
       
        map<char,int>::reverse_iterator rit;
        for (rit=copyConstructor.rbegin(); rit!=copyConstructor.rend(); ++rit)
            std::cout << rit->first << " => " << rit->second << '\n';
    }

    {
    //-----------------------------------------------------------
    //-- ITERATORS
        printTitle("ITERATORS TESTS");
        printFunctionTest("Begin and End");

        map<char, int> iteratorTest;
        iteratorTest.insert(pair<const char, int>('A', 100));
        iteratorTest.insert(pair<const char, int>('B', 200));
        iteratorTest.insert(pair<const char, int>('C', 300));
        for (map<char,int>::iterator it=iteratorTest.begin(); it!=iteratorTest.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        
        printFunctionTest("Rbegin and Rend");
        map<char, int> reverseIteratorTest;
        reverseIteratorTest.insert(pair<const char, int>('A', 100));
        reverseIteratorTest.insert(pair<const char, int>('B', 200));
        reverseIteratorTest.insert(pair<const char, int>('C', 300));
        
        map<char,int>::reverse_iterator rit;
        for (rit=reverseIteratorTest.rbegin(); rit!=reverseIteratorTest.rend(); ++rit)
            std::cout << rit->first << " => " << rit->second << '\n';
    }
    
    //-----------------------------------------------------------
    //-- CAPACITY
    {
        printTitle("CAPACITY TESTS");
        printFunctionTest("Empty()");

        map<char,int> capacityTest;
        if (capacityTest.empty())
          std::cout << "Map is empty" << std::endl;
        else
            std::cout << "Map is NOT empty" << std::endl;

        capacityTest.insert(pair<const char, int>('A', 10));
        capacityTest.insert(pair<const char, int>('B', 20));

        if (capacityTest.empty())
            std::cout << "Map IS empty" << std::endl;
        else
          std::cout << "Map is NOT empty" << std::endl;

        printFunctionTest("Size()");
        std::cout << "Size of Map: "<< capacityTest.size() << std::endl;
        std::cout << "Max size of Map: "<< capacityTest.max_size() << std::endl;
    }
    //-----------------------------------------------------------
    //-- ELEMENT ACCESS
    {
        printTitle("ELEMENT ACCESS TESTS");
    }


    //-----------------------------------------------------------
    //-- MODIFIERS
    {
        printTitle("MODIFIERS TESTS");
        map<const char, int> insertTest;

        printFunctionTest("Insert() with Val");
        //-- Insert (1)
        std::cout << "Size before insertion : " << insertTest.size() << std::endl;
        std::cout << "Map contains :" << std::endl;
        insertTest.insert(pair<const char, int>('A', 12));
        insertTest.insert(pair<const char, int>('B', 6));
        insertTest.insert(pair<const char, int>('C', 30));
        insertTest.insert(pair<const char, int>('C', 45));
        insertTest.insert(pair<const char, int>('E', 65));
        insertTest.insert(pair<const char, int>('F', 85));
        for (map<const char,int>::iterator it=insertTest.begin(); it!=insertTest.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "Size after insertion : " << insertTest.size() << std::endl;
      
        // insertTest.prinTree();

        //-- Insert Pos + Val 
        printFunctionTest("Position Insert()");
        map<const char,int>::iterator ret = insertTest.insert(insertTest.begin(), pair<const char, int>('D', 800));
        for (map<const char,int>::iterator itPos=insertTest.begin(); itPos!= ret; ++itPos)
            std::cout << itPos->first << " => " << itPos->second << '\n';
        std::cout << YELLOW " >>>>>> FOUD NEWLY INSERTED ELEMENT >>>>> " CLEAR << std::endl;
        
        //-- Range Insert(3)
        printFunctionTest("Range Insert()");
        map<const char,int> rangeInsert;
        rangeInsert.insert(insertTest.begin(), insertTest.end());
        for (map<const char,int>::iterator itRange=rangeInsert.begin(); itRange!=rangeInsert.end(); ++itRange)
            std::cout << itRange->first << " => " << itRange->second << '\n';
    }

    //-----------------------------------------------------------
    //-- OBSERVERS
    {
        printTitle("OBSERVERS TESTS"); 
        map<int, std::string> observerTest;

        //-- Key_comp()
        printFunctionTest("key_comp()");  
        map<int, std::string>::key_compare comp = observerTest.key_comp();
        if (comp(14, 5))
            std::cout << "4 is less than 5" << std::endl;
        else
            std::cout << "4 is not less than 5" << std::endl;
        
        //-- Value_comp()
        printFunctionTest("key_comp()"); 
        map<int, std::string>::value_compare val_comp = observerTest.value_comp();
        if (val_comp(make_pair(4, "four"), make_pair(5, "five")))
            std::cout << "4,\"four\" is less than 5,\"five\"" << std::endl;
        else
            std::cout << "4,\"four\" is not less than 5,\"five\"" << std::endl;
    }
    //-----------------------------------------------------------
    //-- OPERATIONS
    {
        printTitle("OPERATIONS TESTS");
    }

    //-----------------------------------------------------------
    //-- ALLOCATOR
    {
        printTitle("ALLOCATOR TESTS");
    }
}