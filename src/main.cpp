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

bool addToQ(int sum, int WordsInQ);
void printSomeOccurences(int step, string*, Hashtable*, AVLTree*, BTree*);
void printTimeComparison(string *, Hashtable *, AVLTree *, BTree *);
int CountWords(string);

int main() {

    BTree bTree;
    AVLTree avlTree;

    string *Q = new string[QSIZE];
    int WordsInQ=0;

    int sum = 0;
    unsigned int i;

    sum=CountWords("small-file.txt");
    Hashtable hashtable(sum);
    cout<<sum<<endl;



    ifstream file("small-file.txt");

    string linestr;
    string word;
    int line = 0;
    int loaderCount=0;

    //sum=0;
    while ( getline(file, linestr) ) {
        if (line % 10000 == 0) {
            loaderCount++;
            cout << '\r' << flush;
            cout << "Reading the words... |" ;
            for (int i=0;i<6;i++) if (i<loaderCount) cout << "+++++++++"; else cout << "     ";
            cout << "|  ";
        }
        line++;
        linestr.append(".");
        word = "";

        for (i=0; i<linestr.length(); i++) {
            if (isalpha(linestr[i]))
                word.append(string(1,linestr[i]));
            else {
                if (word!="") {
                    bTree.addWord(word);
                    avlTree.addWord(word);
                    hashtable.addWord(word);

                    sum++;

                    if (addToQ(sum,WordsInQ)) {
                        WordsInQ++;
                        Q[WordsInQ-1]=word;
                    }
                }
                else continue;
                word = "";
            }
        }
    }

    printSomeOccurences(1, Q, &hashtable, &avlTree, &bTree);

    cout << "------------------------------------" << endl;

    printTimeComparison(Q, &hashtable, &avlTree, &bTree);

    return 0;
}



void printTimeComparison(string *Q, Hashtable *a, AVLTree *atree, BTree *tree) {

    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    //measure the time for the AVL Tree
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < QSIZE; i++)
        atree->findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In AVL Tree : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    //measure the time for the Hashtable
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < QSIZE; i++)
        a->findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In HashTable : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    //measure the time for the Binary Search Tree
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < QSIZE; i++)
        tree->findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In Binary Search Tree : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

}

void printSomeOccurences(int step, string *Q, Hashtable *a, AVLTree *atree, BTree *tree) {
    int num;
    int i;
    Node *node1, *node2;
    TextTable t('-', '|', '+');
    t.add("Word");
    t.add("Hashtable occs");
    t.add("AVL occs");
    t.add("BTRee occs");
    t.endOfRow();
    for (i = 0; i < QSIZE; i += step)
    {


        t.add(" Word: " + Q[i]);

        num = a->findWord(Q[i]);
        t.add(" Hash Occs: " + to_string(num));

        node1 = atree->findWord(Q[i]);
        t.add(" AVL Occs: " + to_string(node1->occurences));

        node2 = tree->findWord(Q[i]);
        t.add(" BTree Occs: " + to_string(node2->occurences));
        t.endOfRow();
    }
    cout << t << endl;
    return;
}

bool addToQ(int sum, int WordsInQ) {
    if (!(sum % 2) && WordsInQ < QSIZE)
        return true;
    return false;
}

int CountWords(string FileName){

    ifstream file(FileName);

    string linestr;
    string word;
    int sum;
    unsigned int i;


    while ( getline(file, linestr) ) {
        linestr.append(".");
        word = "";

        for (i=0; i<linestr.length(); i++) {
            if (isalpha(linestr[i]))
                word.append(string(1,linestr[i]));
            else {
                if (word!="") {
                    sum++;
                }
                else continue;
                word = "";
            }
        }
    }
    file.close();
    return sum;
}
