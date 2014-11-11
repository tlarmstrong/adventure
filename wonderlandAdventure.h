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
    
    Place* whereAmI;                 // person's current location //a place is not a part of a person. If you want to do something like this, it should be a place pointer. Personally, I am pro keeping track of where a person is in just one place. Pros of one place: We don't have to remember to change it in both places, Cons we will have to iterate through something.
    
    // helper function to copy from one list to another
    copyList(List<T> from, List<T> to);
    
public:
    
    // constructor -- all derived use (initialization list)
    Person(const int hLevel, const List<Stuff> list, Place location);
    virtual ~Person();                       // destructor
    
    void Move(const Place to);                       // Person can move from place to place
    void Give(const Stuff item, const Person other); // gives an item to someone else
    void Recieve(const Stuff item);                  // recieves an item
    void Hurt(const int damage);					 // person takes damage
}


/*
 ----------------------------------
 Options for where people are:
 ----------------------------------
 
storing in person:
class person
{
place* whereAmI;
void move(const place& to) {whereAmI=&to;} //to move a person to somewhere else
place* whereAreYou() {return whereAmI;} //to get where someone is
}
class place
{
 person[] whoshere() {for (person* iterator=something...; iterate through everybody) if(thatpersonisthere) then include in array to be returned}		//this will be the hard part of storing in person. I think that we will just keep our people in an array so we can iterate through them. Also it should be noted you cannot actually return an array, but there are ways we can do pretty much that. 
}


storing in place:
class person
{
void move(place& from, place& to) {from.personleaves(this); to.personenters(this)} //to move a person to somewhere else
place* whereAreYou() {for(places* iterator=something...; iterate through all the places) if(personisthere)return iterator} //This will be the difficult part of storing in places. like the people we will probably have an array of places (I think that whichever we do we should keep all our places and people in an list anyway.) )
}
class place
{
list<person> peoplehere;
 person[] whoshere() {return peoplehere}	//since we keep it in a list instead of an array, it will be slightly more complicated than this, but this is really how it will work.
}


//I think we are far more likely to ask who is at a place, which would say we should store that information in place. However, I really like the idea of storing it in person. I don't know I have been going back and forth on where we should store it every minute. Really both options are good.
*/
/*
 ----------------------------------
 Factory Class: Derived from Person to make people
 ----------------------------------
 */

class personFactory: public Person
{
    public:
        personFactory();		//makes a factory
        ~personFactory();		//destroys a factory
    
        static Person* makePerson (string who);		//make a test tube baby
    
        //from here for npc's we will call their constructor but for alice we will call getalice
}
/*
 Factory::makePerson
 {
 person* testtube
 if (who==Bandersnatch){
 testtube=new badguy(description, ffiwoafj, dfjiwofe, afijefiojwsf)
 }
 if (who==)
 }
 
 I think this will all work. I think we should be good :)
 */


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
    Alice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int health, const Place location);
    
public:
    
    virtual ~Alice();        // destructor
    
    //ask about singleton
    static Alice& makeAlice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int hLevel);
    /*
     {
     static Alice alice(const List<Stuff> sList, const List<Helper> hList, const List<BadGuy> bList, const int bodySize, const int hLevel);
     return &alice;
     }
     
     when I looked it up, I saw many different ways of implimentation, I think they all worked. This one seemed the simplest and I think it should work. It might be a good idea to still double check with prather
     */
    
    void taggingAlong(const Person Tagger);  //adds a person to the list of Helpers
    void ditched(const Person Ditcher);      //removes a person from the list of Helpers
    
    void pickup(const Stuff item);                     //Alice adds item to the list of stuff
    void drop(const Stuff item);                       //Alice drops an item
    void use(const Stuff item);                        //Alice uses an item on herself
    void use(const Stuff item, const Place where);     //Alice uses an item in a place
    void use(const Stuff item, const Thing what);      //Alice uses an item on a thing
    void use(const Stuff item, const Person who);      //Alice uses an item on a person
    
    // output what she has, who she's met, body getSize, and health
    std::ostream& render(std::ostream&) const;
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
    NPC(const std::string nm, const std::string dscrpt, const std::string threat, const List<Stuff> list, const int hlth, const bool frndly, const Place location);
    ~NPC();               // destructor
    
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


