#include <iostream>

auto compose_f_gx_hy = [](auto f, auto g, auto h) {
    return [=](auto x) {
        return f(g(x), h(x));
    };
};

int id (int x) {return x;}
int square (int x) {return x * x;}
int mult (int x, int y) {return x * y;}

std::string concat (const std::string& x, const std::string& y) {return x + y;}
std::string msg (std::string message) {return message;}
std::string nl (const std::string& message) {return "\n";}

int main() {
    auto cube = compose_f_gx_hy(mult, id, square);

    std::cout << cube(6) << "\n";
    std::cout << cube(5) << "\n";

    auto msg_c = compose_f_gx_hy(concat, msg, nl);
    std::cout << msg_c("test1");
    std::cout << msg_c("test2");
}