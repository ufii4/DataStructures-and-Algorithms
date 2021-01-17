//
// Created by pcxie on 2020/9/25.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<class T>
class LinkedList {
protected:
    struct Node {
        Node(T object) {
            this->object = object;
            pNext = nullptr;
        }
        T object;
        Node *pNext;
    };

    int size;
    Node *pHead;
    Node *pLast;
    Node *lastNodeGot = nullptr;

    Node *getNode(int index);

public:
    LinkedList();

    LinkedList(int size, T _default);

    ~LinkedList();

    virtual int getSize() const;

    virtual bool pushBack(T object);

    virtual bool pushFront(T object);

    virtual bool set(int index, T object);

    virtual T popFront();

    virtual T popBack();

    virtual T get(int index);

    virtual void clear();

    virtual std::string toString();

    virtual void sort(std::function<bool(T, T)> compare);

    inline T &operator[](int index) { return getNode(index)->object; };

    inline T &operator[](size_t &i) { return this->get(i); }

    inline const T &operator[](const size_t &i) const { return this->get(i); }
};

template<class T>
LinkedList<T>::LinkedList() {
    this->size = 0;
    pHead = nullptr;
    pLast = nullptr;
}

template<class T>
LinkedList<T>::LinkedList(int size, T _default) {
    if (size >= 0) {
        this->size = size;
        for (int i = 0; i < size; i++) {
            this->pushBack(new Node(_default));
        }
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node *p_current = pHead;
    while (p_current != nullptr) {
        Node *p_next = p_current->pNext;
        delete p_current;
        p_current = p_next;
    }
}

template<class T>
typename LinkedList<T>::Node *LinkedList<T>::getNode(int index) {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    auto current = pHead;
    for (int i = 0; i < index; i++) {
        current = current->pNext;
    }
    return current;
}

template<class T>
int LinkedList<T>::getSize() const {
    return this->size;
}

template<class T>
bool LinkedList<T>::pushBack(T object) {
    if (pHead) {
        pLast->pNext = new Node(object);
        pLast = pLast->pNext;
    } else {
        pHead = new Node(object);
        pLast = pHead;
    }
    size++;
    return true;
}

template<class T>
bool LinkedList<T>::pushFront(T object) {
    if (pHead) {
        auto tmp = pHead;
        pHead = new Node(object);
        pHead->pNext = tmp;
        if (size == 0) {
            pLast = pHead;
        }
    } else {
        pHead = new Node(object);
        pLast = pHead;
    }
    size++;
    return true;
}

template<class T>
bool LinkedList<T>::set(int index, T object) {
    auto tmp = getNode(index);
    if (tmp == nullptr) {
        return false;
    } else {
        tmp->object = object;
        return true;
    }
}

template<class T>
T LinkedList<T>::popFront() {
    if (pHead) {
        auto rt = pHead->object;
        if (size == 1) {
            size--;
            delete pHead;
            pLast = nullptr;
            pHead = nullptr;
            return rt;
        }
        size--;
        auto tmp = pHead;
        pHead = pHead->pNext;
        delete tmp;
        return rt;
    }
    return T();
}

template<class T>
T LinkedList<T>::popBack() {
    if (pHead) {
        if (size == 1) {
            return popFront();
        } else {
            auto tmp = pLast->object;
            delete pLast;
            size--;
            pLast = getNode(size - 1);
            return tmp;
        }
    }
    return T();

}

template<class T>
T LinkedList<T>::get(int index) {
    auto node = getNode(index);
    return node ? node->object : T();
}

template<class T>
void LinkedList<T>::clear() {
    while (pHead) {
        popFront();
    }
}

template<class T>
std::string LinkedList<T>::toString() {
    return std::string();
}

template<class T>
void LinkedList<T>::sort(std::function<bool(T, T)>) {

}


#endif //LINKEDLIST_H
