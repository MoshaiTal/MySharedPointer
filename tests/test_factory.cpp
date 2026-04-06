#include <gtest/gtest.h>

#include "my_shared_pointer.hpp"

// test MakeShared function
TEST(MakeMySahredPointer, CreateSharedPointer) {
    struct TestStruct{
        int int_val;
        char char_val;
        TestStruct(int i, char c) : int_val(i), char_val(c) {}
    };

    MySharedPointer<TestStruct> msp = MakeShared<TestStruct>(15, 't');

    EXPECT_NE(msp.get(), nullptr);
    EXPECT_EQ(msp.use_count(), 1);
    EXPECT_EQ(msp->int_val, 15);
    EXPECT_EQ(msp->char_val, 't');
    
}
  
