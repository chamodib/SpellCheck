# Spell Check

In this project, a spell check was implemented based on an open address hash table using quadratic hashing to resolve collisions.
The following were the instructions followed to implement this program:

 - Your program should assume that all words are stored the two text files are in the same folder as the program:
          maindict.txt is the main dictionary of words.

 - You should assume that this file contains tens of thousands of words, one word per line. The words are not in any particular order.

          addedwords.txt are words added by the user with the add command. Since they are stored in a file, user-added words will persist           between runs of your program.

 - Store your words in a (lovingly) hand-crafted hash table with the following properties:

          - it’s implemented as a class that hides its implementation details
            the underlying table is an array
          - it uses open addressing
          - collisions are resolved by quadratic hashing
          - adding a string, finding a string, and removing a string are all fast O(1) operations on average; the performance of all the                commands should feel instantaneous to the user
          - automatically re-sizes itself (e.g. doubles the capacity of the unerlying array) when the load factor is above 0.5; this                   requires re-hashing all the values, and so it’s okay if operations for when this happens take much more time than when re-                 hashing is not done


Here are the commands your program should implement:

- check s: Prints “ok” if string s is a word in the dictionary, and don't know "s" otherwise.

- add s: Adds string s to addedwords.txt. If s is already maindict.txt or addedwords.txt, then this does nothing (so there should not be multiple copies of words in either file).

- remove s: Removes s from addedwords.txt, and print a message like “s removed”. If s is in maindict.txt, then print a message like “can’t remove s: it’s in the main dictionary”. If s is in neither maindict.txt nor addedwords.txt, then print a message like “can’t remove s: unknown word”.

- checkfile s: Opens a text file named s, and finds all misspelled words (i.e words in neither maindict.txt nor addedwords.txt) and lists them in the order they are found. Each misspelled word should be put on its own line and include the line number in the file where it was found.

If s is not the name of a valid file, then print a message like “can’t find file s”.

- suggest s: Gives a list of correctly spelled words similar to s. Usually s is misspelled, but it’s certainly possible that s is a known word. For known words, you should still give a list of suggestions.

The details of exactly what counts as a similar word, and how you can find similar words, are up to you. Do a bit of research on the web to find out how simple spelling suggestions can be made.

- For some words, there might only a few (or even 0) suggestions, and it other cases there may be a lot of suggestions. You probably don’t want to show the user too many possible suggests.

quit or stop or end or done: Ends the program.
