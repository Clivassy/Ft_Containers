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