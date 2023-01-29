#include "map.hpp"
using namespace ft;

//#include <iostream>
//#include <map>
//using namespace std;

int main() {

    map<int, int> test;

    test.begin();
    test.end();
    test.rbegin();
    test.rend();
    if (test.empty())
      std::cout << "Map is empty" << std::endl;
    else
      std::cout << "Map is NOT empty" << std::endl;

    //--------- Size() - MaxSize()
    std::cout << "size: "<< test.size() << std::endl;
    std::cout << "Max size: "<< test.max_size() << std::endl;

    //-----------------------------------------
    pair <int, int> bar;
    bar = make_pair(1,20);
    test.insert(bar);

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
    map<int, std::string> myMap;

    map<int, std::string>::value_compare val_comp = myMap.value_comp();
    if (val_comp(make_pair(4, "four"), make_pair(5, "five")))
        std::cout << "4,\"four\" is less than 5,\"five\"" << std::endl;
    else
        std::cout << "4,\"four\" is not less than 5,\"five\"" << std::endl;


    // MAKE_PAIR TEST 
   /* pair <int, int> foo;
    pair <int, int> bar;
    const pair <int, int> bar2;

    foo = make_pair(10, 20);
    bar = make_pair(1,20);


    std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
    std::cout << "bar: " << bar.first << ", " << bar.second << '\n';*/

  //  test.insert(pair<const int, int>(1, 3));
   // test.insert(std::make_pair(1,3));

}
    //test.insert(pair<int, int>(1,2));

  
  /*tree.insertNode(33);
  tree.insertNode(13);
  tree.insertNode(21);
  tree.insertNode(11);
  tree.insertNode(15);
  tree.insertNode(31);
  tree.insertNode(53);
  tree.insertNode(41);
  tree.insertNode(61);

  tree.printTree();*/
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
