#include <gtest/gtest.h>

#include "my_shared_pointer.hpp"

using namespace std;

// test copy assignment when both MySharedPointer instances manage the same object
TEST(MySharedPointerAssignment, CopyAssinmentSameObjects)
{
    int* object = new int(42);    
    MySharedPointer<int> msp1(object);
    MySharedPointer<int> msp2(msp1);
    msp2 = msp1;
    EXPECT_EQ(msp1.get(), msp2.get());
    EXPECT_EQ(msp1.use_count(), msp2.use_count());
    EXPECT_EQ(msp1.use_count(), 2);
}

// test copy assignment when both MySharedPointer instances manage different objects
TEST(MySharedPointerAssignment, CopyAssinmentDifferentObjects)
{
    MySharedPointer<int> msp1(new int(42));
    MySharedPointer<int> msp2(new int(45));
    msp2 = msp1;
    EXPECT_EQ(msp1.get(), msp2.get());
    EXPECT_EQ(msp1.use_count(), msp2.use_count());
    EXPECT_EQ(msp1.use_count(), 2);
    EXPECT_EQ(*msp2, 42);
}

// test self-assignment for copy assignment operator
TEST(MySharedPointerAssignment, CopySelfAssignment)
{
    MySharedPointer<int> msp1(new int(42));
    EXPECT_THROW(msp1 = msp1, std::runtime_error);
}


// test move assignment when both MySharedPointer instances manage the same object
TEST(MySharedPointerAssignment, MoveAssinmentSameObjects)
{
    int* object = new int(42);    
    MySharedPointer<int> msp1(object);
    MySharedPointer<int> msp2(msp1);

    msp2 = std::move(msp1);
    EXPECT_EQ(msp1.get(), nullptr);
    EXPECT_EQ(msp1.use_count(), 0);
    EXPECT_NE(msp2.get(), nullptr);
    EXPECT_EQ(msp2.use_count(), 1);
    EXPECT_EQ(*msp2, 42);
}

// test copy assignment when both MySharedPointer instances manage different objects
TEST(MySharedPointerAssignment, MoveAssinmentDifferentObjects)
{
    MySharedPointer<int> msp1(new int(42));
    MySharedPointer<int> msp2(new int(45));
    msp2 = std::move(msp1);
    EXPECT_EQ(msp1.get(), nullptr);
    EXPECT_EQ(msp1.use_count(), 0);
    EXPECT_NE(msp2.get(), nullptr);
    EXPECT_EQ(msp2.use_count(), 1);
    EXPECT_EQ(*msp2, 42);
}

// test self-assignment for move assignment operator
TEST(MySharedPointerAssignment, MoveSelfAssignment)
{
    MySharedPointer<int> msp1(new int(42));
    EXPECT_THROW(msp1 = std::move(msp1), std::runtime_error);
}
