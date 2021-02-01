//
// Created by pcxie on 2020/12/7.
//

#ifndef DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
#define DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H

#include <string>
#include <cmath>

//TODO: Dynamic Programming (getHeight())

template<class T>
class AVLTree {
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

        Node(int key, T object);

        ~Node();

        inline Node *getNext(int key);

        inline Node *getNext(dir dir);

        inline void setNext(dir dir, Node *p);

        inline void setNext(int key, Node *p);

        inline void clearChild();
    };

    Node *pRoot;

    unsigned int size;

    bool isBalanced(Node *p);

    Node *getUnbalancedNode(Node *leaf);

    void balance(Node *unBalanced);

    unsigned int getHeight(Node *p);

    Node *treeExtreme(Node *p, dir dir);

    Node *getSuccessor(Node *p, dir dir);

    std::string keyIterate(Node *p);

    T remove(Node *p);

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

    std::string getKeys();
};

template<class T>
AVLTree<T>::Node::Node(int key, T object):key(key), object(object) {
    pLeft = nullptr;
    pRight = nullptr;
    pParent = nullptr;
}

template<class T>
AVLTree<T>::Node::~Node() {
    delete pLeft;
    delete pRight;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getNext(int key) {
    return this->key < key ? pRight : pLeft;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::Node::getNext(dir dir) {
    return dir ? this->pRight : this->pLeft;
}

template<class T>
void AVLTree<T>::Node::setNext(AVLTree::dir dir, AVLTree::Node *p) {
    if (p) {
        p->pParent = this;
    }
    if (dir) {
        this->pRight = p;
    } else {
        this->pLeft = p;
    }
}

template<class T>
void AVLTree<T>::Node::setNext(int key, AVLTree::Node *p) {
    dir dir = this->key < key ? right : left;
    setNext(dir, p);
}

template<class T>
void AVLTree<T>::Node::clearChild() {
    pLeft = nullptr;
    pRight = nullptr;
}

template<class T>
AVLTree<T>::AVLTree() {
    pRoot = nullptr;
    size = 0;
}

template<class T>
AVLTree<T>::~AVLTree() {
    delete pRoot;
}

template<class T>
unsigned int AVLTree<T>::getSize() const {
    return size;
}

template<class T>
unsigned int AVLTree<T>::getHeight() {
    return getHeight(pRoot);
}

template<class T>
bool AVLTree<T>::insert(int key, const T &object) {
    if (!pRoot) {
        pRoot = new Node(key, object);
        size++;
        return true;
    }
    Node *current = pRoot;
    for (Node *next = current->getNext(key); next != nullptr; next = current->getNext(key)) {
        if (current->key == key) {
            return false;
        }
        current = next;
    }
    auto *toSet = new Node(key, object);
    current->setNext(key, toSet);
    balance(getUnbalancedNode(toSet));
    size++;
    return true;
}

template<class T>
T AVLTree<T>::search(int key) const {
    Node *current = pRoot;
    for (Node *next = current->getNext(key); next != nullptr; next = current->getNext(key)) {
        if (current->key == key) {
            return current->object;
        }
        current = next;
    }
    return NULL;
}

template<class T>
T AVLTree<T>::remove(int key) {
    Node *current = pRoot;
    for (Node *next = current->getNext(key); current != nullptr; next = current->getNext(key)) {
        if (current->key == key) {
            return remove(current);
        }
        current = next;
    }
    return NULL;
}

template<class T>
T AVLTree<T>::remove(AVLTree::Node *p) {
    T _ = p->object;
    Node *childLeft = p->getNext(left);
    Node *childRight = p->getNext(right);
    Node *parent = p->pParent;
    Node *unBalanced;
    dir dir = parent && parent->getNext(left) == p ? left : right;
    if (childLeft && childRight) {
        Node *successor = getSuccessor(p, right);
        Node *successorChild = successor->getNext(right);
        Node *successorParent = successor->pParent;
        if (parent) {
            parent->setNext(dir, successor);
        } else {
            pRoot = successor;
            successor->pParent = nullptr;
        }
        successor->setNext(left, childLeft);
        if (successor != childRight) {
            successor->setNext(right, childRight);
            successorParent->setNext(left, successorChild);
        }
        unBalanced = getUnbalancedNode(successor);
    } else if (childRight) {
        if (parent) {
            parent->setNext(dir, childRight);
        } else {
            pRoot = childRight;
            childRight->pParent = nullptr;
        }
        unBalanced = getUnbalancedNode(childRight);
    } else if (childLeft) {
        if (parent) {
            parent->setNext(dir, childLeft);
        } else {
            pRoot = childLeft;
            childLeft->pParent = nullptr;
        }
        unBalanced = getUnbalancedNode(childLeft);
    } else {
        if (parent) {
            parent->setNext(dir, nullptr);
        } else {
            pRoot = nullptr;
        }
        unBalanced = getUnbalancedNode(parent);
    }
    while (unBalanced != nullptr) {
        Node *next = unBalanced->pParent;
        balance(unBalanced);
        unBalanced = getUnbalancedNode(next);
    }
    p->clearChild(); //So that it will not delete other nodes by its destructor.
    delete p;
    size--;
    return _;
}

template<class T>
bool AVLTree<T>::isEmpty() const {
    return !pRoot;
}

template<class T>
void AVLTree<T>::reset() {
    size = 0;
    delete pRoot;
    pRoot = nullptr;
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
    if (p) {
        return abs((int) getHeight(p->getNext(left)) - (int) getHeight(p->getNext(right))) <= 1;
    }
    return true;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::getUnbalancedNode(AVLTree::Node *leaf) {
    if (!leaf) {
        return nullptr;
    }
    if (!isBalanced(leaf)) {
        return leaf;
    }
    return getUnbalancedNode(leaf->pParent);
}

template<class T>
void AVLTree<T>::balance(AVLTree<T>::Node *unBalanced) {
    if (isBalanced(unBalanced)) {
        return;
    }
    dir d1 = getHeight(unBalanced->getNext(left)) >= getHeight(unBalanced->getNext(right)) ? left : right;
    Node *n1 = unBalanced->getNext(d1);
    dir d2 = getHeight(n1->getNext(left)) >= getHeight(n1->getNext(right)) ? left : right;
    Node *n2 = n1->getNext(d2);
    if (d1 == d2) {
        // Single rotation
        Node *t = d1 ? n1->getNext(left) : n1->getNext(right);
        Node *p = unBalanced->pParent;
        if (p) {
            p->setNext(n1->key, n1);
        } else {
            n1->pParent = nullptr;
            pRoot = n1;
        }
        n1->setNext(d1 ? left : right, unBalanced);
        unBalanced->setNext(d1, t);
    } else {
        // Double rotation
        Node *t1 = n2->getNext(d1);
        Node *t2 = n2->getNext(d2);
        Node *p = unBalanced->pParent;
        if (p) {
            p->setNext(n2->key, n2);
        } else {
            n2->pParent = nullptr;
            pRoot = n2;
        }
        n2->setNext(d2, unBalanced);
        n2->setNext(d1, n1);
        n1->setNext(d2, t1);
        unBalanced->setNext(d1, t2);
    }
}

template<class T>
std::string AVLTree<T>::getKeys() {
    std::string _ = keyIterate(pRoot);
    _.pop_back();
    return _;
}

template<class T>
std::string AVLTree<T>::keyIterate(AVLTree::Node *p) {
    std::string _ = p->getNext(left) ? keyIterate(p->getNext(left)) : "";
    _ += std::to_string(p->key) + " ";
    _ += p->getNext(right) ? keyIterate(p->getNext(right)) : "";
    return _;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::treeExtreme(AVLTree::Node *p, AVLTree::dir dir) {
    return p->getNext(dir) ? treeExtreme(p->getNext(dir), dir) : p;
}

template<class T>
typename AVLTree<T>::Node *AVLTree<T>::getSuccessor(AVLTree::Node *p, AVLTree::dir dir) {
    if (p->getNext(dir)) {
        return treeExtreme(p->getNext(dir), dir ? left : right);
    } else {
        Node *current = p;
        Node *next = current->pParent;
        for (; next != nullptr && next->getNext(dir ? left : right) != current; next = current->pParent) {
            current = next;
        }
        return next;
    }
}


#endif //DATASTRUCTURES_AND_ALGORITHMS_AVLTREE_H
