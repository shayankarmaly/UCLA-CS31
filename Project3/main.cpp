#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//Required functions
bool isSyntacticallyCorrect(string pollData);
int tallyVotes(string pollData, char party, int& voteTally);

//Additional functions
bool isValidUppercaseStateCode(string stateCode);


int main()
{
    string str ="23CAd";
    char ch = 'd';
    int n = 00;
    cout << tallyVotes( str, ch, n);

}



// Return true if the argument is a two-uppercase-letter state code, or
// false otherwise.

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.DC.FL.GA.HI.ID.IL.IN.IA.KS."
        "KY.LA.ME.MD.MA.MI.MN.MO.MS.MT.NE.NV.NH.NJ.NM.NY.NC."
        "ND.OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}

bool isSyntacticallyCorrect(string pollData)
{
    
    // checking for empty string
    if(pollData == "")
        return true;
    // if less than 4 its not valid
    if(pollData.size() < 4)
        return false;
    
    // checking to see if the string is all letters and numbers
    for(int i = 0; i != pollData.size(); i++)
    {
        if(isalpha(pollData.at(i) == false && isdigit(pollData.at(i)== false)))
           return false;
    }
    // changing all letters to uppercase to be used by isValidUppercaseStateCode
    for(int i = 0; i != pollData.size(); i++)
    {
        if(isalpha(pollData.at(i)))
           pollData.at(i) = toupper(pollData.at(i));
        
    }
    
    
    // checks to see if electoral votes contain one digit and checks validity of state forecast and if it has one character for the party
    for(int ind = 0; ind < pollData.size();)
    {
       if(isdigit(pollData.at(ind)) && isValidUppercaseStateCode(pollData.substr(ind+1, 2)) && isalpha(pollData.at(ind + 3)))
       {
           ind += 4; // add 4 to get to the beginning of the following state forecast.
       }
        // checks if electoral votes has 2 digits and if its a valid state code, with one character for the party
        else if(isdigit(pollData.at(ind)) && isdigit(pollData.at(ind + 1)) && isValidUppercaseStateCode(pollData.substr(ind+2, 2)))
        {
            // if it reaches the end of the string, returns false
            if((ind + 4 ) == pollData.size())
                return false;
            
            else if(isalpha(pollData.at(ind+4)))
                ind += 5; // start of the begining of the next state forecast
            else
            return false;
        }
        // return false if no condition is met
        else
            return false;
    }
    return true;
}





int tallyVotes(string pollData, char party, int& voteTally)
{
     // return 0 and set voteTally to 0 if pollData is empty string
    if(pollData.size() == 0)
    {
        voteTally = 0;
        return 0;
    }
    
    // return 1 if syntax not correct
    if (!isSyntacticallyCorrect(pollData))
        return 1;
    
    // return 2 if party is not a letter
    if(!isalpha(party))
        return 2;
    
    // returns 3 if syntax is correct and forecast predicts at least one state with 0 electoral votes
    if(pollData.at(0) == '0')
        return 3;
    else
        // goes through each character of pollData and checks if the first character is a 0 and the next one is a letter or both characters are 0's, it returns 3.
        for(int ind = 1; ind != pollData.size() - 1; ind++)
        if((isalpha(pollData.at(ind-1)) && pollData.at(ind) == '0' && isalpha(pollData.at(ind+1))) || (pollData.at(ind) == '0' && pollData.at(ind +1) == '0'))
            return 3;
    // if this is reached, no errors have occurred so setting voteTally to 0 and clearing any values so it can be used to be initialized in the cases regarding one or two digits for electoral votes
    voteTally = 0;
    
    // checks if the electoral vote is one digit
    for(int ind = 0; ind < pollData.size() -3;)
    {
        if(isdigit(pollData.at(ind))) // checking to make sure its a digit.
        {
            if(isalpha(pollData.at(ind +1))) // checking to make sure the next character is a letter
            {
                if(toupper(party) == toupper(pollData.at(ind + 3))) // checking to see if party and the party in pollData are the same
                {
                    voteTally = voteTally + (pollData.at(ind) - '0'); // char to int conversion and adding to voteTally if the parties match
                }
                ind = ind + 4; // putting index to check the next state forecast
                    
            }
        
        
        else
        {
            // checking case of two digit electoral votes
            if(toupper(party) == toupper(pollData.at(ind + 4)))
            {
                // if both parties are the same, convert char to int and add value to voteTally
                voteTally = voteTally + (pollData.at(ind) - '0') * 10 + (pollData.at(ind + 1) - '0');
            }
            ind = ind + 5; // loop to the next potential state forecast
        }
    }
}
    
    return 0;
}
 




