#include <iostream>

int main()
{
    std::setlocale(LC_ALL, "");
    std::wstring diacretics = L"ąęłżźśćńóĄĘŁŻŹŚĆŃÓ";
    std::wcout << diacretics;

    return 0;
}