#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "BTree.h"
#include "AVLTree.h"
#include "Hashtable.h"

using namespace std;

int main()
{
    Hashtable a(500000);
    BTree tree;
    AVLTree atree;

    int sum = 0;

    ifstream file("small-file.txt");
    std::string linestr;
    string word;

    int line = 1;


    while ( getline(file, linestr) ) {
        if ( line%1000==0) cout<<line<<endl;
        line++;
        linestr.append(".");

        word = "";
        for (int i = 0 ; i < linestr.length() ; i++) {
            if ( isalpha(linestr[i]) ) {
                word.append( string(1,linestr[i]) );
                if( i==linestr.length()-1) {
                    //cout<< word << endl;
                    word="";
                    sum++;
                }
            } else {
                if (word!="") {
                    //cout<<word<<endl;
                    tree.addWord(word);
                    atree.addWord(word);
                    a.addWord(word);
                   // cout<<sum<<endl;

                    //a.place(word);
                    sum++;

                } else continue;
                word = "";
            }
        }
    }

/*
    atree.addWord("the");           //atree.printInOrder();
    atree.addWord("project");       //atree.printInOrder();
    atree.addWord("gutenberg");     //atree.printInOrder();
    atree.addWord("eBook");         //atree.printInOrder();
    atree.addWord("of");            //atree.printInOrder();
    atree.addWord("the");           //atree.printInOrder();
    atree.addWord("kostas");        //atree.printInOrder();
    */
    //atree.test(atree.getRoot());

    //atree.printPostOrder();*/


    //cout<<sum<<endl;

    atree.findWord("The");
    tree.findWord("The");
    a.findWord("The");


    return 0;
}

//paok ellada dania cyprus denia bagladesh finland fagito fzlol zebra zabra .
