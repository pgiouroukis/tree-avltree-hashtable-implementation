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

bool updateParentsHeights(Node *node) {
    while (node!=nullptr) {
        if (node->parentNode!=nullptr) {
            if (node->parentNode->leftNode == nullptr) node->parentNode->height = node->parentNode->rightNode->height + 1;
            else if (node->parentNode->rightNode == nullptr) node->parentNode->height = node->parentNode->leftNode->height + 1;
            else node->parentNode->height = max(node->parentNode->leftNode->height, node->parentNode->rightNode->height) + 1;
        }
        node = node->parentNode;
    }
    return true;
}
