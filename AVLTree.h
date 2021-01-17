//
// Created by pcxie on 2020/12/7.
//

#ifndef DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
#define DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H

#include <string>
#include <cmath>
#include <stdexcept>

template<class T>
class AVLTree {
    friend class AVLTreeTests;

private:
    enum dir : bool {
        left = 0, right = 1
    };

    class Node {
    public:
        int key;
        T object;
        Node *pLeft;
        Node *pRight;
        Node *pParent;
        AVLTree<T> *tree;

        Node(int key, T object, AVLTree<T> *tree);

        inline Node *getNext(int key);

        inline Node *getNext(dir dir);

        inline Node *getParent();

        inline int getKey();

        inline T getObject();

        void setNext(int key, T object);

        void setNext(dir dir, Node *p);

        void setNext(int key, Node *p);

        void setAndBalance(int key, T object);

        void setParent(Node *p);

    };

    Node *pHead;

    unsigned int size;

    bool isBalanced(Node *p);

    Node *getUnbalancedNode(Node *leaf);

    void balance(Node *unBalanced);

    unsigned int getHeight(Node *p);

public:
    AVLTree();

    ~AVLTree();

    unsigned int getSize() const;

    unsigned int getHeight();

    bool insert(int key, const T &object);

    T remove(int key);

    T search(int key) const;

    bool isEmpty() const;

    void reset();
};

template<class T>
AVLTree<T>::Node::Node(int key, T object, AVLTree<T> *tree):key(key), object(object), tree(tree) {
    pLeft = nullptr;
    pRight = nullptr;
    pParent = nullptr;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getNext(int key) {
    if (this) {
        return this->getKey() < key ? pRight : pLeft;
    }
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getNext(dir dir) {
    if (this) {
        return dir ? this->pRight : this->pLeft;
    }
    return nullptr;
}

template<class T>
int AVLTree<T>::Node::getKey() {
    if (this) {
        return this->key;
    }
}

template<class T>
T AVLTree<T>::Node::getObject() {
    if (this) {
        return this->object;
    }
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getParent() {
    if (this) {
        return this->pParent;
    }
}

template<class T>
void AVLTree<T>::Node::setParent(AVLTree::Node *p) {
    if (this) {
        this->pParent = p;
    }
}

template<class T>
void AVLTree<T>::Node::setNext(AVLTree::dir dir, AVLTree::Node *p) {
    p->setParent(this);
    if (dir) {
        this->pRight = p;
    } else {
        this->pLeft = p;
    }
}

template<class T>
void AVLTree<T>::Node::setNext(int key, T object) {
    auto *toSet = new Node(key, object, this->tree);
    setNext(key, toSet);
}

template<class T>
void AVLTree<T>::Node::setNext(int key, AVLTree::Node *p) {
    dir dir = this->getKey() < key ? right : left;
    setNext(dir, p);
}

template<class T>
void AVLTree<T>::Node::setAndBalance(int key, T object) {
    auto *toSet = new Node(key, object, this->tree);
    setNext(key, toSet);
    tree->balance(tree->getUnbalancedNode(toSet));
}

template<class T>
AVLTree<T>::AVLTree() {
    pHead = nullptr;
    size = 0;
}

template<class T>
AVLTree<T>::~AVLTree() {
    delete left;
    delete right;
}

template<class T>
unsigned int AVLTree<T>::getSize() const {
    return size;
}

template<class T>
unsigned int AVLTree<T>::getHeight() {
    return getHeight(pHead);
}

template<class T>
bool AVLTree<T>::insert(int key, const T &object) {
    if (!pHead) {
        pHead = new Node(key, object, this);
        size++;
        return true;
    }
    Node *current = pHead;
    for (Node *next = current->getNext(key); next != nullptr; next = current->getNext(key)) {
        if (current->getKey() == key) {
            return false;
        }
        current = next;
    }
    current->setAndBalance(key, object);
    size++;
    return true;
}

template<class T>
T AVLTree<T>::search(int key) const {
    Node *current = pHead;
    while (current != nullptr) {
        if (current->getKey() == key) {
            return current->getObject();
        } else {
            current = current->getNext(key);
        }
    }
    return NULL;
}

template<class T>
T AVLTree<T>::remove(int key) {

}

template<class T>
bool AVLTree<T>::isEmpty() const {
    return !pHead;
}

template<class T>
void AVLTree<T>::reset() {
    delete pHead;
    pHead = nullptr;
}

template<class T>
unsigned int AVLTree<T>::getHeight(AVLTree::Node *p) {
    unsigned int i = 0;
    if (p) {
        i++;
        unsigned int max = std::max(getHeight(p->getNext(left)), getHeight(p->getNext(right)));
        i += max;
    }
    return i;
}

template<class T>
bool AVLTree<T>::isBalanced(AVLTree::Node *p) {
    return abs((int) getHeight(p->getNext(left)) - (int) getHeight(p->getNext(right))) <= 1;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::getUnbalancedNode(AVLTree::Node *leaf) {
    if (leaf == nullptr) {
        return nullptr;
    }
    if (!isBalanced(leaf)) {
        return leaf;
    }
    return getUnbalancedNode(leaf->getParent());
}

template<class T>
void AVLTree<T>::balance(AVLTree<T>::Node *unBalanced) {
    if (isBalanced(unBalanced)) {
        return;
    }
    dir d1;
    dir d2;
    Node *n1;
    Node *n2;
    if (getHeight(unBalanced->getNext(left)) >= getHeight(unBalanced->getNext(right))) {
        d1 = dir::left;
        n1 = unBalanced->getNext(left);
    } else {
        d1 = dir::right;
        n1 = unBalanced->getNext(right);
    }
    if (getHeight(n1->getNext(left)) >= getHeight(n1->getNext(right))) {
        d2 = dir::left;
        n2 = n1->getNext(left);
    } else {
        d2 = dir::right;
        n2 = n1->getNext(right);
    }
    if (d1 == d2) {
        Node *t = d1 ? n1->getNext(left) : n1->getNext(right);
        Node *p = unBalanced->getParent();
        if (p) {
            p->setNext(n1->getKey(), n1);
        } else {
            n1->setParent(nullptr);
            pHead = n1;
        }
        n1->setNext(d1?left:right,unBalanced);
        if (d1) {
            unBalanced->setNext(right, t);
        } else {
            unBalanced->setNext(left, t);
        }
    } else {
        Node *t1 = n2->getNext(left);
        Node *t2 = n2->getNext(right);
        Node *p = unBalanced->getParent();
        if (p) {
            p->setNext(n2->getKey(), n2);
        } else {
            n2->setParent(nullptr);
            pHead = n2;
        }
        n2->setNext(d2, unBalanced);
        n2->setNext(d1, n1);
        if (d1) {
            n1->setNext(left, t2);
            unBalanced->setNext(right, t1);
        } else {
            n1->setNext(right, t2);
            unBalanced->setNext(left, t1);
        }
    }
}


#endif //DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
