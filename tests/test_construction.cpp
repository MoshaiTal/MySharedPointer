#include <gtest/gtest.h>

#include "my_shared_pointer.hpp"

// test the construction of MySharedPointer
TEST(MySharedPointerConstruction, DefaultConstructorIsEmpty)
{
    MySharedPointer<int> msp;
    EXPECT_EQ(msp.get(), nullptr);
}

// test the construction of MySharedPointer
TEST(MySharedPointerConstruction, DefaultConstructorHasCountZero)
{
    MySharedPointer<int> msp;
    EXPECT_EQ(msp.use_count(), 0);
}

// test the construction of MySharedPointer with a raw pointer
TEST(MySharedPointerConstruction, RawPointerConstructorHasCountOne)
{
    MySharedPointer<int> msp(new int(5));
    EXPECT_NE(msp.get(), nullptr);
    EXPECT_EQ(msp.use_count(), 1);
}

// test the construction of MySharedPointer with a raw pointer
TEST(MySharedPointerConstruction, NullRawPointerConstructorHasCountZero)
{
    MySharedPointer<int> msp(nullptr);
    EXPECT_EQ(msp.get(), nullptr);
    EXPECT_EQ(msp.use_count(), 0);
}