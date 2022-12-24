#ifndef QUEUEH
#define QUEUEH

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
                Node():
                next(TERMINATORNODE){};
                //default Ctor has to define everything as null

                bool operator!=(const Node& n1);

                Node(T data):
                data(data), next(TERMINATORNODE){};
                //I think even a struct would do
                //maybe i'll need more functionality Later !
                ~Node() = default;
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
        int size() const;
        Queue():
        head(nullptr), tail(nullptr), size(0){}; 





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
    Node *newNode = new Node(data);
    //Last ptr is suppost to point to null
    size++;
    tail->next = newNode;
    //Setting tail to be the new node
}

template <class T>
T Queue<T>::front() const
{
    assert(size > 0);
    //Else throw an exception!
    return head->data;
}

template <class T>
void Queue<T>::popFront()
{
    //Thorw Exception here *******************************
    assert(head != TERMINATORNODE);
    //Operator != added in Node class
    Node* temp = head;
    //No assignment operator needed since we are dealing with pointers! (ints)
    head = head->next;
    size--;
    delete temp;
    //Destrucor needed for Node ? 
}


template <class T>
int Queue<T>::size() const
{
    return size;
}



//Implemnting the Iterator Part
template <class T>
const T& Queue<T>::Iterator::operator*() const
{
    assert(Queue<T>::Iterator::index >= 0 && Queue<T>::Iterator::index < Queue<T>::size);
    //Check no null pointers
    assert(this->nodeptr);
    return this->nodePtr->data;
}

template <class T>
Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(Queue<T>::head, 1);
}

template <class T>
Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(Queue<T>::tail, Queue<T>::size + 1);
}

template <class T>
Queue<T>::Iterator& Queue<T>::Iterator::operator++()//Prefix
{
    ++index;
    return *this;
}

template <class T>
Queue<T>::Iterator Queue<T>::Iterator::operator++(int)//Prefix
{
    Queue<T>::Iterator result = *this;
    ++*this;
    return result;
    //Genius !!!!!
}

template <class T>
bool Queue<T>::Iterator::operator==(const Iterator& i) const
{
    //Will return true if the iterator points to the same address
    return (i.nodePtr == this->nodePtr);

}

bool operator==(const Iterator& i) const;

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    return (i.nodePtr != this->nodePtr);
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& i) const
{
    return (i.nodePtr != this->nodePtr);
}

template <class T>
T* Queue<T>::Iterator::operator->() const
{
    return &(this->nodePtr->data);
}


template <class T, class Condition>
Queue<T> filter(Queue<T> inputQueue ,Condition condition)
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