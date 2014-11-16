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
    
    void push(const T value);               // appends element to end of array
    T pop(const T value);                   // removes and returns element from array
    T pop();                                // removes first element
    std::string peek();                     // returns element
    
    // copy elements from one list to another
    void copyList(const List<T>& from);
    
    // copy constructor for assignment operator
    List<T>& operator = (const List<T>& other) const;
    
    bool isEmpty() const;                   // returns true if array is empty
    int getSize() const;                    // returns the number of elements in array
    bool contains(const T value) const;     // lets us know if a value is in a list
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
        Node <T>* remove = walker;
        walker = walker->next;
        delete remove;
    }
    
    head = NULL;
}

template <class T>
void List<T>::push(const T value)
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

template<class T>
T List<T>::pop(const T value)
{
    T popped;                   // return variable
    
    if(contains(value))         // check if list contains the value
    {
        // create a walker node and set to head
        Node <T>* walker = head;
        
        // if head's element equals the specified value and list has only one node
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
                    
                    Node<T>* remove = walker;           // create a node pointer to remove
                    Node<T>* newWalker = walker->next;  // create a node pointer to next
                    newWalker->prev = walker->prev;     // reposition pointers
                    walker->prev->next = newWalker;
                    
                    delete remove;                      // delete remove node
                }
                
                // if not found, keep "walking"
                walker = walker->next;
            }
        }
    }
    return popped;
}

template<class T>
T List<T>::pop()
{
    T popped;                   // return variable
    
    // create a walker node and set to head
    Node <T>* walker = head;
    
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
                
        Node<T>* remove = walker;           // create a node pointer to remove
        Node<T>* newWalker = walker->next;  // create a node pointer to next
        newWalker->prev = walker->prev;     // reposition pointers
        walker->prev->next = newWalker;
        
        delete remove;                      // delete remove node
    }
    return popped;
}

// look at element in list without removing node
template <class T>
std::string List<T>::peek()
{
    nodeReturn = pop();         // remove first value from list
    push(nodeReturn);           // add node onto back of list
    
    return nodeReturn->element;          // return the node
}

// copy elements from one list to another
template<class T>
// copy constructor for assignment operator
List<T>& List<T>::operator = (const List<T>& other) const
{
    // check if assigning List to self
    if(this == &other)
        return *this;
    
    // make deep copy from other list to new list
    for(int i = 0; i < other.getSize(); i++)
    {
        push(other.peek());
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
        head->prev->next = NULL;
        Node <T>* walker = head;
        
        // "walk" through list and count nodes
        while(walker != NULL)
        {
            walker = walker->next;
            count++;
        }
        
        // make the list circular again
        head->prev->next = head;
    }
    return count;
}

template <class T>
bool List<T>::contains(const T value) const
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