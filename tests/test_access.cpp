#include <gtest/gtest.h>

#include "my_shared_pointer.hpp"

// test get() on null pointer
TEST(MySharedPointerAccess, GetNullPointer) {
    MySharedPointer<int> msp;
    EXPECT_EQ(msp.get(), nullptr);
}

// test get() on non-null pointer
TEST(MySharedPointerAccess, GetNonNullPointer) {
    int* obj = new int(42);
    MySharedPointer<int> msp(obj);
    EXPECT_EQ(msp.get(), obj);
}

// test operator*() on null pointer
TEST(MySharedPointerAccess, DereferenceNullPointer) {
    MySharedPointer<int> msp;
    EXPECT_THROW(*msp, std::runtime_error);
}       

// test operator*() on non-null pointer
TEST(MySharedPointerAccess, DereferenceNonNullPointer) {
    int* obj = new int(42);
    MySharedPointer<int> msp(obj);
    EXPECT_EQ(*msp, 42);
}

// test operator->() on null pointer
TEST(MySharedPointerAccess, ArrowNullPointer) {
    struct TestStruct {
        int value;
    };
    MySharedPointer<TestStruct> msp;
    EXPECT_THROW(msp->value, std::runtime_error);
}

// test operator->() on non-null pointer
TEST(MySharedPointerAccess, ArrowNonNullPointer) {
    struct TestStruct {
        int value;
    };
    TestStruct* obj = new TestStruct{42};
    MySharedPointer<TestStruct> msp(obj);
    EXPECT_EQ(msp->value, 42);
}

// test use_count() on null pointer
TEST(MySharedPointerAccess, UseCountNullPtr) {
    MySharedPointer<int> msp;

    EXPECT_EQ(msp.use_count(), 0);
}


// test use_count() on non-null pointer
TEST(MySharedPointerAccess, UseCountNonNullPtr) {
    MySharedPointer<int> msp(new int(53));

    EXPECT_EQ(msp.use_count(), 1);
}