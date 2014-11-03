// wonderlandAdventure.h
#include <iostream>

/*
 ----------------------------------
 List Class: Base
 ----------------------------------
 */

// List object to handle lists of places, helpers, bad guys, and stuff for Alice
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
        void push(const T value);     // appends element to end of array
        T pop();                // removes and returns element from the front of array
        bool empty() const;     // returns true if array is empty
        int size() const;       // returns the number of elements in array
        bool contains(const T value) const; //lets us know if a value is in a list I figure we do not need to pull everything out in order
};
/*
 ----------------------------------
 Person Class: Base class for Alice, Helper, and Badguy
 ----------------------------------
 */
 class Person {
     private:
        Person(const Person& other);            //copy constructor
        void operator = (const Person& other);  //assignment operator
    protected:
        static int health;                      //health level of the person
        //do you think each person should have a stuff list, that way if they are holding onto something, like say the white rabbit may have a watch, he might then be able to give it to Alice
        
    public:
        void Move(Place from, place to)         //allows each person to move from place to place
 }
 
 
/*
 ----------------------------------
 Alice Class: Base
 ----------------------------------
 */

class Alice: public Person {
    
    private:
    
        // prevent value semantics (there can only be one Alice)
        Alice(const Alice& other);              // copy constructor
        void operator = (const Alice& other);   // assignment operator (copy)
    
    protected:
        //Oh for our lists, since list is templatized, don't we need to say what type of list is each list* pointing to? maybe not since it is just a pointer... although since we have them as lists, do we need it to be a list pointer? I would think no.
        static List* stuffList;      // list of stuff Alice has
        static List* helperList;     // list of helpers with Alice
        static List* badGuyList;     // list of bad guys Alice will still encounter
        static List* placesList;     // list of places Alice has been //I think this should not be here, but just keep track of who is where in the place. I feel like it is less improtant to remember where each person has been in the past.
    
        static int bodySize;    // size of Alice (small(1), normal(2), big(3))
        static int health;      // health level of Alice
    
    public:
    
        Alice();                // constructor
        virtual~Alice();        // destructor
        
        void TaggingAlong (Person Tagger);  //adds a person to the list of helpers
        void Ditched (Person Ditcher);      //removes a person from the list of helpers
        
        void Pickup (Stuff item);           //Alice picks something up, adds it to the list of stuff
        void Drop (Stuff item);             //Alice drops an item
        void Use (Stuff item);              //Alice uses an item on herself
        void Use (Stuff item, Place where); //Alice uses an item in a place
        void Use (Stuff item, Thing what);  //Alice uses an item on a thing
        void Use (Stuff item, Person who);  //Alice uses an item on a person
    
        // output what she has, where she's been, who she's met, body size, and health
        virtual std::ostream& render(std::ostream&)=0;
};

/*
 ----------------------------------
 Places Class: Derived from Alice
               Base for other Places
               I really don't like the idea of deriving things from alice. they are not an alice
 ----------------------------------
 */

class Places : {
    
    public:
    
        Places();               // constructor
        virtual ~Places();      // destructor
        std::string* description;        // unique description of Tree
        std::string name;               // name of place
    
        void setPlaceName();            // add place name to Alice's list of places
        Places getPlaceName() const;    // get place from Alice's list of places
        //consider this instead
        //List<Person> PeopleHere               //should be protected variable to contain everybody here
        //void PersonEnters(Person enterer);    //somebody comes into the place
        //List<Person> WhoHere();               //returns a list of everybody here
        //void PersonLeaves(Person leaver);     //removes somebody from a place
        
        //consider this for additions
        //List<Stuff> StuffHere;             //list of things in a place should be protected
        //List<Stuff> WhatsHere() const;    //returns the list of stuff here
        //void Dropped(Stuff drop);         //someone dropped an item here, so it is now laying around
        //void Picked(Stuff pick);          //somebody picked up an item here
    
        // pure virtual function, derived classes will have unique output
        virtual std::ostream& narrate(std::ostream&) const=0;

        // pure virtual function: what Alice can do in particular place
        virtual std::string action(const std::string)=0;
    
        // output of where Alice has been
        static std::ostream& render(const std::ostream&);
};

// derived class of Places
class Tree : public Places {
    
    private:
    
        std::string description;        // unique description of Tree
        std::string name;               // name of place
    
    public:
        
        Tree();             // constructor
        ~Tree();            // destructor
    
        // output unique description of Tree place
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = follow white rabbit) / returns result of action
        std::string action(const std::string);
};
/*
list<people> tree(rabbit, eorye, piglet)
list<people> bridge(cristopher, pooh, owl)

Place tree(tree, people, stuff, things, action)
Place garden(bridge, people, stuff, things, action)
tree.narrate
tree.whoshere
*/


/*

place::changedescription(string)

tree.changedescription(string description2)

tree.desciption

describe1 tree
pooh will eat honey from tree. *change description* pooh will play stick game at bridge with christopher. christopher goes to tree. tree description2

describe1 tree
pooh circles thinking about how to get honey. pooh goes to bridge and asks christopher how to get honey. christopher and pooh return to tree. describe1 tree


// derived class of Places
class Garden : public Places {
    
    private:
    
        std::string* description;   // unique description of Garden (array)
        std::string name;           // name of place
        
        //my additions to place would take out these
        WhiteRabbit whtRbbt;        // (Helper) helps Alice, gives advice and intros to Mad Hatter
        Bandersnatch bndrsntch;     // (BadGuy) tries to capture Alice
        BandersnatchEye eye;        // (Stuff) Dormouse takes and gives to Alice
        WhiteRose whtRose;          // (Stuff) Red Queen hates white roses
    
    public:
        
        Garden();       // constructor
        ~Garden();      // destructor
    
        // output description of Garden
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = run to woods) / returns result of action
        std::string action(const std::string);
};

// derived class of Places
class Woods : public Places {
    
    private:
    
        std::string description;    // unique description of Woods
        std::string name;           // name of place
        Key k;                      // (Stuff) Alice can add to stuffList
        CheshireCat cat;            // (Helper) helps Alice, gives advice
    
    public:
        
        Woods();        // constructor
        ~Woods();       // destructor
    
        // output description of Woods
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = go to tea party) / returns result of action
        std::string action(const std::string);
};

// derived class of Places
class TeaParty : public Places {
    
    private:
    
        std::string* description;       // unique description of TeaParty (array)
        std::string name;               // name of place
        MadHatter hatter;               // (Helper) MadHatter gives advice
        Cupcake cake;                   // (Stuff) Alice can add to stuffList
        RoadTea tea;                    // (Stuff) Alice can add to stuffList
    
    public:
        
        TeaParty();        // constructor
        ~TeaParty();       // destructor
    
        // output description of TeaParty
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = go to White Queen's Castle)
        // returns result of action (abducted by Red Queen's men, take her to Castle instead)
        std::string action(const std::string);
};

// derived class of Places
class Castle : public Places {
    
    private:
    
        std::string* description;       // unique description of Castle (array)
        std::string name;               // name of place
        RedQueen rdQeen;                // (BadGuy) who wants to hurt Alice
        Door smallDoor;                 // (Thing) Door Alice can open in castle (must be small)
        Chest highChest;                // (Thing) Chest holding Sword (must use key and be big)
        Sword katana;                   // (Stuff) Alice can add to stuffList
    
    public:
        
        Castle();        // constructor
        ~Castle();       // destructor
        
        // output description of Castle
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = get ready for battle)
        std::string action(const std::string);
};

// derived class of Places
class Battlefield : public Places {
    
    private:

        std::string* description;       // unique description of Battlefield (array)
        std::string name;               // name of place
        Jabberwocky jbbrwcky;           // (BadGuy) wants to hurt Alice
        JabberBlood jbbrbld;            // (Stuff) Jabberwocky blood (A drink to go Home)
    
    public:
        
        Battlefield();        // constructor
        ~Battlefield();       // destructor
    
        // output description of Battlefield
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = drink Jabberwocky's purple blood)
        std::string action(const std::string);
};

// derived class of Places
class Home : public Places {
    
    private:
    
        std::string description;        // unique description of Home
        
    public:
        
        Home();        // constructor
        ~Home();       // destructor
    
        // output description of Home
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = wake up) / returns result of action
        std::string action(std::string);
};

/* 
----------------------------------
Helper Class: Derived from Alice
              Base for other Helpers
              Needs to be derived from person, each helper is not an Alice, but a person.
----------------------------------
 */

class Helper : public Person {
    
    public:
        
        Helper();                 // constructor
        virtual ~Helper();        // destructor
        
        void setHelperName();           // add Helper name to Alice's helper list
        Helper getHelperName() const;   // get Helper from Alice's helper list
        //consider as I what I have done in the Alice class instead
        
        // pure virtual function, derived classes will have unique output
        virtual std::ostream& narrate(std::ostream&) const=0;
    
        // Alice can talk to Helpers in helperList
        // pure virtual function, each helper will have own talkTo();
        virtual void talkTo()=0;
    
        // pure virtual function, each helper will have own
        virtual std::string giveAdvice() const=0;
    
        // output of Helpers Alice has met
        static std::ostream& render(const std::ostream&);
};

// derived class of Helper
class WhiteRabbit : public Helper {
    
    private:
        
        std::string description;        // unique description of White Rabbit
        std::string name;               // name of helper
        Places** appearance;            // list of places where WR can be
        std::string* advice;            // WRs advice for Alice (array)
    
    public:
        
        WhiteRabbit();        // constructor
        ~WhiteRabbit();       // destructor
        
        // output description of White Rabbit
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can talk to White Rabbit
        // Alice input (cin >>) will call giveAdvice();
        void talkTo();
    
        // advice WR can give to Alice
        // depends on Place where they are (appearance == current place)
        std::string giveAdvice() const;
};

// derived class of Helper
class CheshireCat : public Helper {
    
    private:
        
        std::string description;        // unique description of Cheshire Cat
        std::string name;               // name of helper
        Places** appearance;            // list of places where CC can be
        std::string* advice;            // CCs advice for Alice (array)
        
    public:
        
        CheshireCat();        // constructor
        ~CheshireCat();       // destructor
        
        // output description of Cheshire Cat
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can talk to Cheshire Cat
        // Alice input (cin >>) will call giveAdvice();
        void talkTo();
    
        // advice CC can give to Alice
        // depends on Place where they are (appearance == current place)
        std::string giveAdvice() const;
};

// derived class of Helper
class MadHatter : public Helper {
    
    private:
        
        std::string description;        // unique description of Mad Hatter
        std::string name;               // name of helper
        Places** appearance;            // list of places where MH can be
        std::string* advice;            // MHs advice for Alice (array)
        
    public:
        
        MadHatter();        // constructor
        ~MadHatter();       // destructor
        
        // output description of Mad Hatter
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can talk to Mad Hatter
        // Alice input (cin >>) will call giveAdvice();
        void talkTo();
    
        // advice MH can give to Alice
        //depends on Place where they are (appearence == current place)
        std::string giveAdvice(const Places**, const string* advice, const Places**) const;
};

/*
 ----------------------------------
 BadGuy Class: Derived from Alice
               Base for other BadGuys
               I think a badguy is a person
 ----------------------------------
 */

class BadGuy: public Person {
    
    public:
        
        BadGuy();               // constructor
        virtual~BadGuy();       // destructor
        
        void setBadGuyName();             // add BG name to BG list
        BadGuy getBadGuyName() const;     // get BG from BG list
        
        // pure virtual function, derived classes will have unique output
        virtual std::ostream& narrate(std::ostream&) const=0;
    
        // threats BGs pose to Alice
        // depends on Place where they are; each will have unique
        virtual std::string makeThreat() const=0;
    
        // pure virtual function, derived classes will have unique fight()
        virtual void fight()=0;
    
        // output of BadGuys Alice has met
        static std::ostream& render(const std::ostream&);
};

// derived class of BadGuy
class Bandersnatch : public BadGuy {
    
    private:
        
        std::string description;        // unique description of Bandersnatch
        std::string name;               // name of bad guy
        Places** appearance;            // list of places where B can be
        std::string* threat;            // B threat for Alice (array)
        bool friendly;                  // 1 = friend, 0 = not friend
    
    public:
        
        Bandersnatch();        // constructor
        ~Bandersnatch();       // destructor
        
        // output description of Bandersnatch
        std::ostream& narrate(std::ostream&) const;
        
        // threats B poses to Alice (depends on Place where they are)
        std::string makeThreat() const;
    
        // Bandersnatch is BadGuy, but Alice cant't fight him
        void fight();
    
        // If Alice gives Bandersnatch his eye, he will be her friend
        void friendBandersnatch();
};

// derived class of BadGuy
class Jabberwocky : public BadGuy {
    
    private:
        
        std::string description;        // unique description of Jabberwocky
        std::string name;               // name of bad guy
        Places** appearance;            // list of places where J can be
        std::string* threat;            // J threat for Alice (array)
        
    public:
        
        Jabberwocky();        // constructor
        ~Jabberwocky();       // destructor
        
        // output description of Bandersnatch
        std::ostream& narrate(std::ostream&) const;
        
        // threats J poses to Alice (depends on Place where they are)
        std::string makeThreat() const;
        
        // Alice can fight Jabberwocky depending on place, what she has, and health level
        // appearance == current place && list[i] == Sword && health > 2
        void fight();
};

// derived class of BadGuy
class RedQueen : public BadGuy {
    
    private:
        
        std::string description;        // unique description of Red Queen
        std::string name;               // name of bad guy
        Places** appearance;            // list of places where RQ can be
        std::string* threat;            // RQ threat for Alice (array)
        
    public:
        
        RedQueen();        // constructor
        ~RedQueen();       // destructor
        
        // output description of Bandersnatch
        std::ostream& narrate(std::ostream&) const;
        
        // threats RQ poses to Alice (depends on Place where they are)
        std::string makeThreat() const;
        
        // Alice can fight Red Queen depending on place, what she has, and health level
        // appearance == current place && list[i] == whtRose && health > 2
        void fight();
};

/*
 ----------------------------------
 Stuff Class: Derived from Alice
              Base for other Stuff
 ----------------------------------
 */

class Stuff {
    
    protected:
    
        static int size;         // size of list
        static Stuff* list;      // array of Stuff
        static int head;         // index of first element in list
        static int tail;         // index of last element in list
    
    public:
        
        Stuff();                // constructor
        virtual ~Stuff();       // destructor
        
        void setStuffName(const Stuff name);   // add Stuff name to Alice's stuff list
        Stuff getStuffName() const;            // get Stuff from Alice's stuff list
    
        // effects of using stuff
        // pure virtual function each Stuff will have own
        virtual std::string useIt()=0;
    
        // pure virtual function, derived classes will have unique output
        virtual std::ostream& narrate(std::ostream&) const=0;
    
        // output of what Alice has
        static std::ostream& render(const std::ostream&);
};

// derived class of Stuff
class BandersnatchEye : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of Bandersnatch Eye
        
    public:
        
        BandersnatchEye();        // constructor
        ~BandersnatchEye();       // destructor
    
        // effects of using Bandersnatch eye (he becomes a friend)
        std::string useIt();
    
        // output description of BandersnatchEye
        std::ostream& narrate(std::ostream&) const;
};

// derived class of Stuff
class Key : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of Key
        
    public:
        
        Key();        // constructor
        ~Key();       // destructor
    
        // effects of using key on door (it opens)
        std::string useIt();
    
        // output description of Key
        std::ostream& narrate(std::ostream&) const;
};

// derived class of Stuff
class WhiteRose : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of Sword
        
    public:
        
        WhiteRose();        // constructor
        ~WhiteRose();       // destructor
        
        // effects of using white rose on Red Queen (she gets really mad)
        std::string useIt();
        
        // output description of Sword
        std::ostream& narrate(std::ostream&) const;
};

// derived class of Stuff
class Cupcake : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of Cupcake
    
        void wearOff(const int);    // timer so Alice becomes normal (bodySize = 2) automatically?
    
    public:
        
        Cupcake();        // constructor
        ~Cupcake();       // destructor
        
        // output description of Cupcake
        std::ostream& narrate(std::ostream&) const;
    
        // effects of eating cake (becomes tall: bodySize = 3)
        std::string useIt();
};

// derived class of Stuff
class RoadTea : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of RoadTea
        
    public:
        
        RoadTea();        // constructor
        ~RoadTea();       // destructor
        
        // output description of RoadTea
        std::ostream& narrate(std::ostream&) const;
    
        // effects of drinking tea (becomes small: bodySize = 1)
        std::string useIt();
};

// derived class of Stuff
class Sword : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of Sword
        
    public:
        
        Sword();        // constructor
        ~Sword();       // destructor
    
        // effects of using Sword (kills Jabberwocky)
        std::string useIt();
    
        // output description of Sword
        std::ostream& narrate(std::ostream&) const;
};

// derived class of Stuff
class JabberBlood : public Stuff {
    
    private:
        
        bool status;                // if used, status = 0; if not, status = 1
        std::string name;           // name of stuff object
        std::string description;    // description of JabberBlood
        
    public:
        
        JabberBlood();        // constructor
        ~JabberBlood();       // destructor
    
        // effects of drinking JabberBlood (goes Home)
        std::string useIt();
    
        // output description of JabberBlood
        std::ostream& narrate(std::ostream&) const;
};

/*
 ----------------------------------
 Thing Class: Derived from Alice
              Base for other Things
 ----------------------------------
 */

class Thing {

    public:
        
        Thing();            // constructor
        virtual ~Thing();   // destructor
    
        // open thing, depend on Place & Alice's bodySize
        // pure virtual function, each derived will have own
        virtual void openThing()=0;
    
        // output of what Alice has opened (will pass to derived)
        virtual std::ostream& render(const std::ostream&);
};

// derived class of Thing
class Door : public Thing {
    
    private:
    
        bool status;        // status of door: 1 = open, 0 = closed
    
    public:
        
        Door();             // constructor
        ~Door();            // destructor
    
        // open Door to find Chest
        // must be small (bodySize = 1) and must have key
        void openThing();
    
        // effects of openThing()
        std::ostream& render(const std::ostream&);
};

// derived class of Thing
class Chest : public Thing {
    
    private:
        
        bool status;            // status of chest: 1 = open, 0 = closed
        
    public:
        
        Chest();                // constructor
        ~Chest();               // destructor
    
        // open Chest to find Sword
        // must be tall (bodySize = 3)
        void openThing();
    
        // effects of openThing()
        std::ostream& render(const std::ostream&);
};

