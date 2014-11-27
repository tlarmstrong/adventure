// main.cpp for wonderlandAdventure
#include <cassert>
#include <iostream>
#include "wonderlandAdventure.h"
using namespace std;

int main()
{
    // make all places, people, stuff, and things in game
    Game one;

    // input string
    string input="start";
    one.findHere()->alicePtr->getName();
    one.findHere()->alicePtr->render(cout);

    
    static bool finished=false;
    while(!finished && input!="quit")
    {
        one.findHere()->narrate(cout);
        cout << "What do you want to do?" << endl << "Keywords: aboutme, go, pickup, drop, use, approach, attack" << endl;
        
        //we need to write approach for alice so she can approach a person, or a thing
        
        for(map<string, NPC*>::iterator i = one.findHere()->peopleHere.begin(); i!=one.findHere()->peopleHere.end(); i++)
        {
            if((i->second)->getName() == "Bandersnatch" && (i->second)->isfriendly() == false)
            {
                cout << "Bandersnatch attack!" << endl;
            }
            
            if((i->second)->getName() == "Jabberwocky")
            {
                cout << "Jabberwocky attack!" << endl;
            }
            
            if((i->second)->getName() == "Red Queen")
            {
                cout << "Off with her head!" << endl;
            }
        }
        
        cin >> input;
        one.delegate(input);
    }
}
