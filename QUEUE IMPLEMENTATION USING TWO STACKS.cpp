/*
Program: Queue Abstract Data Structure
Author: Dalston J. Karto (Slad)
Description: This program emulates a Queue through the use of two Stacks that are composed as Linked Lists.

Users may add and/or remove items from the Queue
View which item is next in Queue
View all items in Queue
View size of Queue
View the contents of the two Stacks

*/
#include <iostream>
using namespace std;

class TicketItem {
public:
  string personName;
  string reserveCode;
  TicketItem(string personName, string reserveCode) {
    this->personName = personName;
    this->reserveCode = reserveCode;
  }
  void print() {
    cout << endl;
    cout << "------------------------" << endl;
    cout <<  "Name on Ticket: " << personName << endl;
    cout << "Reserve Code: " << reserveCode <<endl;
    cout << "------------------------" << endl;
  }
  ~TicketItem() {
    personName = nullptr;
    reserveCode = nullptr;
  }
};

template <typename T> class Node {
public:
  T *data;
  Node<T> *nextNode;

  Node(T *data) {
    this->data = data;
    nextNode = nullptr;
  }
  void print() { data->print(); }

  ~Node(){
    data = nullptr;
    nextNode = nullptr;
  }
};

template <typename T> class LLStack {
const int S_MAX_ITEMS = 20;
public:  
  Node<T> *top;
  int stackSize;
  // Constructor
  LLStack() {
    top = nullptr;
    stackSize = 0;
  }
  LLStack(T *data) {
    Node<T> *newNode = new Node<T>(data);
    top = newNode;
    stackSize = 1;
  }
  // Destructor
  ~LLStack() {
    Node<T> *temp = top;
    while (temp) {
      top = top->nextNode;
      delete temp;
      temp = top;
    }
  }

  void printLLStack() {
    Node<T> *temp = top;
    while (temp) {
      temp->print();
      temp = temp->nextNode;
    }
  }

  bool isFull() {
    return stackSize == S_MAX_ITEMS;
  }

  bool isEmpty() {
    return stackSize == 0;
  }

  void push(T *data) {
    Node<T> *newNode = new Node<T>(data);
    if (stackSize == 0) {
      top = newNode;
    }
    else {
      newNode->nextNode = top;
      top = newNode;
    }
    stackSize++;
  }

  void pop() {
    Node<T> *temp = top;
    if (stackSize == 0) {
      return;
    }
    if (stackSize == 1) {
      top = nullptr;
      stackSize--;
    } else {
      top = top->nextNode;
      delete temp;
      stackSize--;
    }
  }
  T *peek() {
      if (top == nullptr) {
      cout << "QUEUE EMPTY" << endl;
    } else {
      top->print();
    }
    return top->data;
  }
};

template <typename T> class StackQ {
  const int Q_MAX_ITEMS = 20;
public:
  LLStack<T> *enQStack;
  LLStack<T> *deQStack;
  int queueSize;
  StackQ() {
    enQStack = new LLStack<T>();
    deQStack = new LLStack<T>();
    queueSize = 0;
  }
  StackQ(T *data) {
    enQStack = new LLStack<T>(data);
    deQStack = new LLStack<T>();
    queueSize = 1;
  }
  ~StackQ() {
    delete enQStack;
    delete deQStack;
    queueSize = 0;
  }
  bool isFull() {
    return queueSize == Q_MAX_ITEMS;
  }
  bool isEmpty() {
    return queueSize == 0;
  }

  void enqueue(T *qData) {
    if (enQStack->isEmpty() && deQStack->isEmpty()) {
      enQStack->push(qData);
      queueSize = 1;
    } else {
      enQStack->push(qData);
      queueSize++;
    }
  }
  void dequeue() {
     if (deQStack->isEmpty()) {
      while ( !(enQStack->isEmpty()) ) {
        T* moveData = enQStack->top->data;
        deQStack->push(moveData);
        enQStack->pop();
      }
      deQStack->pop();
      queueSize--;
    }
    else {
      deQStack->pop();
      queueSize--;
    }
  }

  T *peek() {
    if (deQStack->isEmpty() && !(enQStack->isEmpty())) {
      T* tempPeek;
      while ( !(enQStack->isEmpty()) ) {
        T* moveData = enQStack->top->data;
        deQStack->push(moveData);
        enQStack->pop();
      }
      tempPeek = deQStack->peek();
      while ( !(deQStack->isEmpty()) ) {
        T* moveData = deQStack->top->data;
        enQStack->push(moveData);
        deQStack->pop();
      }
      return tempPeek;
    }
    else{
      return deQStack->peek();
    } 
  }

  void printStackQ() {
    if (deQStack->isEmpty() && !(enQStack->isEmpty()) ) {
        while (!(enQStack->isEmpty())) {
            T* moveData = enQStack->top->data;
            deQStack->push(moveData);
            enQStack->pop();
        }
        deQStack->printLLStack();
        while ( !(deQStack->isEmpty()) ) {
            T* moveData = deQStack->top->data;
            enQStack->push(moveData);
            deQStack->pop();
      }
      }
    else {
      LLStack<T> *tempStack = new LLStack<T>();
      while ( !(enQStack->isEmpty()) ) {
            T* moveData = enQStack->top->data;
            tempStack->push(moveData);
            enQStack->pop();
        }
        deQStack->printLLStack();
        tempStack->printLLStack();

      while ( !(tempStack->isEmpty()) ) {
            T* moveData = tempStack->top->data;
            enQStack->push(moveData);
            tempStack->pop();
      }
    }        
  }
};

// Main Program
int main() {
  char userChoice = ' ';
  string personName;
  string reserveCode;
  TicketItem* newTicket;
  StackQ<TicketItem> *TicketQueue = new StackQ<TicketItem>();

  cout << "Welcome to the Ticket Queue System!" << endl;
  
  while(userChoice != 'g'){
    cout << "Please select an option from the Menu by pressing the corresponding key: " << endl << endl;
    cout << "a. Add Item to ticket queue" << endl;
    cout << "b. Delete from ticket queue" << endl;
    cout << "c. Peek from the ticket queue" << endl;
    cout << "d. Display the ticket queue" << endl;
    cout << "e. Display ticket queue size" << endl;
    cout << "f. Display enQStack and deQStack" << endl;
    cout << "g. Exit" << endl;

    cin >> userChoice;

    switch(userChoice){
      case 'a':
        if (TicketQueue->isFull()) {
          cout << endl << "ERROR QUEUE OVERFLOW. QUEUE IS FULL. PLEASE DEQUEUE TICKETS" << endl << endl;
          break;
        }
        else{
          cout << endl << "Please enter the Name: " << endl;
          cin >> personName;
          cout << endl << "Please enter the Reserve Code: " << endl;
          cin >> reserveCode;
          newTicket = new TicketItem(personName, reserveCode);
          TicketQueue->enqueue(newTicket);
          cout << endl << "Ticket has been added to queue." << endl << endl;
          break;
        }
        
      case 'b':
        if (TicketQueue->isEmpty()) {
          cout << endl << "ERROR QUEUE UNDERFLOW. QUEUE IS EMPTY. THERE ARE NO TICKETS IN QUEUE" << endl << endl;
          break;
        }
        else{
          cout << endl << "This ticket has been removed from queue: ";
          TicketQueue->peek();
          TicketQueue->dequeue();
          cout << endl;
          break;
        }
        
      case 'c':
        if (TicketQueue->isEmpty()) {
          cout << endl << endl << "THERE ARE NO TICKETS IN QUEUE" << endl;
          break;
        }
        else{
          cout << endl << endl << "Next ticket in queue: ";
          TicketQueue->peek();
          cout << endl;
          break;
        }

      case 'd':
        if (TicketQueue->isEmpty()) {
          cout << endl << endl << "THERE ARE NO TICKETS IN QUEUE" << endl;
          break;
        }
        else{
          cout << endl << "In Queue: ";
          TicketQueue->printStackQ();
          cout << endl;
          break;
        }
        
      case 'e':
        cout << endl;
        cout << "Current Queue size: " << TicketQueue->queueSize << endl;
        break;

      case 'f':
        cout << endl;
        cout << "enQStack: "; 
        TicketQueue->enQStack->printLLStack();
        cout << endl;
        cout << "deQStack: ";
        TicketQueue->deQStack->printLLStack();
        cout << endl;
        break;

      case 'g':
        cout << endl;
        cout << "Thank you for using Ticket Queue System. Goodbye!" << endl;
        break;

      default:
        cout << endl;
        cout << "Invalid Menu Option. Please try again." << endl << endl;      
    }
  }
}
