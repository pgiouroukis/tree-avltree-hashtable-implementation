#include "Hashtable.h"
#include <string>
#include <iostream>

using namespace std;

Hashtable::Hashtable(int wordCount)
{
    Size = 2 * wordCount; //The size of the arrays should be twice the sum of the words in the file

    setA(Size); //A is the array containing the words of the text
    setB(Size); //B is the array containing the frequency of every word
}

Hashtable::~Hashtable()
{
    delete[] A;
    delete[] B;
}

void Hashtable::setA(int Size) //Construction of an array which contains the words
{
    int i;

    A = new string[Size];

    for (i = 0; i < Size; i++)
        A[i] = "-"; //Each position of the array contains a "-" when it is empty
}

void Hashtable::setB(int Size) //Construction of an array which contains the occurrences of each word found in the text
{
    int i;

    B = new int[Size];

    for (i = 0; i < Size; i++)
        B[i] = 0; //All positions of this array is set to 0 since there are no words given yet.
}

bool Hashtable::addWord(string A_word)
{
    int startPos, i;
    startPos = HashFunction(A_word, Size); //
    i = startPos;

    if (A[startPos] == "-") //If the starting position is empty then the word is placed in that position
    {                       //And +1 is added to the frequency array
        A[startPos] = A_word;
        B[startPos]++;
    }
    else if (A[startPos] == A_word) //If the same word as the one given is already in this position, then +1 is added in
        B[startPos]++;              //the frequency array

    else
    {                                         //The last case checked is if another word than the one given has the same hash value therefore being set
        while (A[i] != "-" && A[i] != A_word) //in the same position. In this case the program starts searching all the positions after it until it finds
        {                                     //an empty spot("-"), where it sets it.
            i++;
            if (i > Size - 1)
                i = 0;
        }
        A[i] = A_word;
        B[i]++;
    }
    return true;
}

int Hashtable::findWord(string A_word)
{
    int startPos, i;
    bool found = 0;

    startPos = HashFunction(A_word, Size); //The search always begins from the posistion the HashFunction returns
    i = startPos;

    if (A[startPos] == "-") //If the hash position of the word is empty then then there is no way the word is in this array and the search
    {                       // is unsuccessful
        return -1;
    }

    while (!found) //found is a guard variable which signals the stop of the while loop if the word is found inside the array
    {

        if (A[i] == A_word) //If the word is in its hash position then we print the appropriate message
        {
            return B[i];
        }
        else
        {
            i++; //if this word is not found in that position then the program starts searching in the rest of the array to find it

            if (i > Size - 1) //if it reaches the end then it goes on from the start of the array
                i = 0;

            if (i == startPos) //Finally if the program does a full circle and still did not find the word, then the search was unsuccessful
            {
                return B[i];
            }
        }
    }

    return true;
}

int HashFunction(string a, int Size) //This function receives a string and the size of the array B and returns an integer
{                                    //that shows where the word should be placed on the word array.
    int key = 151;
    unsigned long hash = 0;
    for (int i = 0; i < a.length(); i++)
    {
        hash = (hash * key) + a[i];
    }
    return hash % Size;
}
