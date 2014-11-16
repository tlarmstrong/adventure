// wonderlandAdventure.h
#include "linkedList.h"
#include <iostream>

/*
 ------------------------------------------------------------
 Person Class: Base class for Alice, NPC, and personFactory
 ------------------------------------------------------------
 */

class Person {
    
private:
    
    // prevent value semantics
    Person(const Person& other);            //copy constructor
    void operator = (const Person& other);  //assignment operator
    
protected:
    
    int health;                     //health level of the person
    List<Stuff> stuffList;          // list of stuff each person has
    // Example: WhiteRabbit may have a watch and give it to Alice | Alice can add this to her list

public:
    
    // constructor -- all derived use (initialization list)
    Person(const int& hLevel, const List<Stuff>& list);
    virtual ~Person();                       // destructor
    
    void move(Place& from, Place& to);               // Person can move from place to place
    
    std::ostream& whereAreYou(std::ostream& cout) const; // get (and display) name of place
    
    void give(const Stuff& item, Person& other);     // gives an item to someone else
    void recieve(const Stuff& item);                 // recieves an item
    void hurt(const int& damage);					 // person takes damage
}

/*
 ----------------------------------
 PersonFactory Class: Derived from Person to make people
 ----------------------------------
 */

class PersonFactory: public Person
{
    private:    
    
        PersonFactory();		//makes a factory // constructor should be private (I moved it)?
    
    public:
    
        ~PersonFactory();		//destroys a factory
    
        //make a test tube baby
        static Person* makePerson (const std::string who);
    
        //from here for npc's we will call their constructor but for alice we will call getalice
};

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// make Alice a singleton
class Alice: public Person {
    
private:
    
    List<NPC> helperList;    // list of helpers with Alice
    List<NPC> badguyList;    // list of badguys with Alice
    int bodySize;            // getSize of Alice (small(1), normal(2), big(3))
    
    // constructor
    Alice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int health);
    
public:
    
    virtual ~Alice();        // destructor
    
    // Singleton
    static Alice& makeAlice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int hLevel);
    
    void taggingAlong(const Person tagger);  //adds a person to the list of Helpers
    void ditched(const Person ditcher);      //removes a person from the list of Helpers
    
    void pickup(const Stuff item);                     //Alice adds item to the list of stuff
    void drop(const Stuff item);                       //Alice drops an item
    void use(const Stuff item);                        //Alice uses an item on herself
    void use(const Stuff item, const Place where);     //Alice uses an item in a place
    void use(const Stuff item, const Thing what);      //Alice uses an item on a thing
    void use(const Stuff item, const Person who);      //Alice uses an item on a person
    
    // output what she has, who she's met, body getSize, and health
    std::ostream& render(std::ostream& cout) const;
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
    
private:
    
    std::string description;      // unique description of helper / badguy
    std::string name;             // name of helper / badguy
    std::string says;             // what helper / badguy says to Alice
    bool friendly;                // 1 = friend, 0 = not friend
    
public:
    
    // constructor
    NPC(const std::string nm, const std::string dscrpt, const std::string threat, const List<Stuff> list, const int hlth, const bool frndly);
    ~NPC();               // destructor
    
    // description of NPC
    std::ostream& narrate(std::ostream& cout) const;
    
    // What NPCs say to Alice
    std::ostream& talk(std::ostream& cout) const;
};

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
        std::string action;              // what Alice can do here
        std::string name;                // name of Place
        List<Person> peopleHere;         // everybody in Place
        List<Stuff> stuffHere;           // list of things in a Place
        List<Thing> thingHere;			 // list of things here
        List<Place> placeTo;			 // list of Place Alice can go from here
        
        static List<Place> placeList;    // list of Place in game
        
    public:

        Place();                                    // constructor
        ~Place();                                   // destructor
        
        List<Person> whoHere() const;               //returns a list of everybody here
        
        std::string getPlaceName() const;           // returns name of Place
        List<Place> getPlaceList() const;           // returns list of Place
        // thought we may need these to get the name of Place (private) and list of Place(s) (private) by calling a public function?
        
        void personEnters(const &Person enterer);   //somebody comes into the place
        void personLeaves(const &Person leaver);    //removes somebody from a place
        
        List<Stuff> whatsHere() const;              //returns the list of stuff here
        void dropped(const Stuff drop);             //someone dropped an item here, so it is now laying around
        void picked(const Stuff pick);              //somebody picked up an item here
        
        // output description of Place
        std::ostream& narrate(std::ostream& cout) const;
        
        // what Alice can do in particular place
        std::string canDo(const std::string);
};

/*
 ----------------------------------
 PlaceFactory Class: Derived from Place to make places
 ----------------------------------
 */

class PlaceFactory: public Place
{
    private:
        
        PlaceFactory();         // constructor makes a factory
        
    public:
        
        ~PlaceFactory();		// destructor destroys a factory
    
        //make a specific Place
        static Place* makePerson (std::string where);
};

/*
 ----------------------------------
 Stuff Class: Base
 ----------------------------------
 
 generic class will instantiate individual stuff dynamically (on demand)
 Stuff will be BandersnatchEye, Key, WhiteRose, CupCake, RoadTea, Sword, JabberBlood...
 
 */

class Stuff {
    
protected:
    
    bool status;                // if used, status = 0; if not, status = 1
    std::string name;           // name of stuff object
    std::string description;    // description of Bandersnatch Eye
    int result;                 // decrease to BGs health / change Alice's health, getSize, or to be defined :) -- are you thinking about the Absolem the Caterpillar's smoke? Would that affect her health, or do we need another variable? // um not quite. it is a I don't know how we control what each different stuff changes. It may be that we need to create different classes for each type of object so each type of object can change the proper thing. Not sure, takes more thinking
    
public:
    
    // constructor
    Stuff(const bool status, const std::string name, const std::string description, const int result);
    virtual ~Stuff();       // destructor
    
    //we should make sure we don't need another function to activate on such as a function that uses the item on a badguy or on alice or...// good question, I'm not sure. Since we have polymorphic use() in Alice, would that take care of it?
    
    // output description of Stuff
    std::ostream& narrate(std::ostream&) const;
};

/*
 ----------------------------------
 Thing Class: Base
 ----------------------------------
 */

class Thing {
    
protected:
    
    bool status;        // status of door: 1 = open, 0 = closed
    
public:
    
    Thing();            // constructor
    virtual ~Thing();   // destructor
    
    // open thing, depend on Place & Alice's bodySize
    // pure virtual function, each derived will have own
    virtual void openThing()=0;
    
    // output of what Alice has opened (will pass to derived)
    virtual std::ostream& render(const std::ostream&)=0;
};

// derived class of Thing
class Door : public Thing {
    
public:
    
    Door(const bool status);             // constructor
    ~Door();            // destructor
    
    // open Door to find Chest
    // must be small (bodySize = 1) and must have key
    
    //should this take other input, how does open and close thing know alice's getSize? Should take person? -- yes, more specifically, should it just be an Alice? I suppose it could just be an alice, although then rabbit cannot open the door, but we might not care about that... I guess it needs to be an alice if it involves her getSize.
    
    //could this be in thing class
    // Not sure, since we talked about Things having a different outcome, I'm not sure if these should be in the base class or in the derived...
    void openThing(const Alice alice);
    void closeThing(const Alice alice);      // automatic close, or should this also take a Person?... good question. I like it taking an Alice
    
    // effects of openThing()
    std::ostream& render(const std::ostream&);
};

// derived class of Thing
class Chest : public Thing {
    
private:
    
    List<Stuff> inside;		//list of stuff inside the chest
    
public:
    
    Chest(const bool status, const List<Stuff> contains);  // constructor
    ~Chest();               // destructor
    
    // open Chest to find Sword
    // must be tall (bodySize = 3)
    void openThing();
    
    // effects of openThing()
    std::ostream& render(const std::ostream&);
};


