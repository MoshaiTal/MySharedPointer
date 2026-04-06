#include <stdexcept>
#include <utility>
#include <functional>
#include "control_block.hpp"


// MySharedPointer class template definition
template <typename T>
class MySharedPointer {
    private:
        T* ptr_;                           // Pointer to the managed object
        ControlBlock<T>* control_block_;   // Pointer to the control block

        void release(){
            if (control_block_ == nullptr) {
                return;
            }
            control_block_->ref_count--;
            if (control_block_->ref_count == 0) {
                control_block_->deleter(ptr_);
                delete control_block_;
            }
            ptr_ = nullptr;
            control_block_ = nullptr;
        }

    public:
        // Default constructor
        MySharedPointer() : ptr_(nullptr), control_block_(nullptr){}

        // Constructor that takes a raw pointer and an optional deleter
        MySharedPointer(T* t, std::function<void(T*)> deleter = [](T* p){ delete p; })
            : ptr_(t), control_block_(nullptr) {
            if (t != nullptr) {
                control_block_ = new ControlBlock<T>(deleter);
            }
        }

        // Copy constructor
        MySharedPointer(const MySharedPointer<T>& other) : ptr_(other.ptr_), control_block_(other.control_block_) {
            if (other.control_block_ != nullptr) {
                control_block_->ref_count++;
            }
        }

        // Move constructor
        MySharedPointer(MySharedPointer<T>&& other) : ptr_(other.ptr_), control_block_(other.control_block_) {
            other.ptr_ = nullptr;
            other.control_block_ = nullptr;
        }

        // Destructor
        ~MySharedPointer() {
            release();
        }

        // Copy assignment operator
        MySharedPointer& operator=(const MySharedPointer<T>& other) {
            if (this == &other) {     // check if both pointers are the same (in the stack)
                throw std::runtime_error("Self-assignment is not allowed for copy assignment operator");
            }
            if (this->ptr_ != other.ptr_ && this->control_block_ != other.control_block_) { // check if both manage the same object
                release();
                ptr_ = other.ptr_;
                control_block_ = other.control_block_;
                if (control_block_!= nullptr) {
                    control_block_->ref_count++;
                }
            }
            return *this;
        }

        // Move assignment operator
        MySharedPointer& operator=(MySharedPointer<T>&& other) {
            if (this == &other) {     // check if both pointers are the same (in the stack)
                throw std::runtime_error("Self-assignment is not allowed for move assignment operator");
            }
            release();
            ptr_ = other.ptr_;
            control_block_ = other.control_block_;
            other.ptr_ = nullptr;
            other.control_block_ = nullptr;
            return *this;
        }

        // reset()
        void reset(T* t) {
            if (this->ptr_ == t) {
                return;
            }
            release();
            if (t != nullptr) {
                ptr_ = t;
                control_block_ = new ControlBlock<T>([](T*p){ delete p; });
            }
        }

        // get()
        T* get()const {
            return ptr_;
        }

        // operator*()
        T& operator*() const {
            if(ptr_ == nullptr) {
                throw std::runtime_error("Dereferencing a null pointer");
            }
            return *ptr_;
        }

        // operator->()
        T* operator->()const {
            if(ptr_ == nullptr) {
                throw std::runtime_error("Accessing members of a null pointer");
            }
            return ptr_;
        }

        // use_count()
        int use_count() const{
            if (this->control_block_ != nullptr)
            {
                return control_block_->ref_count;
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