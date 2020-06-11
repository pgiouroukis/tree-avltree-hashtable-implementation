#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "BTree.h"

using namespace std;

class AVLTree : public BTree
{
    public:
        AVLTree() {}
        virtual ~AVLTree() {}

        void test(Node* node);

        Node* addWord(string word);

    protected:

    private:
};

#endif // AVLTREE_H
