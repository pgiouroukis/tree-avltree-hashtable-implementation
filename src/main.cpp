#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "AVLTree.h"
#include "BTree.h"
#include "Hashtable.h"
#include "TextTable.h"

#define QSIZE 10000

using namespace std;

//declaring some function here, implementing them at the bottom
bool addToQ(int sum, int WordsInQ);                                              //determine whether a word should be added to Q, randomly
void printSomeOccurrences(int step, string *Q, int QcurrentWords, Hashtable *, AVLTree *, BTree *); //print some occurrences of Q, based on a "step", for all three of the DataStructures
void printTimeComparison(string *Q, int QcurrentWords, Hashtable *, AVLTree *, BTree *);            //compare the search time against Q for all the Data Structures
int CountWords(string filename);                                                 //count the words from the file given

int main()
{

    //parse the file to get the number of words
    int sum = CountWords("small-file.txt");

    //initialize the data structures
    BTree bTree;
    AVLTree avlTree;
    Hashtable hashtable(sum);

    //create an array Q, with a size of QSIZE
    string *Q = new string[QSIZE];
    int WordsInQ = 0;

    //open the file
    ifstream file("small-file.txt");

    //declare the rest of the variables
    unsigned int i;      //counter for the loops
    string linestr;      //used to get every line of the file as a string
    string word;         //keeps the word that we will insert in the data structures
    int line = 0;        //the file line we are currently reading
    int loaderCount = 0; //for the loader animation
    int pos = 0;         // the number of word we are currently reading

    //start inserting words to the data structures

    //scan the file line by line
    while (getline(file, linestr))
    {
        //just a silly animation counter, ignore it
        if ((line++) % 10000 == 0)
        {
            loaderCount++;
            cout << '\r' << flush << "Reading the words... |";
            for (int i = 0; i < 6; i++)
                if (i < loaderCount)
                    cout << "+++++++++";
                else
                    cout << "         ";
            cout << "|  ";
        }

        //append a "." at the end of the line, so the following code generalize.
        linestr.append(".");

        word = ""; //initialize an empty "word"

        //start scanning the line character by character
        for (i = 0; i < linestr.length(); i++)
        {

            //append to "word" if the character read is a letter or number (ignoring punctuation and special characters)
            if (isalpha(linestr[i]))
                word.append(string(1, linestr[i]));
            else
            { //otherwise, it reached the end of a word.

                if (word != "")
                {                            // if the "word" variable is not empty, there is a word to add
                    bTree.addWord(word);     //add the word to the bTree
                    avlTree.addWord(word);   //add the word to the avlTree
                    hashtable.addWord(word); //add the word to the hash table

                    pos++; //increase the pos variable

                    if (addToQ(pos, WordsInQ))
                    {                       //determine if the word should be added to Q
                        Q[WordsInQ] = word; //add the word to Q
                        WordsInQ++;
                    }
                }
                else
                    continue; //otherwise, we continue with the next character

                word = ""; //reseting the "word" variable
            }
        }
    }
    file.close(); //closing the file
    cout << endl;

    printSomeOccurrences(100, Q, WordsInQ-1, &hashtable, &avlTree, &bTree);
    cout << "------------------------------------------------------" << endl;
    printTimeComparison(Q, WordsInQ-1,&hashtable, &avlTree, &bTree);

    return 0;
}

void printTimeComparison(string *Q, int QcurrentWords, Hashtable *a, AVLTree *atree, BTree *tree)
{

    //declaring the variables from the chrono library
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;

    //measure the time for the Hashtable
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < QSIZE; i++)
        a->findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In HashTable : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    //measure the time for the AVL Tree
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < QSIZE; i++)
        atree->findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In AVL Tree : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;

    //measure the time for the Binary Search Tree
    begin = std::chrono::steady_clock::now();
    for (int i = 0; i < QSIZE; i++)
        tree->findWord(Q[i]);
    end = std::chrono::steady_clock::now();
    cout << "Time In Binary Search Tree : " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds" << std::endl;
}

void printSomeOccurrences(int step, string *Q, int QcurrentWords, Hashtable *a, AVLTree *atree, BTree *tree)
{

    int num;
    int i;
    Node *node1, *node2;

    //initializing the TextTable, a class provided by a github repo
    TextTable t('-', '|', '+');

    //creating the table head row
    t.add("Word");
    t.add("Hashtable occs");
    t.add("AVL occs");
    t.add("BTRee occs");
    t.endOfRow();

    //starting to search for some words in Q, in every data structure
    for (i = QSIZE - 1; i > 0; i -= step)
    {
        t.add(" Word: " + Q[i]);

        //search the word in the hashtable and print the occurrences
        num = a->findWord(Q[i]);
        t.add(" Hash Occs: " + to_string(num));

        //search the word in the avl tree and print the occurrences
        node1 = atree->findWord(Q[i]);
        t.add(" AVL Occs: " + to_string(node1->occurrences));

        //search the word in the btree and print the occurrences
        node2 = tree->findWord(Q[i]);
        t.add(" BTree Occs: " + to_string(node2->occurrences));
        t.endOfRow();
    }
    cout << t << endl;
    return;
}

int CountWords(string FileName)
{

    //open the file
    ifstream file(FileName);

    //declare some variables
    string linestr;
    string word;
    unsigned int i;
    int sum = 0;

    cout << "Counting the number of words in the text file..." << endl;

    //scan the file line by line
    while (getline(file, linestr))
    {
        linestr.append(".");

        word = "";

        //start scanning the line character by character
        for (i = 0; i < linestr.length(); i++)
        {

            //append to "word" if the character is a letter or number
            if (isalpha(linestr[i]))
                word.append(string(1, linestr[i]));
            else
            { //otherwise, it reached the end of a word.

                //if the "word" is not empty, increase the sum
                if (word != "")
                    sum++;
                else
                    continue; //otherwise, continue scanning the file
                word = "";
            }
        }
    }

    //closing the file and returning
    file.close();
    return sum;
}

bool addToQ(int pos, int WordsInQ)
{
    if (!(pos % 25) && WordsInQ < QSIZE)
        return true;
    return false;
}
