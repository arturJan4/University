#include <iostream>
#include <type_traits>
#include <string>

// obiekt źródłowy jest zadany przez wskaźnik
// From jest T*
template <typename From,typename To>
void move_obj(From f, To& t, std::true_type)
{
    using From_der = typename std::remove_pointer<From>::type;
    if constexpr (std::is_convertible<From_der, To>::value)
    {
        t = static_cast<To&&>(std::move(*f));

        std::cout << "moved what's under the pointer\n";
    }
    else
    {
        std::cout << "conversion error when moving pointer val\n";
    }
}

// obiekt źrodłowy jest zadany przez referencje/wartość
template <typename From,typename To>
void move_obj(From& f, To& t, std::false_type)
{
    if constexpr (std::is_convertible<From, To>::value)
    {
        t = static_cast<To&&>(std::move(f));

        std::cout << "moved value/reference\n";
    }
    else
    {
        std::cout << "conversion error when moving value/reference\n";
    }
}

template <typename From,typename To>
void move_obj(From& f, To& t)
{
    move_obj(f, t, std::is_pointer<From>());
}

int main()
{
    std::string a{"napis"};
    std::string b{"test"};

    // moving of reference
    move_obj(a, b);
    std::cout << b << "\n";

    /* moving of type pointer */
    std::string *c_ptr = new std::string("napis_ptr");

    move_obj(c_ptr, b);
    std::cout << b << "\n";

    // different types
    int test_i = 1337;
    double test_f = 4.2;
    std::string test_str("42");
    std::string* test_str_ptr = &test_str;

    move_obj(test_f, test_i);
    std::cout << test_i << "\n";

    // unconvertible types
    move_obj(test_str, test_i);
    std::cout << test_i << "\n";

    move_obj(test_str_ptr, test_i);
    std::cout << test_i << "\n";

    return 0;
}