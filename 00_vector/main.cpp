#include "Vector.hpp"

using namespace ft;
/*int main()
{
    vector<int> tab; // constructor by default

    tab.push_back(5);
    tab.push_back(15);
    tab.push_back(50);
    for (int i = 0; i < 3; i++)
    {
        std::cout << tab._start[i] << std::endl; // on est sur le first elem
    }
    tab.pop_back();
    for (int i = 0; i < 3; i++)
    {
        std::cout << tab._start[i] << std::endl; // on est sur le first elem
    }*/
   /* vector<int> arr(5, 10); // creation d'un vector de 5 elements qui ont la valeur de 1.
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr._start[i] << std::endl; // on est sur le first elem
    }
    std::cout << "----------------------------" << std::endl;
    arr.push_back(5);
    arr.push_back(15);
    arr.push_back(50);
    
    std::cout << "------------ Before pop back ----------------" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << arr._start[i] << std::endl; // on est sur le first elem
    }
    arr.pop_back();
    
    std::cout << "------------ After pop back ----------------" << std::endl;
    for (int i = 0; i < 8; i++)
    {
        std::cout << arr._start[i] << std::endl; // on est sur le first elem
    }
    return (0);*/
//}


/*#include <vector>
#include <iostream>
int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };
 
    std::vector<int> vec(std::begin(arr), std::end(arr));
 
    // or do initialize like this
    // std::vector<int> vec(arr, arr + sizeof(arr)/sizeof(int));
 
    for (int i: vec) {
        std::cout << i << ' ';
    }
    return 0;
}*/

template <typename T>
void testPopBack(vector<T>& vec, T expected, std::size_t expectedSize) {
  vec.pop_back();
  T lastElement = vec.empty() ? T() : vec.back();
  std::size_t size = vec.size();
  if (lastElement == expected && size == expectedSize) {
    std::cout << "Test passed" << std::endl;
  } else {
    std::cout << "Test failed: got last element " << lastElement << ", expected " << expected << "; got size " << size << ", expected " << expectedSize << std::endl;
  }
}

int main() {
  vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);

  // Test removing the last element from the vector
  testPopBack(vec, 3, 3);  // should print "Test passed"

  // Test removing the last element from an empty vector
  testPopBack(vec, 2, 2);  // should print "Test failed: got last element 2, expected 0; got size 2, expected 0"

  return 0;
}