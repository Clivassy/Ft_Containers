#include "Vector.hpp"

using namespace ft;
int main()
{
    vector<int> tab; // constructor by default


    vector<int> arr(5, 10); // creation d'un vector de 5 elements qui ont la valeur de 1.
    for (int i = 0; i < 5; i++)
    {
        std::cout << arr._start[i] << std::endl; // on est sur le first elem
    }
    std::cout << "----------------------------" << std::endl;
    arr.push_back(5);
    arr.push_back(15);
    arr.push_back(50);
    for (int i = 0; i < 8; i++)
    {
        std::cout << arr._start[i] << std::endl; // on est sur le first elem
    }
    return (0);
}


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

