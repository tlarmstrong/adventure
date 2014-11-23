// wonderlandAdventure.cpp
#include "wonderlandAdventure.h"
#include <map>
using namespace std;


/*
 ----------------------------------
 Place Class: Base
 ----------------------------------
 
 generic class will instantiate individual Place dynamically (on demand)
 Place will be Tree, Garden, Woods, TeaParty, Castle, Battlefield, Home
 
 */

// constructor
Place::Place(const std::string& nm, const std::string& dscpt, const multimap<string, Stuff*>& what, const map<string, Person*>& who, const multimap<string, Thing*>& obj, const map<string, Place*>& trav): name(nm), description(dscpt), stuffHere(what), peopleHere(who), thingHere(obj), placeTo(trav) {}
 
Place::~Place()
{
	/* I am going to leave the commented code so that we can talk about it
	for (map<string, Person*>::iterator i=peopleHere.begin(); i!=peopleHere.end(); i++)		//deletes all people in a place
	{
		for (multimap<string, Stuff*>::iterator j=(i->second)->stuffList.begin(); j!=(i->second)->stuffList.end(); j++)
		{
			delete j->second
		}
		delete i->second;
	}
	
	for (map<string, Stuff*>::iterator i=stuffHere.begin(); i!=stuffHere.end(); i++)	//deletes all the stuff in a place
	{
		delete i->second;
	}
	
	for (map<string, Thing*>::iterator i=thingHere.begin(); i!=thingHere.end(); i++) //deletes all the things in a place
	{
		if(i->first=="chest")
		{
			for (multimap<string, Stuff*>::iterator j=(i->second)->inside.begin(); j!=(i->second)->inside.end(); j++)
			{
				delete j->second
			}
		}
		delete i->second;
	}
	*/
}

map<string, Person*> Place::whoHere() const     //returns a list of everybody here
{
    return peopleHere;
}

// thought we may need these to get the name of Place (private) and list of Place(s) (private) by calling a public function?
string Place::getPlaceName() const  // returns name of Place
{
    return name;
}

void Place::personEnters(Person* enterer)  // somebody comes into the place
{
    peopleHere.insert(pair<string, Person*>(enterer->getName(), enterer));
}

void Place::personLeaves(Person* leaver)   // removes somebody from a place
{
    
    peopleHere.erase(peopleHere.find(leaver->getName()));
}

multimap<string, Stuff*> Place::whatsHere() const              // returns the list of stuff here
{
    return stuffHere;
}

// someone dropped an item, so now it is laying around
void Place::dropped(Stuff* drop, Person* who)
{
    who->getStuffList().erase(who->getStuffList().find(drop->getName()));
    stuffHere.insert(pair<string, Stuff*>(drop->getName(), drop));
} // getting an error "no matching constructor for initialization of 'pair<string,Stuff*>'...removed const from Stuff* and it worked

//somebody picked up an item here
void Place::pickedUp(Stuff* pick, Person* who)
{
    stuffHere.erase(stuffHere.find(pick->getName()));
    who->recieve(pick);
} // error could not convert from const Stuff* to Stuff*; removed const to make work

void Place::genStuff(Stuff* gen)
{
	stuffHere.insert(pair<string, Stuff*>(gen->getName(), gen));
} // getting an error "no matching constructor for initialization of 'pair<string,Stuff*>'...removed const from Stuff* and it worked

void Place::newPlaceToGo(Place* goTo)
{
    placeTo.insert(pair<string, Place*>(goTo->getPlaceName(),goTo));
}

void Place::blockPlaceToGo(Place* block)
{
    placeTo.erase(placeTo.find(block->getPlaceName()));
}

map<string, Place*> Place::getNewPlaceToGo() const
{
    return placeTo;
}

// output description of Place
std::ostream& Place::narrate(std::ostream& out) const
{
    out << description << endl;
    render(out);
    return out;
}

std::ostream& Place::render(std::ostream& out) const
{
	if (peopleHere.empty())
		out << "There is nobody here.";
	else
	{
		out << "You see there are other people here: ";
		std::map<string, Person*>::iterator i;
		i=peopleHere.begin();
		out << i->second->getName();
		for(;i!=peopleHere.end();i++)
		{
			out << ", " <<i->second->getName();
		}
	}
	out << endl;
	if (!(thingHere.empty()))
	{
		out << "You see a ";
		std::map<string, Thing*>::iterator i;
		i=thingHere.begin();
		out << i->second->getName();
		for(;i!=thingHere.end();i++)
		{
			out << ", and a" <<i->second->getName();
		}
		out << "."<< endl;
	}
	if (!(stuffHere.empty()))
	{
		out << "On the ground you see a ";
		std::map<string, Stuff*>::iterator i;
		i=stuffHere.begin();
		out << i->second->getName();
		for(;i!=stuffHere.end();i++)
		{
			out << ", and a" <<i->second->getName();
		}
		out << "."<< endl;
	}
	if (placeTo.empty())
	{
		out << "You can go nowhere from here."
	}
	else
	{
		out << "From here you can go to: ";
		std::map<string, Place*>::iterator i;
		i=placeTo.begin();
		out << i->second->getPlaceName();
		for(;i!=stuffHere.end();i++)
		{
			out << ", " <<i->second->getPlaceName();
		}
		out << "."<< endl;
	}
}

/*// what Alice can do in particular place		//until we nail down that we need this and more exactly what we want it to do, I don't want to have this function written
 std::string Place::canDo(const std::string )
 {
 out << action << endl;
 return out
 }
 */

/*
 -----------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 -----------------------------------------------------------
 */

Person::Person(const int& hLevel, const multimap<string, Stuff*>& sList, const string& nm) : health(hLevel), stuffList(sList), name(nm) {}

// default constructor for Person Factory to work
Person::Person() {}

// destructor
Person::~Person() {}

//allows each person to move from place to place
void Person::move(Place* to) const
{
    Place* from = whereAreYou();
    from->personLeaves(this);        // remove person from current location
    to->personEnters(this);          // move a person to another place
}

// get Place where Person is
Place* Person::whereAreYou() const
{
    return Game::places.find(getName())->second;
}

//gives an item to someone else
void Person::give(Stuff* item, Person* other)
{
    
    
    if(stuffList.find(item->getName())!=stuffList.end())
    {
        stuffList.erase(stuffList.find(item->getName()));
        other->recieve(item);
    }
    
    else
        cout << getName() << " does not have " << item->getName() << endl;
}

//recieves an item
void Person::recieve(Stuff* item)
{
    stuffList.insert(pair<string, Stuff*>(item->getName(), item));
} // getting an error "no matching constructor for initialization of 'pair<string,Stuff*>'...removed const from Stuff* and it worked

//person takes damage
void Person::hurt(const int& damage)
{
    health -= damage;
}

int Person::getHealth() const
{
    return health;
}

multimap<string, Stuff*> Person::getStuffList() const
{
    return stuffList;
}

//gives the person's name
string Person::getName() const
{
    return name;
}

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// constructor (private)
Alice::Alice(const multimap<string, Stuff*>& sList, const map<string, NPC*>& hList, const map<string, NPC*>& bList, const int& bSize, const int& hLevel, const string& nm, const string& dscpt) : Person(hLevel, sList, nm), helperList(hList), badguyList(bList), bodySize(bSize), description(dscpt) {}

// destructor
Alice::~Alice() {}

// Alice is a Singleton
Alice* Alice::makeAlice(const multimap<string, Stuff*>& sList, const map<string, NPC*>& hList, const map<string, NPC*>& bList, const int& bSize, const int& hLevel, const string& nm, const string& dscpt)
{
    static Alice alice(sList, hList, bList, bSize, hLevel, nm, dscpt);
    
    return &alice;
}

//adds a person to the list of Helpers
void Alice::taggingAlong(NPC* tagger)
{
    helperList.insert(pair<string, NPC*>(tagger->getName(),tagger));
}

//removes a person from the list of Helpers
void Alice::ditched(NPC* ditcher)
{
    helperList.erase(helperList.find(ditcher->getName()));
}

//now alice's friends can come with her
void Alice::move(Place* to) const
{
	Place* from = whereAreYou();
	from->personLeaves(this);        // remove person from current location
    	to->personEnters(this);          // move a person to another place
    	for(map<string, NPC*>::iterator i=helperList.begin(); i!=helperList.end(); i++)
    	{
    		(i->second)->move(to);
    	}
}

//Alice adds item to the list of stuff
void Alice::pickup(Stuff* item)
{
    recieve(item);
}

//Alice drops an item
void Alice::drop(Stuff* item)
{
    stuffList.erase(stuffList.find(item->getName()));
}

//something we need to think about is what happens to stuff after it is used.... As I see it we have a couple options: use a find_if (not certain exists for multimaps but we could certainly just apply the normal algorithm with an iterator)

// lets just delete it?

//Alice uses an item on herself
void Alice::use(Stuff* item)
{
    item->useItem(this);		//the item will have a useItem function
}

//Alice uses an item in a place
void Alice::use(Stuff* item, Place* where)
{
    item->useItem(where);
}

//Alice uses an item on a thing
void Alice::use(Stuff* item, Thing* what)
{
    item->useItem(what);
}

//Alice uses an item on a person
void Alice::use(Stuff* item, Person* who)
{
    item->useItem(who);
}

int Alice::getBodySize() const
{
    return bodySize;
}

void Alice::setBodySize(const int& s)
{
    bodySize = s;
}

// output what she has, who she's met, bodySize, and health	//I just renamed it to out instead of cout since cout is a thing already
std::ostream& Alice::render(std::ostream& out) const
{
    string s;
    if(getBodySize() == 2)
        s = "normal size";
    if(getBodySize() == 3)
        s = "BIG";
    if(getBodySize() == 1)
        s = "small";
        
    out << "Alice is " << s << endl;
    out << "Her health level is " << getHealth() << endl;
    
    out << "She has these items: ";

    if(!(stuffList.empty()))
    {
        // No viable conversion from 'const_iterator' (aka '__map_const_iterator<typename __base::const_iterator>') to 'multimap<string, Stuff *>::iterator' (aka '__map_iterator<typename __base::iterator>')
        
        multimap<string, Stuff*>::iterator i;
        i=stuffList.begin();
        out << (i->second)->getName();
        i++;
        
        for(; i!=stuffList.end(); i++)
            out << ", " << (i->second)->getName();
    }
    
    else
        out << "nothing" << endl;
    
    if(!helperList.empty())
    {
        out << "/nHer friends are: ";
        
        // No viable conversion from 'const_iterator' (aka '__map_const_iterator<typename __base::const_iterator>') to 'multimap<string, Stuff *>::iterator' (aka '__map_iterator<typename __base::iterator>')
        
        map<string, NPC*>::iterator i=helperList.begin();
        out << (i->second)->getName();
        i++;
        
        for(; i!=helperList.end(); i++)
            out << ", " << (i->second)->getName();
    }
    
    else
        out << "no friends, yet" << endl;;
    
    if(!badguyList.empty())
    {
        out << "/nHer enemies are: ";
        
        // No viable conversion from 'const_iterator' (aka '__map_const_iterator<typename __base::const_iterator>') to 'multimap<string, Stuff *>::iterator' (aka '__map_iterator<typename __base::iterator>')
        
        map<string, NPC*>::iterator i=badguyList.begin();
        out << (i->second)->getName();
        i++;
        
        for(; i!=badguyList.end(); i++)
            out << ", " << (i->second)->getName();
    }
    
    else
        out << "no enemies, yet" << endl;
    
    out << endl;
    return out;
}

// description of Alice
std::ostream& Alice::narrate(std::ostream& out) const
{
    out << description << endl;
    return out;
}

/*
 ----------------------------------
 NPC: Derived from Person
 ----------------------------------
 
 generic class will instantiate individual bad guys/helpers dynamically (on demand)
 
 */

// constructor
NPC::NPC(const std::string& nm, const std::string& dscrpt, const std::string& sayThings, const multimap<string, Stuff*>& sList, const int& hlth, const bool& frndly): Person (hlth, sList, nm), description(dscrpt), says(sayThings), friendly(frndly) {}

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

ostream& NPC::render(ostream& out) const
{
    string s;
    if(isfriendly() == true)
        s = "a friend";
    else
        s = "not a friend";
        
    out << getName() << " is " << s << endl;
    out << "Health level is: " << getHealth() << endl;
    
    out << getName() << " has these items: ";
    
    if(!stuffList.empty())
    {
        //No viable conversion from 'const_iterator' (aka '__map_const_iterator<typename __base::const_iterator>') to 'multimap<string, Stuff *>::iterator' (aka '__map_iterator<typename __base::iterator>')
        
        multimap<string, Stuff*>::iterator i;
        i=stuffList.begin();
        out << (i->second)->getName();
        i++;
        
        for(; i!=stuffList.end(); i++)
            out << ", " << (i->second)->getName();
    }
    
    else
        out << "nothing";
    
    out << endl;
    return out;
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
    //Person* returnValue;		\\lets just use nullptr so we know that returnValue is not just pointing somewhere random
    
    if (who == "Bandersnatch")
    {
        string nm = "Bandersnatch";
        string dscrpt = "I'm a bad guy";
        string sayThings = "I'm gonna get you";
        
        Stuff* bandersnatchEye = new FriendStuff("BandersnatchEye", "If Alice gives Bandersnatch his missing eye, he will become her friend", 1, true);
        
        multimap<string, Stuff*> bList;
        bList.insert(pair<string, Stuff*>(bandersnatchEye->getName(), bandersnatchEye));
        
        int hLevel = 10;
        bool frndly = false;
        
        Person* bandersnatch = new NPC(nm, dscrpt, sayThings, bList, hLevel, frndly);
        return bandersnatch;
    }
    
    else if (who == "Jabberwocky")
    {
        string nm = "Jabberwocky";
        string dscrpt = "I'm a really bad guy";
        string sayThings = "I'm really gonna get you";
        
        Stuff* excalibur = new HealthStuff("Sword", "Watch out! He has a big sword!", -3, true);
        
        multimap<string, Stuff*> jList;
        jList.insert(pair<string, Stuff*>(excalibur->getName(), excalibur));
        
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
        
        Stuff* elixar = new HealthStuff("Potion", "Drink my potion and see what happens", -5, true);

        multimap<string, Stuff*> rList;
        rList.insert(pair<string, Stuff*>(elixar->getName(), elixar));
        
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
        
        //Stuff* watch = new Stuff("Watch", "My watch can speed up time", 3, true);
        
        multimap<string, Stuff*> wList;
        //wList.push(watch);
        
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
        
        multimap<string, Stuff*> mList;
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
        
        multimap<string, Stuff*> cList;
        
        int hLevel = 10;
        bool frndly = true;
        
        Person* cheshireCat = new NPC(nm, dscrpt, sayThings, cList, hLevel, frndly);
        
        return cheshireCat;
    }
    
    else if (who == "Alice")
    {
        multimap<string, Stuff*> aList;
        map<string, NPC*> hList;
        map<string, NPC*> bList;
        int bSize = 2;
        int hLevel = 10;
        string nm = "Alice";
        string dscpt = "I'm a little girl.";
        
        Person* alice = Alice::makeAlice(aList, hList, bList, bSize, hLevel, nm, dscpt);
        
        return alice;
    }
    
    return nullptr;
}

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
    return name;
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

GrowStuff::~GrowStuff() { }

void GrowStuff::useItem(Alice* who)
{
    who->setBodySize(who->getBodySize()+result);
    status = 0;
    
}

void GrowStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
void GrowStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void GrowStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}
void GrowStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
void GrowStuff::useItem(const Person* who, Place* where) {cout << getName() << "cannot be used on this way";}

// HealthStuff
HealthStuff::HealthStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

HealthStuff::~HealthStuff() {}

void HealthStuff::useItem(Person* who)
{
    who->hurt(result);
    status = 0;
}

void HealthStuff::useItem(Alice* who)
{
	who->hurt(result);
	status = 0;
}
void HealthStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
void HealthStuff::useItem(NPC* who)
{
	who->hurt(result);
	status = 0;
}
void HealthStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
void HealthStuff::useItem(const Person* who, Place* where) {cout << getName() << "cannot be used on this way";}

// FriendStuff
FriendStuff::FriendStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

FriendStuff::~FriendStuff() {}

//we should think about how to customize this to be just for bandersnatch. I suspect that will be in main or something... or maybe not, since it will have to be true all the time...
void FriendStuff::useItem(NPC* who)
{
    who->setFriendly(result);
    status = 0;
}

void FriendStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}
void FriendStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void FriendStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
void FriendStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
void FriendStuff::useItem(const Person* who, Place* where) {cout << getName() << "cannot be used on this way";}

// OpenStuff
OpenStuff::OpenStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

OpenStuff::~OpenStuff() {}

void OpenStuff::useItem(Thing* what)
{
    what->openThing();
    status = 0;
}

void OpenStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
void OpenStuff::useItem(const Person* who, Place* where) {cout << getName() << "cannot be used like this";}

MoveStuff::MoveStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

MoveStuff::~MoveStuff() {}

// move Alice home
void MoveStuff::useItem(const Person* who, Place* where)
{
    map<string, Place*> go = where->getNewPlaceToGo();
        
    for(map<string, Place*>::iterator i=go.begin(); i!=go.end(); i++)
    {
        if((i->second)->getPlaceName() == "Home")
        {
            Place* there = i->second;
            who->move(there);
        }
    }
    status = 0;
    
    /*
    if(where->getPlaceName()=="Home")
    {
    	who->move(where);
    }
    status=0;
    */
}

void MoveStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
void MoveStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}
void MoveStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}
void MoveStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void MoveStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}

/*
 ----------------------------------
 Thing classes: Base
 ----------------------------------
 */

Thing::Thing(const bool& stat, const string nm):status(stat), name(nm){}

Thing::~Thing() {}

string Thing::getName() const
{
    return name;
}

 /*
 ----------------------------------
 Door classes: Derived from Thing 
 ----------------------------------
 */
Door::Door(const bool& stat, string nm, const map<string, Place*>& betwn): Thing(stat, nm)
{
	between = betwn;
    //std::cout << "constructed Door" << std::endl;
}

Door::~Door() {}

void Door::openThing()
{
	if(status==0)
	{
        //Invalid operands to binary expression ('iterator' (aka '__map_iterator<typename __base::iterator>') and 'int')
		between.begin()->second->newPlaceToGo(between.begin()+1);
		(between.begin()+1)->second->newPlaceToGo(between.begin());
		status=1;
	}
		
}

void Door::closeThing()
{
	if(status==1)
	{
        //Invalid operands to binary expression ('iterator' (aka '__map_iterator<typename __base::iterator>') and 'int')
		between.begin()->second->blockPlaceToGo(between.begin()+1);
		(between.begin()+1)->second->blockPlaceToGo(between.begin());
		status=0;
	}
}


/*
 ----------------------------------
 Chest classes: Derived from Thing 
 ----------------------------------
*/

Chest::Chest(const bool stat, string nm, const multimap<string, Stuff*>& contains):Thing(stat, nm)
{
	inside=contains;
    //std::cout << "constructed Chest" << std::endl;
}

Chest::~Chest() {}

void Chest::openThing()
{
	status=1;
}

void Chest::closeThing()
{
	status=0;
}

void Chest::takeStuff(Stuff* tk)
{
	inside.erase(inside.find(tk->getName()));
}

multimap<string, Stuff*>& Chest::whatsinside()
{
	return inside;
}

/*
 ----------------------------------
 Game Class: Base
 ----------------------------------
 */

Game::Game()
{
    makePlaces();
    makePeople();
    makeStuff();
}

Game::~Game() {}

map<string, Place*> Game::getPlaceList() const
{
    return places;
}

//map<string, Person*> Game::getPeopleList() const
//{
//    return people;
//}

void Game::makePlaces()
{
    // Tree
    // changing all List<> to map<>
    map<string, Person*> tPeople;
    multimap<string, Stuff*> tStuff;
    multimap<string,Thing*> tThing;
    map<string, Place*> ttrav;
    
    Place* tree = new Place("Tree", "Alice woke up under a big oak tree. She saw a white rabbit run by.", tStuff, tPeople, tThing, ttrav);
    places.insert(pair<string, Place*>(tree->getPlaceName(), tree));
    
//    Place* walker1 = nullptr;
//    Place* walker2 = nullptr;
//    for (int i=1; i<places.getSize(); i++){
//        if(places.peek(i)->getPlaceName()=="battlefield"){
//            walker1 = places.peek(i);
//        }
//        if(places.peek(i)->getPlaceName()=="tree"){
//            walker2=places.peek(i);
//        }
//    }
//    walker1->newPlaceToGo(walker2);
    
    // Garden
    map<string, Person*> gPeople;
    multimap<string, Stuff*> gStuff;
    multimap<string,Thing*> gThing;
    map<string, Place*> gtrav;
    
    Place* garden = new Place("Garden", "Alice follows the White Rabbit to a beautiful garden full of white roses. Should she pick one?", gStuff, gPeople, gThing, gtrav);
    places.insert(pair<string, Place*>(garden->getPlaceName(), garden));
    
    // Woods
    map<string, Person*> wPeople;
    multimap<string, Stuff*> wStuff;
    multimap<string,Thing*> wThing;
    map<string, Place*> wtrav;
    
    Place* woods = new Place("Woods", "Alice is in the Woods. She sees a cat in a tree.", wStuff, wPeople, wThing, wtrav);
    places.insert(pair<string, Place*>(woods->getPlaceName(), woods));
    
    // TeaParty
    map<string, Person*> pPeople;
    multimap<string, Stuff*> pStuff;
    multimap<string,Thing*> pThing;
    map<string, Place*> ptrav;
    
    Place* teaParty = new Place("TeaParty", "Alice goes to a Tea Party.", pStuff, pPeople, pThing, ptrav);
    places.insert(pair<string, Place*>(teaParty->getPlaceName(), teaParty));
    
    //Castle
    map<string, Person*> cPeople;
    multimap<string, Stuff*> cStuff;
    multimap<string,Thing*> cThing;
    map<string, Place*> ctrav;
    
    Place* castle = new Place("Castle", "Alice is taken to the Red Queen's Castle.", cStuff, cPeople, cThing, ctrav);
    places.insert(pair<string, Place*>(castle->getPlaceName(), castle));
    
    // Battlefield
    map<string, Person*> bPeople;
    multimap<string, Stuff*> bStuff;
    multimap<string,Thing*> bThing;
    map<string, Place*> trav;
    
    Place* battlefield = new Place("Battlefield", "Alice is all suited up and ready to fight.", bStuff, bPeople, bThing, trav);
    
    // places.peek(battlefield)->newPlaceToGo(places.peek(tree));
    
    places.insert(pair<string, Place*>(battlefield->getPlaceName(), battlefield));
    
    // Home
    map<string, Person*> hPeople;
    multimap<string, Stuff*> hStuff;
    multimap<string,Thing*> hThing;
    map<string, Place*> htrav;
    
    Place* home = new Place("Home", "Alice wakes up and remembers a wonderful dream...", hStuff, hPeople, hThing, trav);
    places.insert(pair<string, Place*>(home->getPlaceName(), home));
}

void Game::makePeople()
{
    //Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
    //Helpers will be WhiteRabbit, MadHatter, CheshireCat...
    
    //(1)
    Person* bandersnatch = PersonFactory::makePerson("Bandersnatch");
    places.find("Garden")->second->personEnters(bandersnatch);

    
    // (2)
    Person* jabberwocky = PersonFactory::makePerson("Jabberwocky");
    places.find("Castle")->second->personEnters(jabberwocky);
    
    
    // (3)
    Person* redQueen = PersonFactory::makePerson("RedQueen");
    places.find("Castle")->second->personEnters(redQueen);
    
    // (4)
    Person* whiteRabbit = PersonFactory::makePerson("WhiteRabbit");
    places.find("Tree")->second->personEnters(whiteRabbit);
    
    // (5)
    Person* madHatter = PersonFactory::makePerson("MadHatter");
    places.find("TeaParty")->second->personEnters(madHatter);
    
    // (6)
    Person* cheshireCat = PersonFactory::makePerson("CheshireCat");
    places.find("Woods")->second->personEnters(cheshireCat);
    
    // (7)
    Person* alice = PersonFactory::makePerson("Alice");
    places.find("Tree")->second->personEnters(alice);
    
}

// make list of stuff for each place, call Stuff constructor to make stuff, push into place's stuff list //this is good :) I hadn't planned it like this i dont think but I really like this. It works pretty darn well.
void Game::makeStuff()
{
    // (1) Tree
    // Tree has nothing in list
    
    // (2) Garden
    Stuff* whiteRose = new HealthStuff("WhiteRose", "The Red Queen hates white roses", 3, 1);
    places.find("Garden")->second->genStuff(whiteRose);
    
    // (3) Woods
    Stuff* key = new OpenStuff("Key", "Key can be used to open the door, but Alice needs to be small to get through!", 1, 1);
    places.find("Woods")->second->genStuff(key);
    
    // (4) TeaParty	//how does she get to normal size? Do you want me to make these just iterators so cake makes her one size bigger and tea makes her one size smaller
    Stuff* cake = new GrowStuff("Cake", "The cake will make Alice big!", 3, 1);
    Stuff* tea = new GrowStuff("Tea", "Drinking the tea will make Alice small.", 1, 1);
    places.find("TeaParty")->second->genStuff(cake);
    places.find("TeaParty")->second->genStuff(tea);
    
    // (5) Castle
    Stuff* sword = new HealthStuff("Sword", "Sword can be used to fight the Jabberwocky", 4, 1);
    places.find("Castle")->second->genStuff(sword);
    
    // (6) Battlefield
    Stuff* jabberBlood = new MoveStuff("JabberBlood", "Drinking the Jabberwocky's purple blood will take Alice home", 1, 1);
    
    for(map<string, Place*>::iterator i = places.begin(); i!=places.end(); i++)
    {
        // added Place:: to whoHere (whoHere undefined otherwise)
        if(((((i->second)->Place::whoHere()).find("Jabberwocky")))!=((i->second)->Place::whoHere()).end())
            ((((i->second)->Place::whoHere()).find("Jabberwocky"))->second)->recieve(jabberBlood);
    }
    
    // (7) Home
    // Home has nothing in list
}

//before I change this I want to talk about the plan...
void Game::delegate(const string input)
{
    // removed old code
}

// needed to make static lists work
map<string, Place*> Game::places;
//List<Person*> Game::people;


