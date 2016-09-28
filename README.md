# Problem Set 5
## Mispellings
 
### Objectives
Design and implement a data structure in C to manage a dictionary of words and find mispellings in a text.

### Notes
Only code related to assignment is released here.

To fully work, you should enroll for CS50 course (head to https://cs50.harvard.edu/ ) and integrate with the material provided for the assignment.

Two versions deployed.

- `dictionary.c` implements an hashtable with an array of linked lists. This is the final version submitted for grading.

- `dictionary.trie.c` implements trie.

With same large dictionaries, performances are almost identical.
Trie seems slower with brief texts, due to larger load and unload times.

### Example
As from CS50 IDE

````
~/workspace/pset5 $ ./speller dictionaries/large texts/shakespeare.txt

MISSPELLED WORDS

Etext
CDROMS
Etexts
Etext
ETEXT
SHAREWARE
Etexts
...
ETEXT
Etext

WORDS MISSPELLED:     45691
WORDS IN DICTIONARY:  143091
WORDS IN TEXT:        904612
TIME IN load:         0.14
TIME IN check:        0.66
TIME IN size:         0.00
TIME IN unload:       0.06
TIME IN TOTAL:        0.86
````
