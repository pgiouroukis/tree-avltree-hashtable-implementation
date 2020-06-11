#ifndef BTREE_H
#define BTREE_H

#include <string>

using namespace std;

struct Node {
    string word;
    int occurences;
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

        virtual Node* addWord(string w);
        Node* findWord(string w);
        bool deleteWord(string w);

        void printInOrder();
        void printPostOrder();
        void printPreOrder();

        Node *root;

    protected:

    private:

};

bool updateHeights(Node*);

#endif // BTREE_H
