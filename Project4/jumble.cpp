#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    string word; //word to be mapped
    string key; //sorted key to map word at
    int wordCount = 0; //number of words in text file
    int classCount = 0; //number of distinct classes
    int max = 0; //size of class with most words associated
    string maxClass; //key to class with most words associated

    unordered_map<string, vector<string>> map;
    ifstream file;

    if (argc != 2) // no file given
    {
        std::cout << "usage:  ./jumble <filename>\n";
        std::cout << "goodbye\n";
        return 1;
    }

    file.open(argv[1], ios::in); // open the text file

    if (!file.is_open()) // cant open file
    {
        std::cout << "Error: could not open file '" << argv[1] << "'\n";
        std::cout << "goodbye\n";
        return 1;
    }

    std::cout << "reading input file...\n";

    while (file >> word) //put all words from text file into map
    {
        key = word;
        sort(key.begin(), key.end()); // sort the word to get the key

        map[key].push_back(word);

        wordCount++;
        if (map[key].size() > max){ //update max class
            max = map[key].size();
            maxClass = key;
        }

        if (map[key].size() == 1)
            classCount++;
    }

    file.close(); //close the text file

    cout << "start entering jumbled words (ctrl -d to terminate)" << endl
         << ">";
    while (cin >> word) // take in user input
    {
        sort(word.begin(), word.end());

        if (map[word].size() == 0)
            cout << "no anagrams found...try again" << endl;
        else
        {
            cout << "English anagrams found:" << endl;
            for (int i = 0; i < map[word].size(); i++)
                cout << map[word][i] << endl;
        }
        cout << ">";
    }

    //after user enters ctrl -d print the report of the text file
    cout << "REPORT:" << endl << endl;

    cout << "num_words             :   " << wordCount << endl;
    cout << "num_classes           :   " << classCount << endl;
    cout << "size-of-largest-class :   " << max << endl;
    cout << "largest-class key     :   " << maxClass << endl;

    cout << "members of largest class:" << endl;

    for (int i = 0; i < map[maxClass].size(); i++)
        cout << map[maxClass][i] << endl;

    return 0;
}