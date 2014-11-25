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
    
    one.findHere()->whoHere().find("Alice")->second->render(cout);
    one.findHere()->narrate(cout);
    
    static bool finished=false;
    while(!finished && input!="quit")
    {
        cout << "What do you want to do?" << endl << "Keywords: aboutme, go, pickup, drop, use, approach" << endl;
        
        //we need to write approach for alice so she can approach a person, or a thing
        
        for(map<string, Person*>::iterator i = one.findHere()->whoHere().begin(); i!=one.findHere()->whoHere().end(); i++)
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
