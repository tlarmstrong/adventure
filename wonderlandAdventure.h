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
    List<Stuff*> stuffList;          // list of stuff each person has  //It is better as a pointer so that our list knows how to handle it (== is not always defined and we use ==)
    // Example: WhiteRabbit may have a watch and give it to Alice | Alice can add this to her list
    std::string name;

public:
    
    // constructor -- all derived use (initialization list)
    Person(const int& hLevel, const List<Stuff>& list, const std::string& nm);
    virtual ~Person();                       // destructor
    
    void move(Place& from, Place& to);               // Person can move from place to place
    
    Place* whereAreYou(list<Place*> places) const; // get (and display) name of place	//I would rather return a place pointer that then could output the name of the place. this way if we need to act on the place, we can. Also it needs the list of places to look through, unless we make the list of places static... that might actually be a good idea...
    
    void give(const Stuff& item, Person& other);     // gives an item to someone else
    void recieve(const Stuff& item);                 // recieves an item
    void hurt(const int& damage);					 // person takes damage
    std::string getName();								// gets person's name
}

/*
 ----------------------------------
 Alice Class: Derived from Person
 ----------------------------------
 */

// make Alice a singleton
class Alice: public Person {
    
private:
    
    List<NPC*> helperList;    // list of helpers with Alice
    List<NPC*> badguyList;    // list of badguys with Alice
    int bodySize;            // getSize of Alice (small(1), normal(2), big(3))
    
    // constructor
    Alice(const List<Stuff*>& sList, const List<Helper*>& hList, const List<BadGuy*>& bList, const int& bSize, const int& hLevel, const std::string& nm);
    
public:
    
    virtual ~Alice();        // destructor
    
    // Singleton
    static Alice& makeAlice(const List<Stuff*>& sList, const List<Helper*>& hList, const List<BadGuy*>& bList, const int& bSize, const int& hLevel, const std::string& nm);
    
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
    std::ostream& render(std::ostream& out) const;
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
//    std::string name;             // name of helper / badguy		//I moved this to person
    std::string says;             // what helper / badguy says to Alice
    bool friendly;                // true = friend, false = not friend
    
public:
    
    // constructor
    NPC(const std::string& nm, const std::string& dscrpt, const std::string& threat, const List<Stuff*>& list, const int& hlth, const bool& frndly);
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
    
    //from here for npc's we will call their constructor but for alice we will call getalice
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
        //std::string action;              // what Alice can do here //I am not sure this should be a thing... Her possible actions are determined by what is around her.
        std::string name;                // name of Place
        List<Person*> peopleHere;         // everybody in Place
        List<Stuff*> stuffHere;           // list of things in a Place
        List<Thing*> thingHere;			 // list of things here
        List<Place*> placeTo;			 // list of Place Alice can go from here
        
        //static List<Place> placeList;    // list of Place in game //should be in our main.
        
    public:

        Place();                                    // constructor
        ~Place();                                   // destructor
        
        List<Person*> whoHere() const;               //returns a list of everybody here
        
        std::string getPlaceName() const;           // returns name of Place
        //List<Place> getPlaceList() const;           // returns list of Place		//this might be useful ffor get list of places alice can go from here... I am not certain and haven't figured it out yet. Since I know you intended this for the static list of places I am going to comment it out for now.
        // thought we may need these to get the name of Place (private) and list of Place(s) (private) by calling a public function?
        
        void personEnters(const &Person enterer);   //somebody comes into the place
        void personLeaves(const &Person leaver);    //removes somebody from a place
        
        List<Stuff> whatsHere() const;              //returns the list of stuff here
        void dropped(const Stuff drop);             //someone dropped an item here, so it is now laying around
        void picked(const Stuff pick);              //somebody picked up an item here
        
        // output description of Place
        std::ostream& narrate(std::ostream& cout) const;
        
        // what Alice can do in particular place
        std::string canDo(const std::string& doin);		//dont forget to name your variables. Not sure if we need it, but I will leave it for now.
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
        static Place* makePlace (std::string where);
};

/*
 ----------------------------------
 Stuff Class: Base
 ----------------------------------
 
 generic class will instantiate individual stuff dynamically (on demand)
 uses Chain of Responsibility
 
*/

class Stuff {
    
protected:
    
    bool status;                // if used, status = 0; if not, status = 1
    std::string name;           // name of stuff object
    std::string description;    // description of Stuff
    int result;                 // decrease to BGs health / change Alice's health, getSize
    
    Stuff* next;                // Base pointer for Chain of Responsibility
    
public:
    
    // constructor
    Stuff(const bool status, const std::string name, const std::string description, const int result);
    virtual ~Stuff();       // destructor
    
    // functions for Chain of Responsibility
    void setNext(Stuff* n);
    void add(Stuff* n);
    virtual void handle(std::string sName);
    
    // output description of Stuff
    std::ostream& narrate(std::ostream&) const;
};

/*
 ----------------------------------
 Handler Classes: Derived from Stuff
 ----------------------------------
 
 handlers will be BandersnatchEye, Key, WhiteRose, Cake, Tea, Sword, JabberBlood...
 
 */

class BandersnatchEye : public Stuff {
    
    public:
        BandersnatchEye();              // constructor
        ~BandersnatchEye();             // destructor
        void handle(std::string sName); // handler id
    
};

class Key : public Stuff {
    
    public:
        Key();
        ~Key();
        void handle(std::string sName);
    
};

class WhiteRose : public Stuff {
    
    public:
        WhiteRose();
        ~WhiteRose();
        void handle(std::string sName);
    
};

class Cake : public Stuff {
    
    public:
        Cake();
        ~Cake();
        void handle(std::string sName);
    
};

class Tea : public Stuff {
    
    public:
        Tea();
        ~Tea();
        void handle(std::string sName);
    
};

class Sword : public Stuff {
    
    public:
        Sword();
        ~Sword();
        void handle(std::string sName);
    
};

class JabberBlood : public Stuff {
    
    public:
        JabberBlood();
        ~JabberBlood();
        void handle(std::string sName);
    
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


