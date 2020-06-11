#include "BTree.h"
#include <string>
#include <iostream>

using namespace std;

BTree::BTree() {
    //ctor
    root = nullptr;
}

BTree::~BTree() {
    //dtor
}

Node* newNode(string w, Node* parent){
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

    if (root == nullptr) {
        Node *node = newNode(w, nullptr);
        root = node;
        return node;
    } else {

        Node *ptr = root;
        bool flag = true;

        while( flag ) {

            if( w.compare(ptr->word) == 0) {
                //cout<<w<<"="<<ptr->word<<endl;
                ptr->occurences++;
                return ptr;
            } else if (w.compare(ptr->word) < 0) {
                //cout<<w<<"<"<<ptr->word<<endl;
                if (ptr->leftNode != nullptr) {
                    ptr = ptr->leftNode;
                } else {
                    flag = false;
                    ptr->leftNode = newNode(w, ptr);
                    updateHeights(ptr->leftNode);
                    return ptr->leftNode;
                }
            } else {
                //cout<<w<<">"<<ptr->word<<endl;
                if (ptr->rightNode != nullptr) {
                    ptr = ptr->rightNode;
                } else {
                    flag = false;
                    ptr->rightNode = newNode(w, ptr);
                    updateHeights(ptr->rightNode);
                    return ptr->rightNode;
                }
            }
        }

    }
    return nullptr;
}

Node* BTree::findWord(string w) {

    Node *ptr = root;
    bool found = false;

    while ( !found && ptr!=nullptr ) {
        if (w.compare(ptr->word) == 0) {
            std::cout<<"occurences: " << ptr->occurences <<endl;
            found = true;
            return ptr;
        } else if (w.compare(ptr->word) < 0) {
            ptr = ptr->leftNode;
        } else {
            ptr = ptr->rightNode;
        }
    }
    if (!found) {
        return nullptr;
    }
    return nullptr;
}

bool BTree::deleteWord(string w) {

    //arxika, vrisko to node poy einai pros diagrafi, kai to onomazo ptr
    Node *ptr = this->findWord(w);

    //an den vrethei to node, diladi an to ptr einai null, epistrefo false, diladi den diagrafike to stoixeio
    if (ptr == nullptr) {
        return false;
    } else {
        if (ptr->leftNode == nullptr && ptr->rightNode == nullptr) {
            //to ptr den exei kanena paidi, einai diladi leaf

            //sthn periptosi auti, prepei na enimeroso ton patera toy oste na deixnei se nullptr
            //prota omos prepei na vro an o pateras toy ptr exei to ptr deksi h aristero paidi (oste na min enimeroso to lathos paidi).

            //arxika, elegxo an exei patera (mporei na einai root node)
            if (ptr->parentNode != nullptr) {
                //efoson exei patera, vrisko an to ptr eina deksi i aristero paidi toy
                if (ptr->parentNode->leftNode == ptr) {
                    //to ptr einai aristero paidi
                    ptr->parentNode->leftNode = nullptr;
                } else {
                    //to ptr einai deksi paidi
                    ptr->parentNode->rightNode = nullptr;
                }
            } else {
                //an den exei parent node, einai to root node, ara, afoy eprokeito na to diagrapso,
                //prepei na valo to root node na deixnei se nullptr
                root = nullptr;
            }
            //apodesmeuo ton xoro toy node apo to heap
            delete ptr;

            //epistrefo true, afoy h diagrafh itan epitixis
            return true;

        } else if (ptr->leftNode == nullptr || ptr->rightNode == nullptr) {
            //to ptr exei 1 paidi, esto childPtr (den kseroume akoma an einai deksi h aristero)

            Node *childPtr;

            //vrisko arxika to paidi auto, diladi na einai deksi i aristero, kai to onomazo childPtr
            if (ptr->leftNode != nullptr) {
                childPtr = ptr->leftNode;
            } else {
                childPtr = ptr->rightNode;
            }

            //ama exei patera to ptr, prepei na enimeroso ton patera toy me to childPtr
            if (ptr->parentNode != nullptr) {
                //prepei na valo to childPtr deksia h aristera ston patera toy ptr, analoga me to poy einai o ptr se sxesi me ton patera toy

                if (ptr->parentNode->leftNode == ptr) {
                    //to ptr einai aristero paidi toy patera toy
                    ptr->parentNode->leftNode = childPtr;
                } else {
                    //to ptr einai deksi paidi toy patera toy
                    ptr->parentNode->rightNode = childPtr;
                }
                childPtr->parentNode = ptr->parentNode;
            } else {
                //ama o ptr den exei patera, tote einai to root node
                //ara prepei na theso to childPtr os root
                root = childPtr;
                childPtr->parentNode = nullptr;
            }
            //apodesmeuo ton xoro toy ptr
            delete ptr;

            //epistrefo true, afoy h diagrafi itan epitixis
            return true;

        } else {
            //to ptr exei 2 paidia

            //arxika, thelo na vro to pio aristero leaf apo to deksi ipodentro
            Node *tptr = ptr->rightNode;
            //me thn while authn, vrisko to pio aristeo leaf apo to deksi ipodentro, as to poyme tptr
            while (tptr->leftNode != nullptr) {
                tptr = tptr->leftNode;
            }

            //prosoxi!!! to stoixeio auto (tptr) den mporei na exei aristero paidi (giati telika tha kataligame ekei)
            //omos mporei na exei deksi paidi. to deksi auto paidi toy prepei na to valoyme telika os aristero paidi toy gonea toy tptr.
            //prepei omos prota na eleksoume oti to tptr den einai to deksi paidi toy ptr, allios to parapano den isxyei
            if (ptr->rightNode != tptr) {
                if (tptr->rightNode!=nullptr) {
                    tptr->parentNode->leftNode = tptr->rightNode;
                } else {
                    tptr->parentNode->leftNode = nullptr;
                }
            }

            //metafero to tptr sthn thesi toy ptr
            tptr->leftNode = ptr->leftNode;
            if (ptr->rightNode != tptr)     tptr->rightNode= ptr->rightNode;
            tptr->parentNode = ptr->parentNode;

            //enimerono ton patera toy ptr, afou pleon prepei na deixnei sto tptr. (efoson yparxei, mporei to ptr na einai riza)
            if (ptr->parentNode != nullptr) {
                //prota omos prepei na ksero an to ptr eina deksi i aristero paidi
                if (ptr->parentNode->leftNode == ptr) {
                    //an einai aristero paidi, allakse to kai vale aristero paidi to tptr
                    ptr->parentNode->leftNode = tptr;

                } else {
                    //antistoixa, an einai deksi paidi, allakse to kai vale deksi paidi to tptr
                    ptr->parentNode->rightNode = tptr;
                }
            } else {
                //ama to ptr den exei patera, simainei oti einai to root node
                //ara prepei na thes to root os tptr
                root = tptr;
            }
            //diagrafo ton ptr apo to heap
            delete ptr;

            //epistrefo true, afou itan epitixis h diagrafi
            return true;
        }
    }

}

/* -------------------------------------------------------------------------------- */

void inOrder(Node *n) {

    if (n == nullptr) return;

    inOrder(n->leftNode);

    cout << "Word: " << n->word << " | Occurences: " << n->occurences << endl;

    inOrder(n->rightNode);

    return;

}

void BTree::printInOrder() {

    std::cout << "Starting inOrder Traversal..." << endl;

    inOrder(root);

    std::cout << endl;

    return;

}

void postOrder(Node *n) {

    if (n == nullptr) return;

    postOrder(n->leftNode);

    postOrder(n->rightNode);

    cout << "Word: " << n->word << " | Occurences: " << n->occurences << endl;

    return;

}

void BTree::printPostOrder() {

    std::cout << "Starting postOrder Traversal..." << endl;

    postOrder(root);

    std::cout << endl;

    return;

}

void preOrder(Node *n) {

    if (n == nullptr) return;

    cout << "Word: " << n->word << " | Occurences: " << n->occurences << endl;

    preOrder(n->leftNode);

    preOrder(n->rightNode);

    return;

}

void BTree::printPreOrder() {

    std::cout << "Starting preOrder Traversal..." << endl;

    preOrder(root);

    std::cout << endl;

    return;

}


/* -------------------------------------------------------------------------------- */

bool updateHeights(Node* node) {
    //cout << "HAHA";
    while (node->parentNode!=nullptr) {
        if (node->parentNode->height < node->height + 1) {
            node->parentNode->height = node->height + 1;
            //cout << "Updating height of word '" << node->parentNode->word << "' to " << node->height+1 << endl;
        }
        node = node->parentNode;
    }
    return true;
}
