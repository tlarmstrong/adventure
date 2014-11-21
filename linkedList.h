// linkedList.h

#include <cstddef>
#include <iostream>

template <class T>          // struck Node<T>
struct Node                 // one node in list; "Node" means Node<T>
{
    T element;
    Node<T>* next;
    Node<T>* prev;
};

template <class T>          // class List<T>
class List                  // a List of Nodes; "List" means List<T>
{
    
private:
    
    Node<T>* head;          // pointer to first Node
    
public:
    
    List();                 // constructor
    ~List();                // destructor
    
    void push(const T& value);               // appends element to end of array
    T pop(const T& value);                   // removes and returns element from array
    T pop();                                // removes first element

    T peek(const int& num) const;					//peeks at the num'th element in the list
    
    // copy elements from one list to another
    void copyList(const List<T>& from);
    
    // copy constructor for assignment operator // this is not the copy constructor, it is the assignment operator.
    List<T>& operator = (const List<T>& other);
    
    bool isEmpty() const;                   // returns true if array is empty
    int getSize() const;                    // returns the number of elements in array
    bool contains(const T& value) const;     // lets us know if a value is in a list
};

template <class T>
List<T>::List()             // no-arg constructor
{
    head = NULL;            // first link point to NULL
}

template <class T>
List<T>::~List()
{
    if( head == NULL )                  // emtpy list
        return;                         // nothing to do
    
    //if not empty, break the circular list
    head->prev->next = NULL;
    Node <T>* walker = head;
    
    // "walk" through the list and destroy each node
    while(walker != NULL)
    {
        Node <T>* rmove = walker;	//remove was highlighted, so I wasn't sure if it was a keyword or not.
        walker = walker->next;
        delete rmove;
    }
    
    head = NULL;
}

template <class T>
void List<T>::push(const T& value)
{
    // allocate new node and set value
    Node<T>* n = new Node<T>;
    n->element = value;
    
    // if first element, set pointers to self
    if(head == NULL)
    {
        head = n;
        head->prev = head;
        head->next = head;
    }
    
    // otherwise, set pointers to nodes before and after it
    else
    {
        n->next = head;
        n->prev = head->prev;
        head->prev->next = n;
        head->prev = n;
    }
}

// pop specific value
template<class T>
T List<T>::pop(const T& value)
{
    T popped;                   // return variable
    
    if(contains(value))         // check if list contains the value
    {
        // create a walker node and set to head
        Node <T>* walker = head;
        
        // if head's element equals the specified value and list has only one node	//something to think about: What does it mean for a place to be equal to a place? I don't think the computer knows that. It does know what it means for a pointer to be equal to another pointer. I think that if all our lists are lists of pointers we should be fine (they probably should be anyway). Thus we need to be careful to always pass by reference because a copy will have a different address.
        if(head->element == value && getSize() == 1)
        {
            popped = head->element; // assign value to return variable
            delete head;            // since it is the only value in the list, delete head
            head = NULL;
        }
        
        // otherwise, look for the value
        else
        {
            // if walker's next node is the head, this means we've returned to the beginning
            while(walker->next != head)
            {
                if(walker->element == value)
                {
                    popped = walker->element;           // if found, assign to return variable
                    
                    Node<T>* rmove = walker;           // create a node pointer to remove //was highlighted, not sure if key word
                    Node<T>* newWalker = walker->next;  // create a node pointer to next
                    newWalker->prev = walker->prev;     // reposition pointers
                    walker->prev->next = newWalker;
                    
                    delete rmove;                      // delete rmove node
                }
                
                // if not found, keep "walking"
                walker = walker->next;
            }
        }
    }
    return popped;
}

// pop without arguments
template<class T>
T List<T>::pop()
{
    T popped;                   // return variable
    
    // create a walker node and set to head
    Node <T>* walker = head;
    // what if list is empty? I suppose we cannot do anything about that. It could be a try throw catch thing, but we could just remember to make sure it is not empty before calling.
    // if list has only one node
    if(getSize() == 1)
    {
        popped = head->element; // assign value to return variable
        delete head;            // since it is the only value in the list, delete head
        head = NULL;
    }
    
    // otherwise, return first element and reposition pointers
    else
    {
        popped = walker->element;           // assign head to return variable
        
        Node<T>* rmove = walker;           // create a node pointer to remove
        Node<T>* newWalker = walker->next;  // create a node pointer to next
        newWalker->prev = walker->prev;     // reposition pointers
        walker->prev->next = newWalker;
        
        delete rmove;                      // delete remove node
    }
    return popped;
}

// look at element in list without removing node
/*template <class T>
T List<T>::peek()
{
    T nodeReturn = pop();         // remove first value from list	//don't forget the type of nodereturn	//also if list is empty?
    push(nodeReturn);           // add node onto back of list
    
    return nodeReturn;          // return the node//this is neither a string which you said you would return nor a node. it is a T element, otherwise your code is good. also node return isn't a node, it is a T. Look at your return type of pop.
}
*/

template <class T>
T List<T>::peek(const int& num) const
{
    Node<T>* walker = head;
    Node<T>* returnVal = nullptr;
    
    if(num <= getSize())
    {
        for (int i = 0; i < num; i++)
        {
            walker = walker->next;
        }
        returnVal = walker->element;
    }
    
    return returnVal;
}

// copy elements from one list to another
template<class T>
// copy constructor for assignment operator	//not copy constructor, but assignment operator. Be careful, we could assign to a list that already has stuff in it. We need to delete that stuff first
List<T>& List<T>::operator = (const List<T>& other)
{
    // check if assigning List to self
    if(this == &other)
        return *this;
    
    for (int i = 0; i < getSize(); i++){	//empties list
        pop();
    }
    
    // make deep copy from other list to new list
    for(int i = 0; i < other.getSize(); i++)
    {
        push(other.peek(i));		//be careful about filling a list with just the first element of the new list
    }
    
    return *this;
}

template <class T>
bool List<T>::isEmpty() const
{
    // list is empty if 1st node (head) is null
    return (head == NULL);
}

template <class T>
int List<T>::getSize() const
{
    int count = 0;
    
    // Handle empty list as special case
    if( head == NULL )
        return count;
    
    else
    {
        // temporarily break the circular list
        //head->prev->next = NULL;
        Node <T>* walker = head;
        
        while(walker != head && count != 0)
        {
        // "walk" through list and count nodes		//I see why you broke the list instead of saying while not equal to head, since it starts with walker equal to head. another way to do it would include && count!=0
            while(walker != NULL)
            {
                walker = walker->next;
                count++;
            }
        }
        
        // make the list circular again
        //head->prev->next = head;
    }
    return count;
}

template <class T>
bool List<T>::contains(const T& value) const
{
    Node <T>* walker = head;
    
    // search for the value as long as walker does not equal the specified value
    // and walker's next pointer does not point to head pointer
    while(walker->element != value && walker->next != head)
    {
        walker = walker->next;
    }
    
    // if found, return true
    if(walker->element == value)
        return true;
    
    // otherwise, return false
    return false;
}
