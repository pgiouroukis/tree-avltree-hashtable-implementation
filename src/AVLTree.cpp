#include "AVLTree.h"
#include <cmath>

void printNode(Node* node) {
    cout << "Word: " << node->word << " ||| Parent Word: " << (node->parentNode!= nullptr ? node->parentNode->word : "nullptr")
         << " ||| left Word: " << (node->leftNode!=nullptr ? node->leftNode->word : "nullptr")
         << " ||| right Word: " << (node->rightNode!=nullptr ? node->rightNode->word : "nullptr")
         << " ||| height: " << (node->height) << endl;
    return;
}

int nodeHeight(Node* node) {
    if (node==nullptr) return 0;
    else return node->height;
}

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

Node* rightRotate(Node* node) {
    //kratame sto temp to node->leftNode giati tha to allaksoyme kai tha xasoume
    Node* temp = node->leftNode;

    //allazoume ta parent nodes
    if (temp->rightNode!=nullptr) temp->rightNode->parentNode = node;
    if (node->parentNode!=nullptr){
        if (node->parentNode->rightNode == node) node->parentNode->rightNode = temp;
        else node->parentNode->leftNode = temp;
    }
    temp->parentNode = node->parentNode;
    node->parentNode = temp;

    //kanoyme to rotation
    node->leftNode = node->leftNode->rightNode;
    temp->rightNode = node;

    return temp;
}

Node* leftRotate(Node* node) {

    //kratame sto temp to node->leftNode giati tha to allaksoyme kai tha xasoume
    Node* temp = node->rightNode;

    //allazoume ta parent nodes
    if (temp->leftNode!=nullptr)temp->leftNode->parentNode = node;
    if (node->parentNode!=nullptr) {
        if ( node->parentNode->rightNode == node ) node->parentNode->rightNode = temp;
        else node->parentNode->leftNode = temp;
    }
    temp->parentNode = node->parentNode;
    node->parentNode = temp;

    //kanoyme to rotation
    node->rightNode = node->rightNode->leftNode; //eixame ena thema edo EDO! eixame temp = node->rightNode->leftNode
    temp->leftNode = node;

    return temp;
}

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

void changeRoot(AVLTree *tree, int lheight, int rheight) {
    return;
}

Node* AVLTree::addWord(string word){

    int LHeight;
    int RHeight;

    //we call the parent's add word method, then we balance the tree
    Node* node = BTree::addWord(word);

    //we check if the tree needs balancing
    while (node != nullptr) {
        LHeight = nodeHeight(node->leftNode);
        RHeight = nodeHeight(node->rightNode);
        if ( abs(LHeight-RHeight) > 1 ) {

            if (node == root) {
                //an to node poy exei thema einai to root, logo ton rotations, prepe na allaksoume tin rize tou dentroy
                //changeRoot(this, LHeight, RHeight)
                if (LHeight > RHeight) {
                    if ( nodeHeight(node->leftNode->rightNode) > nodeHeight(node->leftNode->leftNode) ) { //edo einai periptosi left-right rotation
                        this->root = node->leftNode->rightNode;
                    } else { //edo eina periptosi right rotation
                        this->root = node->leftNode;
                    }

                }
                else {
                    if (nodeHeight(node->rightNode->leftNode) > nodeHeight(node->rightNode->rightNode)) { //edo einai periptosi right-left rotation
                        this->root = node->rightNode->leftNode;
                    } else { //edo einai periptosi left rotation
                        this->root = node->rightNode;
                    }
                }
            }
            //cout<<"Starting to balance <<" << node->word << ">> LHEIGHT = " << LHeight << " RHEIGHT = " << RHeight <<endl;
            balance(node, LHeight, RHeight);
            node->height = recursiveHeight(node);
            updateHeights(node);
            //cout<<"Ending the balance <<"<< node->word << ">>" << endl << endl;

        }
        //printNode(node);
        node = node->parentNode;
    }
    //cout << "--------------" << endl;
    return node;
}

void AVLTree::test(Node* node) {
    cout << recursiveHeight(node) << endl;
}
