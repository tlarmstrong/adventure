// main.cpp for wonderlandAdventure
#include <cassert>
#include <iostream>
#include "wonderlandAdventure.h"
using namespace std;

int main()
{
    Game one;
    string input;
    
    cout << one.getPlaceList().peek(0)->getPlaceName() << endl;
}
