# MySharedPointer
A C++ implementation of a custom `shared_ptr`-like smart pointer from scratch.

Project Structure:
MySharedPointer
├── include
│   ├── my_shared_pointer.hpp
│   └── control_block.hpp
├── tests
│   ├── test_construction.cpp
│   ├── test_copy_move.cpp
│   ├── test_assignment.cpp
│   ├── test_destructor.cpp
│   ├── test_reset.cpp
│   ├── test_factory.cpp
│   └── test_access.cpp
└── CMakeLists.txt

Compiling sequence:
1. cmake -S . -B build
2. cmake --build build
3. ctest --test-dir build --output-on-failure