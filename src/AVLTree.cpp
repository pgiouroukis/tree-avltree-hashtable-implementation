#include "AVLTree.h"
#include <cmath>

void printNode(Node* node) {
    cout << "Word: " << node->word << " ||| Parent Word: " << (node->parentNode!= nullptr ? node->parentNode->word : "nullptr")
         << " ||| left Word: " << (node->leftNode!=nullptr ? node->leftNode->word : "nullptr")
         << " ||| right Word: " << (node->rightNode!=nullptr ? node->rightNode->word : "nullptr") << endl;
    return;
}

bool increaseHeight(Node* node) {
    node->height++;
    if (node!=nullptr) {
        increaseHeight(node->leftNode);
        increaseHeight(node->rightNode);
        return true;
    } else return false;
}

int height(Node* node) {
    int LHeight;
    int RHeight;
    if (node != nullptr) {
        LHeight = height(node->leftNode) + 1;
        RHeight = height(node->rightNode) + 1;
        return (LHeight>RHeight ? LHeight : RHeight);
    } else
        return 0;
}


Node* rightRotate(Node* node)
{
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

Node* leftRotate(Node* node)
{

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

        childLeftHeight = height(node->leftNode->leftNode);
        childRightHeight = height(node->leftNode->rightNode);

        if (childLeftHeight >= childRightHeight) {
            //cout<<"    Starting right rotate" << endl;
            rightRotate(node);
        } else {
            //cout<<"    Starting left-right rotate" << endl;
            leftRotate(node->leftNode);
            rightRotate(node);
        }

    } else {

        childLeftHeight = height(node->rightNode->leftNode);
        childRightHeight = height(node->rightNode->rightNode);

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

Node* AVLTree::addWord(string word){

    int LHeight;
    int RHeight;

    //we call the parent's add word method, then we balance the tree
    Node* node = BTree::addWord(word);

    //we check if the tree needs balancing
    while (node != nullptr) {
        LHeight = height(node->leftNode);
        RHeight = height(node->rightNode);
        if ( abs(LHeight-RHeight) > 1 ) {

            if (node == root) {
                //an to node poy exei thema einai to root, logo ton rotations, prepe na allaksoume tin rize tou dentroy
                if (LHeight > RHeight) {
                    if ( height(node->leftNode->rightNode) > height(node->leftNode->leftNode) ) { //edo einai periptosi left-right rotation
                        this->root = node->leftNode->rightNode;
                    } else { //edo eina periptosi right rotation
                        this->root = node->leftNode;
                    }

                }
                else {
                    if (height(node->rightNode->leftNode) > height(node->rightNode->rightNode)) { //edo einai periptosi right-left rotation
                        this->root = node->rightNode->leftNode;
                    } else { //edo einai periptosi left rotation
                        this->root = node->rightNode;
                    }
                }
            }
            //cout<<"Starting to balance <<" << node->word << ">> LHEIGHT = " << LHeight << " RHEIGHT = " << RHeight <<endl;
            balance(node, LHeight, RHeight);
            //cout<<"Ending the balance <<"<< node->word << ">>" << endl << endl;

        }
        node = node->parentNode;
    }

    return node;
}

void AVLTree::test(Node* node) {
    cout << height(node) << endl;
}
