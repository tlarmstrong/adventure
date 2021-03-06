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
Place::Place(const std::string& nm, const std::string& dscpt): name(nm), description(dscpt) {}
 
Place::~Place()
{
	for (map<string, NPC*>::iterator i=peopleHere.begin(); i!=peopleHere.end(); i++)		//deletes all people in a place
	{
		delete i->second;
	}
	
	for (map<string, HealthStuff*>::iterator h=hHere.begin(); h!=hHere.end(); h++)	//deletes all the stuff in a place
	{
		delete h->second;
	}
    
    for (map<string, GrowStuff*>::iterator g=gHere.begin(); g!=gHere.end(); g++)	//deletes all the stuff in a place
    {
        delete g->second;
    }
    
    for (map<string, FriendStuff*>::iterator f=fHere.begin(); f!=fHere.end(); f++)	//deletes all the stuff in a place
    {
        delete f->second;
    }
    
    for (map<string, OpenStuff*>::iterator o=oHere.begin(); o!=oHere.end(); o++)	//deletes all the stuff in a place
    {
        delete o->second;
    }
    
    for (map<string, MoveStuff*>::iterator m=mHere.begin(); m!=mHere.end(); m++)	//deletes all the stuff in a place
    {
        delete m->second;
    }
	
    /* COMMENT OUT TO TEST
	for (map<string, Door*>::iterator d=dHere.begin(); d!=dHere.end(); d++) //deletes all the things in a place
	{
		delete d->second;
	}
    
    for (map<string, Chest*>::iterator c=cHere.begin(); c!=cHere.end(); c++) //deletes all the things in a place
    {
        delete c->second;
    }
	END COMMENT */
}

string Place::getPlaceName() const  // returns name of Place
{
    return name;
}

void Place::personEnters(NPC* enterer)  // somebody comes into the place
{
    peopleHere.insert(pair<string, NPC*>(enterer->getName(), enterer));
}

void Place::personLeaves(NPC* leaver)   // removes somebody from a place
{
    peopleHere.erase(peopleHere.find(leaver->getName()));
}

// someone dropped an item, so now it is laying around
/*
void Place::dropped(Stuff* drop, Person* who)
{
    who->getStuffList().erase(who->getStuffList().find(drop->getName()));
    stuffHere.insert(pair<string, Stuff*>(drop->getName(), drop));
}*/

template<class T>
void Place::dropped(HealthStuff* drop, T* who)
{
    who->hStuff.erase(who->hStuff.find(drop->getName()));
    hHere.insert(pair<string, HealthStuff*>(drop->getName(), drop));
}

template<class T>
void Place::dropped(GrowStuff* drop, T* who)
{
    who->gStuff.erase(who->gStuff.find(drop->getName()));
    gHere.insert(pair<string, GrowStuff*>(drop->getName(), drop));
}

template<class T>
void Place::dropped(FriendStuff* drop, T* who)
{
    who->fStuff.erase(who->fStuff.find(drop->getName()));
    fHere.insert(pair<string, FriendStuff*>(drop->getName(), drop));
}

template<class T>
void Place::dropped(OpenStuff* drop, T* who)
{
    who->oStuff.erase(who->oStuff.find(drop->getName()));
    oHere.insert(pair<string, OpenStuff*>(drop->getName(), drop));
}

template<class T>
void Place::dropped(MoveStuff* drop, T* who)
{
    who->mStuff.erase(who->mStuff.find(drop->getName()));
    mHere.insert(pair<string, MoveStuff*>(drop->getName(), drop));
}

//somebody picked up an item here
template<class T>
void Place::pickedUp(HealthStuff* pick, T* who)
{
    hHere.erase(hHere.find(pick->getName()));
    who->recieve(pick);
}

template<class T>
void Place::pickedUp(GrowStuff* pick, T* who)
{
    gHere.erase(gHere.find(pick->getName()));
    who->recieve(pick);
}

template<class T>
void Place::pickedUp(FriendStuff* pick, T* who)
{
    fHere.erase(fHere.find(pick->getName()));
    who->recieve(pick);
}

template<class T>
void Place::pickedUp(OpenStuff* pick, T* who)
{
    oHere.erase(oHere.find(pick->getName()));
    who->recieve(pick);
}

template<class T>
void Place::pickedUp(MoveStuff* pick, T* who)
{
    mHere.erase(mHere.find(pick->getName()));
    who->recieve(pick);
}

/*
void Place::genStuff(GrowStuff* gen)
{
	gHere.insert(pair<string, GrowStuff*>(gen->getName(), gen));
}

void Place::genStuff(HealthStuff* gen)
{
    hHere.insert(pair<string, HealthStuff*>(gen->getName(), gen));
    cout << gen->getName() << " inserted" << endl;
}

void Place::genStuff(FriendStuff* gen)
{
    fHere.insert(pair<string, FriendStuff*>(gen->getName(), gen));
}

void Place::genStuff(OpenStuff* gen)
{
    oHere.insert(pair<string, OpenStuff*>(gen->getName(), gen));
}

void Place::genStuff(MoveStuff* gen)
{
    mHere.insert(pair<string, MoveStuff*>(gen->getName(), gen));
}
 */

/* COMMENT OUT TO TEST
void Place::genThing(Chest* gen)
{
    cHere.insert(pair<string, Chest*>(gen->getName(), gen));
}

void Place::genThing(Door* gen)
{
    dHere.insert(pair<string, Door*>(gen->getName(), gen));
}
END COMMENT */

/*
void Place::newPlaceToGo(Place* goTo)
{
    placeTo.insert(pair<string, Place*>(goTo->getPlaceName(),goTo));
}
*/

void Place::blockPlaceToGo(Place* block)
{
    placeTo.erase(placeTo.find(block->getPlaceName()));
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
        
		std::map<string, NPC*>::const_iterator i;
		i=peopleHere.begin();
		out << i->second->getName();
		i++;
		for(;i!=peopleHere.end();i++)
		{
			out << ", " <<i->second->getName();
		}
        out << endl;
	}
	
    /* COMMENT OUT TO TEST
	if (dHere.empty() && cHere.empty())
	{
		out << "";
    }
    
    else
    {
        if(!dHere.empty())
        {
            for(map<string, Door*>::const_iterator i = dHere.begin(); i!=dHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        
        if(!dHere.empty())
        {
            for(map<string, Door*>::const_iterator i = dHere.begin(); i!=dHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        else
            out << "";
         
	}
    END COMMENT */
    
    if(getPlaceName() == "Home")
    {
        out << "";
    }
    
    else if(hHere.empty() && gHere.empty() && fHere.empty() && oHere.empty() && mHere.empty())
    {
        out << "There is nothing here to get" << endl;
    }
    
    else
    {
        out << "Things here to get: " << endl;
        
        if(!hHere.empty())
        {
            for(map<string, HealthStuff*>::const_iterator i = hHere.begin(); i!=hHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!gHere.empty())
        {
            for(map<string, GrowStuff*>::const_iterator i = gHere.begin(); i!=gHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!fHere.empty())
        {
            for(map<string, FriendStuff*>::const_iterator i = fHere.begin(); i!=fHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!oHere.empty())
        {
            for(map<string, OpenStuff*>::const_iterator i = oHere.begin(); i!=oHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
        
        if(!mHere.empty())
        {
            for(map<string, MoveStuff*>::const_iterator i = mHere.begin(); i!=mHere.end(); i++)
            {
                out << (i->second)->getName() << endl;
            }
        }
        
        else
            out << "";
    }
    
    out << endl;
    
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

bool Person::isDead()
{
	if (health > 0)
	{
        return false;
	}
    this->dies();
    return true;
}

// get Place where Person is
Place* Person::whereAreYou() const
{
    Place* here=NULL;
    
    for(map<string, Place*>::const_iterator i = Game::places.begin(); i!= Game::places.end(); i++)
    {
        if((((i->second)->peopleHere).find(getName())) != ((i->second)->peopleHere).end())
        {
            here = (i->second);
        }
    }
    return here;
}

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

template<class T>
void Person::drop(T* item, Place* where)
{
    //fStuff.erase(fStuff.find(item->getName()));
    where->dropped(item, this);
}

//person takes damage
void Person::hurt(const int& damage)
{
    health -= damage;
    cout << "Oooooh, health level down " << damage << endl;
    cout << "Total health: " << health << endl;
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

Place* Alice::whereAreYou() const
{
    Place* here=NULL;
    
    for(map<string, Place*>::const_iterator i = Game::places.begin(); i!= Game::places.end(); i++)
    {
        if(i->second->alicePtr != NULL)
        {
            here = (i->second);
        }
    }
    return here;
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

//now alice's friends can come with her
void Alice::move(Place* to)
{
	Place* from = whereAreYou();
    
	from->alicePtr = NULL;        // remove person from current location
    to->alicePtr = this;          // move a person to another place

    	for(map<string, NPC*>::const_iterator i=helperList.begin(); i!=helperList.end(); i++)
    	{
    		(i->second)->move(to);
    	}
}

// **********************

// used templates or made polymorphic

// moved these to just be in Alice, but did we decide to have some of these available to NPCs too (ex: drop())? Move these back to Person and make virtual so NPCs can use, too?

// **********************

/* COMMENT OUT TO TEST
template<class T>
void choose(Chest* chst, T* item)
{
	chst->takeStuff(item);
	recieve(item);
}
 END COMMENT */

template<class T>
void Alice::pickUp(T* item)
{
    recieve(item);
}

/* OLD
//Alice drops an item
void Alice::drop(Stuff* item)
{
    stuffList.erase(stuffList.find(item->getName()));
}
*/

/* MOVED TO PERSON
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
 */

// delete stuff after used?
//Alice uses an item on herself
template<class T>
void Alice::use(T* item)
{
    item->useItem(this);
}

//Alice uses an item in a place
template<class T>
void Alice::use(T* item, Place* where)
{
    item->useItem(this, where);
}

//Alice uses an item on a thing
/*
template<class T>
void Alice::use(T* item, Door* what)
{
    item->useItem(what);
}

template<class T>
void Alice::use(T* item, Chest* what)
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

void Alice::dies()
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
    
    this->whereAreYou()->alicePtr = NULL;
    delete this;
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
    
    out << "Alice is at the " << whereAreYou()->getPlaceName() << endl;
    out << "She is " << sz << endl;
    out << "Her health level is " << getHealth() << endl;
    
    out << "She has these items: " << endl;
    
// **********************************
    
// adjusted to print stuff out of lists one line at a time

// **********************************

    if(!hStuff.empty())
    {
        out << "Weapons: " << endl;
        for(map<string, HealthStuff*>::const_iterator i = hStuff.begin(); i!=hStuff.end(); i++)
        {
            out << "+ " << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "No weapons" << endl;
    
    if(!gStuff.empty())
    {
        out << "Stuff to change her size: " << endl;
        for(map<string, GrowStuff*>::const_iterator i = gStuff.begin(); i!=gStuff.end(); i++)
        {
            out << "+ " << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "Nothing to make her small or big" << endl;
    
    if(!fStuff.empty())
    {
        out << "Things to make friends: " << endl;
        for(map<string, FriendStuff*>::const_iterator i = fStuff.begin(); i!=fStuff.end(); i++)
        {
            out << "+ " << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "Nothing to help make any friends" << endl;
    
    if(!oStuff.empty())
    {
        out << "Open stuff with " << endl;
        for(map<string, OpenStuff*>::const_iterator i = oStuff.begin(); i!=oStuff.end(); i++)
        {
            out << "+ " << (i->second)->getName() << endl;
        }
    }
    
    else
        out << "No keys" << endl;
    
    if(!mStuff.empty())
    {
        out << "Use ";
        for(map<string, MoveStuff*>::const_iterator i = mStuff.begin(); i!=mStuff.end(); i++)
        {
            out << "+ " << (i->second)->getName();
        }
        out << " to go home" << endl;
    }
    
    else
        out << "Nothing that will take her home" << endl;
    
    if(!helperList.empty())
    {
        out << "Her friends are: ";
        
        map<string, NPC*>::const_iterator i=helperList.begin();
        out << (i->second)->getName();
        i++;
        
        for(; i!=helperList.end(); i++)
            out << ", " << (i->second)->getName();
        out << endl;
    }
    
    else
        out << "no friends, yet" << endl;;
    
    if(!badguyList.empty())
    {
        out << "Her enemies are: ";

        map<string, NPC*>::const_iterator i=badguyList.begin();
        out << (i->second)->getName();
        i++;
        
        for(; i!=badguyList.end(); i++)
            out << ", " << (i->second)->getName();
        out << endl;
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

void NPC::move(Place* to) /*const*/
{
    Place* from = whereAreYou();
    
    // remove person from current location
    from->personLeaves(this);
    
    // move a person to another place
    to->personEnters(this);
}

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

// NPC uses item on another NPC or Alice
template<class T, class U>
void NPC::use(T* item, U* who)
{
    item->useItem(who);
}

/*template<class T>
void NPC::use(T* item, Alice* who)
{
    item->useItem(who);
}*/

void NPC::dies()
{
    multimap<string, HealthStuff*>::iterator h;
    h=hStuff.begin();
    for(;!hStuff.empty();h++)
    {
        this->drop(h->second, this->whereAreYou());
    }
    
    multimap<string, GrowStuff*>::iterator g;
    g=gStuff.begin();
    for(;!gStuff.empty();g++)
    {
        this->drop(g->second, this->whereAreYou());
    }
    
    multimap<string, FriendStuff*>::iterator f;
    f=fStuff.begin();
    for(;!fStuff.empty();f++)
    {
        this->drop(f->second, this->whereAreYou());
    }
    
    multimap<string, OpenStuff*>::iterator o;
    o=oStuff.begin();
    for(;!oStuff.empty();o++)
    {
        this->drop(o->second, this->whereAreYou());
    }
    
    multimap<string, MoveStuff*>::iterator m;
    m=mStuff.begin();
    for(;!mStuff.empty();m++)
    {
        this->drop(m->second, this->whereAreYou());
    }
    
    this->whereAreYou()->personLeaves(this);
    delete this;
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
        string nm = "CheshireCat";
        string dscrpt = "I like to smile";
        string sayThings = "I'm a mysterious friend";
        int hLevel = 10;
        bool frndly = true;
        bool attk = false;
        
        NPC* cheshireCat = new NPC(nm, dscrpt, sayThings, hLevel, frndly, attk);
        
        // has nothing in lists
        
        return cheshireCat;
    }
    
    /* PF needs to return NPC* not Person* -- using Alice::makeAlice() to instantiate her instead (see makePeople() in Game)
     
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

//void GrowStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}

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

template<class T>
void HealthStuff::useItem(T* who)
{
	who->hurt(result);
	status = 0;
}

//void HealthStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
/*
void HealthStuff::useItem(NPC* who)
{
	who->hurt(result);
	status = 0;
}*/

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

//void FriendStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}

//void FriendStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
//void FriendStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
//void FriendStuff::useItem(Thing* what) {cout << getName() << "cannot be used on" << what->getName();}
//void FriendStuff::useItem(/*const*/ Person* who, Place* where) {cout << getName() << "cannot be used on this way";}

// OpenStuff


OpenStuff::OpenStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

OpenStuff::~OpenStuff() {}

/* COMMENT OUT TO TEST
template<class T>
void OpenStuff::useItem(T* what)
{
    what->openThing();
    status = 0;
}
 END OF COMMENT */

/*
void OpenStuff::useItem(Alice* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(NPC* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(Person* who) {cout << getName() << "cannot be used on" << who->getName();}
void OpenStuff::useItem(Place* where) {cout << getName() << "cannot be used on" << where->getPlaceName();}
void OpenStuff::useItem(Person* who, Place* where) {cout << getName() << "cannot be used like this";}

 */


MoveStuff::MoveStuff(const string name, const string description, const int result, const bool status) : Stuff(name, description, result, status) {}

MoveStuff::~MoveStuff() {}

// move Alice home
void MoveStuff::useItem(Alice* who, Place* where)
{
    if(where->getPlaceName()=="Home")
    {
    	who->move(where);
    }
    status=0;
}

/*
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
 END COMMENT */

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
END COMMENT */

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

void Game::makePlaces()
{
    // Tree
    // *******************************
    
    // took out the dummy lists and use insert instead (see Person Factory)
    
    // *******************************
    
    Place* tree = new Place("Tree", "Alice woke up under a big oak tree. She saw a whiterabbit run by.");
    places.insert(pair<string, Place*>(tree->getPlaceName(), tree));
    
    // Garden
    Place* garden = new Place("Garden", "Alice follows the WhiteRabbit to a beautiful garden full of white roses.");
    places.insert(pair<string, Place*>(garden->getPlaceName(), garden));
    
    // Woods
    Place* woods = new Place("Woods", "Alice is in the Woods. She sees a cat in a tree.");
    places.insert(pair<string, Place*>(woods->getPlaceName(), woods));
    
    // TeaParty
    Place* teaParty = new Place("TeaParty", "Alice goes to a Tea Party.");
    places.insert(pair<string, Place*>(teaParty->getPlaceName(), teaParty));
    
    //Castle
    Place* castle = new Place("Castle", "Alice is taken to the Red Queen's Castle.");
    places.insert(pair<string, Place*>(castle->getPlaceName(), castle));
    
    /* COMMENT OUT TO TEST
    //CastleP2
    Place* castle2 = new Place("CastleP2", "Escape the Castle.");
    map<string, Place*> doorway;
    doorway.insert(pair<string, Place*>(castle2->getPlaceName(),castle2));
    
    doorway.insert(pair<string, Place*>(castle->getPlaceName(),castle));
    
    Door* cd=new Door(0, "DoorInCastle", doorway);
    castle->genThing(cd);
    castle2->genThing(cd);
    
    multimap<std::string, HealthStuff*> sinchst;
    HealthStuff* aswrd=new HealthStuff("SwordToKillJabberwocky", "You can use this to kill the Jabberwocky", 5, 1);
    
    sinchst.insert(pair<string, HealthStuff*>(aswrd->getName(),aswrd));
    
    Chest* dchst=new Chest(0, "ChestInCastle", sinchst);
    castle->genThing(dchst);
    */
    
    places.insert(pair<string, Place*>(castle->getPlaceName(), castle));
    
    // Battlefield
    Place* battlefield = new Place("Battlefield", "Alice is all suited up and ready to fight.");
    
    places.insert(pair<string, Place*>(battlefield->getPlaceName(), battlefield));
    
    // Home
    Place* home = new Place("Home", "Alice wakes up and remembers a wonderful dream...");
    
    places.insert(pair<string, Place*>(home->getPlaceName(), home));
    
    // places to go from Tree
    places.find("Tree")->second->placeTo.insert(pair<string, Place*>(places.find("Garden")->second->getPlaceName(), places.find("Garden")->second));
    
    // places to go from Garden
    places.find("Garden")->second->placeTo.insert(pair<string, Place*>(places.find("Tree")->second->getPlaceName(), places.find("Tree")->second));
    places.find("Garden")->second->placeTo.insert(pair<string, Place*>(places.find("Woods")->second->getPlaceName(), places.find("Woods")->second));
    
    // places to go from Woods
    places.find("Woods")->second->placeTo.insert(pair<string, Place*>(places.find("Garden")->second->getPlaceName(), places.find("Garden")->second));
    places.find("Woods")->second->placeTo.insert(pair<string, Place*>(places.find("TeaParty")->second->getPlaceName(), places.find("TeaParty")->second));
    
    // places to go from TeaParty
    places.find("TeaParty")->second->placeTo.insert(pair<string, Place*>(places.find("Woods")->second->getPlaceName(), places.find("Woods")->second));
    places.find("TeaParty")->second->placeTo.insert(pair<string, Place*>(places.find("Castle")->second->getPlaceName(), places.find("Castle")->second));
    
    // places to go from Castle
    places.find("Castle")->second->placeTo.insert(pair<string, Place*>(places.find("TeaParty")->second->getPlaceName(), places.find("TeaParty")->second));
    places.find("Castle")->second->placeTo.insert(pair<string, Place*>(places.find("Battlefield")->second->getPlaceName(), places.find("Battlefield")->second));
    
    // places to go from Battlefield
    places.find("Battlefield")->second->placeTo.insert(pair<string, Place*>(places.find("Castle")->second->getPlaceName(), places.find("Castle")->second));
    places.find("Battlefield")->second->placeTo.insert(pair<string, Place*>(places.find("Home")->second->getPlaceName(), places.find("Home")->second));
}

void Game::makePeople()
{
    //Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
    //Helpers will be WhiteRabbit, MadHatter, CheshireCat...
    
    //(1)
    NPC* bandersnatch = PersonFactory::makePerson("Bandersnatch");
    places.find("Garden")->second->peopleHere.insert(pair<string, NPC*>(bandersnatch->getName(), bandersnatch));
    //people.insert(pair<string, NPC*>(bandersnatch->getName(), bandersnatch));
    
    // (2)
    NPC* jabberwocky = PersonFactory::makePerson("Jabberwocky");
    places.find("TeaParty")->second->peopleHere.insert(pair<string, NPC*>(jabberwocky->getName(), jabberwocky));
    //people.insert(pair<string, NPC*>(jabberwocky->getName(), jabberwocky));
    
    // (3)
    NPC* redQueen = PersonFactory::makePerson("RedQueen");
    places.find("Castle")->second->peopleHere.insert(pair<string, NPC*>(redQueen->getName(), redQueen));
    //people.insert(pair<string, NPC*>(redQueen->getName(), redQueen));
    
    // (4)
    NPC* whiteRabbit = PersonFactory::makePerson("WhiteRabbit");
    places.find("Garden")->second->peopleHere.insert(pair<string, NPC*>(whiteRabbit->getName(), whiteRabbit));
    //people.insert(pair<string, NPC*>(whiteRabbit->getName(), whiteRabbit));
    
    // (5)
    NPC* madHatter = PersonFactory::makePerson("MadHatter");
    places.find("TeaParty")->second->peopleHere.insert(pair<string, NPC*>(madHatter->getName(), madHatter));
    //people.insert(pair<string, NPC*>(madHatter->getName(), madHatter));
    
    // (6)
    NPC* cheshireCat = PersonFactory::makePerson("CheshireCat");
    places.find("Woods")->second->peopleHere.insert(pair<string, NPC*>(cheshireCat->getName(), cheshireCat));
    //people.insert(pair<string, NPC*>(cheshireCat->getName(), cheshireCat));
    
    // (7)
    //Person* alice = PersonFactory::makePerson("Alice");
    //places.find("Tree")->second->personEnters(alice);
    
    places.find("Tree")->second->alicePtr = Alice::makeAlice();
}

// make stuff for people and places
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
    places.find("Garden")->second->hHere.insert(pair<string, HealthStuff*>(whiteRose->getName(), whiteRose));
    
    // (3) Woods
    OpenStuff* key = new OpenStuff("Key", "Key can be used to open the door, but Alice needs to be small to get through!", 1, 1);
    places.find("Woods")->second->oHere.insert(pair<string, OpenStuff*>(key->getName(), key));
    
    // (4) TeaParty
    
    //how does she get to normal size? hmmm...magic :). Could we just return her back to normal size after she gets the sword?
    
    //Do you want me to make these just iterators so cake makes her one size bigger and tea makes her one size smaller // that works!
    
    GrowStuff* cake = new GrowStuff("Cake", "The cake will make Alice big!", 3, 1);
    GrowStuff* tea = new GrowStuff("Tea", "Drinking the tea will make Alice small.", 1, 1);
    places.find("TeaParty")->second->gHere.insert(pair<string, GrowStuff*>(cake->getName(), cake));
    places.find("TeaParty")->second->gHere.insert(pair<string, GrowStuff*>(tea->getName(), tea));
    
    // (5) Castle
    HealthStuff* sword = new HealthStuff("Sword", "Sword can be used to fight the Jabberwocky", 4, 1);
    places.find("Castle")->second->hHere.insert(pair<string, HealthStuff*>(sword->getName(), sword));
    
    // (6) Battlefield
    
    /*
     MOVED TO PERSON FACTORY TO INSERT jabberBlood INTO HIS mStuff BEFORE RETURNING HIM
    
    MoveStuff* jabberBlood = new MoveStuff("JabberBlood", "Drinking the Jabberwocky's purple blood will take Alice home", 1, 1);
    
   for(map<string, Place*>::iterator i = places.begin(); i!=places.end(); i++)
    {
        if(((((i->second)->Place::whoHere()).find("Jabberwocky")))!=((i->second)->Place::whoHere()).end())
            ((((i->second)->Place::whoHere()).find("Jabberwocky"))->second)->recieve(jabberBlood);
    }
     */
    
    // (7) Home
    // Home has nothing in list
}

// added to give us ability to find place in main

Place* Game::findHere() const
{
    Place* here=NULL;
    
    for(map<string, Place*>::const_iterator i = places.begin(); i!=places.end(); i++)
    {
        if(i->second->alicePtr != NULL)
        {
            here = (i->second);
        }
    }
    return here;
}

void Game::delegate(const std::string& input)
{
	//"Keywords: aboutme, go, pickup, drop, use, approach"
	string subput="start";
    
    Place* here = findHere();
	
	if(input=="aboutme")
	{
        here->alicePtr->render(cout);
	}
    
    // *****************************************
    
    // Testing people, npc, alice, and stuff
    // get rid of when it gets real
    
    // *****************************************
    
    if(input == "others")
    {
        for(map<string, NPC*>::const_iterator i = here->peopleHere.begin(); i!=here->peopleHere.end(); i++)
        {
            i->second->getName();
            i->second->narrate(cout);
            i->second->render(cout);
        }
    }
    
    /*
    
    if(input == "attack")
    {
        cout << "What would you like to use?" << endl;
        cin >> subput;
        
        string sub3;
        
        cout << "Who would you like to use it on?" << endl;
        cin >> sub3;
        
        for(map<string, HealthStuff*>::const_iterator i = here->alicePtr->hStuff.begin(); i!=here->alicePtr->hStuff.end(); i++)
        {
            if(i->second->getName() == subput)
            {
                here->alicePtr->use(i->second, here->peopleHere.find(sub3)->second);
            }
            here->peopleHere.find(sub3)->second->render(cout);
        }
    }*/
    
	if(input=="go")
	{
		cout << "Where would you like to go? " << endl;
     
        map<string, Place*>::const_iterator i=here->placeTo.begin();
        cout << "[choices: " << (i->second)->getPlaceName();
        i++;
        
        for(; i!=here->placeTo.end(); i++)
            cout << ", " << (i->second)->getPlaceName();
        
        cout << "]" << endl;
        
		cin >> subput;
		if(here->placeTo.find(subput)!= here->placeTo.end())
		{
			(here->alicePtr->move(here->placeTo.find(subput)->second));
            
            findHere()->narrate(cout);
            
            for(map<string, NPC*>::iterator j = findHere()->peopleHere.begin(); j!=findHere()->peopleHere.end(); j++)
            {
                if((j->second)->getName() == "Bandersnatch" && (j->second)->isfriendly() == false)
                {
                    cout << "Bandersnatch attack!" << endl;
                    
                    (j->second)->use((j->second->hStuff.find("Knife")->second), findHere()->alicePtr);
                    
                    j->second->render(cout);
                    
                    if((j->second)->getName() == "Bandersnatch" && !(j->second)->fStuff.empty())
                    {
                        for(map<string, FriendStuff*>::iterator k = j->second->fStuff.begin(); k!=j->second->fStuff.end(); k++)
                        {
                            if(k->second->getName() == "BandersnatchEye")
                            {
                                (j->second)->drop(k->second, findHere());
                                cout << "Oops! He poked his own eye out...it's now laying on the ground. Get it!" << endl << endl;
                                break;
                            }
                        }
                    }
                }
                
                if((j->second)->getName() == "Jabberwocky")
                {
                    cout << "Jabberwocky attack!" << endl;
                    
                    (j->second)->use((j->second->hStuff.find("Sword")->second), findHere()->alicePtr);
                    
                    j->second->render(cout);
                    findHere()->alicePtr->badguyList.insert(pair<string, NPC*>(j->second->getName(), j->second));
                    break;
                }
                
                if((j->second)->getName() == "RedQueen")
                {
                    cout << "Red Queen attack!" << endl;
                    cout << "Off with your head!" << endl;
                    
                    (j->second)->use((j->second->hStuff.find("Potion")->second), findHere()->alicePtr);
                    
                    j->second->render(cout);
                    findHere()->alicePtr->badguyList.insert(pair<string, NPC*>(j->second->getName(), j->second));
                    break;
                }
            }
		}
		else
		{
			cout << "You cannot go there from here.";
		}
	}
    
	if(input=="pickup")
	{
		cout << "What would you like to pick up? ";
		cin >> subput;
		if(here->hHere.find(subput)!=here->hHere.end())
		{
            here->pickedUp(here->hHere.find(subput)->second, here->alicePtr);
            cout << subput << " added to list." << endl;
		}

        else if(here->gHere.find(subput)!=here->gHere.end())
        {
            here->pickedUp(here->gHere.find(subput)->second, here->alicePtr);
            cout << subput << " added to list." << endl;
        }

        else if(here->fHere.find(subput)!=here->fHere.end())
        {
            here->pickedUp(here->fHere.find(subput)->second, here->alicePtr);
            cout << subput << " added to list." << endl;
        }

        else if(here->oHere.find(subput)!=here->oHere.end())
        {
            here->pickedUp(here->oHere.find(subput)->second, here->alicePtr);
            cout << subput << " added to list." << endl;
        }

        else if(here->mHere.find(subput)!=here->mHere.end())
        {
            here->pickedUp(here->mHere.find(subput)->second, here->alicePtr);
            cout << subput << " added to list." << endl;
        }
        else
            cout << subput << " is not here." << endl;
	}

	if (input=="drop")
	{
		cout << "What would you like to drop? ";
		cin >> subput;
		if(here->alicePtr->hStuff.find(subput) != here->alicePtr->hStuff.end())
		{
            here->dropped(here->alicePtr->hStuff.find(subput)->second, here->alicePtr);
		}

        else if(here->alicePtr->gStuff.find(subput) != here->alicePtr->gStuff.end())
        {
            here->dropped(here->alicePtr->gStuff.find(subput)->second, here->alicePtr);
        }

        else if(here->alicePtr->fStuff.find(subput) != here->alicePtr->fStuff.end())
        {
            here->dropped(here->alicePtr->fStuff.find(subput)->second, here->alicePtr);
        }

        else if(here->alicePtr->oStuff.find(subput) != here->alicePtr->oStuff.end())
        {
            here->dropped(here->alicePtr->oStuff.find(subput)->second, here->alicePtr);
        }

        else if(here->alicePtr->mStuff.find(subput) != here->alicePtr->mStuff.end())
        {
            here->dropped(here->alicePtr->mStuff.find(subput)->second, here->alicePtr);
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
		if(here->alicePtr->hStuff.find(subput)!= here->alicePtr->hStuff.end())
		{
			cout << "Who would you like to use that on? ";
            
			string subput2;
			cin >> subput2;
			bool used=false;
            
			HealthStuff* hItem = here->alicePtr->hStuff.find(subput)->second;

			for(multimap<string, NPC*>::iterator i=here->peopleHere.begin();i!=here->peopleHere.end();i++)
			{
				if(i->second->getName()==subput2)
				{
                    here->alicePtr->use(hItem, i->second);
					used=true;
					break;
				}
			}
			if(!used)
				cout <<"Couldn't use item.";
		}
        
        else if(here->alicePtr->gStuff.find(subput)!= here->alicePtr->gStuff.end())
        {
            bool used=false;
            
            GrowStuff* gItem = here->alicePtr->gStuff.find(subput)->second;
            
            here->alicePtr->use(gItem);
            used=true;

            if(!used)
                cout <<"Couldn't use item.";
        }
        
        else if(here->alicePtr->fStuff.find(subput)!= here->alicePtr->fStuff.end())
        {
            cout << "Who would you like to use that on? ";
            
            string subput2;
            cin >> subput2;
            bool used=false;
            
            FriendStuff* fItem = here->alicePtr->fStuff.find(subput)->second;
            
            for(multimap<string, NPC*>::iterator i=here->peopleHere.begin();i!=here->peopleHere.end();i++)
            {
                if(i->second->getName()==subput2 && i->second->getName()=="Bandersnatch")
                {
                    here->alicePtr->use(fItem, i->second);
                    i->second->render(cout);
                    used=true;
                    break;
                }
            }
            if(!used)
                cout <<"Couldn't use item.";
        }
        /*
        else if(here->alicePtr->oStuff.find(subput)!= here->alicePtr->oStuff.end())
        {
            cout << "What would you like to use that on? ";
            
            string subput2;
            cin >> subput2;
            bool used=false;
            
            OpenStuff* oItem = here->alicePtr->oStuff.find(subput)->second;
            
             for(multimap<string, Door*>::iterator i=here->dHere.begin();i!=here->dHere.end();i++)
             {
                 if(i->second->getName()==subput2)
                 {
                     here->alicePtr->use(oItem, i->second);
                     used=true;
                     break;
                 }
             }
            if(!used)
                cout <<"Couldn't use item.";
        }
        */
        
        else if(here->alicePtr->mStuff.find(subput)!= here->alicePtr->mStuff.end())
        {
            cout << "Where would you like to go";
            
            string subput2;
            cin >> subput2;
            bool used=false;
            
            MoveStuff* mItem = here->alicePtr->mStuff.find(subput)->second;
            
            if(subput2=="Home")
            {
                here->alicePtr->use(mItem, places.find("Home")->second);
                used=true;
            }
            if(!used)
                cout <<"Couldn't use item.";
        }
        else
            cout <<"Couldn't use " << subput << endl;
	}
    
	if(input=="approach")
	{
		cout << "What/Who would you like to approach?";
		string subput;
		cin>>subput;
		
        /* COMMENT OUT TO TEST
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
        END COMMENT OUT*/
    
		for(map<string, NPC*>::iterator i=here->peopleHere.begin();i!=here->peopleHere.end(); i++)
		{
			if(i->first==subput)
			{
				NPC* pers=i->second;
				pers->narrate(cout);
				cout << "What would you like to do:\n Keywords: talk, askfollow, askleave, attack";
				cin >>subput;
				if (subput=="talk")
				{
                    pers->talk(cout);
				}
				if (subput=="askfollow")
				{
					if(pers->isfriendly())
					{
						cout << "Sure\n";
						here->alicePtr->taggingAlong(pers);
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
						here->alicePtr->ditched(pers);
					}
					else
					{
						cout << "Huh?\n";
					}
				}
				if (subput=="attack")
				{
					if(here->alicePtr->hStuff.find("Sword")!=here->alicePtr->hStuff.end())
					{
						here->alicePtr->use(here->alicePtr->hStuff.find("Sword")->second, pers);
					}
					else
					{
						cout << "You flail your arms wildly about them. They applaud your dance.";
					}
				}
			}
		}
	}
}


// needed to make static lists work
map<string, Place*> Game::places;
//map<string, NPC*> Game::people;


