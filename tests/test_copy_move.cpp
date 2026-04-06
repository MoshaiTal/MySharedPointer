#include <gtest/gtest.h>

#include "my_shared_pointer.hpp"

// test the copy constructor of MySharedPointer
TEST(MySharedPointerCopyMove, CopyConstructorIncreasesCount)
{
    MySharedPointer<int> msp1(new int(5));
    MySharedPointer<int> msp2(msp1);
    EXPECT_EQ(msp1.get(), msp2.get());
    EXPECT_EQ(msp1.use_count(), 2);
    EXPECT_EQ(msp2.use_count(), 2);
}

// test the copy constructor of MySharedPointer with a null pointer
TEST(MySharedPointerCopyMove,CopyConstructorWithNullPointer)
{
    MySharedPointer<int> msp1;
    MySharedPointer<int> msp2(msp1);
    EXPECT_EQ(msp1.get(),msp2.get());
    EXPECT_EQ(msp1.get(), nullptr);
    EXPECT_EQ(msp2.get(), nullptr);
    EXPECT_EQ(msp1.use_count(), 0);
    EXPECT_EQ(msp2.use_count(), 0);
}

// test the move constructor of MySharedPointer
TEST(MySharedPointerCopyMove, MoveConstructorTransfersOwnership)
{
    MySharedPointer<int> msp1(new int(10));
    MySharedPointer<int> msp2(std::move(msp1));
    EXPECT_EQ(msp1.get(), nullptr);
    EXPECT_EQ(msp1.use_count(), 0);
    EXPECT_NE(msp2.get(), nullptr);
    EXPECT_EQ(msp2.use_count(), 1);
}