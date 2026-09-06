#include <gtest/gtest.h>
#include "mylib/Stack/Stack.hpp" 

TEST(StackTest, PushAndPeek) {
    myLib::Stack<int> s(5);
    s.push(10);
    s.push(20);
    EXPECT_EQ(s.peek(), 20);
}

TEST(StackTest, PopReturnsCorrectValue) {
    myLib::Stack<int> s(5);
    s.push(10);
    s.push(20);
    int popped = s.pop();
    EXPECT_EQ(popped, 20);
    EXPECT_EQ(s.peek(), 10);
}

TEST(StackTest, IsEmptyAndIsFull) {
    myLib::Stack<int> s(2);
    EXPECT_TRUE(s.isEmpty());
    s.push(1);
    s.push(2);
    EXPECT_TRUE(s.isFull());
}

TEST(StackTest, PopOnEmptyThrows) {
    myLib::Stack<int> s(3);
    EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(StackTest, PeekOnEmptyThrows) {
    myLib::Stack<int> s(3);
    EXPECT_THROW(s.peek(), std::out_of_range);
}

TEST(StackTest, DeepCopyConstructor) {
    myLib::Stack<int> s(5);
    s.push(10);
    s.push(20);

    myLib::Stack<int> s2 = s;
    s2.push(999);

    EXPECT_EQ(s.peek(), 20);
    EXPECT_EQ(s2.peek(), 999);
}

TEST(StackTest, DeepCopyAssignment) {
    myLib::Stack<int> s(5);
    s.push(10);
    s.push(20);

    myLib::Stack<int> s2(3);
    s2 = s;
    s2.push(999);

    EXPECT_EQ(s.peek(), 20);
    EXPECT_EQ(s2.peek(), 999);
}

TEST(StackTest, DynamicResize) {
    myLib::Stack<int> s(2);
    for (int i = 1; i <= 10; i++) {
        s.push(i);
    }
    EXPECT_EQ(s.peek(), 10);
    EXPECT_FALSE(s.isEmpty());
}

TEST(StackTest, DeepCopyPreservesAllElements) {
    myLib::Stack<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);

    myLib::Stack<int> s2 = s;
    EXPECT_EQ(s2.pop(), 3);
    EXPECT_EQ(s2.pop(), 2);   // this is the exact case that caught your earlier <= bug!
    EXPECT_EQ(s2.pop(), 1);
}