#include <functional>


// Control block for shared pointer:
// Contains the reference count and the deleter for the managed object.
template <typename T>
class ControlBlock {
    public:
        int ref_count;                      // Reference count
        std::function<void(T*)> deleter;    // Deleter for the managed object

        ControlBlock(std::function<void(T*)> del) : ref_count(1), deleter(del) {
            // Constructor initializes the reference count to 1 and sets the deleter
        }
};
