
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>
#include "BTree.h"

using namespace std;

class AVLTree : public BTree
{
public:
    AVLTree() {}          // the default constructor from BTree is called
    virtual ~AVLTree() {} //the default destructor from BTree is called

    //the overriden methods from BTree
    Node *addWord(string word);
    bool deleteWord(string word);

protected:
private:
};

#endif // AVLTREE_H