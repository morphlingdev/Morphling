#include "Ability.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Constructor, which parses the file specified
Ability::Ability(string filename)
{
    //Set default values

    //Open the file
    ifstream afile;
    afile.open(filename.c_str());
    if(afile.is_open()) //Ensure that file opened successfully
    {
        string line;
        while(afile.good()) //Loop until eof
        {
            getline(afile, line);
            //Parse the line (for now output for testing)
            cout << line << endl;
        }

    }
}
