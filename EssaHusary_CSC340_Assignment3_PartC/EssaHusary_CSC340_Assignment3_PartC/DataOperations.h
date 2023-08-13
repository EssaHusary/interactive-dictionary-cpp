#pragma once

#ifndef DataOperations_hpp
#define DataOperations_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

namespace Operations {
    class DataOperations {
    public:

        void sendInstruction();
        string toString(int i, string key);
        vector<string> distinct(vector<string> previousResults);
        vector<string> partOfSpeech(string key, vector<string> previousResults);
        vector<string> sortInAlphabeticalOrder(string key, map<string, vector<vector<string>>> entries);
        vector<string> displayResultsInReverse(vector<string> previousResults);
        string lowerCaseString(string word);
        void displayResults(vector<string> previousResult);
        vector<string> defineEntry(vector<string> previousResults, string key, int numberOfUserEntries);

    };
}



#endif 