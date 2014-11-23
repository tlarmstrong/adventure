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
    string input;
    
    // start with description of Alice
    one.getPeopleList().peek(6)->narrate(cout);
    
    // description of first place (tree)
    one.getPlaceList().peek(0)->narrate(cout);
    
    // ask what Alice would like to do (follow the White Rabbit)
    cout << "What should Alice do? (hint: follow)" << endl;
    cin >> input;
    one.delegate(input);
    
    // while loop
    while(input != "quit")
    {
        cin >> input;
        one.delegate(input);
    }
    
    /* test output of lists
    int numPlace = one.getPlaceList().getSize();
    int numPeople = one.getPeopleList().getSize();

    for(int i = 0; i < numPlace; i++)
    {
        cout << one.getPlaceList().peek(i)->getPlaceName() << endl;
        one.getPlaceList().peek(i)->narrate(cout);
    }
    
    for(int i = 0; i < numPeople; i++)
    {
        cout << one.getPeopleList().peek(i)->getName() << endl;
        one.getPeopleList().peek(i)->narrate(cout);
    }
    
    for(int i = 0; i < numPeople; i++)
    {
        one.getPeopleList().peek(i)->render(cout);
    }
     */
    
}
