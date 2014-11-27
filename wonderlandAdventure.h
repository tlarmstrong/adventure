// wonderlandAdventure.h
#include <map>
#include <iostream>

// declare Stuff, NPC, Place, Thing, Person
//class Stuff;
class FriendStuff;
class HealthStuff;
class GrowStuff;
class MoveStuff;
class OpenStuff;
class Place;
class Person;
class PersonFactory;
class NPC;
class Alice;
//class Thing;
class Chest;
class Door;
class Game;

/*
 ----------------------------------
 Place Class: Base
 ----------------------------------
 
 generic class will instantiate individual Place dynamically (on demand)
 Place will be Tree, Garden, Woods, TeaParty, Castle, Battlefield, Home
 
 */

class Place {
    
protected:
    
    // unique description of Place
    std::string description;
    
    // name of Place
    std::string name;
    
public:
    
    // Place lists are now public
    std::multimap<std::string, HealthStuff*> hHere;
    std::multimap<std::string, GrowStuff*> gHere;
    std::multimap<std::string, FriendStuff*> fHere;
    std::multimap<std::string, OpenStuff*> oHere;
    std::multimap<std::string, MoveStuff*> mHere;
    
    std::multimap<std::string, Chest*> cHere;
    std::multimap<std::string, Door*> dHere;
    
    std::map<std::string, Place*>& placeTo;
    std::map<std::string, NPC*>& peopleHere;
    
    Alice* alicePtr;
    
    Place(const std::string& nm, const std::string& dscpt);
    //Place();                                    // constructor
    ~Place();                                   // destructor
    
    std::string getPlaceName() const;           // returns name of Place
    
    void personEnters(NPC* enterer);   //somebody comes into the place
    void personLeaves(NPC* leaver);    //removes somebody from a place
    
    //someone dropped an item here, so it is now laying around
    template<class T>
    void dropped(HealthStuff* drop, T* who);
    
    template<class T>
    void dropped(GrowStuff* drop, T* who);
    
    template<class T>
    void dropped(FriendStuff* drop, T* who);
    
    template<class T>
    void dropped(OpenStuff* drop, T* who);
    
    template<class T>
    void dropped(MoveStuff* drop, T* who);
    
    //somebody picked up an item here
    template<class T>
    void pickedUp(HealthStuff* drop, T* who);
    
    template<class T>
    void pickedUp(GrowStuff* drop, T* who);
    
    template<class T>
    void pickedUp(FriendStuff* drop, T* who);
    
    template<class T>
    void pickedUp(OpenStuff* drop, T* who);
    
    template<class T>
    void pickedUp(MoveStuff* drop, T* who);
    
    //to generate an item in the game
    void genStuff(HealthStuff* gen);
    void genStuff(GrowStuff* gen);
    void genStuff(FriendStuff* gen);
    void genStuff(OpenStuff* gen);
    void genStuff(MoveStuff* gen);
    
    //generate a thing
    void genThing(Chest* gen);
    void genThing(Door* gen);
    
    void newPlaceToGo(Place* goTo);
    void blockPlaceToGo(Place* block);
    
    //std::map<std::string, Place*>& getNewPlaceToGo();
    
    // output description of Place
    std::ostream& narrate(std::ostream& out) const;
    
    //output current information
    std::ostream& render(std::ostream& out) const;
};


/*
 ------------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 ------------------------------------------------------------
 */

class Person {
    
    friend class PersonFactory;
    
private:
    // prevent value semantics
    Person(const Person& other);            //copy constructor
    void operator = (const Person& other);  //assignment operator
    
protected:
    
    int health;    //health level of the person 
    std::string name;
    bool isAttack;
    Person();
    bool dead;
    
public:
    
    // stuff lists for NPCs and Alice
    std::multimap<std::string, HealthStuff*> hStuff;
    std::multimap<std::string, GrowStuff*> gStuff;
    std::multimap<std::string, FriendStuff*> fStuff;
    std::multimap<std::string, OpenStuff*> oStuff;
    std::multimap<std::string, MoveStuff*> mStuff;
    
    // constructor -- all derived use (initialization list)
    Person(const int& hLevel, const std::string& nm, bool attk);
    virtual ~Person();                       // destructor
    
    // Person can move from place to place
    virtual void move(Place* to) /*const*/;
    
    // get (and display) name of place
    Place* whereAreYou() const;
    
    // gives an item to someone else
    template<class T>
    void give(GrowStuff* item, T* other);
    
    template<class T>
    void give(FriendStuff* item, T* other);
    
    template<class T>
    void give(OpenStuff* item, T* other);
    
    template<class T>
    void give(MoveStuff* item, T* other);
    
    template<class T>
    void give(HealthStuff* item, T* other);
    
    // recieves an item
    //void recieve(Stuff* item);
    void recieve(HealthStuff* item);
    void recieve(GrowStuff* item);
    void recieve(FriendStuff* item);
    void recieve(OpenStuff* item);
    void recieve(MoveStuff* item);
    
    // Someone drops an item
    template<class T>
    void drop(T* item);
    
    // person takes damage
    void hurt(const int& damage);
    
    void attack();
    
    int getHealth() const;
    
    // gets Stuff list -- LISTS ARE PUBLIC
    //std::multimap<std::string, Stuff*>& getStuffList();
    
    // gets person's name
    std::string getName() const;
    
    void dies();
    bool isDead();
    
    virtual std::ostream& narrate(std::ostream& out) const=0;
    virtual std::ostream& render(std::ostream& out) const=0;
};

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// make Alice a singleton
class Alice: public Person {
    
private:
    
    // list of helpers with Alice
    std::map<std::string, NPC*> helperList;
    
    // list of badguys with Alice
    std::map<std::string, NPC*> badguyList;
    
    // getSize of Alice (small(1), normal(2), big(3))
    int bodySize;
    
    std::string description;
    
    // constructor
    Alice(const int& bSize, const int& hLevel, const std::string& nm, const std::string& dscpt, bool attk);
    
public:
    
    virtual ~Alice();        // destructor
    
    // Singleton
    //static Alice* makeAlice(const int& bSize, const int& hLevel, const std::string& nm, const std::string& dscpt, bool a);
    
    static Alice* makeAlice();
    
    //adds a person to the list of Helpers
    void taggingAlong(NPC* tagger);
    
    //removes a person from the list of Helpers
    void ditched(NPC* ditcher);
    
    // Alice can move from place to place with her friends
    void move(Place* to);

    //Alice chooses an item from a chest
    template<class T>
    void choose(Chest* chst, T* item);
    
    //Alice adds item to the list of stuff
    template<class T>
    void pickUp(T* item);
    
    //Alice uses an item on herself
    template<class T>
    void use(T* item);
    
    //Alice uses an item in a place
    template<class T>
    void use(T* item, Place* where);
    
    //Alice uses an item on a thing
    template<class T>
    void use(T* item, Chest* what);
    
    template<class T>
    void use(T* item, Door* what);
    
    //Alice uses an item on a person
    template<class T>
    void use(T* item, NPC* who);
    
    // Get size of Alice//her size is an int
    int getBodySize() const;
    
    void setBodySize(const int& sz);
    
    // output what she has, who she's met, body getSize, and health
    std::ostream& render(std::ostream& out) const;
    std::ostream& narrate(std::ostream& out) const;
};

/*
 ----------------------------------
 NPC: Derived from Person
 ----------------------------------
 
 generic class will instantiate individual bad guys/helpers dynamically (on demand)
 Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
 Helpers will be WhiteRabbit, MadHatter, CheshireCat...
 
 */

class NPC: public Person {
    
    friend class PersonFactory;
    
private:
    
    // unique description of helper / badguy
    std::string description;
    
    // what helper / badguy says to Alice
    std::string says;
    
    // true = friend, false = not friend
    bool friendly;
    
    // constructor
    NPC(const std::string& nm, const std::string& dscrpt, const std::string& threat, const int& hlth, const bool& frndly, bool attk);

public:
    
    // destructor
    ~NPC();
    
    // set friendly status
    void setFriendly(const bool& x);
    
    //adding these two for character progression
    // set NPC's narration
    void setnarrate(const std::string& nar);
    
    // set what NPC says to Alice
    void settalk(const std::string& nar);
    
    // description of NPC
    std::ostream& narrate(std::ostream& out) const;
    
    // What NPCs say to Alice
    std::ostream& talk(std::ostream& out) const;
    
    // get friendly data
    bool isfriendly() const;
    
    std::ostream& render(std::ostream& out) const;
    
    // NPC uses item on another NPC or Alice
    template<class T>
    void use(T* item, NPC* who);
    
    template<class T>
    void use(T* item, Alice* who);
};

/*
 ----------------------------------
 PersonFactory Class: Derived from Person to make people
 ----------------------------------
 */

class PersonFactory: public Person
{
    
private:
    
    // constructor
    PersonFactory();
    
public:
    
    //destroys a factory
    ~PersonFactory();
    
    //make a test tube baby
    static NPC* makePerson (const std::string who);
    
    //from here for npc's we will call their constructor but for alice we will call makeAlice
};

/*
 ----------------------------------
 Stuff Class: Base
 ----------------------------------
 
 generic class will instantiate individual stuff dynamically (on demand)
 */

class Stuff {
    
protected:
    
    // if used, status = 0; if not, status = 1
    bool status;
    
    // name of stuff object
    std::string name;
    
    // description of Stuff
    std::string description;
    
    // decrease to BGs health / change Alice's health, getSize
    int result;
    
public:
    
    // constructor
    Stuff(const std::string name, const std::string description, const int result,const bool status);
    
    // destructor
    virtual ~Stuff();

    std::string getName() const;
    
    // output description of Stuff
    std::ostream& narrate(std::ostream&) const;
};

/*
 ----------------------------------
 subStuff classes: Derived from Stuff
 ----------------------------------
 
 handlers will be BandersnatchEye, Key, WhiteRose, Cake, Tea, Sword, JabberBlood...
 
 */

class GrowStuff : public Stuff
{
    
    public:
        GrowStuff(const std::string name, const std::string description, const int result,const bool status);
        ~GrowStuff();

        void useItem(Alice* who);
        //void useItem(NPC* who);
    
        //void useItem(Place* where);
        //void useItem(Thing* what);
        //void useItem(/*const*/ Person* who, Place* where);
};

class HealthStuff : public Stuff
{
    public:
        HealthStuff(const std::string name, const std::string description, const int result,const bool status);
        ~HealthStuff();
    
        void useItem(Alice* who);
        void useItem(NPC* who);
    
        //void useItem(Place* where);
        //void useItem(Thing* what);
        //void useItem(/*const*/ Person* who, Place* where);
};

class FriendStuff : public Stuff
{
    public:
        FriendStuff(const std::string name, const std::string description, const int result,const bool status);
        ~FriendStuff();
    
        void useItem(NPC* who);
    
        //void useItem(Alice* who);
        //void useItem(Place* where);
        //void useItem(Thing* what);
        //void useItem(/*const*/ Person* who, Place* where);
};

class OpenStuff : public Stuff
{
    public:
        OpenStuff(const std::string name, const std::string description, const int result,const bool status);
        ~OpenStuff();
    
        template<class T>
        void useItem(T* what);
    
        //void useItem(Alice* who);
        //void useItem(Place* where);
        //void useItem(Person* who);
        //void useItem(NPC* who);
        //void useItem(Person* who, Place* where);
};

class MoveStuff : public Stuff
{
    public:
        MoveStuff(const std::string name, const std::string description, const int result,const bool status);
        ~MoveStuff();
    
        void useItem(Alice* who, Place* where);
    
        //void useItem(Alice* who);
        //void useItem(Place* where);
        //void useItem(Person* who);
        //void useItem(NPC* who);
        //void useItem(Thing* what);
};

/*
 ----------------------------------
 Thing Class: Base
 ----------------------------------
 */
    
/* COMMENT OUT TO TEST
 class Thing {
    
protected:
        
    bool status;        // status of door: 1 = open, 0 = closed
    std::string name;
    
public:
        
    std::string thingtype;	//so i can differentiate between doors and chests easier
    
    Thing(const bool& stat, const std::string name);            // constructor
    virtual ~Thing();   // destructor
    
    std::string getName() const;
    // open thing, depend on Place & Alice's bodySize
    // pure virtual function, each derived will have own
    virtual void openThing()=0;
    virtual void closeThing()=0;
    bool getStatus() const;

    // output of what Alice has opened (will pass to derived)
    virtual std::ostream& render(const std::ostream&)=0;
};
    
// derived class of Thing
class Door : public Thing {
     
private:
	std::map<std::string, Place*> between; 
    std::multimap<std::string, Stuff*> nothing;
        
public:
        
    Door(const bool& stat, std::string nm, const std::map<std::string, Place*>& betwn);             // constructor
    ~Door();            // destructor
        
    // open Door to find Chest
    // must be small (bodySize = 1) and must have key
        
    //should this take other input, how does open and close thing know alice's getSize? Should take person? -- yes, more specifically, should it just be an Alice? I suppose it could just be an alice, although then rabbit cannot open the door, but we might not care about that... I guess it needs to be an alice if it involves her getSize.
        
    //could this be in thing class
    // Not sure, since we talked about Things having a different outcome, I'm not sure if these should be in the base class or in the derived...
    void openThing();
    void closeThing();      // automatic close, or should this also take a Person?... good question. I like it taking an Alice

    // effects of openThing()
    //std::ostream& render(const std::ostream&);
};
    
// derived class of Thing
class Chest : public Thing {
    
private:
    
    std::multimap<std::string, Stuff*> inside;		//list of stuff inside the chest
    
public:
    
    Chest(const bool stat, std::string nm, const std::multimap<std::string, Stuff*>& contains);  // constructor
    ~Chest();               // destructor
    
    // open Chest to find Sword
    // must be tall (bodySize = 3)
    void openThing();
    void closeThing();
    
    bool getStatus();
    std::ostream& narrate(std::ostream& out);
    void takeStuff(Stuff* tk);			//take stuff from the chest
    std::multimap<std::string, Stuff*>& whatsinside();	//show whats inside
    
    // effects of openThing()
    //std::ostream& render(const std::ostream&);
};
 */
    
/*
 ----------------------------------
 Game Class: Base
 ----------------------------------
 */

 class Game {
     
     private:
     
     
         void makePlaces();             // instantiates Places and adds to static list
         void makePeople();             // instantiates People and adds to static list
         void makeStuff();              // instantiates Stuff and adds to Place's stuff list
         
     public:
     
        static std::map<std::string, Place*> places;    // Game class keeps static list of Places in Wonderland
        //static std::map<std::string, NPC*> people;   // Game class keeps static list of People in Wonderland
         
        Game();                        // constructor
        ~Game();                       // destructor
        //std::map<std::string, Place*>& getPlaceList();
     
     
        //Alice* alicePtr;
        //std::map<std::string, NPC*>& getPeopleList() const;
     
        Place* findHere() const;
        void delegate(const std::string& input);
 };


    
