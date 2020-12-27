//
// Created by pcxie on 2020/12/7.
//

#ifndef DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
#define DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H

#include <string>
#include <cmath>

enum dir : bool {
    left = 0, right = 1
};

template<class T>
class AVLTree {
    friend class AVLTreeTests;

public:
    inline void setParent(AVLTree<T> *parent);

    inline void setLeft(AVLTree<T> *left);

    inline void setRight(AVLTree<T> *right);

    inline AVLTree<T> *getLeft() const;

    inline AVLTree<T> *getRight() const;

    inline AVLTree<T> *getParent() const;

    AVLTree<T> *getNext(int key);

    bool setNext(int key, T object);

    AVLTree<T> *getAncestor();

    bool hasNext() const;

    bool isBalanced() const;

    static AVLTree<T> *getUnBalancedNode(AVLTree<T> *leaf);

    static void balanceTree(AVLTree<T> *leef);

public:
    AVLTree();

    AVLTree(int key, T object);

    ~AVLTree();

    AVLTree<T> *getSubTree(int key);

    unsigned int getSize() const;

    unsigned int getHeight() const;

    bool insert(int key, const T &object);

    T remove(int key);

    T search(int key) const;

    bool isEmpty() const;

    T getRoot() const;

    void reset();

private:
    int key;
    T object;
    AVLTree<T> *left;
    AVLTree<T> *right;
    AVLTree<T> *parent;
};

template<class T>
void AVLTree<T>::setParent(AVLTree *parent) {
    if (this) {
        this->parent = parent;
    }
}

template<class T>
AVLTree<T> *AVLTree<T>::getNext(int key) {
    return this->key < key ? right : left;
}

template<class T>
bool AVLTree<T>::setNext(int key, T object) {
    auto *toSet = new AVLTree<T>(key, object);
    toSet->setParent(this);
    if (this->key < key) {
        if (this->getRight() != nullptr) {
            return false;
        }
        this->setRight(toSet);
    } else {
        if (this->getLeft() != nullptr) {
            return false;
        }
        this->setLeft(toSet);
    }
    balanceTree(getUnBalancedNode(toSet));
    return true;
}

template<class T>
AVLTree<T> *AVLTree<T>::getAncestor() {
    return this->parent == nullptr ? this : this->parent->getAncestor();
}

template<class T>
bool AVLTree<T>::hasNext() const {
    if (this) {
        return right == nullptr || left == nullptr;
    }
    return false;
}

template<class T>
bool AVLTree<T>::isBalanced() const {
    if (this) {
        return std::abs((int) left->getHeight() - (int) right->getHeight()) <= 1;
    }
    return true;
}

template<class T>
AVLTree<T>::AVLTree() {
    this->key = NULL;
    this->object = NULL;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<class T>
AVLTree<T>::AVLTree(int key, T object) {
    this->key = key;
    this->object = object;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template<class T>
AVLTree<T>::~AVLTree() {
    delete left;
    delete right;
}

template<class T>
AVLTree<T> *AVLTree<T>::getSubTree(int key) {
    if (this->key == key) {
        return this;
    }
    auto next = this->getNext(key);
    return next == nullptr ? nullptr : next->getSubTree(key);
}

template<class T>
unsigned int AVLTree<T>::getSize() const {
    unsigned int size = 0;
    size += this->object != NULL;
    size += left == nullptr ? 0 : left->getSize();
    size += right == nullptr ? 0 : right->getSize();
    return size;
}

template<class T>
unsigned int AVLTree<T>::getHeight() const {
//      I do realize that this is quite inefficient, especially when isBalanced() uses this method.
//  The idea of dynamic programming should be utilized here. But emm -.- No idea now.
//  ? Add a field height to the class. (cons: height of each tree is hard to manage when updating)
    unsigned int i = 0;
    if (this != nullptr && this->object != NULL) {
        i++;
        unsigned int max = std::max(left->getHeight(), right->getHeight());
        i += max;
    }
    return i;
}

template<class T>
bool AVLTree<T>::insert(int key, const T &object) {
    if (this->object == NULL) {
        this->key = key;
        this->object = object;
        return true;
    }
    if (this->key == key) {
        return false;
    }
    if (this->getNext(object) == nullptr) {
        return this->setNext(key, object);
    }
    return this->getNext(key)->insert(key, object);
}

template<class T>
T AVLTree<T>::search(int key) const {
    if (this->key == key) {
        return this->object;
    } else if (getNext(key) == nullptr) {
        return NULL;
    } else {
        return this->getNext(key)->search(key);
    }
}

template<class T>
T AVLTree<T>::remove(int key) {

}

template<class T>
bool AVLTree<T>::isEmpty() const {
    return false;
}

template<class T>
T AVLTree<T>::getRoot() const {
    return nullptr;
}

template<class T>
void AVLTree<T>::reset() {
    if (parent == nullptr) {
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
        object = NULL;
    }
}

template<class T>
AVLTree<T> *AVLTree<T>::getUnBalancedNode(AVLTree<T> *leaf) {
    if (leaf == nullptr) {
        return nullptr;
    }
    if (!leaf->isBalanced()) {
        return leaf;
    }
    return getUnBalancedNode(leaf->getParent());
}

template<class T>
void AVLTree<T>::balanceTree(AVLTree<T> *unBalanced) {
    if (unBalanced->isBalanced()) {
        return;
    }
    dir d1;
    dir d2;
    AVLTree<T> *n1;
    AVLTree<T> *n2;
    if (unBalanced->getLeft()->getHeight() >= unBalanced->getRight()->getHeight()) {
        d1 = dir::left;
        n1 = unBalanced->getLeft();
    } else {
        d1 = dir::right;
        n1 = unBalanced->getRight();
    }
    if (n1->getLeft()->getHeight() >= n1->getRight()->getHeight()) {
        d2 = dir::left;
        n2 = n1->getLeft();
    } else {
        d2 = dir::right;
        n2 = n1->getRight();
    }
    if (d1 == d2) {
        AVLTree<T> *t = d1 ? n1->getLeft() : n1->getRight();
        n1->setParent(unBalanced->getParent());
        unBalanced->setParent(n1);
        t->setParent(unBalanced);
        if (d1) {
            unBalanced->setRight(t);
        } else {
            unBalanced->setLeft(t);
        }
    } else {
        AVLTree<T> *t1 = n2->getLeft();
        AVLTree<T> *t2 = n2->getRight();
        n2->setParent(unBalanced->getParent());
        n2->setLeft(unBalanced);
        unBalanced->setParent(n2);
        n2->setRight(n1);
        n1->setParent(n2);
        if (d1) {
            n1->setRight(t1);
            unBalanced->setLeft(t2);
        } else {
            n1->setLeft(t2);
            unBalanced->setRight(t1);
        }
    }
}

template<class T>
void AVLTree<T>::setLeft(AVLTree<T> *left) {
    if (this) {
        this->left = left;
    }
}

template<class T>
void AVLTree<T>::setRight(AVLTree<T> *right) {
    if (this) {
        this->right = right;
    }
}

template<class T>
AVLTree<T> *AVLTree<T>::getLeft() const {
    if (this) {
        return this->left;
    }
    return nullptr;
}

template<class T>
AVLTree<T> *AVLTree<T>::getRight() const {
    if (this) {
        return this->right;
    }
    return nullptr;
}

template<class T>
AVLTree<T> *AVLTree<T>::getParent() const {
    if (this) {
        return this->parent;
    }
    return nullptr;
}


#endif //DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
