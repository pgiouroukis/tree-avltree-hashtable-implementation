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
};

class BTree
{
    public:
        BTree();
        virtual ~BTree();

        Node* getRoot() {return root;}

        Node* addWord(string w);
        Node* findWord(string w);
        bool deleteWord(string w);

        void printInOrder();
        void printPostOrder();
        void printPreOrder();

    protected:

    private:
        Node *root;
};

#endif // BTREE_H
