//
// Created by pcxie on 2020/12/7.
//

#ifndef DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
#define DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H

#include <string>

template<class T>
class AVLTree {
    friend class AVLTreeTests;

protected:
    void setParent(AVLTree *parent);

    AVLTree<T> *getNext(int key);

    bool setNext(int key, T object);

    AVLTree<T> *getAncestor();

    bool hasNext() const;

    bool isBalanced() const;

    AVLTree<T> *getUnBalancedNode();

    void balanceTree();
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
    this->parent = parent;
}

template<class T>
AVLTree<T> *AVLTree<T>::getNext(int key) {
    return this->key < key ? right : left;
}

template<class T>
bool AVLTree<T>::setNext(int key, T object) {
    if (this->key < key) {
        if (this->right != nullptr) {
            return false;
        }
        auto *toSet = new AVLTree<T>(key, object);
        toSet->setParent(this);
        this->right = toSet;
        return true;
    } else {
        if (this->left != nullptr) {
            return false;
        }
        auto *toSet = new AVLTree<T>(key, object);
        toSet->setParent(this);
        this->left = toSet;
        return true;
    }
}

template<class T>
AVLTree<T> *AVLTree<T>::getAncestor() {
    return this->parent == nullptr ? this : this->parent->getAncestor();
}

template<class T>
bool AVLTree<T>::hasNext() const {
    return right == nullptr || left == nullptr;
}

template<class T>
bool AVLTree<T>::isBalanced() const {
    return abs(left->getHeight() - right->getHeight()) <= 1;
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
    if (this->key == key) {
        return this->object;
    } else if (getNext(key) == nullptr) {
        return NULL;
    } else {
        return this->getNext(key)->search(key);
    }
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
AVLTree<T> *AVLTree<T>::getUnBalancedNode() {
    return nullptr;
}

template<class T>
void AVLTree<T>::balanceTree() {
    if(isBalanced()){
        return;
    }

}


#endif //DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
