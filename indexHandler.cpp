#include "word.h"
#include "AVLtree.h"
#include <filesystem>
#include <chrono>

class indexHandler
{
private:
    AvlTree<word> masterTree;
    vector<parsedDocument *> docList;
    int totalArticles = 0;
    int64_t timeToIndex;
    

public:
    void buildTree(string filePath)
    {   
        auto it = filesystem::recursive_directory_iterator(filePath);

        // loop over all the entries.
        auto start = chrono::high_resolution_clock::now();
        for (const auto &entry : it)
        {
            if (entry.is_regular_file() && entry.path().extension().string() == ".json")
            {
                parsedDocument *temp = new parsedDocument(entry.path().string()); // where should I delete this?
                docList.push_back(temp);
                addWords(temp);
                totalArticles++;
                if(totalArticles % 10000 == 0){
                    cout << totalArticles << " articles parsed so far." << endl;
                }
            }
        }
        auto stop = chrono::high_resolution_clock::now();
        
        auto duration = chrono::duration_cast<chrono::seconds>(stop - start);

        timeToIndex = duration.count();
    }

    void addWords(parsedDocument *docPtr)
    {
        for (string ite : docPtr->getWords())
        {
            word temp(ite, docPtr);
            word *tempptr = masterTree.insertReturnPointer(temp);
            if (tempptr == nullptr)
            {
                continue;
            }
            tempptr->wordAppearance(docPtr);
        }
    }

    vector<string> breakdownQuery(string fullQuery)
    {
        vector<string> words;
        string temp;
        stringstream ss;

        ss << fullQuery;

        // break full query into individual queries
        while (ss >> temp)
        {
            words.push_back(temp);
        }
        return words;

        
    }

    // may take in vector of already parsed search terms
    vector<token*> searchTree(string query)
    {
        bool isFirstTime = true;
        vector<string> words =breakdownQuery(query);
        vector<token*> results;
        // check each query one by one and call relevant functions to deal with those queries
        // this will basically serve as the "find" function later
        for (string i : words)
        {
            if (i.at(0) == '-')
            {
                cout << "in exclusion function" << endl;
                // call exclusion function
                string exclusion = i.substr(1,i.size());
                Porter2Stemmer::trim(exclusion);
                Porter2Stemmer::stem(exclusion);
                bool matchFlag = true;

                for(size_t j = 0; j < results.size(); j++){
                    for(string k : results.at(j)->getFilePointer()->getWords()){
                        //checks if file has this person in it and sets flag if it is
                        if (k == exclusion){
                            matchFlag = false;
                            break;
                        }
                    }
                    //if flag is set to true then leaves the file in vector
                    if(matchFlag){
                        continue;
                    }
                    //if flag is set to false deletes the file from the vector
                    results.erase(results.begin()+j);
                    j--;
                    matchFlag = true;
                }
            }
            else if (i.substr(0, 7) == "PERSON:")
            {
                cout << "in person function" << endl;
                // filter results by people
                string person =  i.substr(7, i.size());
                bool matchFlag = false;

                for(size_t j = 0; j < results.size(); j++){
                    for(string k : results.at(j)->getFilePointer()->getPeople()){
                        //checks if file has this person in it and sets flag if it is
                        if (k == person){
                            matchFlag = true;
                            break;
                        }
                    }
                    //if flag is set to true then leaves the file in vector
                    if(matchFlag){
                        matchFlag = false;
                        continue;
                    }
                    //if flag is set to false deletes the file from the vector
                    results.erase(results.begin()+j);
                    j--;
                    matchFlag = false;
                }
                // DOES NOT need special case for searches for just person
            }
            else if (i.substr(0, 4) == "ORG:")
            {
                cout << "in org function" << endl;
                // filter results by organization
                string org =  i.substr(4, i.size());
                bool matchFlag = false;

                for(size_t j = 0; j < results.size(); j++){
                    for(string k : results.at(j)->getFilePointer()->getOrgs()){
                        //checks if file has this orginzation in it and sets flag if it is
                        if (k == org){
                            matchFlag = true;
                            break;
                        }
                    }
                    //if flag is set to true then leaves the file in vector
                    if(matchFlag){
                        matchFlag = false;
                        continue;
                    }
                    //if flag is set to false deletes the file from the vector
                    results.erase(results.begin()+j);
                    j--;
                    matchFlag = false;
                }
                // DOES NOT need special case for searches by organization
            }
            else
            {
                //stem and check for stop 
                if(checker.isStop(i)){
                    cout << "word \"" << i << "\" is not in the engine because it is too broad" << endl;
                    continue;
                }
                //clean the word
                Porter2Stemmer::trim(i);
                Porter2Stemmer::stem(i);
                //check that the string isn't empty
                if(i.empty()){continue;}    

                //initalize the list
                if(isFirstTime){
                    results = findWord(i);
                    isFirstTime = false;
                    continue;
                }

                //pair down existing list
                vector<token*> currentResults = findWord(i);
                bool matchFlag = false;
                for(size_t j = 0; j < results.size(); j++){
                    for(token* k : currentResults){
                        //checks if the same file is in both vectors if it is sets flag to true
                        if (k->getFilePointer() == results.at(j)->getFilePointer()){
                            matchFlag = true;
                            break;
                        }
                    }
                    //if flag is set to true then leaves the file in vector
                    if(matchFlag){
                        matchFlag = false;
                        continue;
                    }
                    //if flag is set to false deletes the file from the vector
                    results.erase(results.begin()+j);
                    j--;
                    matchFlag = false;
                }

                // search AVL tree for word
                /*idea for this is to create a vector that holds document objects and pair it down
                as the seach continues to get more specific. this means that the first search terms
                vector of documents should be copied in full*/

            }
        }
        return results;
    }

    //finds a word in the tree and returns that words vector of tokens (files and instances)
    vector<token*> findWord(string query){
        vector<token*> toReturn;
        word temp(query);
        word* inTreeInstance = masterTree.containsReturnPointer(temp);

        if(inTreeInstance == nullptr){return toReturn;}

        toReturn = inTreeInstance->getFileList();
        return toReturn;

    }

    void printMetaData(){
        cout << "Metadata for this search engine:" << endl;
        cout << "This search engine has indexed " << totalArticles << " files." << endl;
        cout << "This search engine has " << masterTree.getTotalNodes() << " words in its tree." << endl;
        cout << "It took " << timeToIndex << " seconds to index" << endl;
    }
};