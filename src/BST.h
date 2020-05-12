#ifndef BST_H
#define BST_H
#include <string.h>

using namespace std;

struct Node {
    string value;
    int counter;
    Node *leftChild;
    Node *rightChild;
};

class BST {

    public:

        BST();
        BST(string);
        virtual ~BST();

        Node* readWord(char *str);

    protected:

    private:
        Node *root;

};

#endif // BST_H
