//
// Created by pcxie on 2020/12/3.
//

#include "gtest/gtest.h"
#include "../includes/LinkedList.h"

class LinkedListTests : public ::testing::Test {
protected:
    void SetUp () override {
        list.pushFront(1);
        list.pushBack(2);
        list.pushFront(3);
        list.pushFront(4);
        list.pushBack(5);
    }

    LinkedList<int> list;
};

TEST_F(LinkedListTests,PushPopTest){
    EXPECT_EQ(5,list.popBack());
    EXPECT_EQ(2,list.popBack());
    EXPECT_EQ(1,list.popBack());
    EXPECT_EQ(4,list.popFront());
    EXPECT_EQ(3,list.popBack());
    EXPECT_EQ(0,list.popBack());
}

TEST_F(LinkedListTests,GetSizeTest){
    EXPECT_EQ(5,list.getSize());
}

TEST_F(LinkedListTests, ClearTest){
    list.clear();
    EXPECT_EQ(0,list.popBack());
    EXPECT_EQ(0,list.getSize());
}

TEST_F(LinkedListTests, SubscriptTest){
    EXPECT_EQ(4,list[0]);
    EXPECT_EQ(3,list[1]);
    EXPECT_EQ(1,list[2]);
    EXPECT_EQ(2,list[3]);
    EXPECT_EQ(5,list[4]);
    list[4] = 3;
    EXPECT_EQ(3,list[4]);
}
