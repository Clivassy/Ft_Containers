#include <vector> 
#include <iostream>

template <typename T>
void testPopBack(std::vector<T>& vec, T expected, std::size_t expectedSize) {
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
  std::vector<int> vec;
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