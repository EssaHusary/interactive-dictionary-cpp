# Interactive Dictionary, C++ version
This is the c++ version of an interactive dictionary I created in which a user can look up the definition of words and apply search filters to their searches. 

I did the following. I created a class called "DataSource". In this class, I read in the text file called, "Data.CS.SFSU.txt", and parsed and tokenized it. This is necessary as the text file contains dictionary terms along with their parts of speech and definitions. I stored this data in a map where the key is the definition term (a String) and the value is a part-of-speech & definition pair (a vector of vectors). Operations are performed on these data in a class called "DataOperations", where these operations include sorting definitions in alphabetical order, sorting definitions in reverse alphabetical order, and filtering out repeat definitions. Everything is put together in a function called finalProduct() in a class called "PuttingEverythingTogether", where the user is prompted to request dictionary definitions. This function, "finalProduct", is called in the class, "InteractiveDictionaryDriver", where main is stored.

Here is how it works from the user's perspective:

1) After where it says: "! Opening data file... ", type in "Data.CS.SFSU.txt". This opens up the text file that the program parses to attain words, parts of speech, and their definitions.
2) After where it says "Search [X]: ", four parameters are possible:
   - The first parameter must be the word you'd like the definition of.
   - The second parameter can be left blank or must be either a part of speech, the key 'distinct', which filters out duplicate definitions, or the key 'reverse', which reverses the        display from A-Z (alphabetical order) to Z-A.
   - The third parameter can be left blank or must be either 'distinct' or 'reverse'.
   - The fourth and final parameter can be left blank or must be the key 'reverse'.
3) The words that are part of the vocabulary of this dictionary are the following: arrow, book, bookable, bookbinder, csc210, csc220, csc340, placeholder, distinct, adverb, adjective, conjunction, interjection, noun, preposition, pronoun, verb, and reverse.

This is how it will look when you run it:
![image](https://github.com/user-attachments/assets/d1e63c93-ba14-4d1d-a0c7-89a5aa0a7821)

Here is us looking up the definition of "reverse":
![image](https://github.com/user-attachments/assets/b5d25576-bbd4-4fa0-b1c0-18f357448ca7)


Here is an example of looking up the definition of "reverse", specifying that we want to see the noun definitions and that we do not want duplicate definitions:
![image](https://github.com/user-attachments/assets/c4a70d85-ae73-48d0-aa16-207cc5a8f957)


Finally, here is an example of reversing the results (reverse alphabetical order) of our previous inquiry:
![image](https://github.com/user-attachments/assets/842b710e-c0e5-4723-a89d-bc4c9d30ef14)
