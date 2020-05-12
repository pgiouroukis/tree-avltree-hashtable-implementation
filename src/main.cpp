#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "BTree.h"

using namespace std;

int main()
{

    BTree tree;
    Node *node;

    ifstream file("sampleText.txt");
    string linestr;
    string word;
    bool flag;

    auto start = chrono::high_resolution_clock::now();
    while ( getline(file, linestr) ) {
        word = "";
        for (int i = 0 ; i < linestr.length() ; i++) {
            if ( isalpha(linestr[i]) ) {
                word.append( string(1,linestr[i]) );
                if( i==linestr.length()-1) {
                    //cout<< word << endl;
                    word="";
                }
            } else {
                if (word!="") {
                    //cout<<word<<endl;
                    tree.addWord(word);
                } else continue;
                word = "";
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cout << "text read duration: " << duration.count() << endl <<endl;



    //tree.printPostOrder();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    node = tree.findWord("without");

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Word find duration = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "[ns]" << std::endl;

    //cout << "duration find: "<<duration.count() << endl;

    cout << "Word found. Occurences: "<<node->occurences << endl;


    return 0;
}

//paok ellada dania cyprus denia bagladesh finland fagito fzlol zebra zabra .
