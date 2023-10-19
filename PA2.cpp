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

    cout << personName << " " << endl;
    cout << reserveCode << " " << endl;
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

//LinkedList Class : Container for Nodes
template <typename T> class LLStack {
private:
  Node<T> *top;
  int stackSize;
  const int S_MAX_ITEMS = 10;
public:
//Constructor
  LLStack(T *data) {
    Node<T> *newNode = new Node<T>(data);
    top = newNode;
    stackSize = 1;
  }

//Destructor
  ~LLStack() {
    Node<T> *temp = top;
    while (top) {
      top = top->nextNode;
      delete temp;
      temp = top;
    }
  }

  void printLLStack() {
    Node<T> *temp = top;
    while (temp != nullptr) {
      temp->print();
      temp = temp->nextNode;
    }
  }

  bool IsFull(){
    if(stackSize == S_MAX_ITEMS){
      return true;
    }
    else {return false;}
  }

  bool IsEmpty(){
    if(stackSize == 0){
      return true;
    }
    else {return false;}
  }

  void push(T *item){
    Node<T> *newNode = new Node<T> (item);
    if (stackSize == 0){
      top = newNode;
    }else{
      newNode->nextNode = top;
      top = newNode;
    }
    stackSize++;
  }

  void pop (){
    if (stackSize == 0){
      return;
    }
    Node<T> *temp = top;
    if(stackSize == 1){
      top == nullptr;
    }
    else {
      head = head->nextNode;
    }
    delete temp;
    stackSize--;
  }

  Node<T> *peek(){
    if (top == nullptr){
      cout << "Top: nullptr" << endl;
    }
    else{
      cout << "Top: " << top->value << endl;
    }
    return top;
  }

};

template <typename T> class StackQ{
  public:
  LLStack* enQStack;
  LLStack* deQStack;
  int queueSize;
  const int Q_MAX_ITEMS = 10;

  bool IsFull(){
    if(queueSize == Q_MAX_ITEMS){
      return true;
    }
    else {return false;}
  }

  bool IsEmpty(){
    if(queueSize == 0){
      return true;
    }
    else {return false;}
  }
};



//Main Program

int main() {
//creating data object
  TicketItem *ticket1 = new TicketItem("Slad", "123");
  TicketItem *ticket2 = new TicketItem("Student", "456");
  TicketItem *ticket3 = new TicketItem("Customer", "789");

//Creating Linked List
  
  LLStack<TicketItem> *llstack1 = new LLStack<TicketItem>(ticket1);
  llstack1->push(ticket2);
  llstack1->push(ticket3);
//Calling operations on Linked List
  
  llstack1->printLLStack();


  return 0;
}