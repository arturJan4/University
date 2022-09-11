#include <iostream>
#include <memory>

int main()
{
    std::weak_ptr<int> weakPtr;

    {
        std::shared_ptr<int> shared = std::make_shared<int>(1337);
        // here we create a weak_ptr
        weakPtr = shared;
        std::cout << *weakPtr.lock() << "\n";
    }
    // shared is out of scope -> weak_ptr has expired

    std::cout << (weakPtr.expired() ? "Expired" : "Not expired");

    // std::cout << *weakPtr.lock();; // <-- segfault


    return 0;
}