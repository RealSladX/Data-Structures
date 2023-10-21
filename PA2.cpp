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
    cout << "Name on Ticket: " << personName << " " << endl;
    cout << "Reserve Code: " << reserveCode << " " << endl;
  }
  ~TicketItem() {
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
  
public:
  const int Q_MAX_ITEMS = 20;
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
    if (queueSize == Q_MAX_ITEMS) {
      return true;
    } else {
      return false;
    }
  }
  bool isEmpty() {
    if (queueSize == 0) {
      return true;
    } else {
      return false;
    }
  }

  void enqueue(T *qData) {
    if (enQStack->isFull()) {
      cout << "ERROR QUEUE OVERFLOW. PLEASE DEQUEUE TICKETS" << endl;
      return;
    } else if (enQStack->isEmpty()) {
      enQStack->push(qData);
      queueSize = 1;
    } else {
      enQStack->push(qData);
      queueSize++;
    }
  }
  void dequeue() {
    if (queueSize == 0) {
      cout << "ERROR QUEUE UNDERFLOW. THERE ARE NO TICKETS IN QUEUE" << endl;
      return;
    } else if (deQStack->isEmpty()) {
      while (enQStack->isEmpty() == false) {
        T* moveData = enQStack->top->data;
        deQStack->push(moveData);
        enQStack->pop();
      }
      deQStack->pop();
      queueSize--;
    } else {
      deQStack->pop();
      queueSize--;
    }
  }
  T *peek() {
    if (deQStack->isEmpty() && !(enQStack->isEmpty())) {
      while (!(enQStack->isEmpty())) {
        T* moveData = enQStack->top->data;
        deQStack->push(moveData);
        enQStack->pop();
      }
      return deQStack->peek();
    }
    else{
      return deQStack->peek();
    }
      
    
  }
  void printStackQ() {
    LLStack<T> *tempStack = new LLStack<T>();
    Node<T> *temp = deQStack->top;
    Node<T> *temp2 = tempStack->top;
    if (deQStack->isEmpty()) {
        while (!(enQStack->isEmpty())) {
            T* moveData = enQStack->top->data;
            deQStack->push(moveData);
            enQStack->pop();
        }
    }
    else{
      while (!(enQStack->isEmpty())) {
            T* moveData = enQStack->top->data;
            tempStack->push(moveData);
            enQStack->pop();
        }
    }
      while (temp) {
        temp->print();
        temp = temp->nextNode;
      }
      while (temp2) {
        temp2->print();
        temp2 = temp2->nextNode;
      }
    while ( !(tempStack->isEmpty()) ) {
            T* moveData = tempStack->top->data;
            enQStack->push(moveData);
            tempStack->pop();
        }  
    
}
};

// Main Program
int main() {
  char userChoice = 'y';
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
        cout << "Please enter the Name and the Reserve Code for the ticket you would like to add: " << endl;
        cin >> personName;
        cin >> reserveCode;
        newTicket = new TicketItem(personName, reserveCode);
        TicketQueue->enqueue(newTicket);
        break;
      case 'b':
        TicketQueue->dequeue();
        break;
      case 'c':
        cout << "Next in queue: ";
        TicketQueue->peek();
        cout << endl;
        break;
      case 'd':
        cout << "In Queue: " << endl;
        TicketQueue->printStackQ();
        break;
      case 'e':
        cout << "Current Queue size: " << TicketQueue->queueSize << endl;
        break;
      case 'f':
        cout << "enQStack: "; 
        TicketQueue->enQStack->printLLStack();
        cout << endl;
        cout << "deQStack: ";
        TicketQueue->deQStack->printLLStack();
        break;
      case 'g':
        cout << "Thank you for using Ticket Queue System. Goodbye!" << endl;
      case 'y':
      break;
      default:
        cout << "Invalid Menu Option. Please try again." << endl;      
    }
  }

}
