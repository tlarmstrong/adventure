// wonderlandAdventure.h
#include <iostream>

/*
 ----------------------------------
 List Class: Base
 ----------------------------------
 
 List object to handle lists of places, helpers, bad guys, and stuff for Alice
 
 */

template <class T>
class List {
    
    private:
        T*  elements;           // array of values
        int sz;                 // size of array
        int head;               // index of head value
        int tail;               // 1 + index of tail value
        void checkSpace();      // check number of spaces available in array
        
    public:
        List();                 // constructor
        ~List();                // destructor
    
        void push(const T value);           // appends element to end of array
    
        //I figured, since our list has no ordering, we need to tell it what value we want -- Good Call!
        T pop(T value);                     // removes and returns element from array
    
        bool empty() const;                 // returns true if array is empty
        int size() const;                   // returns the number of elements in array
        bool contains(const T value) const; // lets us know if a value is in a list
};

/*
 ----------------------------------
 Person Class: Base class for Alice, Helper, and Badguy
 ----------------------------------
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
        Person(const int health, const List<Stuff> list);
        virtual ~Person();                       // destructor
     
        void Move(Place from, Place to);          //allows each person to move from place to place
        void Give(Stuff item, Person other);      //gives an item to someone else
        void Recieve(Stuff item);                 //recieves an item
        void Hurt(int damage);					  //person takes damage -- ooh, this is good -- I think this takes place of the fight() I had in Bad Guys earlier. Makes more sense here.
 }
 
 
/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

class Alice: public Person {
    
    private:

        List<Helper> helperList;    // list of helpers with Alice
    
        int bodySize;               // size of Alice (small(1), normal(2), big(3))
    
    public:
    
        // constructor
        Alice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int health);
        virtual~Alice();        // destructor
        
        void TaggingAlong (const Person Tagger);  //adds a person to the list of Helpers
        void Ditched (const Person Ditcher);      //removes a person from the list of Helpers
        
        void Pickup (const Stuff item);                     //Alice adds item to the list of stuff
        void Drop (const Stuff item);                       //Alice drops an item
        void Use (const Stuff item);                        //Alice uses an item on herself
        void Use (const Stuff item, const Place where);     //Alice uses an item in a place
        void Use (const Stuff item, const Thing what);      //Alice uses an item on a thing
        void Use (const Stuff item, const Person who);      //Alice uses an item on a person
    
        // output what she has, who she's met, body size, and health
        std::ostream& render(std::ostream&) const;
};

/*
 ----------------------------------
 Helper Class: Derived from Person
 ----------------------------------
 
generic class will instantiate individual helpers dynamically (on demand)
Helpers will be WhiteRabbit, MadHatter, CheshireCat...
 
Example:

    List<Stuff> whatHave(Stuff watch);
 
    Helper WhiteRabbit(name, description, advice, whatHave, health);

    Then possible to use base functions:
    WhiteRabbit.narrate();
    WhiteRabbit.talkTo();
    WhiteRabbit.giveAdvice();
*/

class Helper : public Person {
    
    private:
        
        std::string description;        // unique description of Helper
        std::string name;               // name of Helper
        std::string advice;             // Helper's advice for Alice
        
    public:
    
        // constructor
        Helper(const std::string nm, const std::string dscrpt, const std::string advice, const List<Stuff> list, const int hlth);
        ~Helper();                      // destructor
        
        // output description of Helper
        std::ostream& narrate(std::ostream&) const;
        
        // each Helper can give advice to Alice
        std::string giveAdvice() const;
    
        void talkTo();	//how is this different from give advice // input vs. output...could do both in giveAdvice() and get rid of this one?
};

/*
 ----------------------------------
 BadGuy Class: Derived from Person
 ----------------------------------
 
 generic class will instantiate individual bad guys dynamically (on demand)
 Bad guys will be Bandersnatch, Jabberwocky, RedQueen...
 
 */

class BadGuy: public Person {
    
    private:
        
        std::string description;        // unique description of BadGuy
        std::string name;               // name of bad guy
        std::string threat;             // BG threat for Alice
        bool friendly;                  // 1 = friend, 0 = not friend
        
    public:
        
        // constructor
        BadGuy(const std::string nm, const std::string dscrpt, const std::string threat, const List<Stuff> list, const int hlth, const bool frndly);
        ~BadGuy();               // destructor
        
        // description of BadGuy
        std::ostream& narrate(std::ostream&) const;
        
        // threats BGs pose to Alice
        std::string makeThreat() const;
};

/*
 ----------------------------------
 Places Class: Base
 ----------------------------------
 
 generic class will instantiate individual places dynamically (on demand)
 Places will be Tree, Garden, Woods, TeaParty, Castle, Battlefield, Home
 
 Example use:
 List<Person> TeaPartyPeople(WhiteRabbit, MadHatter)
 List<Stuff> TeaPartyStuff(Cupcake, roadTea)
 
 Place TeaParty(name, description, actions, TeaPartyPeople*, TeaPartyStuff*)

 TeaParty.narrate();
 TeaParty.WhoHere();
 
 */

class Places {
    
    protected:
        
        std::string description;         // unique description of Place
        std::string actions;             // what Alice can do here
        std::string name;                // name of Place
        List<Person> PeopleHere;         // everybody in Place
        List<Stuff> StuffHere;           // list of things in a Place
        List<Thing> ThingHere;			 // list of things here
        List<Place> Placeto;			 // list of places Alice can go from here
    
    public:
    
        // constructor
        Places(const std::string name, const std::string descript, const std::string actions, const List<Person> who, const List<Stuff> what, const List<Thing> obj, const List<Place> where);
        ~Places();                                  // destructor
    
        List<Person> WhoHere() const;               //returns a list of everybody here
        void PersonEnters(const Person enterer);    //somebody comes into the place
        void PersonLeaves(const Person leaver);     //removes somebody from a place
    
        List<Stuff> WhatsHere() const;              //returns the list of stuff here
        void Dropped(const Stuff drop);             //someone dropped an item here, so it is now laying around
        void Picked(const Stuff pick);              //somebody picked up an item here
    
        // output description of Place
        std::ostream& narrate(std::ostream&) const;

        // what Alice can do in particular place
        std::string action(const std::string);
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
        int result;                 // decrease to BGs health / change Alice's health, size, or to be defined :) -- are you thinking about the Absolem the Caterpillar's smoke? Would that affect her health, or do we need another variable?
    
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
        //should this take other input, how does open and close thing know alice's size? Should take person? -- yes, more specifically, should it just be an Alice?
    
        //could this be in thing class
        // Not sure, since we talked about Things having a different outcome, I'm not sure if these should be in the base class or in the derived...
        void openThing(const Alice alice);
        void closeThing();      // automatic close, or should this also take a Person?
    
        // effects of openThing()
        std::ostream& render(const std::ostream&);
};

// derived class of Thing
class Chest : public Thing {
    
    private:
        
        bool status;            // status of chest: 1 = open, 0 = closed
        List<Stuff> inside;		//list of stuff inside the chest
        
    public:
        
        Chest(const bool status, const List<Stuff> contains);                // constructor
        ~Chest();               // destructor
    
        // open Chest to find Sword
        // must be tall (bodySize = 3)
        void openThing();
    
        // effects of openThing()
        std::ostream& render(const std::ostream&);
};

