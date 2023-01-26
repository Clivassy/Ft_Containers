
#include "./vector.hpp"
using namespace ft;

//#include <iostream>
//#include <vector>
//using namespace std;

#include <chrono>
using namespace std::chrono;

int main() {

  // CONSTRUCTORS 
  //////////////////////////////////////////////////////////////
  auto start = high_resolution_clock::now();
  std::cout << std::endl;

  std::cout << "------- CONSTRUCTORS TEST--------" << std::endl;
  std::cout << std::endl;

  //---------- Default constructor 
  vector<int> vec;
  if (vec.empty())
    std::cout << "Constructor by Default has been created and: is empty." << std::endl;

  //---------- Fill constructor
  vector<int> vecFill(5, 42);
  std::cout << "Fill Constructor has been created and contains:" << std::endl;
  for (int i = 0; i < 5; i++) {
    std::cout << vecFill[i] << " ";
  }
  std::cout << std::endl;

  //---------- Range constuctor 
  vector<int> rangeConstructor;

  rangeConstructor.push_back(1);
  rangeConstructor.push_back(2);
  rangeConstructor.push_back(3);

  vector<int> rangeVector(rangeConstructor.begin(), rangeConstructor.end());

  std::cout << "Range constuctor has been created and contains: " << std::endl;
  for (unsigned i = 0; i < rangeVector.size(); i++)
    std::cout << rangeVector[i] << ' ';
  std::cout << '\n';

  //--------- Copy Constructor
  
  vector<int> copy(rangeConstructor);
  std::cout << "Copy constuctor has been created and contains: " << std::endl;
  for (unsigned i = 0; i < copy.size(); i++)
    std::cout << copy[i] << ' ';
  std::cout << '\n';

  // ITERATORS
  //////////////////////////////////////////////////////////////

  std::cout << std::endl;
  std::cout << "------- ITERATORS TEST--------" << std::endl;
  std::cout << std::endl;

  //------ Begin - end --------
  vector<int> iteratorTest;
  for (int i=1; i<=5; i++) iteratorTest.push_back(i);

  std::cout << "iteratorTest contains:";
  for (vector<int>::iterator it = iteratorTest.begin() ; it != iteratorTest.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  //------ Rbegin - Rend ------
  std::cout << std::endl;
  vector<int> ReverItTest (5);
  int i = 0;
  
  vector<int>::reverse_iterator rit = ReverItTest.rbegin();
  for (; rit!= ReverItTest.rend(); ++rit)
    *rit = ++i;

  std::cout << "ReverItTest contains:";
  std::cout << std::endl;
  for (vector<int>::iterator it = ReverItTest.begin(); it != ReverItTest.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  //////////////////////////////////////////////////////////////
  // CAPACITY
  std::cout << std::endl;
  std::cout << "------- CAPACITY TESTS--------" << std::endl;

  //--------- size()
  std::cout << std::endl;
  std::cout << "------- Size() ------" << std::endl;
  std::cout << "0. size: " << vec.size() << '\n';

  for (int i=0; i<10; i++) vec.push_back(i);
  std::cout << "1. size: " << vec.size() << '\n';

  vec.insert (vec.end(), 10, 100);
  std::cout << "2. size: " << vec.size() << '\n';

  vec.pop_back();
  std::cout << "3. size: " << vec.size() << '\n';

  vec.clear();

  //--------- max_size()
  std::cout << std::endl;
  std::cout << "------- max_size()--------" << std::endl;
  std::cout << std::endl;

  for (int i=0; i<100; i++) vec.push_back(i);

  std::cout << "size: " << vec.size() << "\n";
  std::cout << "capacity: " << vec.capacity() << "\n";
  std::cout << "max_size: " << vec.max_size() << "\n";

  vec.clear();

  //--------- resize()
  std::cout << std::endl;
  std::cout << "-------Resize() --------" << std::endl;
  std::cout << std::endl;

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
  std::cout << "------- Capacity() --------" << std::endl;
  std::cout << std::endl;

  std::cout << "capacity: " << vec.capacity() << "\n";

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- Empty() --------" << std::endl;
  std::cout << std::endl;

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
  std::cout << "------- reserve() --------" << std::endl;
  std::cout << std::endl;

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
  bar.reserve(100);
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  // ELEMENT ACCESS 
  /////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- ELEMENT ACCESS TESTS--------" << std::endl;
  std::cout << std::endl;

  //-------- Operator[]
  std::cout << "------- Operator[] --------" << std::endl;
  std::cout << std::endl;
  vector<int> operatorTest (10);

  vector<int>::size_type sze = operatorTest.size();

  for (unsigned i=0; i<sze; i++) operatorTest[i]=i;

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

  //-------- at()
  std::cout << std::endl;
  std::cout << "------- at() --------" << std::endl;
  std::cout << std::endl;
  vector<int> myvector (10);

  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  myvector.clear();

  //-------- front()
  std::cout << std::endl;
  std::cout << "------- Front() --------" << std::endl;
  std::cout << std::endl;
  myvector.push_back(78);
  myvector.push_back(16);

  myvector.front() -= myvector.back();
  std::cout << "myvector.front() is now " << myvector.front() << '\n';
  myvector.clear();

  std::cout << std::endl;
  //-------- back()
  std::cout << "------- Back() --------" << std::endl;
  std::cout << std::endl;
  
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
  // MODIFIERS
  std::cout << std::endl;
  std::cout << "------- MODIFIERS TESTS--------" << std::endl;

  // MODIFIERS 
  std::cout << std::endl;
  std::cout << "------- Assign()--------" << std::endl;
  std::cout << std::endl;

  vector<int> first;
  vector<int> second;
  vector<int> third;

  first.assign (7,100); // fill assign 

  vector<int>::iterator it;
  it = first.begin() + 1;

  second.assign (it,first.end()-1); // range assign

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';

  //----------- PushBack() 
  std::cout << std::endl;
  std::cout << "------- Pushback() --------" << std::endl;
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

  //----------- PopBack() 
  std::cout << std::endl;
  std::cout << "------- PopBack() --------" << std::endl;
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

  //----------- Insert() 
  std::cout << std::endl;
  std::cout << "------- insert() --------" << std::endl;
  vector<int>::iterator Insertit;

  myvector.push_back(100);
  myvector.push_back(100);
  myvector.push_back(100);

  Insertit = myvector.begin();
  Insertit = myvector.insert ( Insertit , 200 );

  myvector.insert (Insertit,2,300);

  Insertit = myvector.begin();

  vector<int> anothervector (2,400);
  myvector.insert (Insertit+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (Insertit=myvector.begin(); Insertit<myvector.end(); Insertit++)
    std::cout << ' ' << *Insertit;
  std::cout << '\n';
 
  myvector.clear();
  std::cout << std::endl;

//----------- erase() 
  std::cout << "------- erase()--------" << std::endl;
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
  
//----------- Swap() 
  std::cout << std::endl;
  std::cout << "------- swap() --------" << std::endl;
  vector<int> foo1 (3,100);
  vector<int> bar1 (5,200);

  foo.swap(bar1);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo1.size(); i++)
    std::cout << ' ' << foo1[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar1.size(); i++)
    std::cout << ' ' << bar1[i];
  std::cout << '\n';

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
  // GET_ALLOCATOR
  std::cout << std::endl;
  std::cout << "------- GET ALLOCATOR TEST--------" << std::endl;
  int * p;
  unsigned int index;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (index=0; index<5; index++) myvector.get_allocator().construct(&p[index],index);

  std::cout << "The allocated array contains:";
  for (index=0; index<5; index++) std::cout << ' ' << p[index];
  std::cout << '\n';

  // destroy and deallocate:
  for (index=0; index<5; index++) myvector.get_allocator().destroy(&p[index]);
  myvector.get_allocator().deallocate(p,5);

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- COMPARISON OPERATORS TESTS--------" << std::endl;
  
  vector<int> one (3,100);   // three ints with a value of 100
  vector<int> two (2,200);   // two ints with a value of 200

  if (one==two) std::cout << "foo and bar are equal\n";
  if (one!=two) std::cout << "foo and bar are not equal\n";
  if (one< two) std::cout << "foo is less than bar\n";
  if (one> two) std::cout << "foo is greater than bar\n";
  if (one<=two) std::cout << "foo is less than or equal to bar\n";
  if (one>=two) std::cout << "foo is greater than or equal to bar\n";

  //////////////////////////////////////////////////////////////
  std::cout << std::endl;
  std::cout << "------- SWAP TEMPLATE TESTS--------" << std::endl;
  i =0;
  vector<int> SwapFoo (3,100);   
  vector<int> SwapBar (5,200);  

  SwapFoo.swap(SwapBar);

  std::cout << "foo contains:";
  for (vector<int>::iterator it = SwapFoo.begin(); it!=SwapFoo.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  std::cout << "bar contains:";
  for (vector<int>::iterator it = SwapBar.begin(); it!=SwapBar.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(stop - start);
 
  std::cout << "Time taken by function: "
         << duration.count() << " microseconds" << std::endl;
  return (0);
}
