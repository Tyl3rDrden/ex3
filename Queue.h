#ifndef QUEUEH
#define QUEUEH
#include <exception>
#include <stdexcept>
#include <iostream>
#include <assert.h>

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
                //default Ctor has to define everything as null

                bool operator!=(const Node& n1);

                //I have to in order to use the the -> operator
                friend class Queue<T>::Iterator;
                friend class Queue<T>::ConstIterator;
                friend class Queue<T>;

                Node(T data):
                data(data), next(TERMINATORNODE){};
                //I think even a struct would do
                //maybe i'll need more functionality Later !
        };
        Node* head;
        Node* tail;
        int m_size;
        //First Node (The one that gets poped )

        //The one after the last one the one that is incremented uppon appendage

    public: 
    //Embedding the iterator class
        class Iterator
        {
            private:
                Node* nodePtr; 
                int index; 
            public:
                Iterator(Node* node, int index):
                nodePtr(node), index(index){};
                //Interface part
                T& operator*() const;
                Iterator& operator++();//Prefix
                Iterator operator++(int);//Postfix
                bool operator==(const Iterator& i) const;
                bool operator!=(const Iterator& i) const;
                T* operator->() const;
                class InvalidOperation
                {};
                //I need to check why this returns a pointer
        };
        class ConstIterator
        {
            private:
                const Node* nodePtr; 
                int index; 
            public:
                ConstIterator(const Node* node, int index):
                nodePtr(node), index(index){};
                //Interface part
                const T& operator*() const;
                ConstIterator& operator++();//Prefix
                ConstIterator operator++(int);//Postfix
                bool operator==(const ConstIterator& i) const;
                bool operator!=(const ConstIterator& i) const;
                const T* operator->() const;
                //I need to check why this returns a pointer
                class InvalidOperation
                {};
        };
        friend class Iterator;
        friend class ConstIterator;
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        //Interface part
        void pushBack(T);
        T& front() const;
        void popFront();
        int size() const;
        Queue():
        head(nullptr), tail(nullptr), m_size(0){}; 
        ~Queue();
        class EmptyQueue
        {
            
        };





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
        if(m_size == 0)
        {
            head = newNode;
            tail = head;
        }
        m_size++;
        // Check if queue is empty
            // Set next of current tail to new node
        tail->next = newNode;
        tail = newNode;
        // Set tail to new node
    }
    catch (std::bad_alloc& ba)
    {
        std::cout << "Out of memory!!";
        //Handle Exeption (do nothing)

    }
}


template <class T>
T& Queue<T>::front() const
{
    if(m_size == 0)
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
        throw Queue<T>::EmptyQueue();
            //We may need the exceptions file to be here!
    }
        //Operator != added in Node class
    Node* temp = head;
        //No assignment operator needed since we are dealing with pointers! (ints)
    head = head->next;
    m_size--;
    delete temp;
    //Destrucor needed for Node ? 
}


template <class T>
int Queue<T>::size() const
{
    return m_size;
}

//Implemnting the Iterator Part
template <typename T>
T& Queue<T>::Iterator::operator*() const
{
    
    //Check no null pointers

        if(this->nodePtr == TERMINATORNODE)
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


template <typename T>
const T& Queue<T>::ConstIterator::operator*() const
{
    
    //Check no null pointers

        if(this->nodePtr == TERMINATORNODE)
        {
            //Portnetial problem with the indexes here
            throw Queue<T>::ConstIterator::InvalidOperation();
        }
        if(!this->nodePtr)
        {
            //NullPointer
            throw Queue<T>::ConstIterator::InvalidOperation();
        }
        return this->nodePtr->data;
    
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::begin()
{
        if(m_size == 0)
        {
            //Empty Queue
            throw Queue<T>::EmptyQueue();
        }
        return Iterator(Queue<T>::head, 0);
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::end()
{
    
    return Iterator(nullptr, m_size);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::begin() const
{
        if(m_size == 0)
        {
            //Empty Queue
            throw Queue<T>::EmptyQueue();
        }
        return ConstIterator(Queue<T>::head, 0);
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(nullptr, m_size);
}

template <typename T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()//Prefix
{
    //Index in bounds
    //Check Valid operator 


    if(!&(*this->nodePtr))
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    nodePtr = nodePtr->next;
    return *this;
}

template <typename T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()//Prefix
{
    //Index in bounds
    if(!&(*this->nodePtr))
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    nodePtr = nodePtr->next;
    return *this;
}

template <typename T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)//postfix
{
    if(!&(*this->nodePtr))
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    Queue<T>::ConstIterator result = *this;
    ++*this;
    return result;
    //Genius !!!!!
}
template <typename T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)//postfix
{
    if(!&(*this->nodePtr))
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    Queue<T>::ConstIterator result = *this;
    ++*this;
    return result;
    //Genius !!!!!
}
template <typename T>
bool Queue<T>::Iterator::operator==(const Iterator& i) const
{
    //Will return true if the iterator points to the same address
    return (i.nodePtr == this->nodePtr);

}
template <typename T>
bool Queue<T>::ConstIterator::operator==(const ConstIterator& i) const
{
    //Will return true if the iterator points to the same address
    return (i.nodePtr == this->nodePtr);

}


template <typename T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    return (i.nodePtr != this->nodePtr);
}
template <typename T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& i) const
{
    return (i.nodePtr != this->nodePtr);
}

template <typename T>
T* Queue<T>::Iterator::operator->() const
{
    if(this->nodePtr == TERMINATORNODE)
    {
        throw Queue<T>::Iterator::InvalidOperation();
    }
    return &(this->nodePtr->data);
}

template <typename T>
const T* Queue<T>::ConstIterator::operator->() const
{
    if(this->nodePtr == TERMINATORNODE)
    {
        throw Queue<T>::ConstIterator::InvalidOperation();
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
    Queue<T> result;
    for (typename Queue<T>::Iterator i = inputQueue.begin(); i != inputQueue.end(); ++i) {
        if (condition(*i)) {
            result.pushBack(*i);
        }
    }
    return result;
}

template <class T, class Operation>
void transform(Queue<T>& inputQueue ,Operation operation)
{
    for (T& element : inputQueue) {
        operation(element);
    }
}


#endif