#include "Ability.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//Constructor, which parses the file specified
Ability::Ability(string filename)
{
    //Set default values
    name = "Default";
    desc = "None.";
    target_type = TARGET_LINE;
    range = 1;
    aoe_size = 0;
    aoe_shape = SHAPE_SQUARE;
    channel_time = 0;
    cooldown = 0;

    //Open the file
    ifstream afile;
    afile.open(filename.c_str());
    if(afile.is_open()) //Ensure that file opened successfully
    {
        string line;
        while(afile.good()) //Loop until eof
        {
            getline(afile, line);
            if(line.compare("") != 0)
            {
                //Parse the line
                int colon = line.find(":"); //position of first :
                string command = line.substr(0, colon);
                string vals = line.substr(colon + 1, line.length());
                if(command.compare("name") == 0)
                {
                    name = vals;
                }
                else if(command.compare("desc") == 0)
                {
                    desc = vals;
                }
                else if(command.compare("passive") == 0)
                {
                    colon = vals.find(":");
                    string s_pstat = vals.substr(0, colon);
                    string s_pbonus = vals.substr(colon + 1, vals.length());
                    int pstat;
                    if(s_pstat.compare("str") == 0)
                    {
                        pstat = STAT_STR;
                    }
                    else if(s_pstat.compare("int") == 0)
                    {
                        pstat = STAT_INT;
                    }
                    else if(s_pstat.compare("bob") == 0)
                    {
                        pstat = STAT_BOB;
                    }
                    int pbonus = atoi(s_pbonus.c_str());

                    passive[pstat] += pbonus;
                }
                else if(command.compare("target") == 0)
                {
                    //TYPE_LINE is default, so we only need to check for "smite"
                    if(vals.compare("smite") == 0)
                    {
                        target_type = TARGET_SMITE;
                    }
                }
                else if(command.compare("range") == 0)
                {
                    range = atoi(vals.c_str());
                }
                else if(command.compare("channel") == 0)
                {
                    channel_time = atoi(vals.c_str());
                }
                else if(command.compare("aoe") == 0)
                {
                    aoe_size = atoi(vals.c_str());
                }
                else if(command.compare("aoeshape") == 0)
                {
                    //SHAPE_SQUARE is default, so we only need to check for "circle"
                    if(vals.compare("circle"))
                    {
                        aoe_shape = SHAPE_CIRCLE;
                    }
                }
                else if(command.compare("cost") == 0)
                {
                    colon = vals.find(":");
                    string s_ccost = vals.substr(0, colon);
                    string s_pbonus = vals.substr(colon + 1, vals.length());
                    int ccost;
                    if(s_ccost.compare("mana") == 0)
                    {
                        ccost = COST_MANA;
                    }
                    else if(s_ccost.compare("health") == 0)
                    {
                        ccost = COST_HEALTH;
                    }
                    else if(s_ccost.compare("gold") == 0)
                    {
                        ccost = COST_GOLD;
                    }
                    int cbonus = atoi(s_pbonus.c_str());

                    costs[ccost] += cbonus;
                }


                cout << line << "(" << command << ")" << endl;
            }
            else
            {
                break;
            }
        }
    }
}
