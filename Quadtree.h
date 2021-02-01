//
// Created by pcxie on 2020/10/8.
//

#ifndef PROJECT_2_QUADTREE_H
#define PROJECT_2_QUADTREE_H

#include "string"
#include "iostream"
#include <cmath>
//#include "DOUBLE_COMPARISON.h"

const double EPSILON = 1e-5;
bool isEqual(double lhs, double rhs);

bool isLarger(double lhs, double rhs);

bool isEqual(double lhs, double rhs){
    return std::fabs(lhs-rhs) <= EPSILON;
}

bool isLarger(double lhs, double rhs){
    return lhs>rhs && std::fabs(lhs-rhs) > EPSILON;
}




template<class T>
class Quadtree {
private:
    T object;
    Quadtree *parent;
    Quadtree *pNE;
    Quadtree *pNW;
    Quadtree *pSE;
    Quadtree *pSW;
public:
    Quadtree();

    Quadtree(const T &object);

    ~Quadtree();

    Quadtree *getNE();

    Quadtree *getNW();

    Quadtree *getSE();

    Quadtree *getSW();

    Quadtree *getMostNE();

    Quadtree *getMostNW();

    Quadtree *getMostSE();

    Quadtree *getMostSW();

    Quadtree *getParent();

    void setNext(const T &object);

    void setNext(Quadtree *subTree);

    void setParent(Quadtree *parent);

    unsigned int getSize() const;

    unsigned int getHeight() const;

    T getObject() const;

    double getX() const;

    double getY() const;

    Quadtree *getNext(const T &object);

    Quadtree *getNext(double x, double y);

    Quadtree *getNext(std::string dir);

    bool put(const T &object);

    bool hasNext() const;

    Quadtree *search(const T &object);

    Quadtree *search(double x, double y);

    bool isEmpty() const;

    Quadtree *getHead();

    void print(Quadtree *lastToPrint = nullptr);

    Quadtree *getLastToPrint();

    friend std::ostream& operator<<(std::ostream& os, const Quadtree<T>& tree);
};


template<class T>
Quadtree<T>::Quadtree() {
    object = T();
    parent = nullptr;
    pNE = nullptr;
    pNW = nullptr;
    pSE = nullptr;
    pSW = nullptr;
}

template<class T>
Quadtree<T>::Quadtree(const T &object) {
    this->object = object;
    parent = nullptr;
    pNE = nullptr;
    pNW = nullptr;
    pSE = nullptr;
    pSW = nullptr;
}

template<class T>
Quadtree<T>::~Quadtree() {
    delete pNE;
    delete pNW;
    delete pSE;
    delete pSW;
}

template<class T>
void Quadtree<T>::setParent(Quadtree<T> *parent) {
    this->parent = parent;
}

template<class T>
Quadtree<T> *Quadtree<T>::getParent() {
    return parent;
}

template<class T>
double Quadtree<T>::getX() const {
    return object.getX();
}

template<class T>
double Quadtree<T>::getY() const {
    return object.getY();
}

template<class T>
T Quadtree<T>::getObject() const {
    return object;
}

template<class T>
Quadtree<T> *Quadtree<T>::getNext(const T &object) {
    return getNext(object.getX(), object.getY());
}

template<class T>
Quadtree<T> *Quadtree<T>::getNext(double x, double y) {
    if (x >= getX() && isLarger(y,getY())) {
        return pNE;
    } else if (isLarger(getX(),x) && y >= getY()) {
        return pNW;
    } else if (x <= getX() && isLarger(getY(),y)) {
        return pSW;
    } else if (isLarger(x,getX()) && y <= getY()) {
        return pSE;
    } else {
        return nullptr;
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getNext(std::string dir) {
    if (dir == "NE") {
        return pNE;
    } else if (dir == "NW") {
        return pNW;
    } else if (dir == "SE") {
        return pSE;
    } else if (dir == "SW") {
        return pSW;
    }
    return nullptr;
}

template<class T>
void Quadtree<T>::setNext(const T &object) {
    this->setNext(new Quadtree<T>(object));
}

template<class T>
void Quadtree<T>::setNext(Quadtree<T> *subTree) {
    if (subTree->getX() >= this->getX() && isLarger(subTree->getY(),this->getY())) {
        pNE = subTree;
        pNE->setParent(this);
    } else if (isLarger(this->getX(),subTree->getX()) && subTree->getY() >= this->getY()) {
        pNW = subTree;
        pNW->setParent(this);
    } else if (subTree->getX() <= this->getX() && isLarger(this->getY(),subTree->getY())) {
        pSW = subTree;
        pSW->setParent(this);
    } else if (isLarger(subTree->getX(), this->getX()) && subTree->getY() <= this->getY()) {
        pSE = subTree;
        pSE->setParent(this);
    } else {
        return;
    }
}

template<class T>
bool Quadtree<T>::hasNext() const {
    return !(pNE == nullptr && pNW == nullptr && pSW == nullptr && pSE == nullptr);
}

template<class T>
bool Quadtree<T>::isEmpty() const {
    return this->getSize() == 0;
}

template<class T>
bool Quadtree<T>::put(const T &object) {
    if (this->object.isEmpty()) {
        this->object = object;
        return true;
    }
    if (this->getObject() == object) {
        return false;
    }
    if (this->getNext(object) == nullptr) {
        this->setNext(object);
        return true;
    }
    return this->getNext(object)->put(object);
}

template<class T>
Quadtree<T> *Quadtree<T>::search(const T &object) {
    return search(object.getX(), object.getY());
}

template<class T>
Quadtree<T> *Quadtree<T>::search(double x, double y) {
    if (isEqual(x,getX()) && isEqual(y,getY())) {
        return this;
    } else if (getNext(x, y) == nullptr) {
        return nullptr;
    } else {
        return this->getNext(x, y)->search(x, y);
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getHead() {
    if (this->parent == nullptr) {
        return this;
    } else {
        return this->parent->getHead();
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getNE() {
    return pNE;
}

template<class T>
Quadtree<T> *Quadtree<T>::getNW() {
    return pNW;
}

template<class T>
Quadtree<T> *Quadtree<T>::getSE() {
    return pSE;
}

template<class T>
Quadtree<T> *Quadtree<T>::getSW() {
    return pSW;
}

template<class T>
Quadtree<T> *Quadtree<T>::getMostNE() {
    if (this->getNE() == nullptr) {
        return this;
    } else {
        return this->getNE()->getMostNE();
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getMostNW() {
    if (this->getNW() == nullptr) {
        return this;
    } else {
        return this->getNW()->getMostNW();
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getMostSE() {
    if (this->getSE() == nullptr) {
        return this;
    } else {
        return this->getSE()->getMostSE();
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getMostSW() {
    if (this->getSW() == nullptr) {
        return this;
    } else {
        return this->getSW()->getMostSW();
    }
}

template<class T>
unsigned int Quadtree<T>::getSize() const {
    unsigned int size = 0;
    size += !this->getObject().isEmpty();
    size += pNE == nullptr ? 0 : pNE->getSize();
    size += pNW == nullptr ? 0 : pNW->getSize();
    size += pSE == nullptr ? 0 : pSE->getSize();
    size += pSW == nullptr ? 0 : pSW->getSize();
    return size;
}

template<class T>
unsigned int Quadtree<T>::getHeight() const {
//    Unused, might useful for future use.
    unsigned int i = 0;
    if (this != nullptr && !this->getObject().isEmpty()) {
        i++;
        unsigned int max = std::max(pNE->getHeight(), pNW->getHeight());
        max = std::max(max, pNE->getHeight());
        max = std::max(max, pNE->getHeight());
        i += max;
    }
    return i;
}

template<class T>
void Quadtree<T>::print(Quadtree *lastToPrint) {
//    The argument lastToPrint is used to avoid calling getLastToPrint() recursively as print() is recursively called, saving running time.
//    LastToPrint is set to nullptr by default (no argument passed)
    if (lastToPrint == nullptr){
        lastToPrint = getHead()->getLastToPrint();
    }
    if (this != nullptr && !this->getObject().isEmpty()) {
        if (pNE != nullptr) {
            pNE->print(lastToPrint);
        }
        if (pNW != nullptr) {
            pNW->print(lastToPrint);
        }
        this->object.print();
//        Remove the last blank space in the print output.
//        str.pop_back() removes the last char in the str
        if (this == lastToPrint) {
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
        if (pSW != nullptr) {
            pSW->print(lastToPrint);
        }
        if (pSE != nullptr) {
            pSE->print(lastToPrint);
        }
    }
}

template<class T>
Quadtree<T> *Quadtree<T>::getLastToPrint() {
    if (pSE == nullptr && pSW == nullptr) return this;
    if (pSE != nullptr)return pSE->getLastToPrint();
    if (pSW != nullptr)return pSW->getLastToPrint();
    return this;
}

template <class T>
std::ostream& operator<<(std::ostream& os, const Quadtree<T>& tree){
    std::string str{};
}

#endif //PROJECT_2_QUADTREE_H
