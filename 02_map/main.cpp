#include "RedBlackTree.hpp"
//#include "map.hpp"

using namespace std;
//using namespace ft;


int main() {
    
  RedBlackTree tree;

  tree.insertNode(33);
  tree.insertNode(13);
  tree.insertNode(21);
  tree.insertNode(11);
  tree.insertNode(15);
  tree.insertNode(31);
  tree.insertNode(53);
  tree.insertNode(41);
  tree.insertNode(61);

  tree.printTree();
}
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
