#include <iostream>
#include <string>
using namespace std;

int main()
{
    //variable initializations of variables I'll use in the program
    double importDuty = 0.0;
    double duty1000 = 0.0;
    double duty12000 = 0.0;
    double leftover = 0.0;
    
    
    //ask the user to input a cheese type
    cout << "Cheese type: ";
    string cheeseType;
    getline(cin, cheeseType);
    
    //ask the user to input a value for the cheese
    cout << "Value: ";
    int value;
    cin >> value;
    cin.ignore(10000, '\n'); /*used here because read in an integer and will be reading
                             a string using getline next so this must be used in order to
                             to prevent the program from running incorrectly. */
    
    //ask the user to input the name of the importer
    cout << "Importer: ";
    string importer;
    getline(cin, importer);
    
    // calculate 'duty1000' based on the first $1000 of the value the user inputs
    if( value < 1000)
    {
        duty1000 = (.011 * value);
    }
    
    else
    {
        duty1000 = 11;
    }

    /*calculate 'duty12000' based on the next $12000 of the value the user inputs
     if 'cheeseType' is "cheshire" or "stilton" 'duty1200' is adjusted using calculations
     below.
     */
    
    if(cheeseType == "cheshire" || cheeseType == "stilton")
        {
            if(value > 1000 && value < 13000)
            {
                duty12000 = (value - 1000) * .014;
            }
            else if (value >=13000)
            {
                duty12000 =168;
            }
        }
    
    else if(value > 1000 && value < 13000)
    {
        duty12000 = (value-1000) * .02;
    }
    
    else if (value >= 13000)
    {
        duty12000 = 240;
    }
    
    // calculating 'leftover' based on the leftover value that's above $13000
    if (value > 13000)
    {
        leftover = (value - 13000) * .029;
    }
    
    // the total 'importDuty' is calculating by adding up 'duty1000', 'duty12000' and 'leftover'
    importDuty = duty1000 + duty12000 + leftover;
    
    // making sure 'importDuty' outputs strictly 1 digit on the left and 2 decimals to the right
    cout.setf(ios::fixed);
    cout.precision(2);
    //outputting hyphens in front of any of the possible 4 outputs below
    cout << "---" << endl;
    // condition checking if user inputted a valid entry for 'cheeseType' and is not an empty string
    if(cheeseType == "")
    {
        cout << "You must enter a cheese type" << endl;
        return 0;
    }
    // condition checking if user inputted a valid value of a positive number for 'value'
    else if(value < 1)
    {
        cout << "The value must be positive" << endl;
        return 0;
    }
    //condition checking if user inputted a valid entry for 'importer' and is not an empty string
    else if(importer == "")
    {
        cout << "You must enter an importer" << endl;
        return 0;
    }
    //final statement if everything is correct
    else
        cout <<  "The import duty for " << importer << " is $" << importDuty << endl;
    
    return 0;
}
