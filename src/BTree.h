#ifndef BTREE_H
#define BTREE_H

#include <string>

using namespace std;

struct Node { //declaration of the Node struct
    string word;
    int occurrences;
    Node *leftNode;
    Node *rightNode;
    Node *parentNode;
    int height;
};

class BTree {
    public:
        BTree();
        virtual ~BTree();

        Node* getRoot() {return root;}

        virtual Node* addWord(string w); //let the addWord method to be overridden
        virtual bool deleteWord(string w); //let the deleteWord method to be overridden
        Node* findWord(string w);

        void printInOrder();
        void printPostOrder();
        void printPreOrder();

        Node *root;

    protected:

    private:

};

bool updateHeights(Node*);

#endif // BTREE_H
