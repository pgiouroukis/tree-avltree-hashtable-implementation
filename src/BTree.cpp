#include "BTree.h"
#include <string>
#include <iostream>

using namespace std;

BTree::BTree() { //initialize the tree
    //ctor
    root = nullptr;
}

BTree::~BTree() {
    //dtor
}

Node* newNode(string w, Node* parent){ //initialize a node by setting the proper attributes
    Node *node = new Node;
    node->word = w;
    node->occurences = 1;
    node->leftNode = nullptr;
    node->rightNode = nullptr;
    node->parentNode = parent;
    node->height = 1;
    return node;

}

Node* BTree::addWord(string w) {

    //if the tree is empty, we need to update it's root.
    if (root == nullptr) {
        Node *node = newNode(w, nullptr);
        root = node;
        return node;
    } else {
        //if the tree is not empty, we need to find the proper position to put the new node.

        Node *ptr = root; // begin the traverse from the root of the node

        while( true ) {

            if( w.compare(ptr->word) == 0) {        //if the word we are trying to add is already in the tree...

                ptr->occurences++;                  //...we just increase the number of occurrences...
                return ptr;                         //...and we return the pointer to the existing node

            } else if (w.compare(ptr->word) < 0) {  //if the word we are trying to add is "smaller" than the current word we are at...

                if (ptr->leftNode != nullptr)       //...if the node has left child
                    ptr = ptr->leftNode;            //...continue traversing the tree, going left
                else {
                    ptr->leftNode = newNode(w, ptr);//...or if the node does not have a left node, add the new word to the left of the node...
                    updateHeights(ptr->leftNode);   //...and update the heights all the way to the root
                    return ptr->leftNode;           //...return the pointer to the newly created node
                }
            } else {                                //if the word we are trying to add is "bigger" than the current word we are at...

                if (ptr->rightNode != nullptr)      //...if the node has right child
                    ptr = ptr->rightNode;           //...continue traversing the tree, going right
                else {
                    ptr->rightNode=newNode(w, ptr); //...or if the node does not have a right node, add the new word to the right of the node...
                    updateHeights(ptr->rightNode);  //...and update the heights all the way to the root
                    return ptr->rightNode;          //...return the pointer to the newly created node
                }
            }
        }

    }
    return nullptr; // return nullptr if something goes wrong
}

Node* BTree::findWord(string w) {

    Node *ptr = root; // start traversing the tree from the root

    //while ptr is not nullptr, we are still traversing the tree
    while ( ptr!=nullptr ) {
        if (w.compare(ptr->word) == 0)          //found the word...
            return ptr;                         //..so return it
        else if (w.compare(ptr->word) < 0)      //the word is "smaller"...
            ptr = ptr->leftNode;                //...so go left
        else                                    //the word is "bigger"...
            ptr = ptr->rightNode;               //...so go right
    }

    //if it reaches here, that means the word was not found, so nullptr is returned
    return nullptr;
}

bool BTree::deleteWord(string w) {

    //first, try to find the word to be deleted
    Node *ptr = this->findWord(w);

    //if the word is not in the tree, we return false
    if (ptr == nullptr)
        return false;
    else {

        //in this case, the node to be deleted has no children, so it is a leaf
        if (ptr->leftNode == nullptr && ptr->rightNode == nullptr) {
            //in this case we only have to update the parent of the node
            //but first, we have to determine whether the parent node has the node as a left or as a right child

            //first of all, we check if the node is the root node, so there is no parent node to update
            if (ptr->parentNode != nullptr) {
                //since the node has a parent node, we must determine whether the parent node has the node as a left or as a right child
                if (ptr->parentNode->leftNode == ptr)
                    //our node is a left-child
                    ptr->parentNode->leftNode = nullptr;
                else
                    //our node is a right-child
                    ptr->parentNode->rightNode = nullptr;
            } else {
                //the node is the root of the tree,so we just update the root attribute to nullptr
                root = nullptr;
            }

            //free up the space of the node
            delete ptr;

            //return true, since the deletion was successful
            return true;

        } else if (ptr->leftNode == nullptr || ptr->rightNode == nullptr) {
            //in this case, the node to be deleted has only one child

            Node *childPtr;

            //we find the child of the node, (is it a right or a left child?)
            if (ptr->leftNode != nullptr) {
                childPtr = ptr->leftNode; //the node has left-child
            } else {
                childPtr = ptr->rightNode;//the node has right-child
            }

            //first of all, we check if the node is the root node, so there is no parent node to update
            if (ptr->parentNode != nullptr) {
                //since the node has a parent node, we must determine whether the parent node has the node as a left or as a right child
                if (ptr->parentNode->leftNode == ptr) {
                    //our node is a left-child
                    ptr->parentNode->leftNode = childPtr;
                } else {
                    //our node is a right-child
                    ptr->parentNode->rightNode = childPtr;
                }
                childPtr->parentNode = ptr->parentNode; //set the parent of childptr to be the parent of our node
            } else {
                //if ptr has no parent node,then it is the root, so we have to update the root of the tree
                root = childPtr;
                childPtr->parentNode = nullptr;
            }
            //free up the space of the node
            delete ptr;

            //return true, since the deletion was successful
            return true;

        } else {
            //in this case, the node to be deleted 2 children

            //in tptr, the inorder successor of ptr is stored
            Node *tptr = ptr->rightNode;
            //finding the inorder successor...
            while (tptr->leftNode != nullptr)
                tptr = tptr->leftNode;

            //NOTE: tptr can't have a left child, otherwise this left child would be tptr
            //BUT tptr might have a right child. This right child must be updated so it points to the parent node of tptr
            //and the parent node of tptr must be updated so it points to this child
            if (ptr->rightNode != tptr) { // the latter does not apply in the special case that tptr is right child of ptr
                if (tptr->rightNode!=nullptr) {
                    tptr->parentNode->leftNode = tptr->rightNode;   //update the parent node of tptr, so it points to the right child of tptr
                    tptr->rightNode->parentNode = ptr->parentNode;  //update the right child of tptr, so it points to the parent node of tptr
                } else
                    tptr->parentNode->leftNode = nullptr; // otherwise, set the parent node of tptr to have a nullptr as a left child
            }

            //move tptr to the position of ptr, by making the proper changes
            tptr->leftNode = ptr->leftNode;
            if (ptr->rightNode != tptr)
                tptr->rightNode= ptr->rightNode;
            tptr->parentNode = ptr->parentNode;

            //the parent of ptr must now point to tptr, if ptr is not the root
            if (ptr->parentNode != nullptr) {
                //but we need to know if ptr is right or left child of his parent node
                if (ptr->parentNode->leftNode == ptr)
                    //left-child
                    ptr->parentNode->leftNode = tptr;
                else
                    //right-child
                    ptr->parentNode->rightNode = tptr;
            } else {
                //if ptr is the root, now tptr must be the root
                root = tptr;
            }
            //free up the space of ptr
            delete ptr;

            //return true, since the deletion was successful
            return true;
        }
    }

}

/* -------------------------------------------------------------------------------- */

void inOrder(Node *n) { //recursive inOrder traversal, starting from node n

    if (n == nullptr) return;

    inOrder(n->leftNode);

    cout << "Word: " << n->word << " | Occurences: " << n->occurences << endl;

    inOrder(n->rightNode);

    return;

}

void BTree::printInOrder() { //start inOrder traversal from the root of the tree

    std::cout << "Starting inOrder Traversal..." << endl;

    inOrder(root);

    std::cout << endl;

    return;

}

void postOrder(Node *n) { //recursive postOrder traversal, starting from node n

    if (n == nullptr) return;

    postOrder(n->leftNode);

    postOrder(n->rightNode);

    cout << "Word: " << n->word << " | Occurences: " << n->occurences << endl;

    return;

}

void BTree::printPostOrder() { //start postOrder traversal from the root of the tree

    std::cout << "Starting postOrder Traversal..." << endl;

    postOrder(root);

    std::cout << endl;

    return;

}

void preOrder(Node *n) { //recursive preOrder traversal, starting from node n

    if (n == nullptr) return;

    cout << "Word: " << n->word << " | Occurences: " << n->occurences << endl;

    preOrder(n->leftNode);

    preOrder(n->rightNode);

    return;

}

void BTree::printPreOrder() { //start preOrder traversal from the root of the tree

    std::cout << "Starting preOrder Traversal..." << endl;

    preOrder(root);

    std::cout << endl;

    return;

}

/* -------------------------------------------------------------------------------- */

bool updateHeights(Node* node) { // update the heights of parent nodes, starting from "node" all the way to the root
    while (node->parentNode!=nullptr) { //we reached the root node
        if (node->parentNode->height < node->height + 1) //the node might not need an update of the height, so we have to check
            node->parentNode->height = node->height + 1; //update the parent node's height, by increasing it by 1 from node
        node = node->parentNode; //continue "climbing" the tree
    }
    return true;
}
