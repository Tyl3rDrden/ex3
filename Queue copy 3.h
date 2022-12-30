#ifndef QUEUEH
#define QUEUEH

#include <assert.h>

#define TERMINATORNODE nullptr

#include <exception>

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
        class ConstIterator
        {
            private:
                const Node* nodePtr; 
                int index; 
                ConstIterator(const Node* node, int index):
                node(node), index(index){};
            public:
                //Interface part
                const T& operator*() const;
                ConstIterator& operator++();//Prefix
                ConstIterator operator++(int);//Postfix
                bool operator==(const ConstIterator& i) const;
                bool operator!=(const ConstIterator& i) const;
                T* operator->() const;
                //I need to check why this returns a pointer

        }

        
        
        //i'll 
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;
        //Interface part
        void pushBack(T);
        T front() const;
        void popFront();
        int size() const;
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


//Maybee I forgot to implment stuff I'll ask chatgbt for it
#endif
