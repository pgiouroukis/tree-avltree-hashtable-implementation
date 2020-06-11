#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "AVLTree.h"
#include "BTree.h"
#include "Hashtable.h"

using namespace std;

bool addToQ(int sum, int WordsInQ)
{

    if (!(sum%25) && WordsInQ<10000)
    {
        return true;
    }
    return false;
}


int main()
{
    Hashtable a(500000);
    BTree tree;
    AVLTree atree;

    string *Q;
    Q = new string[10000];
    int WordsInQ=0;

    int sum = 0;
    unsigned int i;

    ifstream file("small-file.txt");
    string linestr;
    string word;

    int line = 1;

    while ( getline(file, linestr) )
    {
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
                    //atree.addWord(word);
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


    for (i=0;i<10000;i++)
    {
        a.findWord(Q[i]);
        tree.findWord(Q[i]);
        //atree.findWord("treachery");
    }

    return 0;
}

