// wonderlandAdventure.cpp
#include "wonderlandAdventure.h"
using namespace std;

/*
 -----------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 -----------------------------------------------------------
 */


Person::Person(const int& hlevel, const List<Stuff>& sList, const string& nm) : health(hLevel), name(nm)
{
    // copy list of stuff into Person's stuff list
    stuffList = sList;
}

// destructor
Person::~Person() {}

//allows each person to move from place to place
void Person::move(Place& from, Place& to)
{
    from.personLeaves(this);        // remove person from current location
    to.personEnters(this);          // move a person to another place
}

//for(Place* iterator=something...; iterate through all the Place) if(personisthere)return iterator} //This will be the difficult part of storing in Place. like the people we will probably have an array of Place (I think that whichever we do we should keep all our Place and people in an list anyway.) )

// Does this mean we need Place to store a static list of all Place(s)? -- I added this to Place, but not sure if it was what you intended. //good instinct. If we do that, it would be in our main though. So our options are to just pass the list when we need it, or make the list of places static.

// get name of Place where Person is
Place* Person::whereAreYou(const List<Place*>& places) const
{
    //good instinct on places being a static list. The list though should not be a part of each place. Instead if we do the static option, it would need to be in main. Our other option is to pass our list of places (also in main) around. For now I will assume we pass our list of places around.
//    int x = Place::getPlaceList().getSize()-1;
    
    for(int i = 0; i < places.getSize(); i++)
    {
        Place* here = places.peek(i);  //we do not want to look at the first thing in places each time.
        
        // whoHere() will return a list of people at place; if people at place == this person, then return the name of Place.
        if((here->whoHere()).contains(this)) //BRILLIANT!!! I couldn't have said it better! I changed it to ask for the pointer to this because ethan said it would work better and our lists should be pointers.
           return here;
    }
}

//gives an item to someone else
void Person::give(const Stuff& item, Person& other)
{
    if(stuffList.contains(&item))
        other.recieve(stuffList.pop(&item));
    
    else
        cout << name() << " does not have " << item.name() << endl;
    //it would be good if we could output the name of the person and object. Shouldn't be too difficult.
    //we would need to write these two functions
}

//recieves an item
void Person::recieve(const Stuff& item)
{
    stuffList.push(&item);
}

//person takes damage
void Person::hurt(const int& damage)
{
    health -= damage;
}

//gives the person's name
string Person::getName()
{
	return name;
}

/*
 ----------------------------------
 Alice Class: Derived from Person
	
 ----------------------------------
 */
 
 /*
private:
    
    List<NPC*> helperList;    // list of helpers with Alice
    List<NPC*> badguyList;    // list of badguys with Alice
    int bodySize;            // getSize of Alice (small(1), normal(2), big(3))
    
    // constructor
    Alice(const List<Stuff*>& sList, const List<Helper*>& hList, const List<BadGuy*>& bList, const int& bSize, const int& hLevel, const string& nm);
    
public:
    
    virtual ~Alice();        // destructor
    
    // Singleton
    static Alice& makeAlice(const List<Stuff*>& sList, const List<Helper*>& hList, const List<BadGuy*>& bList, const int& bSize, const int& hLevel, const string& nm);
    
    void taggingAlong(const Person& tagger);  //adds a person to the list of Helpers
    void ditched(const Person& ditcher);      //removes a person from the list of Helpers
    
    void pickup(const Stuff& item);                     //Alice adds item to the list of stuff
    void drop(const Stuff& item);                       //Alice drops an item
    void use(const Stuff& item);                        //Alice uses an item on herself
    void use(const Stuff& item, Place& where);     		//Alice uses an item in a place
    void use(const Stuff& item, Thing& what);      		//Alice uses an item on a thing
    void use(const Stuff& item, Person& who);      		//Alice uses an item on a person
    
    int getBodySize() const;                   // Get size of Alice//her size is an int
    
    // output what she has, who she's met, body getSize, and health
    std::ostream& render(std::ostream& cout) const;
*/

// constructor (private)
Alice::Alice(const List<Stuff*>& sList, const List<NPC*>& hList, const List<NPC*>& bList, const int& bSize, const int& hLevel, const string& nm): Person(hLevel, sList, nm)
{
    helperList=hList;    // list of helpers with Alice
    badguyList=bList;    // list of badguys with Alice

    // size of Alice (small(1), normal(2), big(3))
    bodySize = bSize;
}

// destructor
Alice::~Alice() {}

// Alice is a Singleton
Alice& Alice::makeAlice(const List<Stuff*>& sList, const List<NPC*>& hList, const List<NPC*>& bList, const int& bSize, const int& hLevel, const string& nm)
{
     static Alice alice(sList, hList, bList, bSize, hLevel, nm);
        
     return &alice;
}

//adds a person to the list of Helpers
void Alice::taggingAlong(const NPC& tagger)
{
    helperList.push(&tagger);
}

//removes a person from the list of Helpers
void Alice::ditched(const NPC& ditcher)
{
    helperList.pop(&ditcher);
}


//Alice adds item to the list of stuff	//could we perhaps just use recieve maybe. it is is the same function. Also, we need to think about how we remove the item from place...
void Alice::pickup(const Stuff& item)
{
    recieve(item);
}

//Alice drops an item
void Alice::drop(const Stuff& item)
{
    stuffList.pop(&item);
}

//to define the ones after this, I think it will be easier if we first define stuffs. I think we will need to create subclasses for stuff. 

//Alice uses an item on herself
void Alice::use(const Stuff& item)
{
    item.useItem(this);		//the item will have a useItem function
}

//Alice uses an item in a place
void Alice::use(const Stuff& item, Place& where)
{
    item.useItem(&where);
}

//Alice uses an item on a thing
void Alice::use(const Stuff& item, Thing& what)
{
    item.useItem(&what);
}

//Alice uses an item on a person
void Alice::use(const Stuff& item, Person& who)
{
    item.useItem(&who);
}

int Alice::getBodySize() const
{
    return bodySize;
}

// output what she has, who she's met, bodySize, and health	//I just renamed it to out instead of cout since cout is a thing already
std::ostream& Alice::render(std::ostream& out) const
{
    out << "Alice is " << getBodySize() << endl;
    out << "Her health level is " << health << endl;		//think we should have a gethealth function...
    
    out << "She has these items: ";
    
    // peek() will return a Stuff object pointer (.getName will return the actual name of the obj)	//I made it so our lists all contain pointers so that our lists work better (note == is not always defined for our classes)
    out << (stuffList.peek())->getName();
    
    for(int i = 1; i < stuffList.getSize(); i++)
        out << " ," << (stuffList.peek(i+1))->getName();
    
    out << "/nHer friends are: ";
    out << (helperList.peek())->getName();
    
    for(int i = 1; i < helperList.getSize(); i++)
        out << " ," << (helperList.peek(i+1))->getName();
    
    out << "/nHer enemies are: ";
    out << (badguyList.peek())->getName();
    
    for(int i = 1; i < badguyList.getSize(); i++)
        out << " ," << (badguyList.peek(i+1))->getName();
    
    out << endl;
    return out;
}


/*
 ----------------------------------
 NPC: Derived from Person
 ----------------------------------
 
 generic class will instantiate individual bad guys/helpers dynamically (on demand)
 
 */

// constructor
NPC::NPC(const std::string nm, const std::string dscrpt, const std::string sayThings, const List<Stuff> sList, const int hLevel, const bool frndly) : health(hLevel),stuffList(sList)
{
    description = dscrpt;       // unique description of badguy / helper
    sname = nm;                 // name of badguy
    says = sayThings;           // what helper / badguy says to Alice
    friendly = frndly;          // 1 = friend, 0 = not friend
}

// destructor
NPC::~NPC() {}

// public function to set friendly status of NPC
void NPC::setFriendly(int x)
{
    friendly = x;
}
    
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
        sList[] = {eyeBall};    // inherits stuffList and health
        hLevel = 10;            // variables from Person?
        bool frndly = 0;
        
        // testtube = new NPC(nm, dscrpt, threat, sList, hLevel, frndly); // instead of this
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?
    }
    
    else if (who == "Jabberwocky")
    {
        std::string nm = "Jabberwocky";
        std::string dscrpt = "I'm a really bad guy";
        std::string sayThings = "I'm really gonna get you";
        sList[] = {sword};
        hLevel = 10;
        bool frndly = 0;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "RedQueen")
    {
        std::string nm = "RedQueen";
        std::string dscrpt = "I'm an evil queen";
        std::string sayThings = "I'm gonna get you, my pretty";
        sList[] = {potion};
        hLevel = 10;
        bool frndly = 0;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "WhiteRabbit")
    {
        std::string nm = "WhiteRabbit";
        std::string dscrpt = "I'm a white rabbit";
        std::string sayThings = "I'm a friend";
        sList[] = {watch};
        hLevel = 10;
        bool frndly = 1;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "MadHatter")
    {
        std::string nm = "MadHatter";
        std::string dscrpt = "I like tea parties";
        std::string sayThings = "Would you like to come to my party?";
        sList[] = {cupcake, tea};
        hLevel = 10;
        bool frndly = 1;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
    
    else if (who == "CheshireCat")
    {
        std::string nm = "CheshireCat";
        std::string dscrpt = "I like to smile";
        std::string sayThings = "I'm a mysterious friend";
        sList[] = {key};
        hLevel = 10;
        bool frndly = 1;
        
        return new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);
    }
}

/*
 ----------------------------------
 Place Class: Base
 ----------------------------------
 
 generic class will instantiate individual Place dynamically (on demand)
 Place will be Tree, Garden, Woods, TeaParty, Castle, Battlefield, Home
 
 */

// should we also make a factory for Place? (see below for PlaceFactory class)

// constructor
Place::Place(const std::string nm, const std::string dscpt, const std::string act, const List<Stuff> what, const List<People> who, const List<Thing> obj,)
{
    name = nm;                      // name of Place
    description = dscrpt;           // unique description of Place
    action = act;                   // what Alice can do here
    peopleHere = who;               // everybody in Place
    stuffHere = what;               // list of things in a Place
    thingHere = obj;                // list of things here
    placeList.push(this*);          // add to master Place list
}

Place::~Place() {}                         // destructor

List<Person> Place::whoHere() const     //returns a list of everybody here
{
    return peopleHere;
}

// thought we may need these to get the name of Place (private) and list of Place(s) (private) by calling a public function?
std::string Place::getPlaceName() const  // returns name of Place
{
    return name;
}

List<Place> Place::getPlaceList() const   // returns list of Place
{
    return placeList;
}

void Place::personEnters(const &Person enterer)  // somebody comes into the place
{
    peopleHere.push(enterer);
}

void Place::personLeaves(const &Person leaver)   // removes somebody from a place
{
    peopleHere.pop(leaver);
}

List<Stuff> Place::whatsHere() const              // returns the list of stuff here
{
    return stuffHere;
}

void Place::dropped(const Stuff drop)    // someone dropped an item, so now it is laying around
{
    stuffHere.push(drop);
}

void Place::pickedUp(const Stuff leftBehind)      //somebody picked up an item here
{
    Person::recieve(leftBehind);
}

// output description of Place
std::ostream& Place::narrate(std::ostream& cout) const
{
    return cout << description << endl;
}

// what Alice can do in particular place
std::string Place::canDo(const std::string)
{
    return cout << action << endl;
}

/*
 ----------------------------------
 PlaceFactory Class: Derived from Place to make places
 ----------------------------------
 */

PlaceFactory::PlaceFactory() {}

PlaceFactory::~PlaceFactory() {}

// Dynamically create new Place in factory
Place* PlaceFactory::makePlace(const std::string where)
{
    if(where == "Tree")
    {
        name = "Tree";
        description = "Alice woke up under a big oak tree. She saw a white rabbit run by.";
        action = "Should she follow the white rabbit?";
        peopleHere[] = {WhiteRabbit};       // to make these lists of People, Stuff, and Thing
        stuffHere[] = {};                   // objects, do we need to instatiate them and then
        thingHere[] = {};                   // add them to the list?
        
        return new Place(name, description, action, peopleHere, stuffHere, thingsHere);
    }
    
    else if(where == "Garden")
    {
        name = "Garden";
        description = "Alice is in a beautiful garden.";
        action = "Should she look around?";
        peopleHere[] = {MadHatter, Bandersnatch};
        stuffHere[] = {WhiteRose};
        thingHere[] = {};
        
        return new Place(name, description, action, peopleHere, stuffHere, thingsHere);
    }
    
    else if(where == "Woods")
    {
        name = "Woods";
        description = "Alice is in the Woods. She sees a cat in a tree.";
        action = "Should she talk to the cat?";
        peopleHere[] = {CheshireCat};
        stuffHere[] = {Key};
        thingHere[] = {};
        
        return new Place(name, description, action, peopleHere, stuffHere, thingHere);
    }
    
    else if(where == "TeaParty")
    {
        name = "TeaParty";
        description = "Alice goes to a Tea Party.";
        action = "Should she have some tea and cake?";
        peopleHere[] = {MadHatter};
        stuffHere[] = {Cake, Tea};
        thingHere[] = {};
        
        return new Place(name, description, action, peopleHere, stuffHere, thingsHere);
    }
    
    else if(where == "Castle")
    {
        name = "Castle";
        description = "Alice is taken to the Red Queen's Castle";
        action = "She sees a door. Should she go in?";
        peopleHere[] = {RedQueen, Jabberwocky, Bandersnatch};
        stuffHere[] = {Sword};
        thingHere[] = {Door, Chest};
        
        return new Place(name, description, action, peopleHere, stuffHere, thingsHere);
    }
    
    else if(where == "Battlefield")
    {
        name = "Battlefield";
        description = "Alice is all suited up and ready to fight.";
        action = "Do you think she will win?";
        peopleHere[] = {WhiteQueen};
        stuffHere[] = {JabberBlood};
        thingHere[] = {};
        
        return new Place(name, description, action, peopleHere, stuffHere, thingsHere);
    }
    
    else if(where == "Home")
    {
        name = "Home";
        description = "Alice wakes up and remembers a wonderful dream...";
        action = "Was the dream real?";
        peopleHere[] = {};
        stuffHere[] = {};
        thingHere[] = {};
        
        return new Place(name, description, action, peopleHere, stuffHere, thingsHere);
    }
}

/*
 ----------------------------------
 Stuff Class: Base
 ----------------------------------
 
 generic class will instantiate individual stuff dynamically (on demand)
 uses Chain of Responsibility
 
 */

// constructor
Stuff::Stuff(const bool stat, const std::string nm, const std::string dscrptn, const int rslt)
{
    status = stat;                // if used, status = 0; if not, status = 1
    name = nm;                    // name of stuff object
    description = dscrptn;        // description of Stuff
    result = rslt;                // decrease to BGs health / change Alice's health, getSize
    
    next = 0;                     // Base pointer for chain
}

Stuff::~Stuff() {}                // destructor

void Stuff::setNext(Stuff* n)
{
    next = n;
}

void add(Stuff* n)
{
    if (next)
        next->add(n);
    else
        next = n;
}

// delegate to the next obj
void Stuff::handle(std::string sName)       // virtual function
{
    next->handle(sName);
}

// output description of Stuff
std::ostream& Stuff::narrate(std::ostream&) const
{
    return cout << description << endl;
}

/*
 ----------------------------------
 Handler Classes: Derived from Stuff
 ----------------------------------
 
 handlers will be BandersnatchEye, Key, WhiteRose, Cake, Tea, Sword, JabberBlood...
 
 */

BandersnatchEye::BandersnatchEye()
{
    name = "BandersnatchEye";
    description = "If Alice gives Bandersnatch his missing eye, he will become her friend";
    result = 1;      // friend = 1
    status = 1;      // not used
}

BandersnatchEye::~BandersnatchEye() {}

void BandersnatchEye::handle(std::string sName)
{
    // if string does not equal "Bandersnatch", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        Bandersnatch.setFriendly(result);
        // not sure this will work since Bandersnatch is an NPC and not a Bandersnatch object...help!
        status = 0;
    }
}

Key::Key()
{
    name = "Key";
    description = "Key can be used to open the door, but Alice needs to be small to get through!";
    result = 1;      // not sure of result here
    status = 1;      // not used
}

Key::~Key () {}

void Key::handle(std::string sName)
{
    // if string does not equal "Key", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        if(Alice::getBodySize == 1)
        {
            // open door, but not sure how
            status = 0;
        }
        else
        {
            // send back to handler (change sName to "Tea")?
            Stuff::handle("Tea");
        }
    }
}

WhiteRose::WhiteRose()
{
    name = "WhiteRose";
    description = "The Red Queen hates white roses";
    result = 3;      // affect on heath of RQ
    status = 1;      // not used
}

WhiteRose::~WhiteRose() {}

void WhiteRose::handle(std::string sName)
{
    // if string does not equal "WhiteRose", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        RedQueen::hurt(result);     // again, since RQ is not RQ object, not sure how to do this
        status = 0;
    }
}

Cake::Cake()
{
    name = "Cake";
    description = "The cake will make Alice big!";
    result = 3;      // make Alice big
    status = 1;      // not used
}

Cake::~Cake () {}

void Cake::handle(std::string sName)
{
    // if string does not equal "Cake", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        Alice::setBodySize(result);
        status = 0;
    }
}

Tea::Tea()
{
    name = "Tea";
    description = "Drinking the tea will make Alice small.";
    result = 1;      // make Alice small
    status = 1;      // not used
}

Tea::~Tea() {}

void Tea::handle(std::string sName)
{
    // if string does not equal "Tea", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        Alice::setBodySize(result);
        status = 0;
    }
}

Sword::Sword()
{
    name = "Sword";
    description = "Sword can be used to fight the Jabberwocky";
    result = 4;      // hurt done to Jabberwocky
    status = 3;      // Alice can hit him 3 times
}

Sword::~Sword() {}

void Sword::handle(std::string sName)
{
    // if string does not equal "Sword", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        // Alice can hit Jabberwocky 3 times
        if(status != 0)
        {
            Jabberwocky.hurt(result); // not sure how this will work since JW is part of NPC class
            status--;
        }
    }
}

JabberBlood::JabberBlood()
{
    name = "JabberBlood";
    description = "Drinking the Jabberwocky's purple blood will take Alice home";
    result = 0;      // don't actually need for this -- take Alice home instead
    status = 1;      // not used
}

JabberBlood::~JabberBlood() {}

void JabberBlood::handle(std::string sName)
{
    // if string does not equal "JabberBlood", pass variable back to Stuff (base)
    if (sName != name)
        Stuff::handle(sName);
    
    else
    {
        // Alice goes home
        Alice::move(Castle, Home);  // not sure this works...
    }
}

// Wow! I really struggled with Stuff, not sure I can make it through Thing...can you help?


