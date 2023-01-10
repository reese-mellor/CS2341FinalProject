#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"
#include "porter2_stemmer.h"
#include "stopFunction.h"

using namespace std;
using namespace rapidjson;

class parsedDocument
{
private:
    string fullText;
    vector<string> organizations;
    vector<string> people;
    vector<string> words;
    string filePath;
    string title;

public:
    parsedDocument(string path){
    // open an ifstream on the file of interest and check that it could be opened.
    filePath = path;
    ifstream input(path);
    if (!input.is_open())
    {
        cerr << "cannot open file: " << path << endl;
        return;
    }

    // Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    Document d;
    d.ParseStream(isw);

    //sort info for later
    title = d["title"].GetString();
    
    auto temp = d["entities"]["persons"].GetArray();
    for (auto &p : temp)
    {
        people.push_back(p["name"].GetString());
    }
    
    
    auto temp2 = d["entities"]["organizations"].GetArray();
    for (auto &p : temp2)
    {
        organizations.push_back(p["name"].GetString());
    }
    
    fullText = d["text"].GetString();

        //these stringstream errors are a lie it compiles just fine
        //break text into individual words
        string oneWord;
        stringstream s(fullText);
       
        //FIXME doesnt currently keep track of instances
        while(s >> oneWord){
            Porter2Stemmer::trim(oneWord);
            Porter2Stemmer::stem(oneWord);
            if(checker.isStop(oneWord) || oneWord.empty()){
                continue;
            }
            words.push_back(oneWord);
        }

    }

    vector<string> getOrgs(){
        return organizations;
    }

     vector<string> getPeople(){
        return people;
    }

     vector<string> getWords(){
        return words;
    }

    string getPath(){
        return filePath;
    }

    string getTitle(){
        return title;
    }

    string getFullText(){
        return fullText;
    }

    };