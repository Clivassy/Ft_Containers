#include <iostream>
#include "RBT_iterator.hpp"

#define BLACK 0
#define RED 1


class RedBlackTree {

    struct Node {

        int value;
        Node *left;
        Node *right;
        Node *parent;
        bool color;
};
    private:
        Node *root;
        Node *leaf;
        size_t size;

    public:
    // CONSTRUCTORS
        RedBlackTree() {
            leaf = new Node;
            leaf->color = BLACK;
            leaf->left = nullptr;
            leaf->right = nullptr;
            leaf->value = 0;
            root = leaf;
        }

    // DESTRUCTOR
    // ITERATORS
    // MODIFIERS

        void    insertNode( int key )
        {
            // create a new node and initialize value
            Node *newNode = new Node;
            newNode->parent = nullptr; 
            newNode->value = key;
            newNode->left = leaf;
            newNode->right = leaf;
            newNode->color = RED;

            // Create temp node to traverse the tree
            Node *PtrY = nullptr; // keep track of x pos - 1
            Node *PtrX = this->root; // will traverse the tree

            // On parcours l'arbre jusqu'a leaf
            // a chaque node on check la value 
            // pour aller soit vers la gauche < 
            // soit vers la droite >
            while (PtrX != leaf)
            {
                PtrY = PtrX;
                if (newNode->value < PtrX->value)
                    PtrX = PtrX->left;
                else
                    PtrX = PtrX->right;
            }
            
            newNode->parent = PtrY;

            if (PtrY == nullptr)
                root = newNode;
            else if (newNode->value < PtrY->value)
                PtrY->left = newNode;
            else 
                PtrY->right = newNode;

            // si le parent n'existe pas : on est root donc
            // Le node est noir
            if (newNode->parent == nullptr)
            {
                std::cout << "root node insertion" << std::endl;
                newNode->color = BLACK;
                return;
            }
            if (newNode->parent->parent == nullptr)
            {
                std::cout << "intermediate node insertion" << std::endl;
                return;
            }
            std::cout << "other node insertion" << std::endl;

            checkInsertionNode(newNode);
            // call function qui va vérifier si toutes les règles
            // du RBT sont respectées.
        }

        void    rotateRight(Node *node)
        {         
            Node *y = node->left;
            node->left = y->right;
            if (y->right != leaf) {
              y->right->parent = node;
            }
            y->parent = node->parent;
            if (node->parent == nullptr) {
              this->root = y;
            } else if (node == node->parent->right) {
              node->parent->right = y;
            } else {
              node->parent->left = y;
            }
            y->right = node;
            node->parent = y;   
        }

        void rotateLeft(Node *node)
        {
            Node *y = node->right;

            node->right = y->left;
            if (y->left != leaf) {
              y->left->parent = node;
            }
            y->parent = node->parent;
            if (node->parent == nullptr) {
              this->root = y;
            } else if (node == node->parent->left) {
              node->parent->left = y;
            } else {
              node->parent->right = y;
            }
            y->left = node;
            node->parent = y;
        }

        void    checkInsertionNode(Node *newNode)
        {
            Node *ptr;

            // while the parent of newNode (p) is RED
            while (newNode->parent->color == RED)
            {         
                if (newNode->parent == newNode->parent->parent->right) 
                {
                    ptr = newNode->parent->parent->left;
                    if (ptr->color == 1) 
                    {
                        ptr->color = 0;
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        newNode = newNode->parent->parent;
                    } 
                    else 
                    {
                        if (newNode == newNode->parent->left) 
                        {
                            newNode = newNode->parent;
                            rotateRight(newNode);
                        }
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        rotateLeft(newNode->parent->parent);
                    }
                } 
                else 
                {
                    ptr = newNode->parent->parent->right;
                    if (ptr->color == 1) 
                    {
                        ptr->color = 0;
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        newNode = newNode->parent->parent;
                    } 
                    else 
                    {
                        if (newNode == newNode->parent->right) 
                        {
                            newNode = newNode->parent;
                            rotateLeft(newNode);
                        }
                        newNode->parent->color = 0;
                        newNode->parent->parent->color = 1;
                        rotateRight(newNode->parent->parent);
                    }
                }
                if (newNode == root) 
                    break;
            }
        root->color = 0;
    }

        ///////////////////// DEBUG //////////////////
        void printHelper(Node *root, std::string indent, bool last) 
        {
            if (root != leaf) 
            {
                std::cout << indent;
                if (last) 
                {
                    std::cout << "R----";
                    indent += "   ";
                }     
                else 
                {
                    std::cout << "L----";
                    indent += "|  ";
                }
                std::string sColor = root->color ? "RED" : "BLACK";
                std::cout << root->value << "(" << sColor << ")" << std::endl;
                printHelper(root->left, indent, false);
                printHelper(root->right, indent, true);
            }
        }

        void    printTree( void )
        {
            if (root)
            {
                printHelper(this->root,"", true);
            }
        }
    ////////////////////////////////////////////////////////////////////////
};