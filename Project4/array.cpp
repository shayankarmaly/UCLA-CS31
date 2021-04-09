//Shayan Karmaly
//Professor Smallberg
//CS 31 Project 4
// 8 November 2020

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

// function prototypes:
int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int countRuns(const string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int rotateLeft(string a[], int n, int pos);
int flip(string a[], int n);
int divide(string a[], int n, string divider);


int main()
{
    /*
    string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
            assert(lookup(h, 7, "kamala") == 5);
            assert(lookup(h, 7, "joe") == 2);
            assert(lookup(h, 2, "joe") == -1);
            assert(positionOfMax(h, 7) == 3);

            string g[4] = { "martha", "mark", "lindsey", "sara" };
            assert(differ(h, 4, g, 4) == 2);
            assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
            assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");

            string e[4] = { "joe", "susan", "", "kamala" };
            assert(subsequence(h, 7, e, 4) == 2);

            string d[5] = { "mark", "mark", "mark", "susan", "susan" };
            assert(countRuns(d, 5) == 2);
        
            string f[3] = { "lindsey", "joe", "mike" };
            assert(lookupAny(h, 7, f, 3) == 2);
            assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");
        
            assert(divide(h, 7, "lindsey") == 3);
        
            cout << "All tests succeeded" << endl;
    */
     
}

// appends a string 'value' to each element of the string array 'a' containing 'n' elements.
int appendToAll(string a[], int n, string value)
{
    // check if n is less than 0, if it is return -1
    if(n < 0)
        return -1;
    // go through each element in the array and append value to each element
    for(int i = 0; i < n; i++)
    {
        a[i].append(value);
    }
    
    return n;
}

int lookup(const string a[], int n, string target)
{
    for(int i = 0; i < n; i++)
    {
        if(a[i] == target)
            return i;
    }
    // will return -1 if target not reached
    return -1;
}

// function that returns the position of the biggest string in the array
int positionOfMax(const string a[], int n)
{
    // assuming the biggest string is at index 0
    int max = 0;
    
    // checking if 'n' is out of bounds
    if (n <= 0)
        return -1;
    // going through array
    for(int i = 0; i < n; i++)
    {
        // conditional statement if an element in the array is bigger than the one that's at index 'max', max is assigned that position
        if(a[i] > a[max])
            max = i;
        
    }
    
    return max;
}

// returns the number of consecutive sequences
int countRuns(const string a[], int n)
{
    if(n < 0)
        return -1;
    if(n == 0)
        return 0;
    
    int runs = 0;
    for(int i = 0; i < n; i++)
    {
        if(a[i] != a[i+1])
            runs++;
    }
    return runs;
}

// function that returns the position where the strings differ.
int differ(const string a1[], int n1, const string a2[], int n2)
{
    // initializing 'count' to 0 so that it can later be initialized to the smallest index needed to search both arrays
    int count = 0;
    
    // checking to see if either 'n1' or 'n2' is out of boundaries and if so it's automatically returning -1 because it's incorrect
    if(n1 < 0 || n2 < 0)
        return -1;
    // checking to see if 'n1' or 'n2' is equal to 0 and if so, there is automatically 0 possibility of matching elements so, it returns 0
    else if (n1 == 0 || n2 == 0)
        return 0;
    
    // checks to see if 'n1' or 'n2' is smaller and initializes the smallest one to 'count' so the for loop knows how many max indexes to check
    if(n1 < n2)
        count = n1;
    else
        count = n2;
    // creating a variable to keep track of the max number of positions it checked before the arrays differed.
    int pos = 0;
    // goes through each element in both arrays
    for (int i = 0; i < count; i++)
    {
        if(a1[i] == a2[i])
            pos++;
    }
    return pos;
}

// function that returns the position of the string element in 'a1' that is in the same position as an element in 'a2'
int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    // checking to see if either 'n1' or 'n2' is out of boundaries and if so it's automatically returning -1 because it's incorrect
    if (n1 < 0 || n2 < 0)
        return -1;
    // if 'n2' == 0 no point in going forward, return 0
    if( n2 == 0)
        return 0;
    
    int sub = 0; // this variable will hold the position the subsequence starts
    bool found = false; // assuming it isn't true, once it is we know the strings are equal or have found a subsequence
    
    // checking each element through 'n1' number of elements
    for (int i = 0; i < n1; i++)
    {
        if(a1[i] == a2[0]) // conditional check if maybe the first position in 'a2' is equal to one of the elements in 'a1'
        {
            sub = i;
            for (int k = 0; k < n2; k++) // check through n2 elements
            {
                if(a1[i + k] == a2[k] && (k + 1 == n2))
                    found = true;
                else if(a1[i + k] != a2[k])
                    break;
            }
        }
        
    }
    if(!found)
        return -1;
    else
        return sub;
}

// function that checks if there is an element in 'a1' that matches with an element in 'a2'
int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
    
    if ( n2 < 0 || n1 < 0) // checking for any out of bounds cases
        return -1;
    
    
    for (int i = 0; i < n2; i++) // outer for loop going through elements in 'a1'
    {
        for (int k = 0; k < n2; k++) // inner for loop going through elements in 'a2'
        {
            if(a1[i] == a2[k]) // case checking, if both elements are the same in any position, return i.
            {
                return i;
            }
        }
    }
        return -1; // returns -1 if otherwise
   
}

// function that rotates every element to the left after the position desired
int rotateLeft(string a[], int n, int pos)
{
    string final = a[pos]; // initializing the last element of the array to a temp variable.
    
    if(n < 0 || pos < 0) // checking out of bounds cases
        return -1;
    
    for (int i = 0; i < n - pos - 1; i++) // go through each element according to where position starts
    {
        a[i + pos] = a[i+ pos +1]; // makes sure each element gets rotated left
            
    }
    
    a[n-1] = final; // initialize the last element to the temporary variable we made earlier
    return pos;
}

// function that reverses the order of a string array
int flip(string a[], int n)
{
    string tempString; // temporary variable holder
    if(n < 0) // checking for out of bounds case
        return -1;
    
    for (int i = 0; i < n/2; i++) // searches the array until it reaches the center
    {
        tempString = a[i]; // temporary variable holds an element
        a[i] = a[n-i-1]; // that element swaps the 'n-i-1'th element
        a[n-i-1] = tempString;
    }
    return n;
}

// function that organizes all the strings less than than 'divider' before all others and the rest after.
int divide(string a[], int n, string divider)
{
    string small;
    if (n < 0)
        return -1;
    
    for (int i = 0; i < n; i++)
    {
        small = a[i]; // set the temporary smallest variable to the first element
        for(int k = i + 1; k < n; k++) // go through each element after the first
        {
            if (small > a[k]) // if the temporary smallest variable is bigger than an element, swap.
            {
                small = a[k];
                a[k] = a[i];
                a[i] = small;
            }
        }
        
    }

    for ( int i = 0; i < n; i++)
    {
        if (a[i] >= divider)
            return i; // returning the position of the string thats greater than or equal than divider
    }
    return n;
}

