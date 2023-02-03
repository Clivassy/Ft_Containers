#include <iostream>
#include "testeur.hpp"

#if 1 // create a real STL example
    #include <map>
    namespace ft = std;
#else
    #include "map.hpp" // create an example with my own vectp 
#endif

using namespace ft;


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
        printFunctionTest("operator[]");
        map<char,std::string> accessTest;

        accessTest['a']="an element";
        accessTest['b']="another element";
        accessTest['c']= accessTest['b'];

        std::cout << "mymap['a'] is " << accessTest['a'] << '\n';
        std::cout << "mymap['b'] is " << accessTest['b'] << '\n';
        std::cout << "mymap['c'] is " << accessTest['c'] << '\n';
        std::cout << "mymap['d'] is " << accessTest['d'] << '\n';

        std::cout << "mymap now contains " << accessTest.size() << " elements.\n";

        // at
        printFunctionTest("at");
        accessTest.at('a') = "I am testing my at function";
        accessTest.at('b') = "I think it is working well";
        
        std::cout << "mymap['a'] is : " << accessTest['a'] << '\n';
        std::cout << "mymap['b'] is : " << accessTest['b'] << '\n';
        try
        {
            accessTest.at('y') = "I am testing my at function";
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception throwed :  " << e.what() << '\n';
        }
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
        insertTest.insert(pair<const char, int>('Z', 6));
        insertTest.insert(pair<const char, int>('C', 30));
        insertTest.insert(pair<const char, int>('C', 45));
        insertTest.insert(pair<const char, int>('E', 65));
        insertTest.insert(pair<const char, int>('F', 85));
        for (map<const char,int>::iterator it=insertTest.begin(); it!=insertTest.end(); ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << "Size after insertion : " << insertTest.size() << std::endl;
      
        //insertTest.prinTree();

        //-- Insert Pos + Val 
        printFunctionTest("Position Insert()");
        map<const char,int>::iterator ret = insertTest.insert(insertTest.begin(), pair<const char, int>('D', 800));
        for (map<const char,int>::iterator itPos=insertTest.begin(); itPos!= ret; ++itPos)
            std::cout << itPos->first << " => " << itPos->second << '\n';
        std::cout << YELLOW " >>>>>> FOUND NEWLY INSERTED ELEMENT >>>>> " CLEAR << std::endl;
        
        //-- Range Insert(3)
        printFunctionTest("Range Insert()");
        map<const char,int> rangeInsert;
        rangeInsert.insert(insertTest.begin(), insertTest.end());
        for (map<const char,int>::iterator itRange=rangeInsert.begin(); itRange!=rangeInsert.end(); ++itRange)
            std::cout << itRange->first << " => " << itRange->second << '\n';

        //-- erase()

        //-- swap()
        printFunctionTest("Swap()");
        map<char,int> testSwap1,testSwap2;

        testSwap1['x']=100;
        testSwap1['y']=200;

        testSwap2['a']=11;
        testSwap2['b']=22;
        testSwap2['c']=33;

        testSwap1.swap(testSwap2);

        std::cout << "MAP (1)  contains:\n";
        for (map<char,int>::iterator it=testSwap1.begin(); it!=testSwap1.end(); ++it)
          std::cout << it->first << " => " << it->second << '\n';

        std::cout << std::endl;
        std::cout << "MAP (2) contains:\n";
        for (map<char,int>::iterator it=testSwap2.begin(); it!=testSwap2.end(); ++it)
          std::cout << it->first << " => " << it->second << '\n';

        //-- clear()
        printFunctionTest("Clear()");
        map<char,int> clearTest;

        clearTest['x']=100;
        clearTest['y']=200;
        clearTest['z']=300;

        std::cout << "The map contains:\n";
        for (map<char,int>::iterator it=clearTest.begin(); it!=clearTest.end(); ++it)
          std::cout << it->first << " => " << it->second << '\n';

        clearTest.clear();
        clearTest['a']=1101;
        clearTest['b']=2202;

        std::cout << std::endl;
        std::cout << "The map contains:\n";
        for (map<char,int>::iterator it=clearTest.begin(); it!=clearTest.end(); ++it)
          std::cout << it->first << " => " << it->second << '\n';
    }

    //-----------------------------------------------------------
    //-- LOOKUP
    {
        printTitle("LOOKUP TESTS");
        map< char, int> lookupTest;

        //-- count()
        printFunctionTest("Count()");
        char c;
    
        lookupTest['a']=101;
        lookupTest['c']=202;
        lookupTest['f']=303;
    
        for (c = 'a'; c < 'h'; c++)
        {
          std::cout << c;
          if (lookupTest.count(c) > 0)
            std::cout << " is an element of mymap.\n";
          else 
            std::cout << " is not an element of mymap.\n";
        }
        lookupTest.clear();

        //-- find()
        printFunctionTest("Count()");
        map<char, int>::iterator found;
        
        lookupTest['a']=50;
        lookupTest['b']=100;
        lookupTest['c']=150;
        lookupTest['d']=200;

        found = lookupTest.find('i');
        for (map<char,int>::iterator it=lookupTest.begin(); it!=found; ++it)
          std::cout << it->first << " => " << it->second << '\n';

        std::cout << "-----------------"<< std::endl;

        found = lookupTest.find('c');
        for (map<char,int>::iterator it=lookupTest.begin(); it!=found; ++it)
          std::cout << it->first << " => " << it->second << '\n';

        lookupTest.clear();
        
        //-- equal_range()




        //-- lower_bound()
        printFunctionTest("Lower_bound()");
        map<char,int>::iterator itlow, itup;

        lookupTest['a']=20;
        lookupTest['b']=40;
        lookupTest['c']=60;
        lookupTest['o']=80;
        lookupTest['x']=100;

        itlow = lookupTest.lower_bound('c');
        for (map<char,int>::iterator it=lookupTest.begin(); it!=itlow; ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << YELLOW " >>>>>> FOUND LOWER BOUND ELEMENT : KEY = " << itlow->first << " >>>>> " CLEAR << std::endl;
        
        //-- upper_bound()
        printFunctionTest("Upper_bound()");
        itup = lookupTest.upper_bound('c');
        for (map<char,int>::iterator it=lookupTest.begin(); it!=itup; ++it)
            std::cout << it->first << " => " << it->second << '\n';
        std::cout << YELLOW " >>>>>> FOUND LOWER BOUND ELEMENT : KEY = " << itup->first << " >>>>> " CLEAR << std::endl;

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
    //-- ALLOCATOR
    {
        printTitle("ALLOCATOR TESTS");
        map<int, int> m;
        std::allocator<std::pair<const int, int>> alloc = m.get_allocator();
        if (alloc == std::allocator<std::pair<const int, int>>()) {
            std::cout << "The allocator is the default allocator." << std::endl;
        } else {
            std::cout << "The allocator is not the default allocator." << std::endl;
        }
    }
}



