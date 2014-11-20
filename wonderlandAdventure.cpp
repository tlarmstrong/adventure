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
void Person::move(Place& from, Place& to)
{
    from.personLeaves(*this);        // remove person from current location
    to.personEnters(*this);          // move a person to another place
}

// get name of Place where Person is
Place* Person::whereAreYou(List<Place*>& places)
{
    Place* here = nullptr;
    
    for(int i = 0; i < places.getSize(); i++)
    {
        here = places.peek();
        
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
    out << (stuffList.peek())->getName();
    
    for(int i = 1; i < stuffList.getSize(); i++)
        out << " ," << (stuffList.peek())->getName();
    
    out << "/nHer friends are: ";
    out << (helperList.peek())->getName();
    
    for(int i = 1; i < helperList.getSize(); i++)
        out << " ," << (helperList.peek())->getName();
    
    out << "/nHer enemies are: ";
    out << (badguyList.peek())->getName();
    
    for(int i = 1; i < badguyList.getSize(); i++)
        out << " ," << (badguyList.peek())->getName();
    
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
    description=nar;
}

//set what NPC says
void NPC::settalk(const std::string& nar)
{
    says=nar;
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
    // Person* testtube; // Do we need this variable, or can we just return new NPC (below)?
    
    if (who == "Bandersnatch")
    {
        std::string nm = "Bandersnatch";
        std::string dscrpt = "I'm a bad guy";
        std::string sayThings = "I'm gonna get you";
        
        List<Stuff*> sList= {new FriendStuff(eyeBall,descrpt,reust),bjhgggjh};    // inherits stuffList and health
        int hLevel = 10;            // variables from Person?
        bool frndly = false;
        
        // testtube = new NPC(nm, dscrpt, threat, sList, hLevel, frndly); // instead of this
        Person* bandersnatch=new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?	//close, I don't think you can make a new thing and return it in the same line
        return bandersnatch;
    }
    
    else if (who == "Jabberwocky")
    {
        std::string nm = "Jabberwocky";
        std::string dscrpt = "I'm a really bad guy";
        std::string sayThings = "I'm really gonna get you";
        Stuff* excalibur=new Stuff(sword);						//needs more input data
        List<Stuff*> sList= {excalibur};
        hLevel = 10;
        bool frndly = false;
        
        Person* jabberwocky=new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?	//close, I don't think you can make a new thing and return it in the same line
        return jabberwocky;
    }
    
    else if (who == "RedQueen")
    {
        std::string nm = "RedQueen";
        std::string dscrpt = "I'm an evil queen";
        std::string sayThings = "I'm gonna get you, my pretty";
        Stuff* elixar=new Stuff(potion);						//needs more input data
        List<Stuff*> sList= {elixar};
        hLevel = 10;
        bool frndly = 0;
        
        Person* rqueen=new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?	//close, I don't think you can make a new thing and return it in the same line
        return rqueen;
    }
    
    else if (who == "WhiteRabbit")
    {
        std::string nm = "WhiteRabbit";
        std::string dscrpt = "I'm a white rabbit";
        std::string sayThings = "I'm a friend";
        Stuff* fob=new Stuff(watch);						//needs more input data
        List<Stuff*> sList= {fob};
        hLevel = 10;
        bool frndly = true;
        
        Person* bugsbunny=new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?	//close, I don't think you can make a new thing and return it in the same line
        return bugsbunny;
    }
    
    else if (who == "MadHatter")
    {
        std::string nm = "MadHatter";
        std::string dscrpt = "I like tea parties";
        std::string sayThings = "Would you like to come to my party?";
        Stuff* drink=new Stuff(Tea);
        Stuff* cake=new Stuff(cupcake);						//needs more input data
        List<Stuff*> sList= {cake, drink};										//I suspect we may new stuff in the creaton of slist but I am not sure
        hLevel = 10;
        bool frndly = true;
        
        Person* madhatter=new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?	//close, I don't think you can make a new thing and return it in the same line
        return maddhatter;
    }
    
    else if (who == "CheshireCat")
    {
        std::string nm = "CheshireCat";
        std::string dscrpt = "I like to smile";
        std::string sayThings = "I'm a mysterious friend";
        Stuff* opener=new Stuff(key);						//needs more input data
        List<Stuff*> sList= {opener};
        hLevel = 10;
        bool frndly = ture;
        
        Person* cc=new NPC(nm, dscrpt, sayThings, sList, hLevel, frndly);     // do this?	//close, I don't think you can make a new thing and return it in the same line
        return cc;
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
Place::Place(const std::string& nm, const std::string& dscpt, const List<Stuff*>& what, const List<People*>& who, const List<Thing*>& obj, const List<Place*>& trav): name(nm), description(dscpt)
{
    peopleHere = who;               // everybody in Place
    stuffHere = what;               // list of things in a Place
    thingHere = obj;                // list of things here
    placeTo = trav;
    //placeList.push(this*);          // add to master Place list
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

List<Place> Place::getPlaceList() const   // returns list of Place
{
    return placeList;
}

void Place::personEnters(const Person& enterer)  // somebody comes into the place
{
    peopleHere.push(enterer);
}

void Place::personLeaves(const Person& leaver)   // removes somebody from a place
{
    peopleHere.pop(leaver);
}

List<Stuff*> Place::whatsHere() const              // returns the list of stuff here
{
    return stuffHere;
}

void Place::dropped(const Stuff& drop)    // someone dropped an item, so now it is laying around	//good thinking
{
    stuffHere.push(drop);
}

void Place::pickedUp(const Stuff& pick)      //somebody picked up an item here	//hmm good thought to call person's recieve. That doesn't remove it from our list though. Also, if we do something like this, it may make more sense to call it from person. But because the place doesn't exist in the person, we probably cannot do that. We will just have to call it in main twice. That would be one advantage of using a static list of places in our main function. We could easily call the place's pickup and drop from person.
{
    stuffHere.pop(pick);
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
Stuff::Stuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : name(nm), description(dscrptn), result(rslt), status(stts) {}

Stuff::~Stuff() {}                // destructor

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
GrowStuff::GrowStuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : Stuff(nm,dscrptn, rslt, stts) {}

GrowStuff::~GrowStuff() {}

void GrowStuff::useItem(Alice* who)
{
    who.bodySize += result;
}

// HealthStuff
HealthStuff::HealthStuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : Stuff(nm,dscrptn, rslt, stts) {}

HealthStuff::~HealthStuff() {}

HealthStuff::useItem(Person* who)
{
    who.health += result;
}

// FriendStuff
FriendStuff::FriendStuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : Stuff(nm,dscrptn, rslt, stts) {}

FriendStuff::~FriendStuff() {}

FriendStuff::useItem(NPC* who)
{
    who.friendly = result;
}

// OpenStuff
OpenStuff::OpenStuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : Stuff(nm,dscrptn, rslt, stts) {}

OpenStuff::~OpenStuff() {}

MoveStuff::MoveStuff(const std::string nm, const std::string dscrptn, const int rslt, const bool stts) : Stuff(nm,dscrptn, rslt, stts) {}

MoveStuff::~MoveStuff() {}

MoveStuff::useItem(Alice* alice, Place* goHome)
{
    
}

/*
 ----------------------------------
 Game Class: Base
 ----------------------------------
 */

Game::Game()
{
    places;
    people;
}

Game::~Game(){}

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
    
    Place* tree = new Place("Tree", "Alice woke up under a big oak tree. She saw a white rabbit run by.", tPeople, tStuff, tThing);
    places.push(tree);
    
    // Garden
    List<Person*> gPeople;
    List<Stuff*> gStuff;
    List<Thing*> gThing;
    
    Place* garden = new Place("Garden", "Alice is in a beautiful garden.", gPeople, gStuff, gThing);
    places.push(garden);
    
    // Woods
    List<Person*> wPeople;
    List<Stuff*> wStuff;
    List<Thing*> wThing;
    
    Place* woods = new Place("Woods", "Alice is in the Woods. She sees a cat in a tree.", wPeople, wStuff, wThing);
    places.push(woods);
    
    // TeaParty
    List<Person*> pPeople;
    List<Stuff*> pStuff;
    List<Thing*> pThing;
    
    Place* teaParty = new Place("Tea Party", "Alice goes to a Tea Party.", pPeople, pStuff, pThing);
    places.push(teaParty);
    
    //Castle
    List<Person*> cPeople;
    List<Stuff*> cStuff;
    List<Thing*> cThing;
    
    Place* teaParty = new Place("Castle", "Alice is taken to the Red Queen's Castle", cPeople, cStuff, cThing);
    places.push(teaParty);
    
    // Battlefield
    List<Person*> bPeople;
    List<Stuff*> bStuff;
    List<Thing*> bThing;
    
    Place* battlefield = new Place("Battlefield", "Alice is all suited up and ready to fight.", bPeople, bStuff, bThing);
    places.push(battlefield);
    
    // Home
    List<Person*> hPeople;
    List<Stuff*> hStuff;
    List<Thing*> hThing;
    
    Place* home = new Place("Home", "Alice wakes up and remembers a wonderful dream...", hPeople, hStuff, hThing);
    places.push(home);
    
    places.peek(battlefield)->newplacetogo(places.peek(tree));
}

void Game::makePeople()
{
    
}

// make list of stuff for each place, call Stuff constructor to make stuff, push into place's stuff list
void Game::makeStuff()
{
    // Tree
    // Tree has nothing in list
    
    //Garden
    Stuff* bandersnatchEye = new FriendStuff("BandersnatchEye", "If Alice gives Bandersnatch his missing eye, he will become her friend", true, 1);
    Stuff* whiteRose = new HealthStuff("WhiteRose", "The Red Queen hates white roses", 3, 1);
    places..whatsHere().push(bandersnatchEye);
    garden.whatsHere().push(whiteRose);
    
    // Woods
    Stuff* key = new OpenStuff("Key", "Key can be used to open the door, but Alice needs to be small to get through!", 1, 1);
    woods.getStuffList.push(key);
    
    // TeaParty
    Stuff* cake = new GrowStuff("Cake", "The cake will make Alice big!", 3, 1);
    Stuff* tea = new GrowStuff("Tea", "Drinking the tea will make Alice small.", 1, 1);
    teaParty.getStuffList.push(cake);
    teaParty.getStuffList.push(tea);
    
    // Castle
    Stuff* sword = new HealthStuff("Sword", "Sword can be used to fight the Jabberwocky", 4, 3);
    castle.getStuffList.push(sword);
    
    // Battlefield
    Stuff* jabberBlood = new moveStuff("JabberBlood", "Drinking the Jabberwocky's purple blood will take Alice home");
    battlefield.getStuffList.push(jabberBlood);
    
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





