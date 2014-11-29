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
        //one.findHere()->narrate(cout);
        //cout << one.findHere()->getPlaceName() << endl;
        
        if(one.findHere()->getPlaceName() == "Home")
        {
            finished = true;
            break;
        }
        
        for(map<string, NPC*>::iterator j = one.findHere()->peopleHere.begin(); j!=one.findHere()->peopleHere.end(); j++)
        {
            if((j->second->isDead()))
            {
                cout << "dead." << endl;
            }
        }
        
        cout << "What do you want to do?" << endl << "Keywords: aboutme, go, pickup, drop, use, approach, attack" << endl;
                
        cin >> input;
        one.delegate(input);
    }
    
    if(finished == true)
        cout << "yay! You win!" << endl;
}
