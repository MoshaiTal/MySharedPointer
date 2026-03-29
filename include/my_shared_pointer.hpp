#include <stdexcept>
#include <utility>
#include <functional>
#include "control_block.hpp"


// MySharedPointer class template definition
template <typename T>
class MySharedPointer {
    private:
        T* ptr;                           // Pointer to the managed object
        ControlBlock<T>* control_block;   // Pointer to the control block

        void release(){
            if (control_block != nullptr) {
                control_block->ref_count--;
                if (control_block->ref_count == 0) {
                    control_block->deleter(ptr);
                    delete control_block;
                }
                ptr = nullptr;
                control_block = nullptr;
            }
        }

    public:
        // Default constructor
        MySharedPointer() : ptr(nullptr), control_block(nullptr){}

        // Constructor that takes a raw pointer and an optional deleter
        MySharedPointer(T* t, std::function<void(T*)> deleter = [](T* p){ delete p; })
            : ptr(t), control_block(nullptr) {
            if (t != nullptr) {
                control_block = new ControlBlock<T>(deleter);
            }
        }

        // Copy constructor
        MySharedPointer(const MySharedPointer<T>& other) : ptr(other.ptr), control_block(other.control_block) {
            if (other.control_block != nullptr) {
                control_block->ref_count++;
            }
        }

        // Move constructor
        MySharedPointer(MySharedPointer<T>&& other) : ptr(other.ptr), control_block(other.control_block) {
            other.ptr = nullptr;
            other.control_block = nullptr;
        }

        // Destructor
        ~MySharedPointer() {
            release();
        }

        // Copy assignment operator
        MySharedPointer& operator=(const MySharedPointer<T>& other) {
            if (this != &other){
                if (this->ptr != other.ptr && this->control_block != other.control_block) { // check if both manage the same object
                    release();
                    ptr = other.ptr;
                    control_block = other.control_block;
                    if (control_block!= nullptr) {
                        control_block->ref_count++;
                    }
                }
                return *this;
            } else {
                throw std::runtime_error("Self-assignment is not allowed for copy assignment operator");
            }
        }

        // Move assignment operator
        MySharedPointer& operator=(MySharedPointer<T>&& other) {
            if (this != &other) {     // check if both pointers are the same (in the stack)
                release();
                ptr = other.ptr;
                control_block = other.control_block;
                other.ptr = nullptr;
                other.control_block = nullptr;
            } else {
                throw std::runtime_error("Self-assignment is not allowed for move assignment operator");
            }
            return *this;
        }

        // reset()
        void reset(T* t) {
            if (this-> ptr != t) {
                release();
                if (t != nullptr) {
                    ptr = t;
                    control_block = new ControlBlock<T>([](T*p){ delete p; });
                }
            }
        }

        // get()
        T* get()const {
            return ptr;
        }

        // operator*()
        T& operator*() const {
            if(ptr != nullptr) {
                return *ptr;
            } else {
                throw std::runtime_error("Dereferencing a null pointer");
            }
        }

        // operator->()
        T* operator->()const {
            if(ptr != nullptr) {
                return ptr;
            } else {
                throw std::runtime_error("Accessing members of a null pointer");
            }
        }

        // use_count()
        int use_count() const{
            if (this->control_block != nullptr)
            {
                return control_block->ref_count;
            } else {
                return 0;
            }
        }
};

template<typename T, typename... Args>
MySharedPointer<T> MakeShared(Args&&... args) {
    T* t = new T(std::forward<Args>(args)...);      // Create a new object of type T with the provided arguments
    return MySharedPointer<T>(t);                   // Return a MySharedPointer managing the new object
}