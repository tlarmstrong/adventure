// wonderlandAdventure.h
#include <iostream>

// base class
class Alice {
    
    friend Places;      // friend classes to update lists / size
    friend Stuff;
    friend Helper;
    
    private:
    
        // prevent value semantics (there can only be one Alice)
    
        Alice(const Alice& other);              // copy constructor
        void operator = (const Alice& other);   // assignment operator (copy)
    
        Places** placeList;      // list of where Alice has been
        Helper** helperList;     // list of people with Alice
        Stuff** stuffList;       // list of what Alice has
        
        int size;                // size of Alice (small(1), normal(2), big(3))
    
    public:
    
        Alice();                // constructor
        virtual~Alice();        // destructor
};

// base class
class Places {
    
    public:
    
        Places();               // constructor
        virtual~Places();       // destructor
    
        void setPlaceName(const Places name);   // add place name to Alice's list of places
        Places getPlaceName() const;            // get place from Alice's list of places
    
        // pure virtual function, derived classes will have unique output
        virtual std::ostream& narrate(std::ostream&) const=0;

        // virtual function, if called, will show all places Alice has been
        virtual std::string action(const std::string);
};

// derived class of Places
class Tree : public Places {
    
    private:
    
        // unique description of Tree (Alice wakes up under a tree...)
        std::string description;
        
    public:
        
        Tree();             // constructor
        ~Tree();            // destructor
    
        // output unique description of Tree place
        std::ostream& narrate(std::ostream&) const;
    
        // what Alice can do (input = follow white rabbit) / returns result of action
        std::string action(std::string);
};

// derived class of Places
class Garden : public Places {
    
    private:
    
        std::string description;    // unique description of Garden
        Helper WhiteRabbit;         // helps Alice, gives advice and intros to Mad Hatter
        BadGuy Bandersnatch;        // tries to capture Alice
        Stuff BandersnatchEye;          // Dormouse takes and gives to Alice
    
    public:
        
        Garden();       // constructor
        ~Garden();      // destructor
    
        // output description of Garden
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can talk to White Rabbit, he will be auto added to her helperList
        void talkTo(const Helper);
    
        // Alice can take Bandersnatch eye from Dormouse (add to stuffList)
        void addTo(const Stuff);
    
        // what Alice can do (input = run to woods) / returns result of action
        std::string action(const std::string);
};

// derived class of Places
class Woods : public Places {
    
    private:
    
        std::string description;        // unique description of Woods
        Stuff Key;                      // thing Alice can add to stuffList
        Helper CheshireCat;             // helps Alice, gives advice
    
    public:
        
        Woods();        // constructor
        ~Woods();       // destructor
    
        // output description of Woods
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can add the key to her stuffList
        void addTo(const Stuff);
    
        // Alice can talk to the Cheshire Cat (auto added to helperList)
        void talkTo(const Helper);
    
        // what Alice can do (input = go to tea party) / returns result of action
        std::string action(const std::string);
};

// derived class of Places
class TeaParty : public Places {
    
    private:
    
        std::string description;        // unique description of TeaParty
        Helper MadHatter;               // helper who gives advice
        Stuff Cupcake;                  // = cupcake | thing Alice can add to stuffList
        Stuff RoadTea;                  // = roadTea | thing Alice can add to stuffList
    
    public:
        
        TeaParty();        // constructor
        ~TeaParty();       // destructor
    
        // output description of TeaParty
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can add cupcake and roadTea to stuffList;
        void addTo(const Stuff);
    
        // Alice can talk to the Mad Hatter (auto add to helperList)
        void talkTo(const Helper);
    
        // what Alice can do (input = go to White Queen's Castle)
        // returns result of action (abducted by Red Queen's men, take to her Castle instead)
        std::string action(const std::string);
};

// derived class of Places
class Castle : public Places {
    
    private:
    
        std::string description;        // unique description of Castle
        BadGuy RedQueen;                // badGuy who wants to hurt Alice
        Stuff Sword;                    // = sword | thing Alice can add to stuffList
    
    public:
        
        Castle();        // constructor
        ~Castle();       // destructor
        
        // output description of Castle
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can add sword to list
        void addTo(const Stuff);
    
        // Alice can eat her cupcake
        void drinkTea(const Stuff**);
    
        // Alice can drink her roadTea
        void eatCake(const Stuff**);
    
        void friendBandersnatch(const Stuff);
    
        // Alice can talk to Helpers already in list / BadGuys
        template <class T>
        void talkTo(const T);
    
        // what Alice can do (input = get ready for battle)
        std::string action(const std::string);
};

// derived class of Places
class Battlefield : public Places {
    
    private:

        std::string description;        // unique description of Battlefield
        BadGuy Jabberwocky;             // badGuy who wants to hurt Alice
    
    public:
        
        Battlefield();        // constructor
        ~Battlefield();       // destructor
    
        // output description of Battlefield
        std::ostream& narrate(std::ostream&) const;
    
        // Alice can get her sword
        void useStuff(std::string* stuffList);
    
        // Alice can fight the Jabberwocky
        void fight(BadGuy);
    
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

// base class
class Helper {
    
    public:
        
        Helper();               // constructor
        virtual~Helper();       // destructor
        
        void setHelperName(const Helper name);  // add stuff name to Alice's list of stuff
        stuff getHelperName() const;            // get stuff from Alice's list of stuff
        
        // pure virtual function, derived classes will have unique output
        virtual std::ostream& narrate(std::ostream&) const=0;
};

class WhiteRabbit : public Helper {
    
};

class CheshireCat : public Helper {
    
};

class MadHatter : public Helper {
    
};


// base class
class Stuff {
    
};

