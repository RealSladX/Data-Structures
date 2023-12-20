#include <iostream>
using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
    int value;
    string name;
    Data(int value, string name) {
        this->value = value;
        this->name = name;
    }
    void print() {

        cout << value << " " << endl;
        cout << name << " " << endl;
    }
    bool compareData(Data* d2)
    {
       // cout<<"Comparing "<<this->value<<" and "<<d2->value<<endl;
       // cout<<"Comparing "<<this->name<<" and "<<d2->name<<endl;
        if((this->value==d2->value)&&(this->name==d2->name)) {

            return true;
        }
        else return false;
    }
    bool compareKey(Data* d2)
    {
       // cout<<"Comparing "<<this->value<<" and "<<d2->value<<endl;
        if((this->value>d2->value))
            return true;
        else return false;
    }
};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
    T *value;
    Node<T> *next;
    Node<T> *prev;
    Node(T *value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
    void print() { value->print(); }

};

template <typename T> class DoubleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
    // Constructor
    DoubleLinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    DoubleLinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    // Destructor
    ~DoubleLinkedList() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            temp->print();
            temp = temp->next;
        }
    }

    // get and set
    Node<T> *getHead() {
        if (head == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << head->value << endl;
        }
        return head;
    }

    Node<T> *getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() {
        cout << "Length: " << length << endl;
        return length;
    }
    bool compareData(T* d1, T* d2)
    {
       // cout<<"Inside LL Class compare"<<endl;
       bool result = d1->compareData(d2);
      // cout<<"Result is: "<< result<<endl;
       return result;
    }
    bool compareKey(T* d1,T* d2)
    {
        return d1->compareKey(d2);
    }
    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

    // All insert methods
    // Insert at end
    void append(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }

    // Insert at beginning

    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    // Insert at Index

    bool insert(int index, T *value) {
        if (index < 0 || index > length)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *prev1 = get(index - 1);
        Node<T> *next1 = prev1->next;
        newNode->prev = prev1;
        newNode->next = next1;
        prev1->next = newNode;
        next1->prev = newNode;
        length++;
        return true;
    }

    // All delete Methods
    //delete head
    void deleteHead() {
        if(head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            if(head != nullptr)
                head->prev = nullptr;
        }
        length--;
    }
    //delete tail
    void deleteTail() {
        if(head != nullptr) {
            if(head->next == nullptr) {
                head = nullptr;
            } else {
                Node<T>* newTail = tail->prev;
                newTail->next = nullptr;
                Node<T>* temp = tail;
                tail = newTail;
                delete temp;
            }
        }
        length--;
    }

    // delete a node at index
    void deleteNode(int index) {
    int length = this->getLength();
        if (index < 1 || index > length)
        {
            cout<<"Index does not exist"<<endl;
            return;
        }

        // delete the first node
        if (index == 1)
        {
           this->deleteHead();
            return;
        }

        if (index == length)
        {
         this->deleteTail();
            return;
        }

        Node<T> *tempNode = head;

        // traverse to the nth node
        int i=1;
        while (i<2)
        {
            tempNode = tempNode->next;
            i++;
        }

       Node<T> *previousNode = tempNode->prev;	// (n-1)th node
       Node<T> *nextNode = tempNode->next;	// (n+1)th node

        // assigning (n-1)th node's next pointer to (n+1)th node
        previousNode->next = tempNode->next;

        // assigning (n+1)th node's previous pointer to (n-1)th node
        nextNode->prev = tempNode->prev;

        // deleting nth node
        delete tempNode;
        this->length--;
    }
    void deleteNode(Node<T> *delNode) {
        int length = this->getLength();

        // delete the first node
        if (delNode == this->head)
        {
            this->deleteHead();
            return;
        }

        if (delNode == this->tail)
        {
            this->deleteTail();
            return;
        }

        Node<T> *previousNode = delNode->prev;	// delNode's previous node
        Node<T> *nextNode = delNode->next;	// (delNode's next node

        //reassigning pointers
        previousNode->next = delNode->next;
        nextNode->prev = delNode->prev;

        // deleting given node
        delete delNode;
        this->length--;
    }

    // Splitting Methods

    void splitListHeadTail(){
        DoubleLinkedList<Data> *headList = new DoubleLinkedList<Data>();
        DoubleLinkedList<Data> *tailList = new DoubleLinkedList<Data>();

        while(this->length!=0){
            headList->append(head->value);
            tailList->append(tail->value);
            this->deleteHead();
            this->deleteTail();
        }
        cout<<"Head List is"<<endl;
        headList->printList();
        cout<<"Tail List is"<<endl;
        tailList->printList();
    }

    void splitListOddEven(){
        //my index starts at 0
        DoubleLinkedList<Data> *evenList = new DoubleLinkedList<Data>();
        DoubleLinkedList<Data> *oddList = new DoubleLinkedList<Data>();
        int i=0;
        while((this->length!=0)&&(i<=length)){
                if(i%2==0)
                    evenList->append(head->value);
                else
                    oddList->append(head->value);
                this->deleteHead();
                i++;
            }
        cout<<"Odd List is"<<endl;
        oddList->printList();
        cout<<"Even List is"<<endl;
        evenList->printList();

    }

    //Multiples
    int countMultiples(T* value)
    {
        int count = 0;
            Node<T> *curr = head;
            while (curr != nullptr) {
                if (compareData(value,curr->value)) {
                    count++;
                }
                curr = curr->next;
            }
        return count;
    }

    void removeDuplicates()
    {
        cout<<"Inside remove"<<endl;
        DoubleLinkedList<T> *del_list = new DoubleLinkedList<T>();
        cout<<"Delete list created"<<endl;
        if (head == nullptr) {
            cout<<"List is empty"<<endl;
            return;
        }

        Node<T>* curr;
        Node<T>* inner;
        cout<<"Next is for"<<endl;
        for (curr = head; curr != nullptr; curr = curr->next) {

            inner = curr->next;
            int count = this->countMultiples(curr->value);
            cout<<"Number of duplicates of  ";
            curr->print();
            cout<<"is "<<count<<endl;
            if(count>1) {
                cout<<"Inserting to be deleted"<<endl;
                del_list->append(curr->value);
                while (inner != nullptr) {
                    if (compareData(curr->value, inner->value)) {
                        Node<T> *temp = inner->next;
                        this->deleteNode(inner);
                        inner = temp;
                    } else {
                        inner = inner->next;
                    }
                }
            }
        }
        for (Node<T>* curr2 = del_list->head; curr2 != nullptr; curr2 = curr2->next){
            Node<T>* inner2 = head;
            while(inner2 != nullptr){
                if(compareData(curr2->value,inner2->value)){
                    Node<T>* temp = inner2->next;
                    this->deleteNode(inner2);
                    inner2=temp;
                }
                else inner2=inner2->next;
            }
        }
        delete del_list;
    }

    //sorting

    void swapAdjNodes(Node<T>* n1, Node<T>* n2)
    {
        // Write special cases if one node is Head or Tail
        // or this swap will not work

        cout<<"Swapping"<<endl;
        n1->print();
        cout<<"and"<<endl;
        n2->print();
        n1->next = n2->next;
        n2->prev=n1->prev;
        n2->next->prev=n1;
        n1->prev->next = n2;
        n1->prev = n2;
        n2->next = n1;
    }
    void sortList()
    {
        bool swapFlag;
        Node<T> *curr;
        if (head == nullptr)
            return;
        do
        {
            swapFlag = false;
            curr = head;
            while (curr->next != nullptr)
            {
                if (compareKey(curr->value,curr->next->value))
                {
                    swapAdjNodes(curr,curr->next);
                    swapFlag = true;
                }
                curr = curr->next;
            }
        }
        while (swapFlag);
    }

};


int main() {
    //Creating List
    DoubleLinkedList<Data> *ll1 = new DoubleLinkedList<Data>();

    //Creating & Adding data
    Data* d1;
    for(int i=0;i<3;i++){
        d1 = new Data (i, "abc");
cout<<"Inserted: "<<i<<endl;
        ll1->append(d1);
    }
    d1= new Data(23, "abc");
    ll1->append(d1);
    d1= new Data(190, "abc");
    ll1->append(d1);
    d1= new Data(190, "abc");
    ll1->append(d1);
    d1= new Data(190, "abc");
    ll1->append(d1);

    // cout<<"Calling split"<<endl;
   // ll1->splitListHeadTail();
   // ll1->splitListOddEven();

   //Counting & Removing Multiples
   Data *cm = new Data(190,"abc");
   cout<<"Number of multiples are :"<<endl;
   cout<<ll1->countMultiples(cm);
   ll1->removeDuplicates();
   ll1->printList();

   //Sorting & Printing
    //ll1->sortList();
    //ll1->printList();
}