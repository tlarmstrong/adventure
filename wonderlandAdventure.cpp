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

/* TEST COMMENT OUT
 
Place::Place(const std::string& nm, const std::string& dscpt, const multimap<string, Stuff*>& what, const map<string, Person*>& who, const multimap<string, Thing*>& obj, const map<string, Place*>& trav): name(nm), description(dscpt), stuffHere(what), peopleHere(who), thingHere(obj), placeTo(trav) {}
 
Place::~Place()
{
	for (map<string, Person*>::iterator i=peopleHere.begin(); i!=peopleHere.end(); i++)		//deletes all people in a place
	{
		delete i->second;
	}
	
	for (map<string, Stuff*>::iterator i=stuffHere.begin(); i!=stuffHere.end(); i++)	//deletes all the stuff in a place
	{
		delete i->second;
	}
	
	for (map<string, Thing*>::iterator i=thingHere.begin(); i!=thingHere.end(); i++) //deletes all the things in a place
	{
		delete i->second;
	}
	
}

// pass all return maps/multimaps by value
map<string, Person*>& Place::whoHere()     //returns a list of everybody here
{
    return peopleHere;
}

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

multimap<string, Stuff*>& Place::whatsHere()              // returns the list of stuff here
{
    return stuffHere;
}

std::multimap<std::string, Thing*>& Place::openHere()
{
    return thingHere;
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
}

void Place::newPlaceToGo(Place* goTo)
{
    placeTo.insert(pair<string, Place*>(goTo->getPlaceName(),goTo));
}

void Place::blockPlaceToGo(Place* block)
{
    placeTo.erase(placeTo.find(block->getPlaceName()));
}

map<string, Place*>& Place::getNewPlaceToGo()
{
    return placeTo;
}

multimap<string, Thing*>& Place::getThingsHere()
{
	return thingHere;
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
	if (!(peopleHere.empty()))
	{
        out << "You see there are other people here: ";
        
        // Error: No viable overloaded '='
        // Fix: Change iterator to const_iterator
        
		std::map<string, Person*>::const_iterator i;
		i=peopleHere.begin();
		out << i->second->getName();
		i++;
		for(;i!=peopleHere.end();i++)
		{
			out << ", " <<i->second->getName();
		}
        out << endl;
	}
	
	if (!(thingHere.empty()))
	{
		out << "You see a ";
        
        // Error: No viable overloaded '='
        // Fix: Change iterator to const_iterator
        
		std::map<string, Thing*>::const_iterator i;
		i=thingHere.begin();
		out << i->second->getName();
		i++;
		for(;i!=thingHere.end();i++)
		{
			out << ", and a" <<i->second->getName();
		}
		out << "."<< endl;
	}
    
	if (!(stuffHere.empty()))
	{
		out << "On the ground you see a ";
        
        // Error: No viable overloaded '='
        // Fix: Change iterator to const_iterator
        
		std::map<string, Stuff*>::const_iterator i;
		i=stuffHere.begin();
		out << i->second->getName();
		i++;
		for(;i!=stuffHere.end();i++)
		{
			out << ", and a" <<i->second->getName();
		}
		out << "."<< endl;
	}
    
	if (!(placeTo.empty()))
	{
		out << "From here you can go to: ";
        
        // Error: No viable overloaded '='
        // Fix: Change iterator to const_iterator
        
		std::map<string, Place*>::const_iterator i;
		i=placeTo.begin();
		out << i->second->getPlaceName();
		i++;
		for(;i!=placeTo.end();i++)
		{
			out << ", " <<i->second->getPlaceName();
		}
		out << "."<< endl;
	}
    out << endl;
    return out;
}

*/

/*
 -----------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 -----------------------------------------------------------
 */

// ***********************

// took all stuff lists out of constructor (person, alice, npc)

// each person still has multiple lists, but we will insert "stuff" in each list in the PersonFactory instead of filling them in the PF, passing them to the constuctor, and then copying them over

// ***********************

Person::Person(const int& hLevel, const string& nm, bool attk) : health(hLevel), name(nm), isAttack(attk) {}

// default constructor for Person Factory to work
Person::Person() {}

// destructor

// *********************

// changed destructor to accommodate different lists, hope it works

// *********************

Person::~Person()
{
	for (multimap<string, HealthStuff*>::iterator h=hStuff.begin(); h!=hStuff.end(); h++)
	{
        	delete h->second;
	}
    
    for (multimap<string, GrowStuff*>::iterator g=gStuff.begin(); g!=gStuff.end(); g++)
    {
        delete g->second;
    }
    
    for (multimap<string, FriendStuff*>::iterator f=fStuff.begin(); f!=fStuff.end(); f++)
    {
        delete f->second;
    }
    
    for (multimap<string, OpenStuff*>::iterator o=oStuff.begin(); o!=oStuff.end(); o++)
    {
        delete o->second;
    }
    
    for (multimap<string, MoveStuff*>::iterator m=mStuff.begin(); m!=mStuff.end(); m++)
    {
        delete m->second;
    }
}

// *********************

// changed dies() to accommodate different lists, hope it works

// *********************

/* COMMENT OUT TO TEST
void Person::dies()
{
	multimap<string, HealthStuff*>::iterator h;
	h=hStuff.begin();
	for(;!hStuff.empty();h++)
	{
		this->whereAreYou()->dropped(h->second, this);
	}
    
    multimap<string, GrowStuff*>::iterator g;
    g=gStuff.begin();
    for(;!gStuff.empty();g++)
    {
        this->whereAreYou()->dropped(g->second, this);
    }
    
    multimap<string, FriendStuff*>::iterator f;
    f=fStuff.begin();
    for(;!fStuff.empty();f++)
    {
        this->whereAreYou()->dropped(f->second, this);
    }
    
    multimap<string, OpenStuff*>::iterator o;
    o=oStuff.begin();
    for(;!oStuff.empty();o++)
    {
        this->whereAreYou()->dropped(o->second, this);
    }
    
    multimap<string, MoveStuff*>::iterator m;
    m=mStuff.begin();
    for(;!mStuff.empty();m++)
    {
        this->whereAreYou()->dropped(m->second, this);
    }
    
    this->whereAreYou()->personLeaves(this);
    delete this;
}
*/

/* COMMENT OUT TO TEST
bool Person::isDead()
{
	if (health<=0)
	{
        this->dies();
		return true;
	}
	else
		return false;
}
 */

/* TEST COMMENT OUT
 
void Person::move(Place* to) const
{
    Place* from = whereAreYou();

    // remove person from current location
    from->personLeaves(this);
    
    // move a person to another place
    to->personEnters(this);
}


// get Place where Person is
Place* Person::whereAreYou() const
{
    Place* here=NULL;
    
    for(map<string, Place*>::const_iterator i = Game::places.begin(); i!= Game::places.end(); i++)
    {
        if((((i->second)->whoHere()).find(getName())) != ((i->second)->whoHere()).end())
        {
            here = (i->second);
        }
    }
    return here;
}
 
 */

// ***********************

// made give() templated/polymorphic and receive() polymorphic

// ***********************

//gives an item to someone else
/*
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
 */

template<class T>
void Person::give(HealthStuff* item, T* other)
{
    if(hStuff.find(item->getName()) != hStuff.end())
    {
        hStuff.erase(hStuff.find(item->getName()));
        other->recieve(item);
    }
}

template<class T>
void Person::give(GrowStuff* item, T* other)
{
    if(gStuff.find(item->getName()) != gStuff.end())
    {
        gStuff.erase(gStuff.find(item->getName()));
        other->recieve(item);
    }
}

template<class T>
void Person::give(FriendStuff* item, T* other)
{
    if(fStuff.find(item->getName()) != fStuff.end())
    {
        fStuff.erase(fStuff.find(item->getName()));
        other->recieve(item);
    }
}

template<class T>
void Person::give(OpenStuff* item, T* other)
{
    if(oStuff.find(item->getName()) != oStuff.end())
    {
        oStuff.erase(oStuff.find(item->getName()));
        other->recieve(item);
    }
}

template<class T>
void Person::give(MoveStuff* item, T* other)
{
    if(mStuff.find(item->getName()) != mStuff.end())
    {
        mStuff.erase(mStuff.find(item->getName()));
        other->recieve(item);
    }
}

void Person::recieve(HealthStuff* item)
{
    hStuff.insert(pair<string, HealthStuff*>(item->getName(), item));
}

void Person::recieve(GrowStuff* item)
{
    gStuff.insert(pair<string, GrowStuff*>(item->getName(), item));
}

void Person::recieve(FriendStuff* item)
{
    fStuff.insert(pair<string, FriendStuff*>(item->getName(), item));
}

void Person::recieve(OpenStuff* item)
{
    oStuff.insert(pair<string, OpenStuff*>(item->getName(), item));
}

void Person::recieve(MoveStuff* item)
{
    mStuff.insert(pair<string, MoveStuff*>(item->getName(), item));
}

// **************************

// end of possible polymorphic functions

// **************************

//person takes damage
void Person::hurt(const int& damage)
{
    health -= damage;
}

void Person::attack()
{
    isAttack = true;
}

int Person::getHealth() const
{
    return health;
}

// ************************

// let's make the stuff lists public

// ************************

/*
multimap<string, Stuff*>& Person::getStuffList()
{
    return stuffList;
}
 */

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
Alice::Alice(const int& bSize, const int& hLevel, const string& nm, const string& dscpt, bool attk) : Person(hLevel, nm, attk), description(dscpt) {}

// destructor
Alice::~Alice() {}

// Alice is a Singleton
//Alice* Alice::makeAlice(const int& bSize, const int& hLevel, const string& nm, const string& dscpt, bool attk)

Alice* Alice::makeAlice()
{
    int bSize = 2;
    int hLevel = 30;
    string nm = "Alice";
    string dscpt = "Hi! I'm Alice";
    bool attk = false;

    static Alice alice(bSize, hLevel, nm, dscpt, attk);
    
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
    if(this->helperList.find(ditcher->getName())!=this->helperList.end())
    {
    	helperList.erase(helperList.find(ditcher->getName()));
    }

}

/* COMMENT OUT TO TEST
//now alice's friends can come with her
void Alice::move(Place* to) const
{
	Place* from = whereAreYou();
    
	from->personLeaves(this);        // remove person from current location
    to->personEnters(this);          // move a person to another place

    	for(map<string, NPC*>::const_iterator i=helperList.begin(); i!=helperList.end(); i++)
    	{
    		(i->second)->move(to);
    	}
}

 */

// **********************

// used templates or made polymorphic

// moved these to just be in Alice, but did we decide to have some of these available to NPCs too (ex: drop())? Move these back to Person and make virtual so NPCs can use, too?

// **********************

/* COMMENT OUT TO TEST
void Alice::choose(Chest* chst, Stuff* item)
{
	chst->takeStuff(item);
	recieve(item);
}
*/

template<class T>
void Alice::pickUp(T* item)
{
    recieve(item);
}

/*
//Alice drops an item
void Alice::drop(Stuff* item)
{
    stuffList.erase(stuffList.find(item->getName()));
}
*/

template<class T>
void Alice::drop(T* item)
{
    if(hStuff.find(item))
    {
        hStuff.erase(hStuff.find(item->getName()));
    }
    
    if(gStuff.find(item))
    {
        gStuff.erase(gStuff.find(item->getName()));
    }
    
    if(fStuff.find(item))
    {
        fStuff.erase(fStuff.find(item->getName()));
    }
    
    if(oStuff.find(item))
    {
        oStuff.erase(oStuff.find(item->getName()));
    }
    
    if(mStuff.find(item))
    {
        mStuff.erase(mStuff.find(item->getName()));
    }
}

// delete stuff after used?
//Alice uses an item on herself
template<class T>
void Alice::use(T* item)
{
    item->useItem(this);
}

/* COMMENT OUT TO TEST
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

 */

//Alice uses an item on a person
template<class T>
void Alice::use(T* item, NPC* who)
{
    item->useItem(who);
}

int Alice::getBodySize() const
{
    return bodySize;
}

void Alice::setBodySize(const int& sz)
{
    bodySize = sz;
}

// output what she has, who she's met, bodySize, and health
std::ostream& Alice::render(std::ostream& out) const
{
    string sz;
    if(bodySize == 1)
        sz = "small";
    
    else if(bodySize == 3)
        sz = "BIG";
    
    else
        sz = "normal size";
    
    //out << "Alice is at the " << whereAreYou()->getPlaceName() << endl;
    out << "She is " << sz << endl;
    out << "Her health level is " << getHealth() << endl;
    
    out << "She has these items: " << endl;
    
// **********************************
    
// adjusted to print stuff out of lists one line at a time

// **********************************

    if(!hStuff.empty())
    {
        for(map<string, HealthStuff*>::const_iterator i = hStuff.begin(); i!=hStuff.end(); i++)
        {
            out << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "No weapons" << endl;
    
    if(!gStuff.empty())
    {
        for(map<string, GrowStuff*>::const_iterator i = gStuff.begin(); i!=gStuff.end(); i++)
        {
            out << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "Nothing to make her small or big" << endl;
    
    if(!fStuff.empty())
    {
        for(map<string, FriendStuff*>::const_iterator i = fStuff.begin(); i!=fStuff.end(); i++)
        {
            out << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "Nothing to help make any friends" << endl;
    
    if(!oStuff.empty())
    {
        for(map<string, OpenStuff*>::const_iterator i = oStuff.begin(); i!=oStuff.end(); i++)
        {
            out << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "No keys" << endl;
    
    if(!mStuff.empty())
    {
        for(map<string, MoveStuff*>::const_iterator i = mStuff.begin(); i!=mStuff.end(); i++)
        {
            out << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "Nothing that will take her home" << endl;
    
    if(!helperList.empty())
    {
        out << "/nHer friends are: ";
        
        map<string, NPC*>::const_iterator i=helperList.begin();
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

        map<string, NPC*>::const_iterator i=badguyList.begin();
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
NPC::NPC(const std::string& nm, const std::string& dscrpt, const std::string& sayThings, const int& hlth, const bool& frndly, bool a): Person (hlth, nm, a), description(dscrpt), says(sayThings), friendly(frndly) {}

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
    
    out << getName() << " has these items: " << endl;
    
    // **********************************
    
    // adjusted to print stuff in each list one line at a time
    
    // **********************************
    
    if(hStuff.empty() && gStuff.empty() && fStuff.empty() && oStuff.empty() && mStuff.empty())
    {
        out << "nothing" << endl;
    }
    
    else
    {
        if(!hStuff.empty())
        {
            for(map<string, HealthStuff*>::const_iterator i = hStuff.begin(); i!=hStuff.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!gStuff.empty())
        {
            for(map<string, GrowStuff*>::const_iterator i = gStuff.begin(); i!=gStuff.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!fStuff.empty())
        {
            for(map<string, FriendStuff*>::const_iterator i = fStuff.begin(); i!=fStuff.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!oStuff.empty())
        {
            for(map<string, OpenStuff*>::const_iterator i = oStuff.begin(); i!=oStuff.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!mStuff.empty())
        {
            for(map<string, MoveStuff*>::const_iterator i = mStuff.begin(); i!=mStuff.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
    }
    
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
NPC* PersonFactory::makePerson(std::string who)
{
    if (who == "Bandersnatch")
    {
        string nm = "Bandersnatch";
        string dscrpt = "I'm a bad guy";
        string sayThings = "I'm gonna get you";
        
        int hLevel = 10;
        bool frndly = false;
        bool attk = false;
        
        NPC* bandersnatch = new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        
        FriendStuff* bandersnatchEye = new FriendStuff("BandersnatchEye", "If Alice gives Bandersnatch his missing eye, he will become her friend", 1, true);
        
        HealthStuff* knife = new HealthStuff("Knife", "Watch out! He has a sharp knife!", 3, true);
        
        // *******************
        
        // inserting stuff here instead of inserting into dummy list and passing to constructor to copy (constructors for person, alice, and npc no longer take lists)
        
        // *******************
        
        bandersnatch->fStuff.insert(pair<string, FriendStuff*>(bandersnatchEye->getName(), bandersnatchEye));
        bandersnatch->hStuff.insert(pair<string, HealthStuff*>(knife->getName(), knife));
        
        return bandersnatch;
    }
    
    else if (who == "Jabberwocky")
    {
        string nm = "Jabberwocky";
        string dscrpt = "I'm a really bad guy";
        string sayThings = "I'm really gonna get you";
        int hLevel = 10;
        bool frndly = false;
        bool attk = false;
        
        NPC* jabberwocky = new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        
        HealthStuff* excalibur = new HealthStuff("Sword", "Watch out! He has a big sword!", 5, true);
        
        MoveStuff* jabberBlood = new MoveStuff("jabberBlood", "It's magic...it can take you home", 1, true);
        
        jabberwocky->hStuff.insert(pair<string, HealthStuff*>(excalibur->getName(), excalibur));
        
        // ********************
        
        // moved jabberBlood here from makePlaces() in Game
        
        // ********************
        
        jabberwocky->mStuff.insert(pair<string, MoveStuff*>(jabberBlood->getName(), jabberBlood));
        
        return jabberwocky;
    }
    
    else if (who == "RedQueen")
    {
        string nm = "RedQueen";
        string dscrpt = "I'm an evil queen";
        string sayThings = "I'm gonna get you, my pretty";
        int hLevel = 10;
        bool frndly = false;
        bool attk = false;
        
        NPC* rqueen=new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        
        HealthStuff* elixar = new HealthStuff("Potion", "Drink my potion and see what happens", 5, true);
        
        rqueen->hStuff.insert(pair<string, HealthStuff*>(elixar->getName(), elixar));

        return rqueen;
    }
    
    else if (who == "WhiteRabbit")
    {
        string nm = "WhiteRabbit";
        string dscrpt = "I'm a whiterabbit";
        string sayThings = "I'm a friend";
        int hLevel = 10;
        bool frndly = true;
        bool attk = false;
        
        NPC* whiteRabbit = new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        
        // has nothing in lists
        
        return whiteRabbit;
    }
    
    else if (who == "MadHatter")
    {
        string nm = "MadHatter";
        string dscrpt = "I like tea parties";
        string sayThings = "Would you like to come to my party?";
        int hLevel = 10;
        bool frndly = true;
        bool attk = false;
        
        // has nothing in lists
        
        NPC* madHatter = new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        return madHatter;
    }
    
    else if (who == "CheshireCat")
    {
        string nm = "Cheshire Cat";
        string dscrpt = "I like to smile";
        string sayThings = "I'm a mysterious friend";
        int hLevel = 10;
        bool frndly = true;
        bool attk = false;
        
        NPC* cheshireCat = new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        
        // has nothing in lists
        
        return cheshireCat;
    }
    
    /* PF needs to return NPC* not Person* -- using makeAlice to instantiate her instead (see makePeople() in Game)
     
     else if (who == "Alice")
    {
        int bSize = 2;
        int hLevel = 30;
        string nm = "Alice";
        string dscpt = "Hi! I'm Alice";
        bool attk = false;
        
        Alice* alice = Alice::makeAlice( bSize, hLevel, nm, dscpt, attk);
        
        // starts with nothing in lists
        
        return alice;
    }
     */
    
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

// ************************************************************
// Added earlier

int Stuff::getResult()
{
    return result;
}
// ************************************************************

string Stuff::getName() const
{
    return name;
}

// output description of Stuff
std::ostream& Stuff::narrate(std::ostream& cout) const
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
    who->setBodySize(result);
    status = 0;
    
}

// *************************

// Since we are now using specific stuff-type lists, can we get rid of the virtual functions (although they do seem helpful)?

// *************************

//void GrowStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
//void GrowStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}

void GrowStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}

//void GrowStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
//void GrowStuff::useItem(/*const*/ Person* who, Place* where) {cout << getName() << "cannot be used on this way";}

// HealthStuff
HealthStuff::HealthStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

HealthStuff::~HealthStuff() {}

/* NO LONGER USING Person*, NEEDED?
void HealthStuff::useItem(Person* who)
{
    who->hurt(result);
    status = 0;
}
*/

void HealthStuff::useItem(Alice* who)
{
	who->hurt(result);
	status = 0;
}

/* COMMENT OUT TO TEST
void HealthStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
*/

void HealthStuff::useItem(NPC* who)
{
	who->hurt(result);
	status = 0;
}

/* NEEDED?
void HealthStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
void HealthStuff::useItem(Person* who, Place* where) {cout << getName() << "cannot be used on this way";}
*/

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

//void FriendStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
//void FriendStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
//void FriendStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
//void FriendStuff::useItem(/*const*/ Person* who, Place* where) {cout << getName() << "cannot be used on this way";}

// OpenStuff


OpenStuff::OpenStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

OpenStuff::~OpenStuff() {}

/* COMMENT OUT TO TEST
void OpenStuff::useItem(Thing* what)
{
    what->openThing();
    status = 0;
}

void OpenStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
void OpenStuff::useItem(Person* who, Place* where) {cout << getName() << "cannot be used like this";}

 */


MoveStuff::MoveStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

MoveStuff::~MoveStuff() {}

/* COMMENT OUT TO TEST
// move Alice home
void MoveStuff::useItem(Alice* who, Place* where)
{
    if(where->getPlaceName()=="Home")
    {
    	who->move(where);
    }
    status=0;
}

void MoveStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
void MoveStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}
void MoveStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}
void MoveStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void MoveStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
*/


/*
 ----------------------------------
 Thing classes: Base
 ----------------------------------
 */

/* COMMENT OUT TO TEST
Thing::Thing(const bool& stat, const string nm):status(stat), name(nm){}

Thing::~Thing() {}

string Thing::getName() const
{
    return name;
}

bool Thing::getStatus() const
{
	return status;
}

 */

 /*
 ----------------------------------
 Door classes: Derived from Thing 
 ----------------------------------
 */

/* COMMENT OUT TO TEST
Door::Door(const bool& stat, const string nm, const map<string, Place*>& betwn): Thing(stat, nm)
{
	between = betwn;
	thingtype="door";
    //std::cout << "constructed Door" << std::endl;
}

Door::~Door() {}

void Door::openThing()
{
	if(status==0)
	{
        between.begin()->second->blockPlaceToGo(((between.begin())++)->second);
        ((between.begin())++)->second->blockPlaceToGo(between.begin()->second);
		status=1;
	}
}

void Door::closeThing()
{
	map<string, Place*>::const_iterator i;
    i=Game::places.begin();
    for(; i!=Game::places.end();i++)
	{
		if(i->second->whoHere().find("Alice")!=i->second->whoHere().end())
		{
            i->second->whoHere().find("Alice")->second
			Alice* ali=
		}
	}
	if(status==1)
	{
        between.begin()->second->blockPlaceToGo(((between.begin())++)->second);
		((between.begin())++)->second->blockPlaceToGo(between.begin()->second);
		status=0;
	}
}
 */

/*
 ----------------------------------
 Chest classes: Derived from Thing 
 ----------------------------------
*/

/* COMMENT OUT TO TEST
Chest::Chest(const bool stat, const string nm, const multimap<string, Stuff*>& contains):Thing(stat, nm)
{
	inside=contains;
	thingtype="chest";
    //std::cout << "constructed Chest" << std::endl;
}

Chest::~Chest()
{
	for (multimap<string, Stuff*>::iterator j=inside.begin(); j!=inside.end(); j++)
	{
		delete j->second;
	}
}

void Chest::openThing()
{
	status=1;
}

void Chest::closeThing()
{
	status=0;
}
bool Chest::getStatus()
{
	return status;
}

void Chest::takeStuff(Stuff* tk)
{
	inside.erase(inside.find(tk->getName()));
}

multimap<string, Stuff*>& Chest::whatsinside()
{
	return inside;
}

std::ostream& Chest::narrate(std::ostream& out)
{
	out << "Inside you see:";
	if(this->whatsinside().empty())
		out << "nothing";
	else
	{
		multimap<string, Stuff*>::const_iterator i;
		i=this->whatsinside().begin();
		out << i->second->getName();
        i++;
		for(;i!=this->whatsinside().end();i++)
			out<< ", " <<i->second->getName();
		
	}
	return out;
}
*/

/*
 ----------------------------------
 Game Class: Base
 ----------------------------------
 */

Game::Game()
{
    //makePlaces(); COMMENT OUT TO TEST
    makePeople();
    //makeStuff(); COMMENT OUT TO TEST
}

Game::~Game() {}

/* COMMENT OUT TO TEST
map<string, Place*>& Game::getPlaceList()
{
    return places;
}
*/

/* COMMENT OUT TO TEST
void Game::makePlaces()
{
    // Tree
    // *******************************
    
    // could we take out the dummy lists and use insert instead (see Person Factory)
    
    // *******************************
    
    map<string, Person*> tPeople;
    multimap<string, Stuff*> tStuff;
    multimap<string,Thing*> tThing;
    map<string, Place*> ttrav;
    
    Place* tree = new Place("Tree", "Alice woke up under a big oak tree. She saw a whiterabbit run by.", tStuff, tPeople, tThing, ttrav);
    places.insert(pair<string, Place*>(tree->getPlaceName(), tree));
    
    // Garden
    map<string, Person*> gPeople;
    multimap<string, Stuff*> gStuff;
    multimap<string,Thing*> gThing;
    map<string, Place*> gtrav;
    
    Place* garden = new Place("Garden", "Alice follows the WhiteRabbit to a beautiful garden full of white roses. Should she pick one?", gStuff, gPeople, gThing, gtrav);
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
    
    //CastleP1
    map<string, Person*> cPeople;
    multimap<string, Stuff*> cStuff;
    multimap<string,Thing*> cThing;
    map<string, Place*> ctrav;
    
    Place* castle = new Place("CastleP1", "Alice is taken to the Red Queen's Castle.", cStuff, cPeople, cThing, ctrav);
    places.insert(pair<string, Place*>(castle->getPlaceName(), castle));
    
    //CastleP2
    map<string, Person*> c2People;
    multimap<string, Stuff*> c2Stuff;
    multimap<string,Thing*> c2Thing;
    map<string, Place*> c2trav;
    
    Place* castle2 = new Place("CastleP2", "Escape the Castle.", c2Stuff, c2People, c2Thing, c2trav);
    
    map<string, Place*> doorway;
    doorway.insert(pair<string, Place*>(castle2->getPlaceName(),castle2));
    doorway.insert(pair<string, Place*>(castle->getPlaceName(),castle));
    Thing* cd=new Door(0, "DoorInCastle", doorway);
    castle->genThing(cd);
    castle2->genThing(cd);
    
    multimap<std::string, Stuff*> sinchst;
    Stuff* aswrd=new HealthStuff("SwordToKillJabberwocky", "You can use this to kill the Jabberwocky", 5, 1);
    sinchst.insert(pair<string, Stuff*>(aswrd->getName(),aswrd));
    Thing* dchst=new Chest(0, "ChestInCastle", sinchst);
    castle->genThing(dchst);
    
    places.insert(pair<string, Place*>(castle->getPlaceName(), castle));
    
    // Battlefield
    map<string, Person*> bPeople;
    multimap<string, Stuff*> bStuff;
    multimap<string,Thing*> bThing;
    map<string, Place*> trav;
    
    Place* battlefield = new Place("Battlefield", "Alice is all suited up and ready to fight.", bStuff, bPeople, bThing, trav);
    
    places.insert(pair<string, Place*>(battlefield->getPlaceName(), battlefield));
    
    // Home
    map<string, Person*> hPeople;
    multimap<string, Stuff*> hStuff;
    multimap<string,Thing*> hThing;
    map<string, Place*> htrav;
    
    Place* home = new Place("Home", "Alice wakes up and remembers a wonderful dream...", hStuff, hPeople, hThing, trav);
    places.insert(pair<string, Place*>(home->getPlaceName(), home));
    
    // places to go from Tree
    places.find("Tree")->second->newPlaceToGo(places.find("Garden")->second);
    
    // places to go from Garden
    places.find("Garden")->second->newPlaceToGo(places.find("Woods")->second);
    places.find("Garden")->second->newPlaceToGo(places.find("Tree")->second);
    
    // places to go from Woods
    places.find("Woods")->second->newPlaceToGo(places.find("Garden")->second);
    places.find("Woods")->second->newPlaceToGo(places.find("TeaParty")->second);
    
    // places to go from TeaParty
    places.find("TeaParty")->second->newPlaceToGo(places.find("Woods")->second);
    places.find("TeaParty")->second->newPlaceToGo(places.find("CastleP1")->second);
    
    // places to go from Castle
    places.find("CastleP1")->second->newPlaceToGo(places.find("TeaParty")->second);
    places.find("CastleP1")->second->newPlaceToGo(places.find("Battlefield")->second);
    
    // places to go from Battlefield
    places.find("Battlefield")->second->newPlaceToGo(places.find("CastleP1")->second);
    places.find("Battlefield")->second->newPlaceToGo(places.find("Home")->second);
}
*/

void Game::makePeople()
{
    //Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
    //Helpers will be WhiteRabbit, MadHatter, CheshireCat...
    
    //(1)
    NPC* bandersnatch = PersonFactory::makePerson("Bandersnatch");
    //places.find("Garden")->second->personEnters(bandersnatch);
    people.insert(pair<string, NPC*>(bandersnatch->getName(), bandersnatch));
    
    // (2)
    NPC* jabberwocky = PersonFactory::makePerson("Jabberwocky");
    //places.find("Castle")->second->personEnters(jabberwocky);
    people.insert(pair<string, NPC*>(jabberwocky->getName(), jabberwocky));
    
    // (3)
    NPC* redQueen = PersonFactory::makePerson("RedQueen");
    //places.find("Castle")->second->personEnters(redQueen);
    people.insert(pair<string, NPC*>(redQueen->getName(), redQueen));
    
    // (4)
    NPC* whiteRabbit = PersonFactory::makePerson("WhiteRabbit");
    //places.find("Tree")->second->personEnters(whiteRabbit);
    people.insert(pair<string, NPC*>(whiteRabbit->getName(), whiteRabbit));
    
    // (5)
    NPC* madHatter = PersonFactory::makePerson("MadHatter");
    //places.find("TeaParty")->second->personEnters(madHatter);
    people.insert(pair<string, NPC*>(madHatter->getName(), madHatter));
    
    // (6)
    NPC* cheshireCat = PersonFactory::makePerson("CheshireCat");
    //places.find("Woods")->second->personEnters(cheshireCat);
    people.insert(pair<string, NPC*>(cheshireCat->getName(), cheshireCat));
    
    // (7)
    //Person* alice = PersonFactory::makePerson("Alice");
    //places.find("Tree")->second->personEnters(alice);
    
    alicePtr = Alice::makeAlice();
}

// make stuff for people and places

/* COMMENT OUT TO TEST
void Game::makeStuff()
{
    // **********************
    
    // Switched stuff over to make specific types of stuff
    // not sure of the genStuff function?
    
    // **********************
    
    // (1) Tree
    // Tree has nothing in list
    
    // (2) Garden
    HealthStuff* whiteRose = new HealthStuff("WhiteRose", "The Red Queen hates white roses", 3, 1);
    places.find("Garden")->second->genStuff(whiteRose);
    
    // (3) Woods
    OpenStuff* key = new OpenStuff("Key", "Key can be used to open the door, but Alice needs to be small to get through!", 1, 1);
    places.find("Woods")->second->genStuff(key);
    
    // (4) TeaParty
    
    //how does she get to normal size? hmmm...magic :). Could we just return her back to normal size after she gets the sword?
    
    //Do you want me to make these just iterators so cake makes her one size bigger and tea makes her one size smaller // that works!
    
    GrowStuff* cake = new GrowStuff("Cake", "The cake will make Alice big!", 3, 1);
    GrowStuff* tea = new GrowStuff("Tea", "Drinking the tea will make Alice small.", 1, 1);
    places.find("TeaParty")->second->genStuff(cake);
    places.find("TeaParty")->second->genStuff(tea);
    
    // (5) Castle
    HealthStuff* sword = new HealthStuff("Sword", "Sword can be used to fight the Jabberwocky", 4, 1);
    places.find("Castle")->second->genStuff(sword);
    
    // (6) Battlefield
    
    MOVED TO PERSON FACTORY TO INSERT jabberBlood INTO HIS mStuff BEFORE RETURNING HIM
    
    MoveStuff* jabberBlood = new MoveStuff("JabberBlood", "Drinking the Jabberwocky's purple blood will take Alice home", 1, 1);
    
   for(map<string, Place*>::iterator i = places.begin(); i!=places.end(); i++)
    {
        if(((((i->second)->Place::whoHere()).find("Jabberwocky")))!=((i->second)->Place::whoHere()).end())
            ((((i->second)->Place::whoHere()).find("Jabberwocky"))->second)->recieve(jabberBlood);
    }
 
    
    // (7) Home
    // Home has nothing in list
}
*/

// added to give us ability to find place in main

/* COMMENT OUT TO TEST
Place* Game::findHere() const
{
    Place* here=NULL;
    
    for(map<string, Place*>::const_iterator i = places.begin(); i!=places.end(); i++)
    {
        if((((i->second)->whoHere()).find("Alice")) != ((i->second)->whoHere()).end())
        {
            here = (i->second);
        }
    }
    return here;
}
 */

void Game::delegate(const std::string& input)
{
	//"Keywords: aboutme, go, pickup, drop, use, approach"
	string subput="start";
    
    //Place* here = findHere(); COMMENT OUT TO TEST
	
	if(input=="aboutme")
	{
		//here->whoHere().find("Alice")->second->render(cout);
        alicePtr->narrate(cout);
	}
    
    // *****************************************
    
    // Testing people, npc, alice, and stuff
    // get rid of when it gets real
    
    // *****************************************
    
    if(input == "others")
    {
        for(map<string, NPC*>::const_iterator i = people.begin(); i!=people.end(); i++)
        {
            i->second->getName();
            i->second->narrate(cout);
            i->second->render(cout);
        }
    }
    
    if(input == "get")
    {
        cout << "What would you like to get?" << endl;
        cin >> subput;
        for(map<string, NPC*>::const_iterator i = people.begin(); i!=people.end(); i++)
        {
            for(map<string, HealthStuff*>::const_iterator h = (i->second)->hStuff.begin(); h!=(i->second)->hStuff.end(); h++)
            {
                if(h->second->getName() == subput)
                {
                    alicePtr->recieve(h->second);
                }
            }
        }
        alicePtr->render(cout);
    }
    
    if(input == "use")
    {
        cout << "What would you like to use?" << endl;
        cin >> subput;
        
        string sub3;
        
        cout << "Who would you like to use it on?" << endl;
        cin >> sub3;
        
        for(map<string, HealthStuff*>::const_iterator i = alicePtr->hStuff.begin(); i!=alicePtr->hStuff.end(); i++)
        {
            if(i->second->getName() == subput)
            {
                alicePtr->use(i->second, people.find(sub3)->second);
            }
            people.find(sub3)->second->render(cout);
        }
        
    }
    // end of code for testing ********************************
	
    
    /* COMMENT OUT TO TEST
	if(input=="go")
	{
		cout << "Where would you like to go? " << endl;
     
        map<string, Place*>::const_iterator i=here->getNewPlaceToGo().begin();
        cout << "[choices: " << (i->second)->getPlaceName();
        i++;
        
        for(; i!=here->getNewPlaceToGo().end(); i++)
            cout << ", " << (i->second)->getPlaceName();
        
        cout << "]" << endl;
        
		cin >> subput;
		if(here->getNewPlaceToGo().find(subput)!= here->getNewPlaceToGo().end())
		{
			(here->whoHere().find("Alice")->second)->move(here->getNewPlaceToGo().find(subput)->second);
		}
		else
		{
			cout << "You cannot go there from here.";
		}
	}
	*/
    
    /* COMMENT OUT TO TEST
	if(input=="pickup")
	{
		cout << "What would you like to pick up? ";
		cin >> subput;
		if(here->whatsHere().find(subput)!=here->whatsHere().end())
		{
            here->pickedUp(here->whatsHere().find(subput)->second, here->whoHere().find("Alice")->second);
		}
		else
		{
			cout << "That item is not here.";
		}
	}
     */
	
    /* COMMENT OUT TO TEST
	if (input=="drop")
	{
		cout << "What would you like to drop? ";
		cin >> subput;
		if(here->whoHere().find("Alice")->second->getStuffList().find(subput) != here->whoHere().find("Alice")->second->getStuffList().end())
		{
            here->dropped(here->whoHere().find("Alice")->second->getStuffList().find(subput)->second, here->whoHere().find("Alice")->second);
		}
		else
		{
			cout << "You do not have that item to drop.";
		}
	}
     
	
	if(input=="use")
	{
		cout << "What would you like to use? ";
		cin >> subput;
		if(here->whoHere().find("Alice")->second->getStuffList().find(subput)!= here->whoHere().find("Alice")->second->getStuffList().end())
		{
			cout << "What/Who/Where would you like to use that (to use on alice: Alice)? ";
            
			string subput2;
			cin >> subput2;
			bool used=false;
            
			Stuff* item = here->whoHere().find("Alice")->second->getStuffList().find(subput)->second;
            
			if(subput2=="Alice")
			{
                here->whoHere().find("Alice")->second->use(item);
				used=true;
			}
			for(multimap<string, Thing*>::iterator i=here->getThingsHere().begin();i!=here->getThingsHere().end();i++)
			{
				if(i->second->getName()==subput2)
				{
					here->whoHere().find("Alice")->second->use(item, i->second);
					used=true;
					break;
				}
			}
			for(multimap<string, Person*>::iterator i=here->whoHere().begin();i!=here->whoHere().end();i++)
			{
				if(i->second->getName()==subput2)
				{
                    			here->whoHere().find("Alice")->second->use(item, i->second);
					used=true;
					break;
				}
			}
			if(!used)
				cout <<"Couldn't use item.";

			
		}
		
	}
    
	if(input=="approach")
	{
		cout << "What/Who would you like to approach?";
		string subput;
		cin>>subput;
		
        for(map<string, Thing*>::iterator i=here->openHere().begin();i!=here->openHere().end(); i++)
		{

			if(i->first==subput)
			{
				//NEED TO WRITE
				if(i->second->thingtype=="door")
				{
					Door* dr=here->getThingsHere().find(subput);
					cout<<"What would you like to do?\n Keywords: use, open, close\n";
					cin>>subput;
					if (subput=="use")
					{
						cout << "Use what item\n";
						cin>>subput;
						if (here->whoHere().find("Alice")->second->getStuffList().find(subput)!=here->whoHere().find("Alice")->second->getStuffList().end())
						{
							here->whoHere().find("Alice")->second->use(here->whoHere().find("Alice")->second->getStuffList().find(subput)->second,dr);
						
							//Austin is here in writing... sleep will write better
						}
					}
					if (subput=="open")
					{
						dr->openThing();
					}
					if (subput=="close")
					{
						dr->closeThing();
					}
				}
				if(i->second->thingtype=="chest")
				{
					Chest* chst=here->getThingsHere().find(subput);
					if(i->getStatus())
					{
						i->narrate(cout);
					}
					cout<<"What would you like to do?\n Keywords: use, open, close, take\n";
					cin>>subput;
					if (subput=="use")
					{
						cout << "Use what item\n";
						cin>>subput;
						if (here->whoHere().find("Alice")->second->getStuffList().find(subput)!=here->whoHere().find("Alice")->second->getStuffList().end())
						{
							here->whoHere().find("Alice")->second->use(here->whoHere().find("Alice")->second->getStuffList().find(subput)->second,chst);
						
							//Austin is here in writing... sleep will write better
						}
					}
					if (subput=="open")
					{
						chst->openThing();
					}
					if (subput=="close")
					{
						chst->closeThing();
					}
					if (subput=="take")
					{
						if(i->getStatus())
						{
							cout << "What would you like to take\n";
							cin>>subput;
							if(chst->whatsinside().find(subput)!=chst->whatsinside().end())
							{
								here->whoHere().find("Alice")->second->choose(chst,chst->whatsinside().find(subput)->second)
							}
							else
							{
								cout << "That is not in here";
							}
						}
						if(i->getStatus())
						{
							cout << "You must open the chest first";
						}
					}
				}
			}
		}
        
     
        
		for(map<string, NPC*>::iterator i=here->whoHere().begin();i!=here->whoHere().end(); i++)
		{
			if(i->first==subput)
			{
				NPC* pers=i->second;
				pers->narrate(cout);
				cout << "What would you like to do:\n Keywords:talk, askfollow, askleave, attack";
				cin >>subput;
				if (subput=="talk")
				{
                    pers->talk(cout
                               );
				}
				if (subput=="askfollow")
				{
					if(pers->isfriendly())
					{
						cout << "Sure\n";
						here->whoHere().find("Alice")->second->taggingAlong(pers);
					}
					else
					{
						cout << "No, I have you\n";
					}
				}
				if(subput=="askleave")
				{
					if(pers->isfriendly())
					{
						cout << "Sure\n";
						here->whoHere().find("Alice")->second->ditched
                        (pers);
					}
					else
					{
						cout << "Huh?\n";
					}
				}
				if (subput=="attack")
				{
					if(here->whoHere().find("Alice")->second->getStuffList().find("sword")!=here->whoHere().find("Alice")->second->getStuffList().end())
					{
						here->whoHere().find("Alice")->second->use(here->whoHere().find("Alice")->second->getStuffList().find("sword"),pers);
					}
					else
					{
						cout << "You flail your arms wildly about them. They applaud your dance.";
					}
				}
			}
		}
	}
     */
}


// needed to make static lists work
//map<string, Place*> Game::places; COMMENT OUT TO TEST
map<string, NPC*> Game::people;


