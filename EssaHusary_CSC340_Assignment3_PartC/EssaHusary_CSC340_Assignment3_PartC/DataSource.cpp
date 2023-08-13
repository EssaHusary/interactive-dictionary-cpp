#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstring>
#include "DataSource.h"



using namespace Source;



map<string, vector<vector<string>>> Source::DataSource::addWordsToDatabase()
{
    
    numberOfDefinitions = 0;  // we'll be counting the number of definitions by incrementing this variable in our while loop

    fstream file;

    string line;

    file.open("Data.CS.SFSU.txt", ios::in);

    map<string, vector<vector<string>>> words;
    std::map<string, vector<vector<string>>>::iterator it3;
    it3 = words.begin();


    /* This is how our while loop works. We define, at the beginning of the while loop, a variable named "stop" which will be set to 0 upon every iteration
       of our outer while loop. It represents the char index of our line. At the beginning of each iteration of the outer while loop, it's set to 0 to 
       represent the beginning of a new line, as it is working with getline(). At every intermediate step in the iteration in the inner while loop, it 
       gets reset as we go along the line, stopping at a keyword and a p.o.s and a definition repeatedly until the end of the line. Once the end
       of the line has been reached, it gets set to "delimiterIndex" to end the inner while loop. The variable named "delimiterIndex" is the index 
       where the string ". " is, which, if we look at the end of each line of the text file, represents the end of every line in the file.  In the outer 
       while loop, we have "end3" set to 0. "end3" is named such because it represents the index where we've reached the end of a definition. It gets 
       reset upon each iteration of the inner while loop, as there may be multiple definitions for a word, and gets reset to 0 in the outer while loop, 
       because we're starting a new line. In the inner while loop, if end3 is greater than 0, which again, it can be for words with more than one 
       definition (because there are multiple stops or "ends"), "keyword", the keyword the user wants the definition to, acquires the value of 
       "keyForMap", our map's key, because we want each of our vectors of strings, named "wordParts" to have their intial values be the keyword, 
       (one part of "wordParts", hence the name). Otherwise, the initial value that would be stored would be "." because of the substr() and find() 
       methods grabbing a period, because there's no "keyword", hence the important 'if' statement. Vector "wordParts" gets reset in the inner while loop, 
       as want to store all and only three parts of a search result (word, p.o.s, and definition) separately in one "wordParts" vector in the vector of 
       vectors named "wordPartsContainer". "wordPartsContainer" contains/stores the three parts of a search result, a set of three parts per index, 
       hence the name. This vector of vectors is our maps' value. We can see in the while loop that we are using the substr() function to grab chars to 
       store into strings (as strings are arrays of chars, essentially). We have strings "keyForMap", for our map's (called "words") keys, getting reset 
       upon every iteration (every new line), and we have the self explanatory "keyword", "partOfSpeech", and "definition" strings. So, three strings
       get stored in a vector of strings, "wordParts", which gets reset in the inner loop, then each vector of vectors (of strings), gets stored in our 
       map. The vector of vectors (of strings) gets reset in the outer loop, as we're moving on to the mext line (new vector of "wordParts" vectors, 
       new map value). In the outer for loop, we put the vector of vectors (of strings) in the map, assigned to its rspective key. Finally, we return the map. */


    while (getline(file, line)) {

        int stop = 0;
        int delimiterIndex = line.find(". ");   /* our custom delimiter index used to exit out of our inner while loop (can be seen below) at the end of the 
                                                   line */

        int end3 = 0;    // index to be used in the find() function representing the end of a definition
        
        
        int start1 = 0;
        int end1 = line.find("|", start1);   // end1 is the index right after the keyword (and key for our map) 
        string keyForMap = line.substr(start1, end1 - start1);     // key for our map is grabbed and stored

        std::vector<string>::iterator it;

        vector<vector<string>> wordPartsContainer;
        std::vector<vector<string>>::iterator it2;
        it2 = wordPartsContainer.begin();


        while (stop != delimiterIndex) {     // while loop ends if "stop" resets to be the index at the end of the line

            vector<string> wordParts;
            std::vector<string>::iterator it1;
            it1 = wordParts.begin();



            int start1 = end3;                         // begins just before the keyword
            int end1 = line.find("|", start1);
            string keyword = line.substr(start1, end1 - start1);
            if (end3 > 0) {                            // necessary 'if' statement when "keyword" == ".", which happens as we traverse the line
                keyword = keyForMap;
            }
            stop = end1;                               // stop gets reset
            it1 = wordParts.insert(it1, keyword);



             
            int start2 = end1 + 1;                    // begins just before the part of speech
            int end2 = line.find(" -=>> ", start2);   // end2 is the index right after the part of speech
            string partOfSpeech = line.substr(start2, end2 - start2);
            stop = end2;
            it1 = wordParts.insert(it1, partOfSpeech);




            int start3 = end2 + 6;             // begins just before the definition
            end3 = line.find(".|", start3);    // end3 is the index right after the definition
            string definition = line.substr(start3, end3 - start3);
            it1 = wordParts.insert(it1, definition);



            it2 = wordPartsContainer.insert(it2, wordParts);    // our vector of vectors

            Source::DataSource::numberOfDefinitions++;    



            if (end3 == -1) {          /* if end3 has index of - 1, which is returned by the find() function when the end of the line is reached,
                                          "stop" == "delimiterIndex" which ends inner while loop */
                stop = delimiterIndex;
            }
            else {                    // otherwise, "stop" == index at the end of the current definition
                stop = end3;
            }

        }



        words.insert({ keyForMap, wordPartsContainer });


    }



    file.close();



    return words;
    
    
}
