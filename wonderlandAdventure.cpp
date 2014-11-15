// wonderlandAdventure.cpp
#include "wonderlandAdventure.h"
using namespace std;

/*
 -----------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 -----------------------------------------------------------
 */

// constructor -- all derived use (initialization list)			//it is fine if you want to keep where a person is in two locations (places keep people, then people keep where they are) but if we keep it in both places we need to be careful to always change it in both places and keep it consistent.
Person::Person(const int& hlevel, const List<Stuff>& slist) : health(hLevel)
{
    // copy list of stuff into Person's stuff list
    copyList(slist, stuffList);
}

// destructor
Person::~Person() {}

//allows each person to move from place to place
void Person::Move(Place& from, Place& to)
{
    from.PersonLeaves(*this);
    to.PersonEnters(*this);
}

//gives an item to someone else
void Person::Give(const Stuff& item, Person& other) //we are not keeping the person constant, we are changing what is in their inventory
{
    if(stuffList.contains(item))
    {
        other.Recieve(stuffList.pop(item));       //we cannot touch someone else's private parts. We need to use the recieve function
    }
    else {
      	cout << "You do not have that item";	//it would be good if we could output the name of the person and object. Shouldn't be too difficult.
    }
}

//recieves an item
void Person::Recieve(const Stuff& item)
{
    stuffList.push(item);
}

//person takes damage
void Person::Hurt(const int& damage)
{
    health -= damage;
}

/*
template<class T>
void Person::copyList(const List<T> from, const List<T> to)		//what is the purpose of a person copying a list? shouldn't this be part of our list, not person?
{
    for(int i = 0; i < from.getSize()-1; i++)
        to.push(from[i]);
}
*/

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// constructor (private)
Alice::Alice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int hlevel, const Place location) : health(hLevel), whereAmI(location), stuffList(sList)
{
    copyList(hList, helperList);    // list of helpers with Alice
    copyList(bList, badguyList);    // list of badguys with Alice

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
    stuffList.push(item);
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
std::ostream& Alice::render(std::ostream&) const
{
    cout << "Alice is " << getBodySize(bodySize) << endl;
    cout << "Her health level is " << health << endl;
    
    cout << "She has these items: ";
    
    cout << stuffList[0];
    
    for(int i = 1; i < stuffList.getSize()-1; i++)
        cout << " ," << stuffList.peek();
    
    cout << "/nHer friends are: ";
    cout << helperList[0];
    
    for(int i = 1; i < helperList.getSize()-1; i++)
        cout << " ," << helperList.peek();
    
    cout << "/nHer enemies are: ";
    cout << badguyList[0];
    
    for(int i = 1; i < badguyList.getSize()-1; i++)
        cout << " ," << badguyList.peek();
    
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
NPC::NPC(const std::string nm, const std::string dscrpt, const std::string threat, const List<Stuff> slist, const int hLevel, const bool frndly, const Place location) : health(hLevel), whereAmI(location), stuffList(sList)
{
    std::string description;        // unique description of badguy / helper
    std::string name;               // name of badguy
    std::string says;               // what helper / badguy says to Alice
    bool friendly;                  // 1 = friend, 0 = not friend
}

// destructor
NPC::~NPC() {}
    
// description of BadGuy
std::ostream& narrate(std::ostream&) const
{
    
}
    
// threats BGs pose to Alice
std::string makeThreat() const
{
    
}

/*
 --------------------------------------------------
 Factory Class: Derived from Person to make people
 --------------------------------------------------
 */

Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
Helpers will be WhiteRabbit, MadHatter, CheshireCat...

// constructor makes a factory
personFactory::personFactory()
{
    
}

// destructor destroys a factory
personFactory::~personFactory()
{
    
}

void personFactory::Person* makePerson (string who)
{
    Person* testtube;
    
    if (who == Bandersnatch)
    {
        std::string nm;
        std::string dscrpt;
        std::string threat;
        List<Stuff> slist;
        int hLevel;
        bool frndly;
        Place location;
        
        testtube = new NPC(nm, dscrpt, threat, slist, hLevel, frndly, location);
    }
    
    else if (who == Jabberwocky)
    {
        
    }
    
    else if (who == RedQueen)
    {
        
    }
    
    else if (who == WhiteRabbit)
    {
        
    }
    
    else if (who == MadHatter)
    {
        
    }
    
    else if (who == CheshireCat)
    {
        
    }
}

