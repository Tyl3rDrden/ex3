#ifndef QUEUEH
#define QUEUEH
#include <cstdlib>
template <class T> class Queue {
public:
    Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    ~Queue();
    void pushBack(T);
    T& front() const;
    void popFront();
    int size() const;
    class EmptyQueue {};
    class Iterator;
    Iterator begin();
    Iterator end();
    class ConstIterator;
    ConstIterator begin() const;
    ConstIterator end() const;


private:
    T* m_data;
    int m_size;
    int m_maxSize;
    void grow();

    static const int GROW_RATE = 2;
    static const int INITIAL_SIZE = 1;
};

template <class T> Queue<T>::Queue()
{
    m_size = 0;
    m_maxSize = INITIAL_SIZE;
    m_data = new T[m_maxSize];
}

template <class T> Queue<T>::Queue(const Queue<T>& other)
{
    Queue<T> temp;
    m_size = other.m_size;
    m_maxSize = other.m_size;
    m_data = new T[m_size];
    for (int i = 0; i < m_maxSize; ++i) {
        m_data[i] = other.m_data[i];
    }
}

template <class T> Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this == &other) {
        return *this;
    }
    T* temp = new T[other.m_size];
    for (int i = 0; i < other.m_size; ++i) {
        temp[i] = other.m_data[i];
    }

    delete[] m_data;
    m_data = temp;
    m_size = other.m_size;
    m_maxSize = other.m_size;
    return *this;
}

template <class T> Queue<T>::~Queue()
{
    delete[] m_data;
}

template <class T> void Queue<T>::grow()
{
    m_maxSize *= GROW_RATE;
    T* temp = new T[m_maxSize];
    for (int i = 0; i < m_size; ++i) {
        temp[i] = m_data[i];
    }

    delete[] m_data;
    m_data = temp;
}

template <class T> void Queue<T>::pushBack(T data)
{
    if (m_maxSize == m_size) {
        grow();
    }

    m_data[m_size] = data;
    m_size++;
}

template <class T> T& Queue<T>::front() const
{
    if (m_size == 0) {
        throw EmptyQueue();
    }
    return m_data[0];
}

template <class T> void Queue<T>::popFront()
{
    if (m_size == 0) {
        throw EmptyQueue();
    }

    for (int i = 0; i < m_size - 1; ++i) {
        m_data[i] = m_data[i + 1];
    }
    m_size--;
}

template <class T> int Queue<T>::size() const
{
    return m_size;
}

template <class T> class Queue<T>::Iterator {
private:
    Queue<T>* m_queue;
    int m_index;
    Iterator(Queue<T>* queue, int index);
    friend class Queue<T>;

public:
    T& operator*() const;
    T* operator->() const;
    Iterator& operator++();
    Iterator operator++(int);

    bool operator==(const Iterator& iter) const;
    bool operator!=(const Iterator& iter) const;

    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    class InvalidOperation {};
};

template <class T>
Queue<T>::Iterator::Iterator(Queue<T>* queue, int index)
    : m_queue(queue)
    , m_index(index)
{
}

template <class T> T& Queue<T>::Iterator::operator*() const
{
    return m_queue->m_data[m_index];
}

template <class T> T* Queue<T>::Iterator::operator->() const
{
    if (m_index < 0 || m_index > m_queue->size()) {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    return &(m_queue->m_data[m_index]);
}


template <class T> typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (m_index == m_queue->m_size) {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template <class T> typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Iterator result = *this;
    ++*this;
    return result;
}

template <class T> bool Queue<T>::Iterator::operator==(const Iterator& iter) const
{
    return m_index == iter.m_index;
}

template <class T> bool Queue<T>::Iterator::operator!=(const Iterator& iter) const
{
    return !(*this == iter);
}

template <class T> typename Queue<T>::Iterator Queue<T>::begin()
{
    return Iterator(this, 0);
}

template <class T> typename Queue<T>::Iterator Queue<T>::end()
{
    return Iterator(this, m_size);
}

template <class T> class Queue<T>::ConstIterator {
private:
    const Queue<T>* m_queue;
    int m_index;
    ConstIterator(const Queue<T>* queue, int index);
    friend class Queue<T>;

public:
    const T& operator*() const;
    const T* operator->() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);

    bool operator==(const ConstIterator& iter) const;
    bool operator!=(const ConstIterator& iter) const;

    ConstIterator(const ConstIterator&) = default;
    ConstIterator& operator=(const ConstIterator&) = default;
    class InvalidOperation {};
};

template <class T>
Queue<T>::ConstIterator::ConstIterator(const Queue<T>* queue, int index)
    : m_queue(queue)
    , m_index(index)
{
}

template <class T> const T& Queue<T>::ConstIterator::operator*() const
{
    return m_queue->m_data[m_index];
}

template <class T> const T* Queue<T>::ConstIterator::operator->() const
{
    if (m_index < 0 || m_index > m_queue->size()) {
        throw Queue<T>::ConstIterator::InvalidOperation();
    }
    return &(m_queue->m_data[m_index]);
}

template <class T> typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if (m_index < 0 || m_index >= m_queue->m_size) {
        throw InvalidOperation();
    }
    ++m_index;
    return *this;
}

template <class T> typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    ConstIterator result = *this;
    ++*this;
    return result;
}

template <class T> bool Queue<T>::ConstIterator::operator==(const ConstIterator& iter) const
{
    return m_index == iter.m_index;
}

template <class T> bool Queue<T>::ConstIterator::operator!=(const ConstIterator& iter) const
{
    return !(*this == iter);
}

template <class T> typename Queue<T>::ConstIterator Queue<T>::begin() const
{
    return ConstIterator(this, 0);
}

template <class T> typename Queue<T>::ConstIterator Queue<T>::end() const
{
    return ConstIterator(this, m_size);
}


template <class T, class Condition> Queue<T> filter(Queue<T>& queue, const Condition& condition)
{
    Queue<T> result;
    for (T element : queue) {
        if (condition(element)) {
            result.pushBack(element);
        }
    }
    return result;
}

template <class T, class Operation> void transform(Queue<T>& inputQueue, Operation operation)
{
    for (T& element : inputQueue) {
        operation(element);
    }
}

#endif
