#ifndef QUEUEH
#define QUEUEH

#include <assert.h>
#include "QueueExeptions.h"

#define TERMINATORNODE nullptr

template <class T>
class Queue
{
     private: 
        class Node
        {
            private:
                T data;
                Node* next;
            public: 
            //c'tor 
                Node() : next(TERMINATORNODE) {};
                ~Node() = default;
                next(TERMINATORNODE){};
                //default Ctor has to define everything as null

                bool operator!=(const Node& n1);

                Node(T data):
                data(data), next(TERMINATORNODE){};
                //I think even a struct would do
                //maybe i'll need more functionality Later !
        };
        Node* head;
        Node* tail;
        int size;
        //First Node (The one that gets poped )

        //The one after the last one the one that is incremented uppon appendage

    public: 
    //Embedding the iterator class
        class Iterator
        {
            private:
                Node* nodePtr; 
                int index; 
                Iterator(const Node* node, int index):
                node(node), index(index){};
            public:
                //Interface part
                const T& operator*() const;
                Iterator& operator++();//Prefix
                Iterator operator++(int);//Postfix
                bool operator==(const Iterator& i) const;
                bool operator!=(const Iterator& i) const;
                T* operator->() const;
                //I need to check why this returns a pointer
        };
        
        //i'll 
        Iterator begin() const;
        Iterator end() const;
        //Interface part
        void pushBack(T);
        T front() const;
        void popFront();
        int size();
        Queue():
        head(nullptr), tail(nullptr), size(0){}; 
        ~Queue();





    //The Queue will be impemented using A generic Node Type 

};



//Implmenting the Node class

template <class T>
bool Queue<T>::Node::operator!=(const Node& n1)
{
    return (this != &n1);

} 


//Maybee I forgot to implment stuff I'll ask chatgbt for it's suggestion!

template <class T>
void Queue<T>::pushBack(T data)
{
    try
    {
        Node *newNode = new Node(data);
        // Bad alloc exception here
        // Update size
        size++;
        // Check if queue is empty
        if(head == nullptr)
        {
            // Set head to new node
            throw Queue<T>::EmptyQueue();
        }
        else
        {
            // Set next of current tail to new node
            tail->next = newNode;
        }

        // Set tail to new node
        tail = newNode;
    }
    catch(std::bad_alloc e)
    {
        //Handle Exeption (do nothing)

    }
}


template <class T>
T Queue<T>::front() const
{

    if(size == 0)
    {
        //Queue is empty, Throw exception
        throw Queue<T>::EmptyQueue();
    }
    //Else throw an exception!
        return head->data;
}

template <class T>
void Queue<T>::popFront()
{
    //Thorw Exception here *******************************
    if(head == nullptr)//Empty queue
    {
        throw Queue<T>::EmptyQueue()
            //We may need the exceptions file to be here!
    }
        //Operator != added in Node class
    Node* temp = head;
        //No assignment operator needed since we are dealing with pointers! (ints)
    head = head->next;
    size--;
    delete temp;
    //Destrucor needed for Node ? 
}


template <class T>
int Queue<T>::size()
{
    return size;
}

//Implemnting the Iterator Part
template <class T>
const T& Queue<T>::Iterator::operator*() const
{
    
    //Check no null pointers

        if(index <= 0 || index > size)
        {
            //Portnetial problem with the indexes here
            throw Queue<T>::Iterator::InvalidOperation();
        }
        if(!this->nodePtr)
        {
            //NullPointer
            throw Queue<T>::Iterator::InvalidOperation();
        }
        return this->nodePtr->data;
    
}

template <class T>
Queue<T>::Iterator Queue<T>::begin() const
{
        if(size == 0)
        {
            //Empty Queue
            throw Queue<T>::EmptyQueue();
        }
        return Iterator(Queue<T>::head, 0);
}

template <class T>
Queue<T>::Iterator Queue<T>::end() const
{
    if(size == 0)
    {
            //Empty Queue
        throw Queue<T>::EmptyQueue();
    }
    return Iterator(Queue<T>::tail, Queue<T>::size);
}

template <class T>
Queue<T>::Iterator& Queue<T>::Iterator::operator++()//Prefix
{
    //Index in bounds
    if(index + 1 < 0 || index + 1 > size)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    ++index;
    return *this;
}

template <class T>
Queue<T>::Iterator Queue<T>::Iterator::operator++(int)//Prefix
{
    if(index + 1 < 0 || index + 1 > size)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    Queue<T>::Iterator result = *this;
    ++*this;
    return result;
    //Genius !!!!!
}

template <class T>
bool Queue<T>::Iterator::operator==(const Iterator& i) const
{
    if(index < 0 || index > size )
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    //Will return true if the iterator points to the same address
    return (i.nodePtr == this->nodePtr);

}


template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    if(index < 0 || index > size )
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return (i.nodePtr != this->nodePtr);
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    if(index < 0 || index > size )
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return (i.nodePtr != this->nodePtr);
}

template <class T>
T* Queue<T>::Iterator::operator->() const
{
    if(index < 0 || index > size )
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return &(this->nodePtr->data);
}

//Destructor that cleans the queue
template <class T>
Queue<T>::~Queue()
{
    for (Node* current = head; current != TERMINATORNODE; )
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}



template <class T, class Condition>
Queue<T> filter(Queue<T>& inputQueue ,const Condition& condition)
{
    Queue<T> result = Queue<T>(); 
    for (const T& element : inputQueue) {
        if(condition(element))
        {
            result.pushBack(element);
        }
    }
    
}

template <class T, class Operation>
Queue<T> transform(Queue<T> inputQueue ,Operation operation)
{
    for (T& element : inputQueue) {
        element = operation(element);
    }
}


#endif