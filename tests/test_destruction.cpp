#include <gtest/gtest.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cerrno>

#include "my_shared_pointer.hpp"


// helper struct to track destruction (wraps a file)
struct FileHolder {
    int fd;     // file descriptor

    // constructor opens the file
    FileHolder(const std::string& path) 
        // create a new file with read-write premmissions, truncating it if it already exists
        : fd(open(path.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0644))
    {
    }

    ~FileHolder() {
        if (fd >= 0) {
            close(fd);
            fd = -1;
        }
    }

    int get_fd() const { return fd; }

};

// test destruction of MySharedPointer 
TEST(MySharedPointerTest, FileHolderDestruction) {

    std::string path = "test_file.txt";
    int current_fd = -1;

    {
        // create a MySharedPointer that manages a FileHolder object, which opens a file
        MySharedPointer<FileHolder> msp1(new FileHolder(path));
        current_fd = msp1->get_fd();
        EXPECT_NE(msp1.get(), nullptr);
        EXPECT_EQ(msp1.use_count(), 1);
        EXPECT_NE(fcntl(current_fd, F_GETFD), -1);
        {
            //  duplicate the MySharedPointer to test that the reference count is correctly updated and that the file is not closed until all MySharedPointer instances are destroyed
            MySharedPointer<FileHolder> msp2(msp1);
            EXPECT_EQ(msp1.use_count(), 2);
            EXPECT_EQ(msp2.use_count(), msp1.use_count());
            EXPECT_EQ(msp2->get_fd(), current_fd);
            EXPECT_NE(fcntl(current_fd, F_GETFD), -1);
        }
        // after msp2 goes out of scope, the file should still be open because msp1 is still managing it
        EXPECT_EQ(msp1.use_count(), 1);
        EXPECT_NE(fcntl(current_fd, F_GETFD), -1);
    }
    // make sure the file is closed after msp1 goes out of scope
    EXPECT_EQ(fcntl(current_fd, F_GETFD), -1); // file should be closed after msp1 goes out of scope
    EXPECT_EQ(errno, EBADF); // check that the error is EBADF (bad file descriptor)

    // remove the test file
    std::remove(path.c_str());
}