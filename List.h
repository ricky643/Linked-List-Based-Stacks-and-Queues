/*
 * Ricardo Varona:
 * Date Submitted: 9/9/2023
 * Lab Section: 1
 * Assignment Name: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
    start = nullptr; 
    mySize = 0;

}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){

    Node<T> *garbage = start;
    while (garbage != nullptr) {
        // front points to next node
        start = start->next;
        //garbage points to next which  is null
        garbage->next = nullptr;
        delete garbage;
        //resets garbage back to front
        garbage = start;
    }
    
}

//Return the size of this list
template <class T>
int List<T>::size(){
    return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
    bool list;
    // determins if list is empty or not based on mySize variable
    if(mySize == 0) {
        list = true;
    }
    else {
        list = false;
    }
    return list;

}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
    // new node is created
    Node<T> *newNode = new Node<T>(value);
    // newNode needs to be inserted before start, so start is the node next to newNode
    newNode->next = start;
    // newNode is now the start
    start = newNode;
    // needs to set the next node to null pointer
    mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
    // creates newNode and allocates memory space for it
    Node<T> *newNode = new Node<T>(value);
    // tempNode created, allow temp to be updated while head stays the same
    Node<T> *tempNode;
    if(start == nullptr) {
        // since there is no nodes, there is no end, so a node is created and mySize is incremented
        newNode->next = start;
        start = newNode;
        mySize++;
    }
    // else not empty, check each node until you get to the end
    else { 
        tempNode = start;
        // updates temp to point to the next node until it is null
        while(tempNode->next != nullptr) {
            tempNode = tempNode->next;
        }
        // once the last node is found, points to newNode and and ads it to the end of the list;
        tempNode->next = newNode;
        mySize++;
    }
}


//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
    // creates newNode and allocates memory space for it
    Node<T> *newNode = new Node<T>(value);
    // tempNode created, allows temp to be updated while head stats the same
    Node<T> *tempNode;
    tempNode = start; 
    // temp will update for j amount of times, assuming j is the postion the node is supposed to be inserted
    if(j == 0) {
        // creates a newnode before the start
        newNode->next = start;
        start = newNode;
        mySize++;
    }
    // else, will iterate through each node until it gets to the node before j,
    else {
        for(int i = 0; i < j - 1; i++) {
            tempNode = tempNode->next;
        }
        // Since it has found the node before J, newNode is next, then temp takes the place of next
        newNode->next = tempNode->next;
        // then the node after that is the new node which is J, then increments mySize;
        tempNode->next = newNode;
        mySize++;
        // once j position is found, poitns to newNode and ads it to the end of the list
    }
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
    Node<T> *tempNode;
    tempNode = start;
    // if there is no nodes, deletes start
    if(mySize == 0) {
        delete start;
    }
    // if there are multiple nodes, looks at next node, then deletes tempNode which has original start value
    else if (mySize > 1) {
        start = start->next;
        delete tempNode;
        mySize--;
    }
    // else, if mySize == 1, set start to nullptr, since tempnode has original start value, delete tempNode
    else if(mySize == 1) {
        start = nullptr;
        delete tempNode;
        mySize--;
    }
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
    // tempNode created, allow temp to be updated while head stays the same
    Node<T> *tempNode;
    Node<T> *previousNode;
    tempNode = start;

    bool loopGoing = true; 

    // if there are no nodes, returns nothing
    if(start == nullptr) {
        return;
    }
    // only one node, since there is only one one, removing end is the same as removing start
    else if (start->next == nullptr) {
        delete start;
        start = nullptr;
        mySize--;
    }
    // goes until it finds the last nost, then sets tempnode = to that node 
    else {
        while(tempNode->next != nullptr) {
            previousNode = tempNode; 
            tempNode = tempNode->next; 
        }
        // deletes tempNode then sets the previous node to null to effectively get rid of thr last node. Decrements mySize
        delete tempNode;
        previousNode->next = nullptr; 
        mySize--;
    }
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
    // tempNode created, allows temp to be updated while head stats the same
    Node<T> *previousNode;
    Node<T> *tempNode;
    previousNode = start;
    // if there are no previousNode, returns nothing
    if(previousNode == nullptr) {
        return;
    }
    // if only one node, immidiatly removes it
    else if(j == 0) {
        removeStart();
    }
    else {
        for(int i = 0; i < j - 1; i++) {
            // finds the node before j
            previousNode = previousNode->next;
        }
        // Since the node before j was found, set tempNode = to the next node which is j
        tempNode = previousNode->next;
        previousNode->next = tempNode->next; 
        // then delete tempNode and update size;
        delete tempNode;
        mySize--;        
    }
    // once j position is found, poitns to newNode and ads it to the end of the list
}



//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
   if(start == nullptr) {
       return T();
   }
   return start->value;
   

}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
    Node<T> *tempNode;
    tempNode = start;
    if(start == nullptr) {
        return T(); 
    }

    // updates temp to point to the next node until it is null
    while(tempNode->next != nullptr) {
        tempNode = tempNode->next;
    }
    return tempNode->value;
    
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
    Node<T> *tempNode;
    tempNode = start;
    if(start == nullptr) {
        return T();
    }
    // temp will update for j amount of times, assuming j is the postion the node is supposed to be inserted
        for(int i = 0; i < j; i++) {
            tempNode = tempNode->next;
        }
        return tempNode->value;
    }

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){
   Node<T> *tempNode;
   tempNode = start;
   int position = 0;
   if(start == nullptr) {
       return -1;
   }
   // while not null ptr
   while(tempNode->next != nullptr) {
       // if the key and the value match, will return position
       if(tempNode->value == key) {
           return position; 
           
       }
       // updates position each iteration of while loop
       tempNode = tempNode->next;
       position++;
   }
   // get to end of linked list and found no match, so return -1
   return -1;
}
