#include "RedBlackTree.hpp"

using namespace std;

int main() {
    
  RedBlackTree tree;

  tree.insertNode(3);
  tree.insertNode(30);
  tree.insertNode(1);
  tree.insertNode(12);

  tree.printTree();
}