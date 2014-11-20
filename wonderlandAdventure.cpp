// wonderlandAdventure.cpp
#include "wonderlandAdventure.h"
using namespace std;

/*
 -----------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 -----------------------------------------------------------
 */


Person::Person(const int& hLevel, const List<Stuff*>& sList, const string& nm) : health(hLevel), name(nm), stuffList(sList) {}

// default constructor for Person Factory to work
Person::Person() {}

// destructor
Person::~Person() {}

//allows each person to move from place to place
<<<<<<< HEAD
void Person::move(Place& to)
=======
void Person::move(Place& from, Place& to) const
>>>>>>> 23deead59d3ca9f12f02ccabe443ac3bdc5f894a
{
    Place from = *this->whereAreYou();
    from.personLeaves(this);        // remove person from current location
    to.personEnters(this);          // move a person to another place
}

// get name of Place where Person is
<<<<<<< HEAD
Place* Person::whereAreYou()
{
    Place* here = nullptr;
    
    for(int i = 0; i < Game::places.getSize(); i++)
    {
        here = Game::places.peek(i);
=======
Place* Person::whereAreYou(const List<Place*>& places) const
{
    Place* here = nullptr;
    
    for(int i = 1; i <= places.getSize(); i++)
    {
        here = places.peek(i);
>>>>>>> 23deead59d3ca9f12f02ccabe443ac3bdc5f894a
        
        // whoHere() will return a list of people at place; if people at place == this person, then return the name of Place.
        if((here->whoHere()).contains(this))
            return here;
    }
    return here;
}

//gives an item to someone else
void Person::give(Stuff& item, Person& other)
{
    if(stuffList.contains(&item))
    {
        Stuff* popped = stuffList.pop(&item);
        other.recieve(*popped);
    }
    
    else
        cout << getName() << " does not have " << item.getName() << endl;
}

//recieves an item
void Person::recieve(Stuff& item)
{
    stuffList.push(&item);
}

//person takes damage
void Person::hurt(const int& damage)
{
    health -= damage;
}

List<Stuff*> Person::getStuffList() const
{
    return stuffList;
}

//gives the person's name
std::string Person::getName() const
{
    return name;
}

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// constructor (private)
Alice::Alice(const List<Stuff*>& sList, const List<NPC*>& hList, const List<NPC*>& bList, const int& bSize, const int& hLevel, const string& nm) : Person(hLevel, sList, nm)
{
    helperList = hList;    // list of helpers with Alice
    badguyList = bList;    // list of badguys with Alice
    
    // size of Alice (small(1), normal(2), big(3))
    bodySize = bSize;
}

// destructor
Alice::~Alice() {}

// Alice is a Singleton
Alice& Alice::makeAlice(const List<Stuff*>& sList, const List<NPC*>& hList, const List<NPC*>& bList, const int& bSize, const int& hLevel, const string& nm)
{
    static Alice alice(sList, hList, bList, bSize, hLevel, nm);
    
    return alice;
}

//adds a person to the list of Helpers
void Alice::taggingAlong(NPC& tagger)
{
    helperList.push(&tagger);
}

//removes a person from the list of Helpers
void Alice::ditched(NPC& ditcher)
{
    helperList.pop(&ditcher);
}


//Alice adds item to the list of stuff	//could we perhaps just use recieve maybe. it is is the same function. Also, we need to think about how we remove the item from place...
void Alice::pickup(Stuff& item)
{
    recieve(item);
}

//Alice drops an item
void Alice::drop(Stuff& item)
{
    stuffList.pop(&item);
}

//to define the ones after this, I think it will be easier if we first define stuffs. I think we will need to create subclasses for stuff.

//Alice uses an item on herself
void Alice::use(Stuff& item)
{
    item.useItem(this);		//the item will have a useItem function
}

//Alice uses an item in a place
void Alice::use(Stuff& item, Place& where)
{
    item.useItem(&where);
}

//Alice uses an item on a thing
void Alice::use(Stuff& item, Thing& what)
{
    item.useItem(&what);
}

//Alice uses an item on a person
void Alice::use(Stuff& item, Person& who)
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
<<<<<<< HEAD
    out << (stuffList.peek(0))->getName();
    
    for(int i = 1; i < stuffList.getSize(); i++)
        out << " ," << (stuffList.peek(i))->getName();
    
    out << "/nHer friends are: ";
    out << (helperList.peek(0))->getName();
    
    for(int i = 1; i < helperList.getSize(); i++)
        out << " ," << (helperList.peek(i))->getName();
    
    out << "/nHer enemies are: ";
    out << (badguyList.peek(0))->getName();
    
    for(int i = 1; i < badguyList.getSize(); i++)
=======
    out << (stuffList.peek(1))->getName();
    
    for(int i = 2; i <= stuffList.getSize(); i++)
        out << " ," << (stuffList.peek(i))->getName();
    
    out << "/nHer friends are: ";
    out << (helperList.peek(1))->getName();
    
    for(int i = 1; i <= helperList.getSize(); i++)
        out << " ," << (helperList.peek(i))->getName();
    
    out << "/nHer enemies are: ";
    out << (badguyList.peek(1))->getName();
    
    for(int i = 1; i <= badguyList.getSize(); i++)
>>>>>>> 23deead59d3ca9f12f02ccabe443ac3bdc5f894a
        out << " ," << (badguyList.peek(i))->getName();
    
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
NPC::NPC(const std::string& nm, const std::string& dscrpt, const std::string& sayThings, const List<Stuff*>& sList, const int& hlth, const bool& frndly): Person (hlth, sList, nm), description(dscrpt), says(sayThings), friendly(frndly) {}

// destructor
NPC::~NPC() {}

// public function to set friendly status of NPC
void NPC::setFriendly(const bool& x)
{
    friendly = x;
}

//set NPC's description
void NPC::setnarrate(const std::string& nar)
{
    description = nar;
}

//set what NPC says
void NPC::settalk(const std::string& nar)
{
    says = nar;
}

// description of helper/badguy
std::ostream& NPC::narrate(std::ostream& out) const
{
    out << description << endl;
    return out;
}

// helpers/badguys talk to Alice
std::ostream& NPC::talk(std::ostream& out) const
{
    out << says << endl;
    return out;
}

// get friendly data
bool NPC::isfriendly() const
{
    return friendly;
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
    if (who == "Bandersnatch")
    {
        string nm = "Bandersnatch";
        string dscrpt = "I'm a bad guy";
        string sayThings = "I'm gonna get you";
        
        Stuff* bandersnatchEye = new FriendStuff("BandersnatchEye", "If Alice gives Bandersnatch his missing eye, he will become her friend", 1, true);
        
        List<Stuff*> bList;
        bList.push(bandersnatchEye);
        
<<<<<<< HEAD
        int hLevel = 10;            // variables from Person?
=======
        List<Stuff*> sList= {new FriendStuff(eyeBall,descrpt,reust),bjhgggjh};    // inherits stuffList and health
        int hLevel = 10;            // variables from Person? I don't understand the question...
>>>>>>> 23deead59d3ca9f12f02ccabe443ac3bdc5f894a
        bool frndly = false;
        
        Person* bandersnatch=new NPC(nm, dscrpt, sayThings, bList, hLevel, frndly);
        return bandersnatch;
    }
    
    else if (who == "Jabberwocky")
    {
        string nm = "Jabberwocky";
        string dscrpt = "I'm a really bad guy";
        string sayThings = "I'm really gonna get you";
        
        Stuff* excalibur = new Stuff("Sword", "Watch out! He has a big sword!", -3, true);
        
        List<Stuff*> jList;
        jList.push(excalibur);
        
        int hLevel = 10;
        bool frndly = false;
        
        Person* jabberwocky = new NPC(nm, dscrpt, sayThings, jList, hLevel, frndly);
        return jabberwocky;
    }
    
    else if (who == "RedQueen")
    {
        string nm = "RedQueen";
        string dscrpt = "I'm an evil queen";
        string sayThings = "I'm gonna get you, my pretty";
        
        Stuff* elixar = new Stuff("Potion", "Drink my potion and see what happens", -5, true);

        List<Stuff*> rList;
        rList.push(elixar);
        
        int hLevel = 10;
        bool frndly = false;
        
        Person* rqueen=new NPC(nm, dscrpt, sayThings, rList, hLevel, frndly);
        return rqueen;
    }
    
    else if (who == "WhiteRabbit")
    {
        string nm = "White Rabbit";
        string dscrpt = "I'm a white rabbit";
        string sayThings = "I'm a friend";
        
        Stuff* watch = new Stuff("Watch", "My watch can speed up time", 3, true);
        
        List<Stuff*> wList;
        wList.push(watch);
        
        int hLevel = 10;
        bool frndly = true;
        
        Person* whiteRabbit = new NPC(nm, dscrpt, sayThings, wList, hLevel, frndly);
        return whiteRabbit;
    }
    
    else if (who == "MadHatter")
    {
        string nm = "MadHatter";
        string dscrpt = "I like tea parties";
        string sayThings = "Would you like to come to my party?";
        
        List<Stuff*> mList;
        int hLevel = 10;
        bool frndly = true;
        
        Person* madHatter = new NPC(nm, dscrpt, sayThings, mList, hLevel, frndly);
        return madHatter;
    }
    
    else if (who == "CheshireCat")
    {
        string nm = "Cheshire Cat";
        string dscrpt = "I like to smile";
        string sayThings = "I'm a mysterious friend";
        
        List<Stuff*> cList;
        
        int hLevel = 10;
        bool frndly = true;
        
        Person* chesireCat = new NPC(nm, dscrpt, sayThings, cList, hLevel, frndly);
        return chesireCat;
    }
}

/*
 ----------------------------------
 Place Class: Base
 ----------------------------------
 
 generic class will instantiate individual Place dynamically (on demand)
 Place will be Tree, Garden, Woods, TeaParty, Castle, Battlefield, Home
 
 */

// constructor
Place::Place(const std::string& nm, const std::string& dscpt, const List<Stuff*>& what, const List<Person*>& who, const List<Thing*>& obj, const List<Place*>& trav): name(nm), description(dscpt)
{
    peopleHere = who;               // everybody in Place
    stuffHere = what;               // list of things in a Place
    thingHere = obj;                // list of things here
    placeTo = trav;
}

Place::~Place() {}                         // destructor

List<Person*> Place::whoHere() const     //returns a list of everybody here
{
    return peopleHere;
}

// thought we may need these to get the name of Place (private) and list of Place(s) (private) by calling a public function?
std::string Place::getPlaceName() const  // returns name of Place	//I like this
{
    return name;
}

/*List<Place> Place::getPlaceList() const   // returns list of Place
{
    return placeList;
}*/

void Place::personEnters(Person* enterer)  // somebody comes into the place
{
    peopleHere.push(enterer);
}

void Place::personLeaves(Person* leaver)   // removes somebody from a place
{
    peopleHere.pop(leaver);
}

List<Stuff*> Place::whatsHere() const              // returns the list of stuff here
{
    return stuffHere;
}

// someone dropped an item, so now it is laying around
void Place::dropped(Stuff* drop, Person* who)
{
    who->getStuffList().pop(drop);
    stuffHere.push(drop);
}

//somebody picked up an item here
void Place::pickedUp(Stuff* pick, Person* who)
{
    stuffHere.pop(pick);
    who->recieve(*pick);
}

void Place::newPlaceToGo(Place* goTo)
{
    placeTo.push(goTo);
}

List<Place*> Place::getNewPlaceToGo() const
{
    return placeTo;
}

// output description of Place
std::ostream& Place::narrate(std::ostream& out) const
{
    out << description << endl;
    return out;
}

/*// what Alice can do in particular place		//until we nail down that we need this and more exactly what we want it to do, I don't want to have this function written
 std::string Place::canDo(const std::string )
 {
 out << action << endl;
 return out
 }
 */

/*
 ----------------------------------
 Stuff Class: Base
 ----------------------------------
 
 generic class will instantiate individual stuff dynamically (on demand)
 
 */

// constructor
Stuff::Stuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : name(nm), description(dscrptn), result(rslt), status(stts)
{
    next = 0;
}

Stuff::~Stuff() {}                // destructor

void Stuff::setNext(Stuff* n)
{
    next = n;
}

void Stuff::add(Stuff* n)
{
    if (next)
        next->add(n);
    else
        next = n;
}

//use or delegate to next obj
void Stuff::useItem(const Person* who)
{
    next->useItem(who);
}

string Stuff::getName() const
{
    return this->name;
}

// output description of Stuff
std::ostream& Stuff::narrate(std::ostream&) const
{
    return cout << description << endl;
}

/*
 ----------------------------------
 subStuff classes: Derived from Stuff
 ----------------------------------
 
 BandersnatchEye, Key, WhiteRose, Cake, Tea, Sword, JabberBlood...
 
 */

// GrowStuff
GrowStuff::GrowStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

GrowStuff::~GrowStuff() {}

void GrowStuff::useItem(const Person* who)
{
    if((this->name == "Cake" || this->name == "Tea") && who->getName() == "Alice")
            who->bodySize += result;        // how to convert to Alice to get member data?

    else
        Stuff::useItem(who);
}

// HealthStuff
HealthStuff::HealthStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

HealthStuff::~HealthStuff() {}

void HealthStuff::useItem(Person* who)
{
    if(this->name == "Sword" || this->name == "White Rose")
        who->hurt(result);
    
    else
        Stuff::useItem(who);
}

// FriendStuff
FriendStuff::FriendStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

FriendStuff::~FriendStuff() {}

void FriendStuff::useItem(Person* who)
{
    if(who->getName() == "BandersnatchEye")
        who->setFriendly(result);      // how to convert to NPC to get member function?
    
    else
        Stuff::useItem(who);
}

// OpenStuff
OpenStuff::OpenStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

OpenStuff::~OpenStuff() {}

void OpenStuff::useItem(Thing* what, Person* who)
{
    if(this->name == "Key")
        what->open();
        
    else
        Stuff::useItem(who);
}

MoveStuff::MoveStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

MoveStuff::~MoveStuff() {}

void MoveStuff::useItem(Person* who, Place* where)
{
    if(this->name == "JabberBlood" && who->getName() == "Alice")
    {
        List<Place*> go = where->getNewPlaceToGo();
        
        for(int i = 0; i < go.getSize(); i++)
        {
            if(go.peek(i)->getPlaceName() == "Home")
            {
                Place* there = go.peek(i);
                who->move(*there);
            }
        }
    }
    
    else
        Stuff::useItem(who);
}
                 

/*
 ----------------------------------
 Game Class: Base
 ----------------------------------
 */

Game::Game()
{
    makePeople();
    makePeople();
    makeStuff();
}

Game::~Game(){}

List<Place*> Game::getPlaceList() const
{
    return places;
}

List<Person*> Game::getPeopleList() const
{
    return people;
}
                 
void Game::makePlaces()
{
    /*
     EX:
     places.push(new Place(name, description, action, peopleHere, stuffHere, thingsHere));
     
     places.push(tree, efkfwufehif,feiufhw)
     places.push(castle, ewafwifh,wjofejew)
     tree.placego(castle)
     */
    
    // Tree
    List<Person*> tPeople;
    List<Stuff*> tStuff;
    List<Thing*> tThing;
    
    Place* tree = new Place("Tree", "Alice woke up under a big oak tree. She saw a white rabbit run by.", tStuff, tPeople, tThing, places);
    places.push(tree);
    
    // Garden
    List<Person*> gPeople;
    List<Stuff*> gStuff;
    List<Thing*> gThing;
    
    Place* garden = new Place("Garden", "Alice is in a beautiful garden.", gStuff, gPeople, gThing, places);
    places.push(garden);
    
    // Woods
    List<Person*> wPeople;
    List<Stuff*> wStuff;
    List<Thing*> wThing;
    
    Place* woods = new Place("Woods", "Alice is in the Woods. She sees a cat in a tree.", wStuff, wPeople, wThing, places);
    places.push(woods);
    
    // TeaParty
    List<Person*> pPeople;
    List<Stuff*> pStuff;
    List<Thing*> pThing;
    
    Place* teaParty = new Place("Tea Party", "Alice goes to a Tea Party.", pStuff, pPeople, pThing, places);
    places.push(teaParty);
    
    //Castle
    List<Person*> cPeople;
    List<Stuff*> cStuff;
    List<Thing*> cThing;
    
    Place* castle = new Place("Castle", "Alice is taken to the Red Queen's Castle.", cStuff, cPeople, cThing, places);
    places.push(castle);
    
    // Battlefield
    List<Person*> bPeople;
    List<Stuff*> bStuff;
    List<Thing*> bThing;
    List<Place*> trav;
    
    Place* battlefield = new Place("Battlefield", "Alice is all suited up and ready to fight.", bStuff, bPeople, bThing, trav);
    
    // places.peek(battlefield)->newPlaceToGo(places.peek(tree));
    
    places.push(battlefield);
    
    // Home
    List<Person*> hPeople;
    List<Stuff*> hStuff;
    List<Thing*> hThing;
    List<Place*> htrav;
    
    Place* home = new Place("Home", "Alice wakes up and remembers a wonderful dream...", hStuff, hPeople, hThing, trav);
    places.push(home);
<<<<<<< HEAD
=======
    
    Place* walker1;
    Place* walker2;
    for (int i=1; i<=places.getSize(); i++){
    	if(places.peek(i)->getName()=="battlefield"){
    		walker1=places.peek(i)
    	}
    	if(places.peek(i)->getName()=="tree"){
    		walker2=places.peek(i)
    	}
    }
    walker1->newPlacetoGo(walker2);
>>>>>>> 23deead59d3ca9f12f02ccabe443ac3bdc5f894a
}

void Game::makePeople()
{
    //Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
    //Helpers will be WhiteRabbit, MadHatter, CheshireCat...
    
    Person* bandersnatch = PersonFactory::makePerson("Bandersnatch");
    people.push(bandersnatch);
    
    Person* jabberwocky = PersonFactory::makePerson("Jabberwocky");
    people.push(jabberwocky);
    
    Person* redQueen = PersonFactory::makePerson("RedQueen");
    people.push(redQueen);
    
    Person* whiteRabbit = PersonFactory::makePerson("WhiteRabbit");
    people.push(whiteRabbit);
    
    Person* madHatter = PersonFactory::makePerson("MadHatter");
    people.push(madHatter);
    
    Person* cheshireCat = PersonFactory::makePerson("ChesireCat");
    people.push(cheshireCat);
    
    List<Stuff*> aList;
    List<NPC*> hList;
    List<NPC*> bList;
    int bSize = 2;
    int hLevel = 10;
    string nm = "Alice";
    
    Alice alice = Alice::makeAlice(aList, hList, bList, bSize, hLevel, nm);
    people.push(alice);
}

// make list of stuff for each place, call Stuff constructor to make stuff, push into place's stuff list //this is good :) I hadn't planned it like this i dont think but I really like this. It works pretty darn well.
void Game::makeStuff()
{
    // Tree
    // Tree has nothing in list
    
    //Garden
    Stuff* bandersnatchEye = new FriendStuff("BandersnatchEye", "If Alice gives Bandersnatch his missing eye, he will become her friend", true, 1);
<<<<<<< HEAD
    Stuff* whiteRose = new HealthStuff("White Rose", "The Red Queen hates white roses", 3, 1);
    
    for(int i = 0; i < places.getSize(); i++)
    {
        if(places.peek(i)->getPlaceName() == "Garden")
            (places.peek(i))->whatsHere().push(whiteRose);
    }
    
    for(int i = 0; i < people.getSize(); i++)
    {
        if(people.peek(i)->getName() == "Bandersnatch")
            people.peek(i)->getStuffList().push(bandersnatchEye);
    }
=======
    Stuff* whiteRose = new HealthStuff("WhiteRose", "The Red Queen hates white roses", 3, 1);
    places.whatsHere().push(bandersnatchEye);
    garden.whatsHere().push(whiteRose);
>>>>>>> 23deead59d3ca9f12f02ccabe443ac3bdc5f894a
    
    // Woods
    Stuff* key = new OpenStuff("Key", "Key can be used to open the door, but Alice needs to be small to get through!", 1, 1);

    for(int i = 0; i < places.getSize(); i++)
    {
        if(places.peek(i)->getPlaceName() == "Woods")
            (places.peek(i))->whatsHere().push(key);
    }
    
    // TeaParty
    Stuff* cake = new GrowStuff("Cake", "The cake will make Alice big!", 3, 1);
    Stuff* tea = new GrowStuff("Tea", "Drinking the tea will make Alice small.", 1, 1);
    
    for(int i = 0; i < places.getSize(); i++)
    {
        if(places.peek(i)->getPlaceName() == "Tea Party")
        {
            (places.peek(i))->whatsHere().push(cake);
            (places.peek(i))->whatsHere().push(tea);
        }
    }
    
    // Castle
    Stuff* sword = new HealthStuff("Sword", "Sword can be used to fight the Jabberwocky", 4, 3);
    
    for(int i = 0; i < places.getSize(); i++)
    {
        if(places.peek(i)->getPlaceName() == "Castle")
            (places.peek(i))->whatsHere().push(sword);
    }
    
    // Battlefield
    Stuff* jabberBlood = new MoveStuff("JabberBlood", "Drinking the Jabberwocky's purple blood will take Alice home", 1, 1);
    
    for(int i = 0; i < people.getSize(); i++)
    {
        if(people.peek(i)->getName() == "Jabberwocky")
            people.peek(i)->getStuffList().push(jabberBlood);
    }
    
    // Home
    // Home has nothing in list
    
    /*
     EX:
     tree.getStuffList.push(new healthStuff tea(feklfa,fwjlef,efjewf jowef))
     tree.getStuffList.push(new healthStuff cake(feklfa,fwjlef,efjewf jowef))
     */
}







/*

}
void makePeoplefefjwoiief {
    make(Bandersnatch)
}
void makeStuff

public:
void newPlace (efahfew, fejifhsf){places.push(new Place(sfkefefh, sehiufhf))}
newPersonfjgjhhg


};


Game()
{
    places.push(tree, efkfwufehif,feiufhw)
    places.push(castle, ewafwifh,wjofejew)
    tree.placego(castle)
    
    
}
main
{
    Game AliceinWonderland()
    
}
*/
/*
 places.peek(shjefe)->personEnters(WhiteRabbit);
 */





