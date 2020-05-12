#include <iostream>
#include <string.h>
#include "BST.h"

using namespace std;

void printNode(Node* n) {

    cout << "Node pointer: " << n << endl;
    cout << "Node value: " << n->value << endl;
    cout << "Node counter: " << n->counter << endl;
    cout << "Node leftChild: " << n->leftChild<< endl;
    cout << "Node rightChild: " << n->rightChild<< endl;
    return;

}

int add(int x, int y) {return x+y;}

BST::BST() {
    root = nullptr;
}

BST::BST(string str)
{
    root = new Node;
    root->value = str;
    root->counter = 0;
    root->leftChild = nullptr;
    root->rightChild = nullptr;

    //cout << add(1,2);
    printNode(root);

}


/*
Node * BST::readWord(char *str) {

    if (root == NULL) {

        root = new Node;

        root->value = new char[50];
        strcpy(root->value, str);

        root->counter = 0;
        root->leftChild = NULL;
        root->rightChild = NULL;

    } else {

        Node *traversal = root;

        while (*traversal != NULL) {

            if ( strcmp(traversal->value, str) < 0 ) {
                if (traversal->leftChild != NULL)
                    traversal = traversal->leftChild;
                else break
            }
            else if ( strcmp(traversal->value, str) > 0 ) traversal = traversal->rightChild;
            else {
                traversal->counter++;
                traversal = NULL;
            }

        }

    }

}
*/

BST::~BST()
{
    //dtor
}
