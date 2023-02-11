#include "stack.hpp"
#include "../00_vector/vector.hpp"
#include "../utils/testeur.hpp"

using namespace ft;
int main()
{
    //-- Constructor
    printTitle("CONSTRUCTORS TESTS");
    printFunctionTest("Default Construtor");
    stack<int> intStack;

    printTitle("CONSTRUCTORS TESTS");
    //-- Empty
    printFunctionTest("Empty");
    if (intStack.empty())
        std::cout << "stack is empty" << std::endl;
    else
        std::cout << "stack is NOT empty" << std::endl;
    //-- PushBack
    intStack.push(125);
    if (intStack.empty())
        std::cout << "stack is empty" << std::endl;
    else
        std::cout << "stack is NOT empty" << std::endl;
    std::cout << intStack.top() << std::endl;
    //-- 
    return (0);
}