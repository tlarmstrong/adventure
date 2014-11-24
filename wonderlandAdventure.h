// wonderlandAdventure.h
#include <map>
#include <iostream>

// declare Stuff, NPC, Place, Thing, Person
class Stuff;
class Place;
class Person;
class PersonFactory;
class NPC;
class Thing;
class Chest;
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
    
    std::string description;         // unique description of Place
    //std::string action;              // what Alice can do here //I am not sure this should be a thing... Her possible actions are determined by what is around her.
    std::string name;                // name of Place
    std::map<std::string, Person*> peopleHere;         // everybody in Place
    std::multimap<std::string, Stuff*> stuffHere;           // list of things in a Place
    std::multimap<std::string, Thing*> thingHere;			 // list of things here
    std::map<std::string, Place*> placeTo;			 // list of Place Alice can go from here
    
public:
    
    Place(const std::string& nm, const std::string& dscpt, const std::multimap<std::string, Stuff*>& what, const std::map<std::string, Person*>& who, const std::multimap<std::string,Thing*>& obj, const std::map<std::string, Place*>& trav);
    //Place();                                    // constructor
    ~Place();                                   // destructor
    
    std::map<std::string, Person*> whoHere() const;               //constructed list
    std::string getPlaceName() const;           // returns name of Place
    
    void personEnters(Person* enterer);   //somebody comes into the place
    void personLeaves(Person* leaver);    //removes somebody from a place
    
    std::multimap<std::string, Stuff*> whatsHere() const;              //returns the list of stuff here
    void dropped(Stuff* drop, Person* who);             //someone dropped an item here, so it is now laying around
    void pickedUp(Stuff* pick, Person* who);              //somebody picked up an item here
    void genStuff(Stuff* gen);				//to generate an item in the game
    
    void newPlaceToGo(Place* goTo);
    void blockPlaceToGo(Place* block);
    
    std::multimap<std::string, Thing*> getThingsHere() const;	//gets things here
    
    std::map<std::string, Place*> getNewPlaceToGo() const;
    
    // output description of Place
    std::ostream& narrate(std::ostream& out) const;
    
    //output current information
    std::ostream& render(std::ostream& out) const;
    
    
    // what Alice can do in particular place
    //std::string canDo(const std::string& doin);		//dont forget to name your variables. Not sure if we need it nor what we want it to do exactly.
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
    
    int health;                     //health level of the person
    std::multimap<std::string, Stuff*> stuffList;          // list of stuff each person has  
    std::string name;
    Person();
    
public:
    
    // constructor -- all derived use (initialization list)

    Person(const int& hLevel, const std::multimap<std::string, Stuff*>& sList, const std::string& nm);
    virtual ~Person();                       // destructor
    
    virtual void move(Place* to) const;               // Person can move from place to place
    
    Place* whereAreYou() const; // get (and display) name of place	//I would rather return a place pointer that then could output the name of the place. this way if we need to act on the place, we can. Also it needs the list of places to look through, unless we make the list of places static... that might actually be a good idea...
    
    void give(Stuff* item, Person* other);     // gives an item to someone else
    void recieve(Stuff* item);                 // recieves an item
    void hurt(const int& damage);					 // person takes damage
    
    int getHealth() const;
    
    std::multimap<std::string, Stuff*> getStuffList() const;
    std::string getName() const;								// gets person's name
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
    
    std::map<std::string, NPC*> helperList;    // list of helpers with Alice
    std::map<std::string, NPC*> badguyList;    // list of badguys with Alice
    int bodySize;            // getSize of Alice (small(1), normal(2), big(3))
    std::string description;
    
    // constructor
    Alice(const std::multimap<std::string, Stuff*>& sList, const std::map<std::string, NPC*>& hList, const std::map<std::string, NPC*>& bList, const int& bSize, const int& hLevel, const std::string& nm, const std::string& dscpt);
    
public:
    
    virtual ~Alice();        // destructor
    
    // Singleton
    static Alice* makeAlice(const std::multimap<std::string, Stuff*>& sList, const std::map<std::string, NPC*>& hList, const std::map<std::string,NPC*>& bList, const int& bSize, const int& hLevel, const std::string& nm, const std::string& dscpt);
    
    void taggingAlong(NPC* tagger);  //adds a person to the list of Helpers
    void ditched(NPC* ditcher);      //removes a person from the list of Helpers
    void move(Place* to) const;               // Alice can move from place to place with her friends

    
    void choose(Chest* chst, Stuff* item);			//Alice chooses an item from a chest
    void pickup(Stuff* item);                     //Alice adds item to the list of stuff
    void drop(Stuff* item);                       //Alice drops an item
    void use(Stuff* item);                        //Alice uses an item on herself
    void use(Stuff* item, Place* where);     		//Alice uses an item in a place
    void use(Stuff* item, Thing* what);      		//Alice uses an item on a thing
    void use(Stuff* item, Person* who);      		//Alice uses an item on a person
    
    int getBodySize() const;                   // Get size of Alice//her size is an int
    
    void setBodySize(const int& s);
    
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
    
    std::string description;      // unique description of helper / badguy
    //    std::string name;             // name of helper / badguy		//I moved this to person
    std::string says;             // what helper / badguy says to Alice
    bool friendly;                // true = friend, false = not friend
    NPC(const std::string& nm, const std::string& dscrpt, const std::string& threat, const std::multimap<std::string, Stuff*>& sList, const int& hlth, const bool& frndly);

    
public:
    
    // constructor
    ~NPC();               // destructor
    
    // set friendly status
    void setFriendly(const bool& x);
    
    // set NPC's narration					//adding these two for character progression
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
};

/*
 ----------------------------------
 PersonFactory Class: Derived from Person to make people
 ----------------------------------
 */

class PersonFactory: public Person
{
    
private:
    
    PersonFactory();		//makes a factory // constructor should be private (I moved it)? I think having it in private will work, we just won't ever make one. The reason why I think it will work is because our function is static. Thus I think we can call it without instantiating factory.
    
public:
    
    ~PersonFactory();		//destroys a factory
    
    //make a test tube baby
    static Person* makePerson (const std::string who);
    
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
    
    //Stuff* next	        //"next" pointer in the base class		//stopped using chain of command
    bool status;                // if used, status = 0; if not, status = 1
    std::string name;           // name of stuff object
    std::string description;    // description of Stuff
    int result;                 // decrease to BGs health / change Alice's health, getSize
    
public:
    
    // constructor
    Stuff(const std::string name, const std::string description, const int result,const bool status);
    virtual ~Stuff();       // destructor
    
    virtual void useItem(Alice*)=0;
    virtual void useItem(Place*)=0;
    virtual void useItem(Person*)=0;
    virtual void useItem(NPC*)=0;
    virtual void useItem(Thing*)=0;
    virtual void useItem(const Person* who, Place* where)=0;
                         
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
        GrowStuff(std::string name, std::string description, int result, bool status);
        ~GrowStuff();

        void useItem(Alice* who);
    
        void useItem(Place* where);
        void useItem(Person* who);
        void useItem(NPC* who);
        void useItem(Thing* what);
        void useItem(const Person* who, Place* where);
};

class HealthStuff : public Stuff
{
    public:
        HealthStuff(std::string name, std::string description, int result, bool status);
        ~HealthStuff();
    
        void useItem(Person* who);
    
        void useItem(Alice* who);
        void useItem(Place* where);
        void useItem(NPC* who);
        void useItem(Thing* what);
        void useItem(const Person* who, Place* where);
};

class FriendStuff : public Stuff
{
    public:
        FriendStuff(std::string name, std::string description, int result, bool status);
        ~FriendStuff();
    
        void useItem(NPC* who);
    
        void useItem(Alice* who);
        void useItem(Person* who);
        void useItem(Place* where);
        void useItem(Thing* what);
        void useItem(const Person* who, Place* where);
};

class OpenStuff : public Stuff
{
    public:
        OpenStuff(std::string name, std::string description, int result, bool status);
        ~OpenStuff();
    
        void useItem(Thing* what);		//clearly this is separated for this to be the actual function to be called... what is the who being acted on? Is this a trap?
        
        void useItem(Alice* who);
        void useItem(Place* where);
        void useItem(Person* who);
        void useItem(NPC* who);
        void useItem(const Person* who, Place* where);
};

class MoveStuff : public Stuff
{
    public:
        MoveStuff(std::string name, std::string description, int result, bool status);
        ~MoveStuff();
    
        void useItem(const Person* who, Place* where);
    
        void useItem(Alice* who);
        void useItem(Place* where);
        void useItem(Person* who);
        void useItem(NPC* who);
        void useItem(Thing* what);
};

/*
 ----------------------------------
 Thing Class: Base
 ----------------------------------
 */
    
class Thing {
    
protected:
        
    bool status;        // status of door: 1 = open, 0 = closed
    std::string name;
    
public:
        
    Thing(const bool& stat, const std::string name);            // constructor
    virtual ~Thing();   // destructor
    
    std::string getName() const;
    // open thing, depend on Place & Alice's bodySize
    // pure virtual function, each derived will have own
    virtual void openThing()=0;
    virtual void closeThing()=0;
        
    // output of what Alice has opened (will pass to derived)
    virtual std::ostream& render(const std::ostream&)=0;
};
    
// derived class of Thing
class Door : public Thing {
     
private:
	std::map<std::string, Place*> between; // unused?
        
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
    
    void takeStuff(Stuff* tk);
    std::multimap<std::string, Stuff*>& whatsinside();
    
    // effects of openThing()
    //std::ostream& render(const std::ostream&);
};
    
    
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
        //static std::map<std::string, Person*> people;   // Game class keeps static list of People in Wonderland
         
        Game();                        // constructor
        ~Game();                       // destructor
        std::map<std::string, Place*> getPlaceList() const;
        //std::map<std::string, Person*> getPeopleList() const;
        void delegate(const std::string& input);
 };


    
