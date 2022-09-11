#include <iostream>
#include <memory>
#include <random>

class Cls
{
private:
    uint64_t m_counter = 1;
public:
    uint64_t getCounter() const
    { return this->m_counter; }

    void setCounter(uint64_t value)
    { this->m_counter = value; }

    friend std::ostream &operator<<(std::ostream &os, const Cls &cls)
    {
        os << cls.m_counter;
        return os;
    }

    virtual ~Cls()
    {
        std::cerr << "Counter value: " << m_counter << "\n";
    }
};

bool is_picked()
{
    static std::random_device seed;
    static std::mt19937 gen{seed()}; // seed

    return static_cast<bool>(std::uniform_int_distribution<int>{0, 1}(gen));
}

auto counter_add(std::unique_ptr<Cls[]> arr, uint64_t i, uint64_t n, uint64_t m)
{
    if (i > m)
        return arr;

    // add i to n random elements of array
    for (uint64_t iter = 0; iter < n; ++iter) {
        if (is_picked()) {
            arr[iter].setCounter(arr[iter].getCounter() + i);
        }
    }

    return counter_add(std::move(arr), i + 1, n, m);
}

int main()
{
    constexpr uint64_t n = 10;
    constexpr uint64_t m = 5;
    std::unique_ptr<Cls[]> arr{new Cls[n]};

    arr = counter_add(std::move(arr), 1, n, m);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}

