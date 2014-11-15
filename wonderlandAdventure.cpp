// wonderlandAdventure.cpp
#include "wonderlandAdventure.h"
using namespace std;

/*
 -----------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 -----------------------------------------------------------
 */

// constructor -- all derived use (initialization list)
Person::Person(const int hlevel, const List<Stuff>& slist) : health(hLevel)
{
    // copy list of stuff into Person's stuff list
    stuffList.copyList(slist);
}

// destructor
Person::~Person() {}

//allows each person to move from place to place
void Person::move(Place& from, Place& to)
{
    from.personLeaves(*this);        // remove person from current location
    to.personEnters(*this);          // move a person to another place
}

//for(Places* iterator=something...; iterate through all the places) if(personisthere)return iterator} //This will be the difficult part of storing in places. like the people we will probably have an array of places (I think that whichever we do we should keep all our places and people in an list anyway.) )

// do we need Place to store a static list of all Places?

// get name of Place where Person is
std::ostream& Person::whereAreYou(std::ostream& cout) const
{
    std::string youAreHere;

    int x = Place::getPlaceList().getSize()-1;
    
    for(int i = 0; i < x; i++)
    {
        Place* here = Place::getPlaceList.peek();
        
        // whoHere() will return a list of people at place; if people at place == this person, then assign string to the name of place.
        if((here->whoHere().contains(this))
               youAreHere = Place::getPlaceName();
    }

    return cout << youAreHere << endl;
}

//gives an item to someone else
void Person::give(const Stuff item, Person other) 
{
    if(stuffList.contains(item))
        other.recieve(stuffList.pop(item));
}

//recieves an item
void Person::recieve(const Stuff item)
{
    stuffList.push(item);
}

//person takes damage
void Person::hurt(const int damage)
{
    health -= damage;
}

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// constructor (private)
Alice::Alice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int hlevel) : health(hLevel), stuffList(sList)
{
    helperList.copyList(hList);    // list of helpers with Alice
    badguyList.copyList(bList);    // list of badguys with Alice

    // size of Alice (small(1), normal(2), big(3))
    bodySize = 2;
}

// destructor
Alice::~Alice() {}

// Alice is a Singleton
Alice& Alice::makeAlice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int hLevel)
{
     static Alice alice(sList, hList, bList, bodySize, hLevel);
        
     return &alice;
}

//adds a person to the list of Helpers
void Alice::taggingAlong(const Person tagger)
{
    helperList.push(tagger);
}

//removes a person from the list of Helpers
void Alice::ditched(const Person ditcher)
{
    helperList.pop(ditcher);
}

//Alice adds item to the list of stuff	//could we perhaps just use recieve maybe. it is is the same function. Also, we need to think about how we remove the item from place...
void Alice::pickup(const Stuff item)
{
    recieve(item);
}

//Alice drops an item
void Alice::drop(const Stuff item)
{
    stuffList.pop(item);
}

//to define the ones after this, I think it will be easier if we first define stuffs. I think we will need to create subclasses for stuff. 

//Alice uses an item on herself
void Alice::use(const Stuff item)
{
    
}

//Alice uses an item in a place
void Alice::use(const Stuff item, const Place where)
{
    
}

//Alice uses an item on a thing
void Alice::use(const Stuff item, const Thing what)
{
    
}

//Alice uses an item on a person
void Alice::use(const Stuff item, const Person who)
{
    
}

std::string Alice::getBodySize(int size)
{
    if(size == 1)
        return "small";
    
    else if(size == 3)
        return "big";
    
    return "normal";
}

// output what she has, who she's met, bodySize, and health
std::ostream& Alice::render(std::ostream& cout) const
{
    cout << "Alice is " << getBodySize(bodySize) << endl;
    cout << "Her health level is " << health << endl;
    
    cout << "She has these items: ";
    
    // peek() will return a Stuff object (.name will return the actual name of the obj)
    cout << (stuffList.peek()).name;
    
    for(int i = 1; i < stuffList.getSize()-1; i++)
        cout << " ," << (stuffList.peek()).name;
    
    cout << "/nHer friends are: ";
    cout << (helperList.peek()).name;
    
    for(int i = 1; i < helperList.getSize()-1; i++)
        cout << " ," << (helperList.peek()).name;
    
    cout << "/nHer enemies are: ";
    cout << (badguyList.peek()).name;
    
    for(int i = 1; i < badguyList.getSize()-1; i++)
        cout << " ," << (badguyList.peek()).name;
    
    cout << endl;
    return cout;
}


/*
 ----------------------------------
 NPC: Derived from Person
 ----------------------------------
 
 generic class will instantiate individual bad guys/helpers dynamically (on demand)
 Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
 Helpers will be WhiteRabbit, MadHatter, CheshireCat...
 
 */

// constructor
NPC::NPC(const std::string nm, const std::string dscrpt, const std::string sayThings, const List<Stuff> sList, const int hLevel, const bool frndly) : health(hLevel),stuffList(sList)
{
    std::string description = dscrpt;    // unique description of badguy / helper
    std::string name = nm;               // name of badguy
    std::string says = sayThings;        // what helper / badguy says to Alice
    bool friendly = frndly;              // 1 = friend, 0 = not friend
}

// destructor
NPC::~NPC() {}
    
// description of helper/badguy
std::ostream& NPC::narrate(std::ostream& cout) const
{
    return cout << description << endl;
}
    
// helpers/badguys talk to Alice
std::ostream& NPC::talk(std::ostream& cout) const
{
    return cout << says << endl;
}

/*
 --------------------------------------------------
 Factory Class: Derived from Person to make people
 --------------------------------------------------
 
 Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
 Helpers will be WhiteRabbit, MadHatter, CheshireCat...
 
 */

// constructor makes a factory
PersonFactory::PersonFactory() {}

// destructor destroys a factory
PersonFactory::~PersonFactory() {}

// dynamically create characters based on input
Person* PersonFactory::makePerson(std::string who)
{
    // Person* testtube; // Do we need this variable, or can we just return new NPC (below)?
    
    if (who == "Bandersnatch")
    {
        std::string nm = "Bandersnatch";
        std::string dscrpt = "I'm a bad guy";
        std::string sayThings = "I'm gonna get you";
        sList = [eyeBall];  // inherits stuffList and health variables from Person?
        hLevel = 10;
        bool frndly = 0;
        
        // testtube = new NPC(nm, dscrpt, threat, sList, hLevel, frndly); // instead of this
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?
    }
    
    else if (who == "Jabberwocky")
    {
        std::string nm = "Jabberwocky";
        std::string dscrpt = "I'm a really bad guy";
        std::string sayThings = "I'm really gonna get you";
        sList = [sword];
        hLevel = 10;
        bool frndly = 0;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "RedQueen")
    {
        std::string nm = "RedQueen";
        std::string dscrpt = "I'm an evil queen";
        std::string sayThings = "I'm gonna get you, my pretty";
        sList = [potion];
        hLevel = 10;
        bool frndly = 0;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "WhiteRabbit")
    {
        std::string nm = "WhiteRabbit";
        std::string dscrpt = "I'm a white rabbit";
        std::string sayThings = "I'm a friend";
        sList = [watch];
        hLevel = 10;
        bool frndly = 1;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "MadHatter")
    {
        std::string nm = "MadHatter";
        std::string dscrpt = "I like tea parties";
        std::string sayThings = "Would you like to come to my party?";
        sList = [cupcake, tea];
        hLevel = 10;
        bool frndly = 1;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "CheshireCat")
    {
        std::string nm = "CheshireCat";
        std::string dscrpt = "I like to smile";
        std::string sayThings = "I'm a mysterious friend";
        sList = [key];
        hLevel = 10;
        bool frndly = 1;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
}

