//
// Created by pcxie on 2020/9/26.
//

#ifndef PROJECT_1_HASHTABLE_H
#define PROJECT_1_HASHTABLE_H

#include <iostream>
#include "vector"


//      In order to use a hash table to store the data, a key is required. Thus, the class will expect the template
//  class to have the member function getKey().
template<class T>
class HashTable {
protected:
    int size{};
    std::vector<T> table;
public:
    HashTable();

    explicit HashTable(int size);

    int getSize() const;

    bool isFull() const;

    int primeHashFunction(unsigned long key) const;
};

template<class T>
HashTable<T>::HashTable() = default;

template<class T>
HashTable<T>::HashTable(int size) {
    this->size = size;
    table = std::vector<T>(size);
}

template<class T>
int HashTable<T>::getSize() const {
    return size;
}

template<class T>
bool HashTable<T>::isFull() const {
    for (int i = 0; i < size; i++) {
        if (table[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

template<class T>
int HashTable<T>::primeHashFunction(unsigned long key) const {
    return key % size;
}


#endif //PROJECT_1_HASHTABLE_H