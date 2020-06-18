#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>

using namespace std;

class Hashtable
{
public:
    Hashtable(int);
    ~Hashtable();
    void setA(int);
    void setB(int);
    bool addWord(string);
    int findWord(string);

private:
    string *A;
    int *B;
    int Size;
};

int HashFunction(string, int);

#endif // HASHTABLE_H