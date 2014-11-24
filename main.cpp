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
    
    static bool finished=false;
    while(!finished && input!="quit")
    {
        one.findHere()->whoHere().find("Alice")->second->narrate(cout);
        
        cout << "What do you want to do?" << endl << "Keywords: aboutme, go, pickup, drop, use, approach" << endl;   //we need to write approach for alice so she can approach a person, or a thing
        cin >> input;
        one.delegate(input);
    }
}
