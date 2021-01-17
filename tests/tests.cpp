//
// Created by pcxie on 2020/12/3.
//

#include <utility>
#include <exception>
#include <cmath>

#include "gtest/gtest.h"
#include "../LinkedList.h"
#include "../Heap.h"
#include "../AVLTree.h"
#include "../DisjointSet.h"

int *generateRandomIntegerArray(int n) {
    if (n <= 0) {
        throw std::invalid_argument("Array size must be positive integers.");
    }
    int *ar = new int[n];
    std::srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        ar[i] = std::rand();
    }
    return ar;
};

class ArraySort : public ::testing::Test {
protected:
    void SetUp() override {
        array = generateRandomIntegerArray(n);
    }

    int n = 10;
    int *array;

    std::function<bool(int, int)> compare = [](int a, int b) {
        return a >= b;
    };

    static bool inOrder(int n, int *array, std::function<bool(int, int)> compare) {
        for (int i = 0; i < n-1; i++) {
            if (!compare(array[i],array[i+1])){
                return false;
            }
        }
        return true;
    }
};

class LinkedListTests : public ::testing::Test {
protected:
    void SetUp() override {
        list.pushFront(1);
        list.pushBack(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushBack(5);
    }

    LinkedList<int> list;
};

TEST_F(LinkedListTests, PushPopTest) {
    EXPECT_EQ(5, list.popBack());
    EXPECT_EQ(2, list.popBack());
    EXPECT_EQ(1, list.popBack());
    EXPECT_EQ(4, list.popFront());
    EXPECT_EQ(3, list.popBack());
    EXPECT_EQ(0, list.popBack());
}

TEST_F(LinkedListTests, GetSizeTest) {
    EXPECT_EQ(5, list.getSize());
}

TEST_F(LinkedListTests, ClearTest) {
    list.clear();
    EXPECT_EQ(0, list.popBack());
    EXPECT_EQ(0, list.getSize());
}

TEST_F(LinkedListTests, SubscriptTest) {
    EXPECT_EQ(4, list[0]);
    EXPECT_EQ(3, list[1]);
    EXPECT_EQ(1, list[2]);
    EXPECT_EQ(2, list[3]);
    EXPECT_EQ(5, list[4]);
    list[4] = 3;
    EXPECT_EQ(3, list[4]);
}

class HeapTests : public ArraySort {

};

TEST_F(HeapTests, HeapifyTest) {

}

TEST_F(HeapTests, BuildHeapTest) {
    Heap<int>::buildHeap(n, array, compare);
    int max = array[0];
    for (int i = 1; i < n; i++) {
        EXPECT_TRUE(max>array[i]);
    }
}

TEST_F(HeapTests, HeapSortTest) {
    Heap<int>::heapSort(n, array, compare);
    EXPECT_TRUE(!inOrder(n,array,compare));
}

class AVLTreeTests : public ::testing::Test{
protected:
    void SetUp() override {
        tree = new AVLTree<int>();
    }
    AVLTree<int> *tree;
};

TEST_F(AVLTreeTests, edgeCaseTests){
    EXPECT_EQ(0,tree->getSize());
    EXPECT_EQ(0,tree->getHeight());
    tree->insert(1,1);
    EXPECT_EQ(1,tree->getSize());
    EXPECT_EQ(1,tree->getHeight());
}

TEST_F(AVLTreeTests,test1){
    tree->insert(3, 3);
    tree->insert(2,2);
    tree->insert(1,1);
    tree->insert(4,4);
    tree->insert(5,5);
    tree->insert(6,6);
    tree->insert(7,7);
    tree->insert(16,16);
    tree->insert(4,4);
    tree->insert(15,15);
    tree->insert(14,14);
    tree->insert(13,13);
    tree->insert(12,12);
    tree->insert(11,11);
    tree->insert(10,10);
    tree->insert(8,8);
    tree->insert(9,9);
    EXPECT_EQ(17,tree->getSize());
    EXPECT_EQ(5,tree->getHeight());

}

TEST(DisjointSetTests,test0){
    auto set = DisjointSet(6);
    EXPECT_EQ(1,set.find(1));
    set.merge(1,2);
    EXPECT_EQ(set.find(1),set.find(2));
    set.merge(1,3);
    set.merge(4,5);
    set.merge(3,5);
    EXPECT_EQ(set.find(3),set.find(4));

}