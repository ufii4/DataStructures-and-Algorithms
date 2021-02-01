//
// Created by pcxie on 2020/10/2.
//

#ifndef PROJECT_1_CHAININGHASHTABLE_H
#define PROJECT_1_CHAININGHASHTABLE_H

#include "HashTable.h"
#include "LinkedList.h"

template<class T>
class ChainingHashTable : public HashTable<LinkedList<T>> {
public:
    ChainingHashTable() = default;

    explicit ChainingHashTable(int size) : HashTable<LinkedList<T>>(size) {}

    bool put(const T &object);

    unsigned int search(T &object);

    bool remove(const T &object);

    void print() const;

    void print(unsigned int index) const;
};

template<class T>
bool ChainingHashTable<T>::put(const T &object) {
    unsigned long key = this->primeHashFunction(object.getKey());
    if (this->table[key].search(object) != -1) {
        return false;
    } else {
        this->table[key].insertInAscendingOrder(object);
    }
    return true;
}

template<class T>
unsigned int ChainingHashTable<T>::search(T &object) {
    unsigned long key = this->primeHashFunction(object.getKey());
    unsigned int index = this->table[key].search(object);
    if (index == -1) {
        return -1;
    }
    object = this->table[key].get(index);
    return key;
}

template<class T>
bool ChainingHashTable<T>::remove(const T &object) {
    return this->table[this->primeHashFunction(object.getKey())].remove(object);
}

template<class T>
void ChainingHashTable<T>::print() const {
    for (int i = 0; i < this->size; i++) {
        this->table[i].print();
    }
}

template<class T>
void ChainingHashTable<T>::print(unsigned int index) const {
    if(index>this->size-1) return;
    std::cout << this->table[index]->toString() << std::endl;
}

#endif //PROJECT_1_CHAININGHASHTABLE_H
