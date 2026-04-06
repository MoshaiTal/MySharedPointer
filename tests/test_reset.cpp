#include <gtest/gtest.h>

#include "my_shared_pointer.hpp"

// test reset() on a null shared pointer that is assigned a new object
TEST(SharedPointerTest, ResetNullPointerToNewObject) {
    MySharedPointer<int> msp;
    int* obj = new int(13);
    msp.reset(obj);

    EXPECT_EQ(*msp,13);
    EXPECT_EQ(msp.use_count(), 1);
}

// test reset() on a non-null shared pointer that is assigned a new object
TEST(SharedPointerTest, ResetNonNullPointerToNewObject) {
    int *obj1 = new int(16);
    int *obj2 = new int(13);
    MySharedPointer<int> msp1(obj1);
    MySharedPointer<int> msp2(msp1);            // msp2 shares ownership of obj1
    
    msp1.reset(obj2);

    EXPECT_EQ(msp1.get(), obj2);
    EXPECT_EQ(msp1.use_count(), 1);
    EXPECT_EQ(msp2.get(), obj1);
    EXPECT_EQ(msp2.use_count(), 1);
}

// test reset() on a non-null shared pointer that is assigned a null pointer
TEST(SharedPointerTest, ResetNonNullPointerToNull) {
    MySharedPointer<int> msp(new int(20));
    msp.reset(nullptr);

    EXPECT_EQ(msp.get(), nullptr);
    EXPECT_EQ(msp.use_count(), 0);
}

// test reset() on a non-null shared pointer that is assigned the same object (should not change anything)
TEST(SharedPointerTest, ResetNonNullPointerToSameObject) {
    int* obj = new int(13);
    MySharedPointer<int> msp(obj);
    msp.reset(obj);

    EXPECT_EQ(msp.get(), obj);
    EXPECT_EQ(msp.use_count(), 1);
}
