#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include "DataOperations.h"
#include "DataSource.h"



using namespace Operations;
using namespace std;
using namespace Source;




void DataOperations::sendInstruction() {

    cout << "       |" << endl;
    cout << "        PARAMETER HOW-TO,  please enter: " << endl;
    cout << "        1. A search key -then 2. An optional part of speech -then" << endl;
    cout << "        3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
    cout << "       |";

}




string Operations::DataOperations::toString(int i, string key)
{
    
    DataSource w;

    return  w.addWordsToDatabase().at(key)[i][2] + " [" + w.addWordsToDatabase().at(key)[i][1] + "] " + ": " + w.addWordsToDatabase().at(key)[i][0];
    
   
}




// returns a lower case version of a word to be used in comparisons so that search results don't depend on letter casing
string Operations::DataOperations::lowerCaseString(string word) {
    
    for (int i = 0; i < word.length(); i++) {

        word[i] = tolower(word[i]);
    }

    return word;
}




/* Displays our results after doing all of the operations we want to do (this uses the final "previousResults" variable in the 
   "PuttingEverythingTogether.cpp" class */
void DataOperations::displayResults(vector<string> previousResult) {
    
    
    if (!previousResult.empty()) {

        cout << "       |" << endl;

        for (string entry : previousResult) {

            cout << "        " << entry << endl;

        }

        cout << "       |";
    }
}




vector<string> Operations::DataOperations::displayResultsInReverse(vector<string> previousResults) {

    for (int i = 0; i < previousResults.size(); i++) {

        for (int j = 0; j < previousResults.size(); j++) {

            if (previousResults.at(i).compare(previousResults.at(j)) > 0) {

                swap(previousResults.at(i), previousResults.at(j));
            }
        }
    }

    return previousResults;
}




/* This function combines our strings from our string vector (vector<string>) from our copied database map into longer strings containing the keyword, 
   part of speech, and definition, stores those strings in a new vector of strings, swaps the strings in this new vector after doing comparisons, and 
   then returns this new vector. The returned value will be used as the first "previousResults" variable in the "PuttingEverythingTogether" class to 
   perform operations such as "distinct", "reverse", and specifying a part of speech */
vector<string> Operations::DataOperations::sortInAlphabeticalOrder(string key, map<string, vector<vector<string>>> entries) {

    vector<string> stringsToBeCompared;

    DataOperations sortObject;

    if (key == "") {
        
        return stringsToBeCompared;
    }

    else {

        for (int i = 0; i < entries.at(key).size(); i++) {

            stringsToBeCompared.push_back(sortObject.toString(i, key));
        }

        for (int i = 0; i < stringsToBeCompared.size(); i++) {

            for (int j = 0; j < stringsToBeCompared.size(); j++) {

                if (stringsToBeCompared.at(i).compare(stringsToBeCompared.at(j)) < 0) {

                    swap(stringsToBeCompared.at(i), stringsToBeCompared.at(j));
                }
            }
        }

        return stringsToBeCompared;
    }

}



/* Uses a counter variable where everytime we match two strings, the variable increases in value (and the duplicate
   gets removed). Counter variable gets reset in the outer 'for' loop so that we can check if the next string has
   duplicates */
vector<string> Operations::DataOperations::distinct(vector<string> previousResults) {

    int stringApperanceCount = 0;

    DataOperations distinctObject;

    for (int i = 0; i < previousResults.size(); i++) {

        for (int j = 0; j < previousResults.size(); j++) {

            if (previousResults[i] == previousResults[j]) {

                stringApperanceCount++;

                if (stringApperanceCount >= 2) {
                    
                    previousResults.erase(previousResults.begin() + j - 1);

                }
            }
        }

        stringApperanceCount = 0;

    }

    return previousResults;
}



/* Tries finding a substring comprised of a part of speech key (in brackets). If the substring is not contained in a "result" string, that string from
   "previousResults" is removed from the vector. If that substring isn't contained in ANY of the result strings, we inform the user that we don't have,
   in our dictionary, that part of speech for that keyword */
vector<string> Operations::DataOperations::partOfSpeech(string key, vector<string> previousResults) {

    DataOperations partOfSpeechObject;

    for (int i = 0; i < previousResults.size(); i++) {

        if (previousResults[i].find("[" + key + "]") == std::string::npos) {

            previousResults.erase(previousResults.begin() + i);
            i--;
        }
    }

    if (previousResults.empty()) {

        cout << "       |\n" << "        <NOT FOUND> To be considered for the next release. Thank you.\n" << "       |" << endl;
        partOfSpeechObject.sendInstruction();

    }

    return previousResults;
}




/* This method takes in user input to determine what operation to perform. It uses previous results to perform such
   operations since we're doing back-to-back operations (hence the name, "previousResults"). It also uses the number of entries the user
   has inputted thus far to determine if a key/parameter belongs in a certain position */

vector<string> Operations::DataOperations::defineEntry(vector<string> previousResults, string key, int numberOfUserEntries) {

    DataOperations defineEntryObject;


    // Parameter #2 only
    if (numberOfUserEntries == 2 && (defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("noun") || defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("verb") ||
        defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("adjective") || defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("adverb") ||
        defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("pronoun") || defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("preposition")
        || defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("conjunction") || defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("interjection") ||
        defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("article"))) {


        return defineEntryObject.partOfSpeech(key, previousResults);


    }

    // Parameters #2 and #3 only
    else if (((defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("distinct")) && numberOfUserEntries == 2) || 
            ((defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("distinct")) && numberOfUserEntries == 3)) {


        return defineEntryObject.distinct(previousResults);


    }

    // Parameters #2, #3, and #4
    else if (((defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("reverse")) && numberOfUserEntries == 2) ||
             ((defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("reverse")) && numberOfUserEntries == 3) ||
             ((defineEntryObject.lowerCaseString(key) == defineEntryObject.lowerCaseString("reverse")) && numberOfUserEntries == 4)) {


        return defineEntryObject.displayResultsInReverse(previousResults);


    }

    // if above conditions aren't met...
    else {


        // key doesn't belong in position #2
        if (numberOfUserEntries == 2 && !previousResults.empty()) {

            cout << "       |\n" <<
                "        <The entered 2nd parameter '" << key << "' is NOT a part of speech.>\n" <<
                "        <The entered 2nd parameter '" << key << "' is NOT 'distinct'.>\n" <<
                "        <The entered 2nd parameter '" << key << "' is NOT 'reverse'.>\n" <<
                "        <The entered 2nd parameter '" << key << "' was disregarded.>\n" <<
                "        <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>\n" <<
                "       |\n" << endl;
        }

        // key doesn't belong in position #3
        if (numberOfUserEntries == 3 && !previousResults.empty()) {

            cout << "       |\n" <<
                "        <The entered 3rd parameter '" << key << "' is NOT 'distinct'.>\n" <<
                "        <The entered 3rd parameter '" << key << "' is NOT 'reverse'.>\n" <<
                "        <The entered 3rd parameter '" << key << "' was disregarded.>\n" <<
                "        <The 3rd parameter should be 'distinct' or 'reverse'.>\n" <<
                "       |\n" << endl;
        }

        // key doesn't belong in position #4
        if (numberOfUserEntries == 4 && !previousResults.empty()) {

            cout << "       |\n" <<
                "        <The entered 4th parameter '" << key << "' is NOT 'reverse'.>\n" <<
                "        <The entered 4th parameter '" << key << "' was disregarded.>\n" <<
                "        <The 4th parameter should be 'reverse'.>\n" <<
                "       |\n" << endl;
        }

       

        return previousResults;


    }
}

