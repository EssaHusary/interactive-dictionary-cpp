# interactive-dictionary-cpp
This is the c++ version of an interactive dictionary I created in which a user can look up the definition of words and apply search filters to their searches. Here is how it works:

1) After where it says: "! Opening data file... ", type in "Data.CS.SFSU.txt". This opens up the text file that the program parses to attain words, parts of speech, and their definitions.
2) After where it says "Search [X]: ", four parameters are possible:
   - The first parameter must be the word you'd like the definition of.
   - The second parameter can be left blank or must be either a part of speech, the key 'distinct', which filters out duplicate definitions, or the key 'reverse', which reverses the        display from A-Z (alphabetical order) to Z-A.
   - The third parameter can be left blank or must be either 'distinct' or 'reverse'.
   - The fourth and final parameter can be left blank or must be the key 'reverse'.
