#include "AVLTree.h"
#include <cmath>

//just a utility function for printing the node. Helpful for debugging
void printNode(Node* node) {
    cout << "Word: " << node->word << " ||| Parent Word: " << (node->parentNode!= nullptr ? node->parentNode->word : "nullptr")
         << " ||| left Word: " << (node->leftNode!=nullptr ? node->leftNode->word : "nullptr")
         << " ||| right Word: " << (node->rightNode!=nullptr ? node->rightNode->word : "nullptr")
         << " ||| height: " << (node->height) << endl;
    return;
}

//nodeHeight uses the node's 'height' field, which is way faster than calculating the height recursively.
//Don't use this right after rotating the tree, use recursiveHeight instead.
int nodeHeight(Node* node) {
    if (node==nullptr) return 0;
    else return node->height;
}

//Calculate the height of the tree recursively.
//Note, it is way slower than accessing the node's 'height' field, so avoid if possible.
int recursiveHeight(Node* node) {
    int LHeight;
    int RHeight;
    if (node != nullptr) {
        LHeight = recursiveHeight(node->leftNode) + 1;
        RHeight = recursiveHeight(node->rightNode) + 1;
        return (LHeight>RHeight ? LHeight : RHeight);
    } else
        return 0;
}

//the good ol' right rotate
Node* rightRotate(Node* node) {

    //keep this node in a temp variable so it's value is stored after the following updates
    Node* temp = node->leftNode;

    //the parent nodes are changed
    if (temp->rightNode!=nullptr) temp->rightNode->parentNode = node;
    if (node->parentNode!=nullptr){
        if (node->parentNode->rightNode == node) node->parentNode->rightNode = temp;
        else node->parentNode->leftNode = temp;
    }
    temp->parentNode = node->parentNode;
    node->parentNode = temp;

    //rotate the nodes
    node->leftNode = node->leftNode->rightNode;
    temp->rightNode = node;

    //the initial node is returned
    return node;
}

//a classic left rotate
Node* leftRotate(Node* node) {

    //keep this node in a temp variable so it's value is stored after the following updates
    Node* temp = node->rightNode;

    //the parent nodes are changed
    if (temp->leftNode!=nullptr)temp->leftNode->parentNode = node;
    if (node->parentNode!=nullptr) {
        if ( node->parentNode->rightNode == node ) node->parentNode->rightNode = temp;
        else node->parentNode->leftNode = temp;
    }
    temp->parentNode = node->parentNode;
    node->parentNode = temp;

    //rotate the nodes
    node->rightNode = node->rightNode->leftNode; //eixame ena thema edo EDO! eixame temp = node->rightNode->leftNode
    temp->leftNode = node;

    //the initial node is returned
    return temp;
}

//determine whether the tree needs left rotate, right rotate, left-right rotate or right-left rotate,
//and then call the proper rotates accordingly
void balance(Node* node, int LHeight, int RHeight) {
    int childLeftHeight;
    int childRightHeight;

    if (LHeight > RHeight) {

        //childLeftHeight = recursiveHeight(node->leftNode->leftNode);
        childLeftHeight = nodeHeight(node->leftNode->leftNode);
        //childRightHeight = recursiveHeight(node->leftNode->rightNode);
        childRightHeight = nodeHeight(node->leftNode->rightNode);

        if (childLeftHeight >= childRightHeight) {
            //cout<<"    Starting right rotate" << endl;
            rightRotate(node);
        } else {
            //cout<<"    Starting left-right rotate" << endl;
            leftRotate(node->leftNode);
            rightRotate(node);
        }

    } else {

        childLeftHeight = nodeHeight(node->rightNode->leftNode);
        childRightHeight = nodeHeight(node->rightNode->rightNode);

        if (childRightHeight >= childLeftHeight ) {
            //cout<<"    Starting left rotate" << endl;
            leftRotate(node);
        } else {
            //cout<<"    Starting right-left rotate" << endl;
            rightRotate(node->rightNode);
            leftRotate(node);
        }

    }

    return;
}

//if the root of a tree needs to be balanced, then we need to change the root node.
void changeRoot(AVLTree *tree, int lheight, int rheight) {

    //determine the rotation that is about to happen
    if (lheight> rheight)
        if ( nodeHeight(tree->root->leftNode->rightNode) > nodeHeight(tree->root->leftNode->leftNode) ) //left-right rotation
            tree->root = tree->root->leftNode->rightNode;
        else tree->root = tree->root->leftNode; //right rotation
    else
        if (nodeHeight(tree->root->rightNode->leftNode) > nodeHeight(tree->root->rightNode->rightNode))//right-left rotation
            tree->root = tree->root->rightNode->leftNode;
        else tree->root = tree->root->rightNode; //left rotation
    return;
}

//override the addWord method, so the balance of the nodes can be checked
Node* AVLTree::addWord(string word){

    int LHeight;
    int RHeight;

    //call the parent's add word method to add the word, then balance the tree
    Node* addedNode = BTree::addWord(word);

    //Create a 'node' variable, so we can 'climb' the tree to check if it needs balancing, without losing the recently added node
    Node* node = addedNode;

    //check if the tree needs balancing, by parsing it from the node added all the way to the root
    while (node != nullptr) {
        LHeight = nodeHeight(node->leftNode);
        RHeight = nodeHeight(node->rightNode);
        if ( abs(LHeight-RHeight) > 1 ) {

            //If the root node needs balancing, then, because of the rotations, we need to change the root of the tree.
            if (node == root) changeRoot(this, LHeight, RHeight);

            //Balance the tree
            balance(node, LHeight, RHeight);

            //Update the height of the node that needed balance
            node->height = recursiveHeight(node);

            //Update the heights all the way to the top, if needed
            updateHeights(node);

        }

        // 'Climb' one node up
        node = node->parentNode;
    }

    //Return the initialNode
    return addedNode;
}

