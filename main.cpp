// main.cpp for wonderlandAdventure
#include <cassert>
#include <iostream>
#include "wonderlandAdventure.h"
using namespace std;

int main()
{
    Game one;
    string input;
    
    List<Person*> list = one.getPeopleList();
    cout << "Person List: " << list.getSize() << endl;
    
    List<Place*> plist = one.getPlaceList();
    cout << "Place List: " << plist.getSize() << endl;

    cout << one.getPeopleList().peek(0)->getName() << endl;
}
