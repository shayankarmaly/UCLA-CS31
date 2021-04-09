//Shayan Karmaly
//Professor Smallberg CS31
//Project 5

#include <iostream>
#include <cstring>
#include <cctype>
#include <cassert>

using namespace std;


// constant global variables that are used throughout the program
const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;

// function prototypes:
bool isValidCase(char word[]);
int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules);
int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH + 1], const char wordout[][MAX_WORD_LENGTH + 1], int nRules);

//when passed it checks for a valid case of every element in the array 
bool isValidCase(char word[])
{
    if (strlen(word) <= 0)
        return false;
    
    for (int i = 0; i < strlen(word); i++)
        if (!islower(word[i]))
            return false;
    
    return true;
}


int cleanupRules(char wordin[][MAX_WORD_LENGTH + 1], char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
    // checks if nRules is out of bounds
    if (nRules <= 0)
        return 0;
    
    // goes through each element in wordin and wordout and changes each character into lowercase.
    for (int i = 0; i < nRules; i++)
    {
        for (int p = 0; p < strlen(wordin[i]); p++)
        {
            wordin[i][p] = tolower(wordin[i][p]);
        }
        
        for (int z = 0; z < strlen(wordout[i]); z++)
        {
            wordout[i][z] = tolower(wordout[i][z]);
        }
    }
    
    // nextInd holds the index of wordin and wordout that does not have a known one-word rule
    int nextInd = 0;
    
    // iterates through potential one-word rules
    for (int i = 0; i < nRules; i++)
    {
        // check for an empty string
        if (strlen(wordin[i]) > 0)
        {
            // double checking if every element in wordin has a valid lowercase character.
            if (isValidCase(wordin[i]))
            {
                
                if (strlen(wordout[i]) == 0)
                {
                    // checking to see if there's a duplicate one-word rule
                    int repeat;
                    for (repeat = 0; repeat < nextInd; repeat++)
                        if (strcmp(wordin[i], wordin[repeat]) == 0)
                            break;
                    
                    // shifting every element in wordin and wordout to the right before wordin[i] and wordout[i] are copied
                    if (repeat == nextInd)
                    {
                        //tempIn and tempOut are temporary arrays used to help transfer the elements in clean form
                        char tempIn[MAX_WORD_LENGTH + 1];
                        char tempOut[MAX_WORD_LENGTH + 1];
                        
                        strcpy(tempIn, wordin[i]);
                        strcpy(tempOut, wordout[i]);
                        for (int ind = i - 1; ind >= nextInd; ind--)
                        {
                            strcpy(wordin[ind + 1], wordin[ind]);
                            strcpy(wordout[ind + 1], wordout[ind]);
                        }
                        
                        strcpy(wordin[nextInd], tempIn);
                        strcpy(wordout[nextInd], tempOut);
                        cerr << wordin[nextInd] << " " << wordout[nextInd] << endl;////////////////////////////////////////
                        
                        nextInd++;
                    }
                }
            }
        }
    }
    
    // iterating through any possible two-word rules
    for (int i = 0; i < nRules; i++)
    {
        // checking for an empty string
        if (strlen(wordin[i]) > 0 && strlen(wordout[i]) > 0)
        {
            // double checking each element is in the right lowercase
            if (isValidCase(wordin[i]) && isValidCase(wordout[i]))
            {
                // making sure there are no exact same elements at the same position
                if (strcmp(wordin[i], wordout[i]) != 0)
                {
                    int repeat;
                    
                    // iterating through wordin and wordout to make sure there are no duplicate one-word rule
                    for (repeat = 0; repeat < nextInd; repeat++)
                    {
                        // checks to make sure there are no duplicate two-word rules
                        if (strcmp(wordin[repeat], wordin[i]) == 0 && strlen(wordout[repeat]) == 0)
                            break;
                        
                        if (strcmp(wordin[repeat], wordin[i]) == 0 && strcmp(wordout[repeat], wordout[i]) == 0)
                            break;
                    }
                    
                    // shifting each element to the right like previously
                    if (repeat == nextInd)
                    {
                        
                        char tempIn[MAX_WORD_LENGTH + 1];
                        char tempOut[MAX_WORD_LENGTH + 1];
                        
                        strcpy(tempIn, wordin[i]);
                        strcpy(tempIn, wordout[i]);
                        for (int ind = i - 1; ind >= nextInd; ind--)
                        {
                            strcpy(wordin[ind + 1], wordin[ind]);
                            strcpy(wordout[ind + 1], wordout[ind]);
                        }
                        
                        strcpy(wordin[nextInd], tempIn);
                        strcpy(wordout[nextInd], tempOut);
                        
                        cerr << wordin[nextInd] << " " << wordout[nextInd] << endl;
                        
                        nextInd++;
                    }
                }
            }
        }
    }
    
    // returns the number of temporary arrays which is also the number of clean form word rules.
    return nextInd;
}
// function that returns the number of rules that the document matches
int determineScore(const char document[], const char wordin[][MAX_WORD_LENGTH + 1], const char wordout[][MAX_WORD_LENGTH + 1], int nRules)
{
    // matchIn and matchOut are bool arrays set to false by default
    bool matchIn[MAX_DOCUMENT_LENGTH + 1] = {false};
    bool matchOut[MAX_DOCUMENT_LENGTH + 1] = {false};
    
    // temporary array to be compared with match rules
    char current[MAX_DOCUMENT_LENGTH + 1];
    
    // holding the next index of interest in the array document
    int nextInd = 0;
    
    while (nextInd < strlen(document))
    {
        // basically skips through all non alphabetic characters
        while (!isalpha(document[nextInd]))
        {
            nextInd++;
        }
        
        // used to hold the next index of interest in array current
        int next = 0;
        
        // checking to make sure the next character is not a newline or space or the null byte
        while (!isspace(document[nextInd]) && document[nextInd] != '\0')
        {
            // if the character at index nextInd is a character, store it in next and change it to lowercase.
            if (isalpha(document[nextInd]))
            {
                current[next] = tolower(document[nextInd]);
                next++;
            }
            nextInd++;
            
            // checking if the index has reached the null byte
            if (isspace(document[nextInd]) || document[nextInd] == '\0')
            {
                current[next] = '\0';
            }
        }
        
        // setting the bool arrays to true if a word rule is found, makes sure there are no duplicates
        for (int found = 0; found < nRules; found++)
        {
            if (strcmp(current, wordin[found]) == 0)
                matchIn[found] = true;
            if (strcmp(current, wordout[found]) == 0)
                matchOut[found] = true;
        }
    }
    
    // keeps track of number of matches
    int score = 0;
    
  // iterate through both matchIn and matchOut arrays and add to score each time the condition is met
    for (int find = 0; find < nRules; find++)
    {
        if (matchIn[find] && !matchOut[find])
            score++;
    }
    
    return score;
}

int main()
{
    /*
    char win[][MAX_WORD_LENGTH + 1] = {"", "apple", "pear", "Cherry", "pineapple", "coconut", "apple!", "banana", "lychee", "applepear", "guava", "plummmmmmmmmmmmmm", "peachessssssssssssss"};
    char wout[][MAX_WORD_LENGTH + 1] = {"peach", "", "guava", "plum", "COCOnut", "", "", "blu3berry", "", "apple", "raspberry", "bbbbbbbbanana", ""};
    
    assert(cleanupRules(win, wout, -1) == 0);
    assert(cleanupRules(win, wout, 0) == 0);
    assert(cleanupRules(win, wout, 1) == 0);
    assert(cleanupRules(win, wout, 2) == 1);
    assert(cleanupRules(win, wout, 3) == 2);
    assert(cleanupRules(win, wout, 4) == 3);
    assert(cleanupRules(win, wout, 5) == 4);
    assert(cleanupRules(win, wout, 6) == 3);
    assert(cleanupRules(win, wout, 7) == 3);
    assert(cleanupRules(win, wout, 8) == 3);
    assert(cleanupRules(win, wout, 9) == 3);
    assert(cleanupRules(win, wout, 10) == 4);
    assert(cleanupRules(win, wout, 11) == 4);

    
    assert(determineScore("I like dog", win3, wout3, -1) == 0);
    assert(determineScore("I like dog", win3, wout3, 0) == 0);
    assert(determineScore("", win3, wout3, 2) == 0);
    assert(determineScore(" !@#$%^&*() ", win3, wout3, 2) == 0);
    assert(determineScore("I like dog", win3, wout3, 2) == 1);
    assert(determineScore("I like big dog", win3, wout3, 2) == 2);
    assert(determineScore("I like BIG dog", win3, wout3, 2) == 2);
    assert(determineScore("I like B-I-G dog", win3, wout3, 2) == 2);
    assert(determineScore(" !@#$%^&*() I like big dog !@#$%^&*() ", win3, wout3, 2) == 2);
    assert(determineScore("I ^&*(&*() like     big    dog", win3, wout3, 2) == 2);
    assert(determineScore("Ilikebigdog", win3, wout3, 2) == 0);
    assert(determineScore("I like big, big dog", win3, wout3, 2) == 2);
    assert(determineScore("I like big horse", win3, wout3, 2) == 0);
    assert(determineScore("I like bigger", win3, wout3, 2) == 0);
    assert(determineScore("I like big horse", win3, wout3, 3) == 1);
    assert(determineScore("I like big", win3, wout3, 3) == 2);
    assert(determineScore("I like big ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg", win3, wout3, 3) == 2);
*/
}