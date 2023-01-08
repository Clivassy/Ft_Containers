
#include "Vector.hpp"
using namespace ft;

//#include <iostream>
//#include <vector>
//using namespace std;

// CAPACITY TESTS
/*template <typename T>
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
 tab.insert (tab.end(),10,100);
  testSize(tab, 20)
  tab.pop_back();
  testSize(tab, 19) */

  //////////////////////////////////////////////////////////////
  /*std::cout << std::endl;
  std::cout << "------- MAX_SIZE TEST--------" << std::endl;
  vector<int> myvector;
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- RE_SIZE TEST--------" << std::endl;  


  //////////////////////////////////////////////////////////////
  return (0);
}*/

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

/*template <typename T>
void testIterators(vector<T>& vec) {
  // Test begin() and end()
  for (typename vector<T>::iterator it = vec.begin(); it != vec.end(); it++) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  // Test dereference operator
  typename vector<T>::iterator it = vec.begin();
  *it = 42;

  // Test pre-increment operator
  ++it;

  // Test post-increment operator
  it++;

  // Test comparison operators
  if (it == it)//vec.end()) 
  {
    std::cout << "Iterators are equal" << std::endl;
  } else {
    std::cout << "Iterators are not equal" << std::endl;
  }
   if (it == vec.end()) 
  {
    std::cout << "Iterators are equal" << std::endl;
  } else {
    std::cout << "Iterators are not equal" << std::endl;
  }
}

int main() {
  vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);

  testIterators(vec);

  return 0;
}*/


int main() {
  
  vector<int> vec;

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- SIZE TEST--------" << std::endl;
  std::cout << "0. size: " << vec.size() << '\n';

  for (int i=0; i<10; i++) vec.push_back(i);
  std::cout << "1. size: " << vec.size() << '\n';

  vec.insert (vec.end(), 10, 100);
  std::cout << "2. size: " << vec.size() << '\n';

  vec.pop_back();
  std::cout << "3. size: " << vec.size() << '\n';

  vec.clear();

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- MAX_SIZE TEST--------" << std::endl;

  for (int i=0; i<100; i++) vec.push_back(i);

  std::cout << "size: " << vec.size() << "\n";
  std::cout << "capacity: " << vec.capacity() << "\n";
  std::cout << "max_size: " << vec.max_size() << "\n";

  vec.clear();

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- RESIZE TEST--------" << std::endl;

  for (int i=1;i<10;i++) vec.push_back(i);
  vec.resize(5);
  vec.resize(8,100);
  vec.resize(12);

  std::cout << "vec contains:";
  for (int i=0;i<vec.size();i++)
    std::cout << ' ' << vec[i];
  std::cout << '\n';

  vec.clear();
  
  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- CAPACITY TEST--------" << std::endl;

  std::cout << "capacity: " << vec.capacity() << "\n";

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- EMPTY TEST--------" << std::endl;
  for (int i=0; i<10; i++) vec.push_back(i);
  if (vec.empty())
    std::cout << "Vector is empty" << "\n";
  else
    std::cout << "Vector is not empty" << "\n";
  vec.clear();
 
  if (vec.empty())
      std::cout << "Vector is empty" << "\n";
  else
    std::cout << "Vector is not empty" << "\n";
  
   vec.clear();
  
  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- RESERVE TEST--------" << std::endl;
  vector<int>::size_type sz;

  vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- ASSIGN TEST--------" << std::endl;
  // Fill the vector with 10 copies of the value 42
  vec.assign(10, 42);

  // Print the elements of the vector
  for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
      std::cout << *it << " ";
      std::cout << std::endl;
  }
  vec.clear();
  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- OPEARTOR[] TEST--------" << std::endl;
  vector<int> operatorTest (10);   // 10 zero-initialized elements

  vector<int>::size_type sze = operatorTest.size();

  // assign some values:
  for (unsigned i=0; i<sze; i++) operatorTest[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sze/2; i++)
  {
    int temp;
    temp = operatorTest[sze-1-i];
    operatorTest[sze-1-i]=operatorTest[i];
    operatorTest[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sze; i++)
    std::cout << ' ' << operatorTest[i];
  std::cout << '\n';

  ///////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- AT TEST--------" << std::endl;
  vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  myvector.clear();

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- FRONT TEST--------" << std::endl;
  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();
  std::cout << "myvector.front() is now " << myvector.front() << '\n';

  myvector.clear();

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- BACK TEST--------" << std::endl;
    myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }
  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();

  //////////////////////////////////////////////////////////////
  /*std::cout << std::endl;
  std::cout << "------- ASSIGN TEST--------" << std::endl;
  vector<int> first;
  vector<int> second;
  vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  vector<int>::iterator it;
  it = first.begin() + 1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';*/

 //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- PUSH_BACK TEST--------" << std::endl;
  myvector.push_back(1);
  myvector.push_back(2);
  myvector.push_back(3);

  // Check the size of the vector
  if (myvector.size() != 3) {
    std::cout << "Error: Unexpected vector size" << std::endl;
  }
  // Check the elements of the vector
  else if (myvector[0] != 1 || myvector[1] != 2 || myvector[2] != 3) {
    std::cout << "Error: Unexpected vector elements" << std::endl;
  }
  else
    std::cout << "Success" << std::endl;

   myvector.clear();

//////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- POP_BACK TEST--------" << std::endl;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }
  std::cout << "The elements of myvector add up to " << sum << '\n';
  myvector.clear();

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- INSERT TEST--------" << std::endl;
  // TO DO 
  std::cout << "TO DO " << '\n';
  //////////////////////////////////////////////////////////////
  myvector.clear();
  std::cout << std::endl;
  std::cout << "------- ERASE TEST--------" << std::endl;
  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase (myvector.begin()+5);

  // erase the first 3 elements:
  myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  myvector.clear();
  
  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- SWAP TEST--------" << std::endl;
  vector<int> foo1 (3,100);   // three ints with a value of 100
  vector<int> bar1 (5,200);   // five ints with a value of 200

  foo.swap(bar1);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo1.size(); i++)
    std::cout << ' ' << foo1[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar1.size(); i++)
    std::cout << ' ' << bar1[i];
  std::cout << '\n';
  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- CLEAR TEST--------" << std::endl;
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  myvector.clear();

  //////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- GET ALLOCATOR TEST--------" << std::endl;
  int * p;
  unsigned int i;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p,5);

//////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- OPERATOR == TEST--------" << std::endl;
  
  vector<int> test1;
  vector<int> test2;
  test1.push_back(4);
  test1.push_back(40);
  test2.push_back(4);
  test2.push_back(40);
  if (test1 == test2)
    std::cout << "Vectors are equal" << std::endl;
  else
    std::cout << "Vectors are not equal" << std::endl;

//////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- COPY CONSTRUCTOR TEST--------" << std::endl;
  
  vector<int> copy(test1);

  std::cout << "Test1 contains:";
  for (unsigned i = 0; i < test1.size(); i++)
    std::cout << ' ' << test1[i];
  std::cout << '\n';

  std::cout << "Copy Vector contains:";
  for (unsigned i = 0; i < copy.size(); i++)
    std::cout << ' ' << copy[i];
  std::cout << '\n';

//////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- RANGE CONSTRUCTOR TEST--------" << std::endl;
  
  vector<int> test3;
  test3.push_back(10);
  test3.push_back(11);
  test3.push_back(12);

  vector<int> rangeVector(test3.begin(), test3.end());

  std::cout << "Range Vector contains:";
  for (unsigned i = 0; i < rangeVector.size(); i++)
    std::cout << ' ' << rangeVector[i];
  std::cout << '\n';
  return (0);
}

