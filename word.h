#include "document.h"


//token holds a document and instances in that document
class token{
    private:
    parsedDocument* file;
    int instances;
    
    public:
    token(parsedDocument *i){
        file = i;
        instances = 1;
    }

    void increment(){
        instances++;
    }

    int getInstances(){
        return instances;
    }

    parsedDocument* getFilePointer(){
        return file;
    }
};


//word holds a master word and a vector of tokens that show where the word appears and how many times it does
class word{
    private:
    string wordProper;
    vector<token*> fileList;

    public:
    //pass in file pointer
    word(string input, parsedDocument *file){
        wordProper = input;
        token* temp = new token(file);
        fileList.push_back(temp);
    }

    //word object without doc
    word(string input){
        wordProper = input;
    }

    void wordAppearance(parsedDocument *file){
        for(token* i : fileList){
            if(i->getFilePointer() == file){
                i->increment();
                return;
            }
        }
        token* temp = new token(file);
        fileList.push_back(temp);

    }

    string getWordProper(){
        return wordProper;
    }

    int getWordAppearancesFile(parsedDocument *file){
        for(token* i : fileList){
            if(i->getFilePointer() == file){
                return i->getInstances();
            }
        }
        return -1;
    }

    vector<token*> getFileList(){
        return fileList;
    }

    bool operator<(const word &rhs){
        if(wordProper < rhs.wordProper){
            return true;
        }
        return false;
    }

    bool operator>(const word &rhs){
        if(wordProper > rhs.wordProper){
            return true;
        }
        return false;
    }

    bool operator==(const word &rhs){
        if(wordProper == rhs.wordProper){
            return true;
        }
        return false;
    }

     friend std::ostream &operator<<(std::ostream &output, const word &toOutput)
    {
        output << toOutput.wordProper;
        return output;
    }

};