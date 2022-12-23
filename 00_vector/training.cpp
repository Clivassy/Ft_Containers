#include <iostream>
#include <cstddef>

template <typename T>
class Vector {
 public:
  // Constructors
  Vector() : size_(0), capacity_(0), elements_(nullptr) {}
  Vector(std::size_t size) : size_(size), capacity_(size), elements_(new T[size]) {}

  // Destructor
  ~Vector() {
    delete[] elements_;
  }

  // Adds an element to the end of the vector
  void push_back(const T& value) {
    // Check if the vector needs to increase its capacity to store the new element
    if (size_ == capacity_) {
      // Increase the capacity of the vector
      capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;
      T* newElements = new T[capacity_];
      for (std::size_t i = 0; i < size_; i++) {
        newElements[i] = elements_[i];
      }
      delete[] elements_;
      elements_ = newElements;
    }
    // Add the new element to the end of the vector
    elements_[size_++] = value;
  }

    // Removes the last element from the vector and returns it
  T pop_back() {
    //if (size_ == 0) {
      // Handle the case where the vector is empty
      // You can throw an exception here, or return a default value
      //return T();
   // }
    // Decrement the size of the vector and return the last element
    return elements_[--size_];
  }

  void reserve(std::size_t newCapacity) {
    if (newCapacity > capacity_) {
      // Allocate a new block of memory and copy the existing elements to it
      capacity_ = newCapacity;
      T* newElements = new T[capacity_];
      for (std::size_t i = 0; i < size_; i++) {
        newElements[i] = elements_[i];
      }
      delete[] elements_;
      elements_ = newElements;
    }
  }

  // Other vector functions...

//private:
  std::size_t size_;  // current size of the vector
  std::size_t capacity_;  // current capacity of the vector
  T* elements_;  // pointer to the elements of the vector
};

int main()
{
   /* Vector<int> tab; // constructor by default
    tab.push_back(2);
    std::cout << tab.elements_[0] << std::endl;*/

    Vector<int> arr(0);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    for (int i = 0; i < 3; i++)
        std::cout << arr.elements_[i] << std::endl;
    arr.pop_back();
    arr.pop_back();
    arr.pop_back();
    for (int i = 0; i < 3; i++)
      std::cout << arr.elements_[i] << std::endl;
    return (0);
}
