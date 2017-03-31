//Marya Poterek
//LinkedList.cpp
//CSE 20312



//Class Node interface
#include <iostream>

using namespace std;

template <typename T> class List; //Forward declaration of List

template <typename T> //Templated node type
class Node {  
   
   friend class List<T>; //Gives List access to Node private variables
    
   public:
     Node(const T &); //Constructor
     ~Node(); //Deconstructor
     T getData(); //Returns value found at a node
     Node<T>* getNext(); //Returns the address of the next node

   private:
     T data; //Data for linked list node
     Node<T> *next; //Pointer to next object
};


//Class Node implementation, in same file to avoid linking issues

//Constructor, using member initialization list syntax
template <typename T>
Node<T>::Node(const T &info) : data(info), next(NULL) {}

//Deconstructor
template <typename T>
Node<T>::~Node() {}

//Accessor function
template <typename T>
T Node<T>::getData() {
   return data;
}

//Accessor function
template<typename T>
Node<T> * Node <T>::getNext() {
   return next;
}



//Class List interface
#include <iostream>

using namespace std;

template<typename T> //Templated class
class List {
   public:
     List(); //Constructor
     ~List(); //Deconstructor
     void pushFront(const T &); //Adds a number to the front 
     void print(); //Prints contents of linked list
     bool empty(); //Determines if list is empty
     Node <T> *head; //Dynamic memory allocation, points to front of node

   private: 
     Node <T> *newNode(const T &); //Creates new node
};    


//Class List implementation

//Constructor, initializes head to nullptr
template <typename T>
List<T>::List() : head(NULL) {}

template <typename T>
List<T>::~List() {
   if (!empty()) {//Follow the links to destroy nodes
     Node<T> *p = head;
 
     while ( p!= NULL) {
       Node<T> * next = p->next; //Check this node's 'next' before it's destroyed
       delete p; //p removed from memory when out of scope
       p = next;
     };
   }
}

//Utility function to create a node 
template <typename T>
Node<T> * List<T>::newNode(const T &value) {
 return new Node<T>(value);
}

//Performs linkage to create new node, calls newNode to establish memory location for value
template <typename T>    
void List<T>::pushFront(const T &value) {
 
   Node<T> * x = newNode(value);
   x->next = head;
   head = x;
}

//Checks if list is empty
template <typename T>
bool List<T>::empty() { return (head == NULL); }

//Moves through list and prints content/pointer values
template <typename T>
void List<T>::print() { 
   Node<T> * p = head;
   for (; p != NULL; p = p->next) {
     cout << p->getData() ;
   }
   cout << endl;
}

//Function to add two integers as lists and return a list
List<int>addNumberLists(List<int>&, List<int>&);

int main() {
  
  //Continues while there is still input
   while(!cin.eof()) {
     string num1, num2; //Input entered as strings
     List<int> list1; //Stores first number as a linked list
     List<int> list2; //Stores second number as a linked list

     cin >> num1 >> num2;
    
     //For loops convert strings to single ints
     for (unsigned int i = 0; i < num1.length(); i++) {
       char c = num1[i];
       list1.pushFront(c-'0');
     }
     for (unsigned int j = 0; j < num2.length(); j++) {
       char d = num2[j];
       list2.pushFront(d-'0');
     }
     
     //Passes lists to function to be added and returned as a list
     List<int>sumList = addNumberLists(list1, list2);
 
     //Prints each sum
     sumList.print();
   }
      
   return 0;
}


//Function called from main to add two lists
List<int>addNumberLists(List<int>&list1, List<int>&list2) {
   int sum; //Value (digit) added to temp linked list
   int carry = 0; //Either 1 or 0, depending on result of addition of a set of digits
   List<int> temp; //List to store sum
   Node<int> * p = list1.head; //Pointer to nodes of first list
   Node<int> * q = list2.head; //Pointer to nodes of second list


   //Enters loop if either list still has values in it
   while (p != NULL || q != NULL) {  
  
     //Adds carry value, data values/0
     sum = carry + (p == NULL ? 0 : p->getData() ) + (q == NULL ? 0 : q->getData());
     
     //Update carry variable
     carry = (sum >= 10) ? 1 : 0; //Can't carry more than 1

     //Update sum if greater than 10
      sum = sum % 10;
         
      //Add the sum (a digit) to the sum linked list 
      temp.pushFront(sum);

      //Checks that a node exists before pointing to nonexistent memory
      if (p != NULL) p = p->getNext();
      if (q != NULL)  q = q->getNext();
   } 
   
   //Adds to front of number if final addition exceeded 10
   if (carry > 0) { 
     temp.pushFront(carry);
   }
   return temp; //Returns the sum to main to be output
}
