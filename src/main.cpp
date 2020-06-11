#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <iostream>

#include "AVLTree.h"
#include "BTree.h"
#include "Hashtable.h"
#include "TextTable.h"

#define QSIZE 10000

using namespace std;

bool addToQ(int sum, int WordsInQ) {
    if (!(sum % 22) && WordsInQ < QSIZE)
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

    int num;
    Node *node1,*node2;
    TextTable t('-', '|', '+');
    t.add("Word");t.add("Hashtable occs");t.add("AVL occs");t.add("BTRee occs");t.endOfRow();
    for (i = 0; i < QSIZE; i+=100) {

        t.add(" Word: " + Q[i]);

        num = a.findWord(Q[i]);
        t.add(" Hashtable Occs: " + to_string(num));

        node1 = atree.findWord(Q[i]);
        t.add(" AVLTree Occs: " + to_string(node1->occurences));

        node2 = tree.findWord(Q[i]);
        t.add(" BTree Occs: " + to_string(node2->occurences));
        t.endOfRow();
    }
    //t.setAlignment(2, TextTable::Alignment::LEFT);
    cout << t << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;


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
