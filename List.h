/*
 * Meg Jaffy
 * Khue Le
 *
 * Date: 4/13/18
 * File: List.h
 * -----------------
 * This interface exports a class for representing Python-like List
*/

#ifndef _List_h
#define _List_h

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;

/*
 * Class: List
 * ---------------
 * The List class is used to resemble the Python list class, which can do certain
 * operatations such as append, get length, insert, index, pop, ...
 */

template <typename ValueType>
class List {

public:

/*
 * Constructor: List
 * Usage: List l;
 * ---------------
 * Creates a List object. The default constructor creates a list that
 * has its initial capacity equals to 10.
 */

  List();                                           // default constructor

/*
 * Copy constructor: List
 * Usage: List l;
 * ----------------------
 * Makes a copy of the List object.
 */

  List(const List & src);                          // copy constructor

/*
 * destructor: ~List
 * Usage: (usuallly implicit)
 * --------------------------
 * Frees any help storage associated with this List
 */

  ~List();                                        // destructor

/*
 * Method: append
 * Usage: l.append(value)
 * ---------------------
 * Adds a value to the end of the list
 */

  void append(ValueType value);                 // append a new value to the end of the list

/*
 * Method: length
 * Usage: l.length()
 * ------------------
 * Returns the length of the list
 */

  int length() const;                     // return the length of the list

/*
 * Method: insert
 * Usage: l.insert(index, value)
 * ----------------------------
 * Inserts a value to the list at a give position. If index is out of range, raise
 * an error
 */

  void insert(int index, ValueType value);      // insert value in position index

/*
 * Method: pop
 * Usage: l.pop(index)
 * ----------------------------
 * Removes the value at a given position in the list, and return the value at that given
 * position index. If index is out of range or users attempt to pop an empty list,
 * raise an error
 */

  ValueType pop(int index);                    // remove and return the value at position index

/*
 * Operator: []
 * Usage: l[index]
 * ----------------
 * Return the value at a given position in the list. If index is out of range,
 * raises an error. Also allows user to change value at index.
 */

  ValueType & operator[](int index);        // indexing operator

/*
 * Operator: =
 * Usage: List new_list = l;
 * ------------------------
 * Assign src to the new_list so that the two stacks are independent copies
 */

  List& operator=(const List& src);   // assignment operator

/* Private section */

private:

  struct Node
  {
    Node* prev;
    Node* next;
    ValueType value;
  };

/* Instance variables*/
  Node* head;
  Node* tail;
  int size;

/* Private method prototype*/
void deepCopy(const List<ValueType> & src);
int checkBound(int index);
Node* go2node(int index);

};

template <typename ValueType>
ostream & operator<<(ostream & os, List<ValueType> & l);









/*
 * Implementation section
 * ------------------------
 * Implemented as a DOUBLY-LINKED  list.
 */


 /*
  * Implementation notes: constructor and destructor
  * ------------------------------------------------
  * The construcor initiates a head and tail to NULL and size to 0.
  * The destructor frees any heap memory allocated by the class,
  * by going through and deleting each node of the object.
  */

template <typename ValueType>
List<ValueType>::List()
{
  head=NULL;
  tail=NULL;
  size=0;
}

template <typename ValueType>
List<ValueType>::~List()
{
  Node *curr=head;
  while (curr!=NULL)
  {
    Node*hold=curr->next;
    delete curr;
    curr=hold;
  }
}

template <typename ValueType>
List<ValueType>::List(const List<ValueType>& src)
{
  deepCopy(src);
}



/*
 * Implementation notes: append
 * ----------------------------
 * This function adds a node after the current tail and updates the tail
 * to reflect this change.
 */

template <typename ValueType>
void List<ValueType>::append(ValueType value)
{
  if (head==NULL)//append to empty list
  {
    Node*temp= new Node;
    temp->value= value;
    temp->prev=NULL;
    temp->next=NULL;
    head=temp;
    tail=temp;
    size++;
  }
  else
  {
    Node*temp= new Node;
    temp->value=value;
    temp->next=NULL;
    tail->next=temp;
    temp->prev=tail;
    tail=temp;
    size++;
  }
}



/*
 * Implementation notes: length
 * ----------------------------
 * Check the size of the list. Notes that this leaves the list unchanged
*/
template <typename ValueType>
int List<ValueType>::length() const
{
  return size;
}



/*
 * Implementation notes: insert
 * ----------------------------
 * After bound checking, this function inserts a new node to the list at
 * given index. Afterwards, it updates the previous/next pointers accordingly.
*/
template <typename ValueType>
void List<ValueType>::insert(int index, ValueType value)
{
  if (index==size) append(value);//insert at end of list = append
  else
  {
    index=checkBound(index);
    if (size==0)//insert to empty list
    {
      Node*temp=new Node;
      temp->value=value;
      temp->prev=NULL;
      temp->next=NULL;
      head=temp;
      tail=temp;
      size++;
    }
    else if (index==0)//insert at head
    {
      Node* temp=new Node;
      temp->value=value;
      temp->next=head;
      head->prev=temp;
      temp->prev=NULL;
      head=temp;
      size++;
    }
    else
    {
      Node*temp=new Node;
      temp->value=value;
      Node*curr=go2node(index);
      temp->next=curr;
      temp->prev=curr->prev;
      curr->prev->next=temp;
      curr->prev=temp;
      size++;

    }
  }
}




/*
 * Implementation notes: pop
 * ----------------------------
 * After bound checking, this function deletes the existing node at
 * given index. Afterwards, it updates the previous/next pointers accordingly
*/
template <typename ValueType>
ValueType List<ValueType>::pop(int index)
{
  index=checkBound(index);
  if (size==1)//list with only 1 item
  {
    ValueType value=head->value;
    delete head;
    head=NULL;
    tail=NULL;
    size=0;
    return value;
  }
  if (index==0)//pop head
  {
    Node*temp=head;
    head->next->prev=NULL;
    head=head->next;
    ValueType value =temp->value;
    delete temp;
    size--;
    return value;
  }
  if (index==size-1)//pop tail
  {
    Node*temp=tail;
    tail->prev->next=NULL;
    tail=tail->prev;
    ValueType value =temp->value;
    delete temp;
    size--;
    return value;
  }
  else
  {
    Node*curr=go2node(index);
    ValueType value=curr->value;
    curr->prev->next=curr->next;
    curr->next->prev=curr->prev;
    delete curr;
    size--;
    return value;
  }
}



/*
 * Implementation notes: []
 * ----------------------------
 * Returns by reference the value of the node at a given index.
*/
template <typename ValueType>
ValueType & List<ValueType>::operator[](int index)
{
  index=checkBound(index);
  Node*curr=go2node(index);
  return curr->value;
}


/*
 * Implementation notes: assignment operator
 * ------------------------------------------
 * This method make it possible to pass a List by value or assign one List to
 * another. The actual work is done by the private deepCopy, which represents a
 * useful pattern for designing other classes that need to implement deep
 * copying.
 */
template <typename ValueType>
List<ValueType>& List<ValueType>::operator=(const List<ValueType>& src)
{
  if (this != &src)
  {
    Node *curr=head;
    while (curr!=NULL)
    {
      Node*hold=curr->next;
      delete curr;
      curr=hold;
    }

    deepCopy(src);
  }
  return *this;
}



/*
 * Implementation notes: deepCopy
 * ------------------------------
 * This method copies the data from the src parameter into the current object.
 * All dynamic memory is reallocated to create a "deep copy" in which  the current
 * object and the source object are independent.
 */
template <typename ValueType>
void List<ValueType>::deepCopy(const List<ValueType> & src)
{
  size=src.size;
  head=NULL;
  if (src.head!=NULL)
  {
    head=new Node;
    head->value=src.head->value;
    head->prev=NULL;
    Node*temp=head;
    Node*srctemp=src.head->next;
    while (srctemp!=NULL)
    {
      temp->next=new Node;
      Node*templast=temp;
      temp=temp->next;
      temp->value = srctemp->value;
      srctemp=srctemp->next;
      temp->prev=templast;
      if (srctemp==NULL)
      {
        tail=temp;
        tail->next=NULL;
      }
    }
  }
}


/*
 * Implementation notes: checkBound
 * ------------------------------
 * - Converts negative indexing to normal indexing.
 * - Check bound and raise error when out-of-bound.
 */
template <typename ValueType>
int List<ValueType>::checkBound(int index)
{
  if (index<0) index+=size;
  if (index>=size||index<0)
  {
    cerr<<"index out of range";
  }
  return index;
}


/*
 * Implementation notes: go2node
 * ------------------------------
 * Iterates through the nodes in the fastest way possible
 * returns pointer to node at given index.
 */
template <typename ValueType>
typename List<ValueType>::Node* List<ValueType>::go2node(int index)
{
  if (index<size/2)//node is in first half of list
  {
    Node*curr=head;
    for(int i=0;i<index;++i)
    {
      curr=curr->next;
    }
    return curr;
  }
  else//node is in second half of list
  {
    Node*curr=tail;
    for(int i=0;i<size-index-1;++i)
    {
      curr=curr->prev;
    }
    return curr;
  }
}



/*
 * Implementation notes: <<
 * ------------------------------
 * Allows user to print out a list to cout stream.
 * Form of list: [item1, item2, item3]
 */
template <typename ValueType>
typename std::ostream & operator<<(ostream & os, List<ValueType> & l)
{
  string list="[";

  for (int i=0;i<l.length()-1;++i)
  {
    //convert type char to string
    string ch;
    stringstream ss;

    ss<<l[i];
    ss>>ch;

    //insert each element in list
    list=list+ch+", ";
  }

  string ch;
  stringstream ss;

  ss<<l[l.length()-1];
  ss>>ch;

  list=list+ch+"]";

  os << list;
  return os;
}

#endif
