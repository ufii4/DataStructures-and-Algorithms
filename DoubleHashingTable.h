//
// Created by pcxie on 2020/10/2.
//

#ifndef PROJECT_1_DOUBLEHASHINGTABLE_H
#define PROJECT_1_DOUBLEHASHINGTABLE_H

#include "HashTable.h"

template<class T>
class DoubleHashingTable : public HashTable<T> {
private:
    std::vector<bool> isDeleted;
public:
    DoubleHashingTable() = default;

    explicit DoubleHashingTable(int size) : HashTable<T>(size) {
        isDeleted = std::vector<bool>(size);
    }

    int secondaryHashFunction(unsigned long key) const;

//    Checks if all of the spots in the index have been modified (occupied or deleted),
    bool isAllOperated() const;

    bool put(const T &object);

    unsigned int search(T &object) const;

    bool remove(const T &object);

//    For debug
    void print() const;
};

template<class T>
int DoubleHashingTable<T>::secondaryHashFunction(unsigned long key) const {
    return (key / this->size) % this->size +
           (((key / this->size) % this->size) % 2 == 0);
}

template<class T>
bool DoubleHashingTable<T>::isAllOperated() const {
    for (int i = 0; i < this->size; i++) {
        if (this->table[i].isEmpty() && !isDeleted[i]) {
            return false;
        }
    }
    return true;
}

template<class T>
bool DoubleHashingTable<T>::put(const T &object) {
    if (this->isFull()) {
        return false;
    } else {
        unsigned long key = object.getKey();
        int probe = this->primeHashFunction(key);
        int offset = secondaryHashFunction(key);
        while (!this->table[probe].isEmpty()) {
            if (this->table[probe] == object) {
                return false;
            }
            probe = (probe + offset) % this->size;
        }
        this->table[probe] = object;
        return true;
    }
}

template<class T>
unsigned int DoubleHashingTable<T>::search(T &object) const {
    unsigned long key = object.getKey();
    int probe = this->primeHashFunction(key);
    int offset = secondaryHashFunction(key);
    if (isAllOperated()) {
        for (int i = 0; i < this->size; i++) {
            if (this->table[i] == object) {
//                Update the object.
                object = this->table[i];
                return i;
            }
        }
        return -1;
    }
//        Without the above algorithm, this will cause a infinite loop if every index is not empty or marked deleted.
    while (!this->table[probe].isEmpty() || isDeleted[probe]) {
        if (this->table[probe] == object) {
//            Update the object.
            object = this->table[probe];
            return probe;
        }
        probe = (probe + offset) % this->size;
    }
    return -1;
}

template<class T>
bool DoubleHashingTable<T>::remove(const T &object) {
    unsigned long key = object.getKey();
    int probe = this->primeHashFunction(key);
    int offset = secondaryHashFunction(key);
    if (isAllOperated()) {
        for (int i = 0; i < this->size; i++) {
            if (this->table[i] == object) {
                T temp;
                std::swap(temp, this->table[probe]);
                isDeleted[probe] = true;
                return true;
            }
        }
        return false;
    }
    while (!this->table[probe].isEmpty() || isDeleted[probe]) {
        if (this->table[probe] == object) {
            T temp;
            std::swap(temp, this->table[probe]);
            isDeleted[probe] = true;
            return true;
        }
        probe = (probe + offset) % this->size;
    }
    return false;
}

template<class T>
void DoubleHashingTable<T>::print() const {
    for (int i = 0; i < this->size; i++) {
        std::cout << i << " " << this->table[i] << ' ' << isDeleted[i] << std::endl;
    }
}


#endif //PROJECT_1_DOUBLEHASHINGTABLE_H
