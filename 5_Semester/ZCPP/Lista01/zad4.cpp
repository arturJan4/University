#include <iostream>
#include <string>

enum class name : uint16_t
{
    Artur,
    Adam,
    Dawid,
    Ola,
    Julia,
    Daria
};

const char* name_to_char(const name &in_name)
{
    switch (in_name)
    {
        case name::Artur: return "Artur";
        case name::Adam: return "Adam";
        case name::Dawid: return "Dawid";
        case name::Ola: return "Ola";
        case name::Julia: return "Julia";
        case name::Daria: return "Daria";
        default: throw std::invalid_argument( "name string not implemented" );
    };
}

void print_msg(const std::string &msg, const name &in_name)
{
    auto str_name = name_to_char(in_name);

    std::cout << str_name << ", " << msg;;
}


int main()
{
    name test = name::Adam;
    name test2 = name::Daria;
    std::string msg = "tu jest twój komunikat.\n";

    print_msg(msg, test);
    print_msg(msg, test2);

    return 0;
}
