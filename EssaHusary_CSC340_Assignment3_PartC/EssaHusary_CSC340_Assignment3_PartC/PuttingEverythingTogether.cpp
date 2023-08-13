#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>
#include "PuttingEverythingTogether.h"
#include "DataOperations.h"
#include "DataSource.h"



using namespace Together;
using namespace Operations;
using namespace Source;
using namespace std;



vector<string> Together::PuttingEverythingTogether::splitString(string word) {

    DataOperations splitStringObject;
    vector<string> splitInputIntoParts;   // vector storing 1 - 4 user inputted keys
    string inputtedKey = "";
    
    for (int i = 0; i < word.length(); i++) {

        if (word[i] == ' ') {             /* if there's a char ' ' (which is a space) in between keys, we "push_back" the string of chars just before ' ' into 
                                             "splitInputIntoParts" and reset the value of "inputtedKey" */

            splitInputIntoParts.push_back(inputtedKey);
            inputtedKey = "";
        }
        
        else {                           /* Otherwise, we "push_back" the current char into "inputtedKey" until the for loop encounters another ' ' */
            
            inputtedKey.push_back(word[i]);
        }
    }
    
    splitInputIntoParts.push_back(splitStringObject.lowerCaseString(inputtedKey));    /* we store the lowercase version of "inputtedKey" to be  
                                                                                         used in other methods because we want to ignore letter casing 
                                                                                         (see function "lowerCaseString()" in "DataOperations.cpp) */

    return splitInputIntoParts;
}




void PuttingEverythingTogether::finalProduct() {

    DataOperations key;
    DataSource data;


    string userProvidedFilePath;
    cout << "! Opening data file... ";
    cin >> userProvidedFilePath;        // user inputs a file path
    
    
    while (userProvidedFilePath != "Data.CS.SFSU.txt") {              // runs until user provides correct and *relative* path
        cout << "<!>ERROR<!> ===> File could not be opened." << endl;
        cout << "<!>ERROR<!> ===> Provided file path : " << userProvidedFilePath << endl;
        cout << "<!>Enter the CORRECT data file path : "; 
        cin >> userProvidedFilePath;
    }

    cin.ignore();    // clears the input buffer so as to prevent undesirable results



    cout << "! Loading data..." << endl;

    map<string, vector<vector<string>>> dictionaryData = data.addWordsToDatabase();    // copy of our map

    cout << "! Loading completed..." << endl;
    cout << "! Closing data file... " << userProvidedFilePath;
    cout << "\n" << endl;
    cout << "==== Dictionary 340 C++ ====" << endl;
    cout << "---- Keywords: " << dictionaryData.size() << endl;
    cout << "---- Definitions: " << data.numberOfDefinitions << endl;
    cout << endl;

    int search = 1;       // we're going to track the search number
    string stringOfInputtedKeys;          // will be used to store an entire line of user input


    while (true) {

        int numberOfUserEntries = 1;    /* tracks the number of user inputted keys/entries for the "defineEntry" function in "DataOperations.cpp" to 
                                           determine if a parameter belongs in a certain position */

        cout << "\n" << "Search [" << search++ << "]: ";
        

        vector<string> keyWords;
        vector<string> previousResults;
        getline(cin, stringOfInputtedKeys);             // gets an entire line of input from the user


        keyWords = splitString(key.lowerCaseString(stringOfInputtedKeys)); /* vector of keys/entries. copy of "splitInputIntoParts" from our 
                                                                              "splitString()" function */


        if (key.lowerCaseString(keyWords[0]) == key.lowerCaseString("!q")) {
            break;
        }

        else if (keyWords[0].empty() || key.lowerCaseString(keyWords[0]) == key.lowerCaseString("!help")) {

            key.sendInstruction();
        }

        else if (!dictionaryData.count(keyWords[0])) {

            cout << "       |\n" << "        <NOT FOUND> To be considered for the next release. Thank you.\n" << "       |" << endl;
            key.sendInstruction();
            continue;

        }
        else if (keyWords.size() == 1) {    // if true, prints the definitions of the word in alpha order and increments our entry tracker variable

            numberOfUserEntries++;
            key.displayResults(key.sortInAlphabeticalOrder(keyWords[0], dictionaryData));
        }

        if (keyWords.size() >= 5 && keyWords[4] != "") {        /* sends instructions only if there are five keys/entries. if there are 4 words and a 
                                                                   space(s) after the four words, this statement is ignored */
            key.sendInstruction();
        }

        else if (keyWords.size() >= 2) {     // if true, we start by returning the results in alphabetical order

            numberOfUserEntries++;
            previousResults = key.defineEntry(key.sortInAlphabeticalOrder(keyWords[0], dictionaryData), keyWords[1], numberOfUserEntries);

            if (keyWords.size() >= 3) {      // if true, we take and use the previous results to perform the next operation on them, such as reversing

                numberOfUserEntries++;
                previousResults = key.defineEntry(previousResults, keyWords[2], numberOfUserEntries);
                
                if (keyWords.size() >= 4) {   // if true, we take and use the previous results to perform the next operation on them, such as reversing

                    numberOfUserEntries++;
                    previousResults = key.defineEntry(previousResults, keyWords[3], numberOfUserEntries);
                }
            }

            key.displayResults(previousResults);   // takes previous results as input and prints/displays the results to the user

        }

    }

    cout << endl;
    cout << "-----THANK YOU-----" << endl;
}