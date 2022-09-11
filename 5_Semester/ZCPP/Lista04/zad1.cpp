#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <string>
#include <utility>


// function object
template <typename T>
auto print_between(const T &left, const T &right)
{
    return [&](const T& elem)
    {
        if((left < elem) && (elem < right))
        {
            std::cout << elem << ' ';
        }
    };
}

template <typename T>
void print_every_nth(const T& collection, const size_t &k, const size_t &p)
{
    if (k < 1)
        throw std::invalid_argument("k must be positive");

    auto begin_it = collection.begin();
    // using T_inner = typename std::decay<decltype(begin_it)>::type;

    std::advance(begin_it, p);

    std::for_each(begin_it, collection.end(), [k](typename T::value_type x) {
        static size_t counter = 0;
        if (counter % k == 0)
        {
            std::cout << x << ' ';
        }
        counter++;
    });
    std::cout << '\n';
}

template <typename T>
auto sum_collection(const T& collection, const typename T::value_type& initial_val)
{
    typename T::value_type s = initial_val;
    std::for_each(collection.begin(), collection.end(), [&](typename T::value_type val) {
      s += val;
    });
    return s;
}

template <typename T>
auto min_max_iterators(const T& collection)
{
    auto min = collection.begin();
    auto max = collection.begin();

    auto iterator = collection.begin();
    std::for_each(collection.begin(), collection.end(), [&](auto& val) {
        if (val < *min)
            min = iterator;
        else if (val > *max)
            max = iterator;

        iterator++;
    });
    return std::make_pair(min, max);
}

int main()
{
    std::vector<double> double_vec({2.0, -1.0, -5.3, 4.2, 9.3, -14, 5.0, 2.2, 1.2});
    std::list<std::string> string_list({"text", "test", "abc", "random"});
    std::set<int> int_set({-1, 0, 42, -20, 3, 5, 6, 2, 1, 0, -4, 5});

    std::cout << "a) all in range (a, b):\n";
    std::for_each(double_vec.begin(), double_vec.end(), print_between<double>(-0.5, 6.0));
    std::cout << "\n";
    std::for_each(string_list.begin(), string_list.end(), print_between<std::string>("bac", "uoc"));
    std::cout << "\n";
    std::for_each(int_set.begin(), int_set.end(), print_between<int>(0, 6));
    std::cout << "\n";

    std::cout << "b) each k-th starting from p-th (0 indexed):\n";
    print_every_nth(double_vec, 3, 2);
    print_every_nth(string_list, 2, 1);
    print_every_nth(int_set, 1, 0);

    std::cout << "c) arithmetic average for number's collections\n";
    std::cout << sum_collection(double_vec, 0.0) / static_cast<double>(double_vec.size()) << "\n";
    std::cout << sum_collection(int_set, 0) / static_cast<double>(int_set.size()) << "\n";

    std::cout << "d) min-max iterator pair\n";
    {
        auto x = min_max_iterators(double_vec);
        std::cout << *x.first << " " << *x.second << "\n";

        auto y = min_max_iterators(string_list);
        std::cout << *y.first << " " << *y.second << "\n";

        auto z = min_max_iterators(int_set);
        std::cout << *z.first << " " << *z.second << "\n";
    }

    std::cout << "e) sum of all elements\n";
    std::cout << sum_collection(double_vec, 0.0) << "\n";
    std::cout << sum_collection(string_list, "") << "\n";
    std::cout << sum_collection(int_set, 0) << "\n";

    return 0;
}
