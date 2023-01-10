#include <sstream>
#include "indexHandler.cpp"
using namespace std;

// query processor is the user interface
class queryProcessor
{
public:
    int startEngine()
    {
        string userEntry;
        indexHandler masterIndex;
        while (true)
        {
            cout << "\nwelcome to the search engine. Please choose what you would like to do" << endl;
            cout << "To build the search engine enter: \'1\'" << endl;
            cout << "To enter a query enter: \'2\'" << endl;
            cout << "To check the metadata for this search engine enter: \'3\'" << endl;
            cout << "To exit the program enter \'0\'" << endl
                 << endl;

            getline(cin, userEntry);

            if (userEntry == "0")
            {
                cout << "ending program " << endl;
                break;
            }
            else if (userEntry == "1")
            {
                string masterPath;
                cout << "enter path to files that should be indexed: " << endl;
                getline(cin, masterPath);
                cout << "building search engine" << endl;
                // need to add an additional prompt for path to the data from which to build a search engine
                masterIndex.buildTree(masterPath); 
            }
            else if (userEntry == "2")
            {
                // in context enter a "query state" where the user can enter as many queries they want
                // prompt and read in user input
                string fullQuery;
                cout << "enter query:" << endl;
                getline(cin, fullQuery);

                // send that input to the indexHandler
                vector<token *> searchResults = masterIndex.searchTree(fullQuery);
                printSearchResults(searchResults);
            }
            else if (userEntry =="3"){
                masterIndex.printMetaData();
            }
            else
            {
                cout << "invalid option please try again" << endl;
                // loop back to the top
            }
        }
        return 0;
    }

    void printSearchResults(vector<token *> results)
    {

        if (results.empty())
        {
            cout << "no files matched your search." << endl;
        }
        else
        {
            cout << "search results: \n"
                 << endl;
            int counter = 1;
            for (token *i : results)
            {
                cout << "result " << counter << ":" << endl;
                cout << i->getFilePointer()->getTitle() << endl;
                cout << "the path to this file is: " << i->getFilePointer()->getPath() << endl;
                counter++;
            }
            int fileChoice;
            cout << "To get the entire text of a file enter the number of the file. Otherwise enter 0" << endl;
            cin >> fileChoice;
            cin.ignore();
            
            if(fileChoice != 0){
                if(fileChoice <= results.size()){
                    cout << results.at(fileChoice-1)->getFilePointer()->getFullText() << endl;
                }
            }
        }
    }
};