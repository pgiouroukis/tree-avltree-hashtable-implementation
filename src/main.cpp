#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "AVLTree.h"
#include "BTree.h"
#include "Hashtable.h"

#define QSIZE 10000

using namespace std;

bool addToQ(int sum, int WordsInQ) {
    if (!(sum % 23) && WordsInQ < QSIZE)
        return true;
    return false;
}


int main() {
    Hashtable a(500000);
    BTree tree;
    AVLTree atree;

    string *Q = new string[QSIZE];
    int WordsInQ=0;

    int sum = 0;
    unsigned int i;

    ifstream file("small-file.txt");
    
    string linestr;
    string word;
    int line = 1;

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    while ( getline(file, linestr) ) {
        line++;
        linestr.append(".");

        word = "";

        for (i=0; i<linestr.length(); i++)
        {
            if (isalpha(linestr[i]))
            {
                word.append(string(1,linestr[i]));
            }
            else
            {
                if (word!="")
                {
                    tree.addWord(word);
                    atree.addWord(word);
                    a.addWord(word);

                    sum++;

                    if (addToQ(sum,WordsInQ))
                    {
                        WordsInQ++;
                        Q[WordsInQ-1]=word;
                    }
                }
                else continue;
                word = "";
            }
        }
    }

    begin = std::chrono::steady_clock::now();
    for (i = 0; i < QSIZE; i++)
        a.findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In HashTable : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    begin = std::chrono::steady_clock::now();
    for (i = 0; i < QSIZE; i++)
        atree.findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In AVL Tree : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    begin = std::chrono::steady_clock::now();
    for (i = 0; i < QSIZE; i++)
        tree.findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In Binary Search Tree : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;


    return 0;
}

