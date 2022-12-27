#include "Vector.hpp"
using namespace ft;

//#include <iostream>
//#include <vector>
//using namespace std;

// CAPACITY TESTS
template <typename T>
void  testSize(const vector<T> vec, size_t expectedSize)
{
  size_t size = vec.size();
  if (size == expectedSize){
    std::cout << "Test passed: got size " 
    << size << ", expected " << expectedSize << std::endl;
  }
  else {
    std::cout << "Test failed: got size " 
    << size << ", expected " << expectedSize << std::endl;
  }
}

int main()
{
  vector<int> tab;
  std::cout << "------- SIZE TEST--------" << std::endl;
  testSize(tab, 0);
  for (int i = 0; i < 10; i++) tab.push_back(i);
  testSize(tab, 10);
 /*tab.insert (tab.end(),10,100);
  testSize(tab, 20)
  tab.pop_back();
  testSize(tab, 19) */

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- MAX_SIZE TEST--------" << std::endl;
  vector<int> myvector;
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- RE_SIZE TEST--------" << std::endl;  

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- CAPACITY TEST--------" << std::endl;

  std::cout << "capacity: " << myvector.capacity() << "\n";

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- EMPTY TEST--------" << std::endl;
  if (myvector.empty())
      std::cout << "Vector is empty" << "\n";
  else
    std::cout << "Vector is not empty" << "\n";
  myvector.clear();
  if (myvector.empty())
      std::cout << "Vector is empty" << "\n";
  else
    std::cout << "Vector is not empty" << "\n";
  return (0);
}

/* -------------------------
  Test PopBack et Push back
 -------------------------*/ 
/*template <typename T>
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
}*/


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