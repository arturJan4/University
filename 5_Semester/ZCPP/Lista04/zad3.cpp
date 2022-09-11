#include <iostream>

// slajd 8 i 9
// objekt funkcyjny to inaczej funktor
// Standard C++ używa pojęcia obiektu funkcyjnego w odniesieniu do
// wszystkich obiektów, których da się użyć jako funkcji – pojęcie to
// obejmuje więc wskaźniki do funkcji, obiekty klas przeciążających
// operator (), obiekty klas definiujących konwersję na wskaźnik do
// funkcji oraz lambdy.

int id (int x) {std::cout << "id\n"; return x;}
int square (int x) {std::cout << "square\n"; return x * x;}
int inc (int x) {std::cout << "inc\n"; return x + 1;}

auto po_kolei = [](auto f, auto g) {
    return [=](auto x) {
        f(x);
        g(x);
    };
};

int main()
{
    auto comp = po_kolei(id, inc);
    comp(0);
    std::cout << "\n";

    po_kolei(square, inc)(0);
    std::cout << "\n";

    po_kolei(inc, square)(0);
    std::cout << "\n";

    po_kolei(inc, po_kolei(square, inc))(0);
    return 0;
}
