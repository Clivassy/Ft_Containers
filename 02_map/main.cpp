#include "map.hpp"
using namespace ft;

//#include <iostream>
//#include <map>
//using namespace std;

int main() {

    map<int, int> test;

    //////////////////////////////////////////////////////////////
    // ITERATORS
    std::cout << std::endl;
    std::cout << "------- ITERATORS TESTS--------" << std::endl;
    std::cout << std::endl;
    test.begin();
    test.end();
    test.rbegin();
    test.rend();
    //////////////////////////////////////////////////////////////
    // CAPACITY
    std::cout << std::endl;
    std::cout << "------- CAPACITY TESTS--------" << std::endl;
    std::cout << std::endl;
    if (test.empty())
      std::cout << "Map is empty" << std::endl;
    else
      std::cout << "Map is NOT empty" << std::endl;

    //--------- Size() - MaxSize()
    std::cout << "size: "<< test.size() << std::endl;
    std::cout << "Max size: "<< test.max_size() << std::endl;

    //////////////////////////////////////////////////////////////
    // PAIR
    std::cout << std::endl;
    std::cout << "------- PAIR TESTS--------" << std::endl;
    std::cout << std::endl;
    //-----------------------------------------
    pair <int, int> bar;
    bar = make_pair(1,20);
   // test.insert(bar);

    //////////////////////////////////////////////////////////////
    // OBSERVERS
    std::cout << std::endl;
    std::cout << "------- OBSERVERS TESTS--------" << std::endl;
    std::cout << std::endl;
    //--------------------------------
    // Key_comp test 
    //---------------------------------
    // will print "4 is less than 5" because 4 is 
    // less than 5 according to the default comparison 
    // function (which is std::less<int>)
    //-------------------------------- 
    map<int, std::string> myMap1;
 
    map<int, std::string>::key_compare comp = myMap1.key_comp();
    if (comp(14, 5))
        std::cout << "4 is less than 5" << std::endl;
    else
        std::cout << "4 is not less than 5" << std::endl;

    //--------------------------------
    // Value_compare test 
    //---------------------------------
    // will print "4 is less than 5" because 4 is 
    // less than 5 according to the default comparison 
    // function (which is std::less<int>)
    //-------------------------------- 
    /*map<int, std::string> myMap;

    map<int, std::string>::value_compare val_comp = myMap.value_comp();
    if (val_comp(make_pair(4, "four"), make_pair(5, "five")))
        std::cout << "4,\"four\" is less than 5,\"five\"" << std::endl;
    else
        std::cout << "4,\"four\" is not less than 5,\"five\"" << std::endl;*/
    //////////////////////////////////////////////////////////////
    // INSERT
    std::cout << std::endl;
    std::cout << "------- INSERT TESTS--------" << std::endl;
    std::cout << std::endl;
    std::cout << "Size before insertion : " << test.size() << std::endl;
    test.insert(pair<const int, int>(1, 12));
    test.insert(pair<const int, int>(1, 6));
    test.insert(pair<const int, int>(6, 30));
    test.insert(pair<const int, int>(4, 45));
    test.insert(pair<const int, int>(2, 65));
    test.insert(pair<const int, int>(2, 85));
    std::cout << "Size after insertion : " << test.size() << std::endl;
    test.prinTree();
    
    map<int,int>::iterator itlow;
    itlow = test.lower_bound(2);


    map<int,int> mymap;
    mymap.insert(test.begin(), test.end()); 


   // test.insert(std::make_pair(1,3));
    //test.insert(pair<int, int>(1,2));
}

  
//}
// Fill constructor 
/*
int main() {
    std::pair<std::string, int> data[] = { {"apple", 1}, {"banana", 2}, {"cherry", 3} };
    std::map<std::string, int> myMap(data, data + 3);

    for(const auto& elem : myMap) {
        std::cout << elem.first << " : " << elem.second << std::endl;
    }
    return 0;
}
*/
