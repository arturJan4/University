#include <iostream>
#include <vector>

int main()
{
    std::setlocale(LC_ALL, "");
    std::vector<std::wstring> names{L"żubr", L"łoś", L"jeż", L"zając", L"dzik", L"lis", L"jastrząb",
                                    L"ropucha", L"bóbr", L"łasica", L"bodziszek łąkowy", L"ziarnopłon wiosenny",
                                    L"nawłoć olbrzymia", L"Omieg kozłowiec", L"chaber bławatek"};

    std::sort(names.begin(), names.end(), std::locale("pl_PL.UTF-8"));

    for (const auto &s : names)
        std::wcout << s << '\n';


    return 0;
}