#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class stopList{
    private:

    vector<string> stopWords;

    public:

    stopList(){
        ifstream fileIn;

        fileIn.open("../stopWord.txt");
        if(!fileIn.is_open()){
            cerr << "stopwords file cannot be opened" << endl;
            return;
        }

        string wordString;
        while(getline(fileIn, wordString)){
            stopWords.push_back(wordString);
        }
    }

    //returns true if a passed string is a stop word PASS IN STEMMED WORD
    bool isStop(string query){
        for(string i : stopWords){
            if(i == query){
                return true;
            }
        }
        return false;
    }
};

//declare here so it only builds once
static stopList checker;
