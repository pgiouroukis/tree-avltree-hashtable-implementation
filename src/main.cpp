#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "AVLTree.h"
#include "BTree.h"
#include "Hashtable.h"

#include "TestClass.h"

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
                    //tree.addWord(word);
                    atree.addWord(word);
                    //a.addWord(word);
                   // cout<<sum<<endl;

                    //a.place(word);
                    sum++;

                } else continue;
                word = "";
            }
        }
    }

    /*
    atree.addWord("the");
    atree.addWord("project");
    atree.addWord("gutenberg");
    atree.addWord("eBook");
    atree.addWord("of");
    atree.addWord("the");
    atree.addWord("kostas");
    */
    //atree.test(atree.getRoot());

    //atree.printPostOrder();*/


    //cout<<sum<<endl;

    atree.findWord("The");


    return 0;
}

//paok ellada dania cyprus denia bagladesh finland fagito fzlol zebra zabra .
