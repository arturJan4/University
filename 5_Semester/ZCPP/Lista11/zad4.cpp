#include <iostream>
#include <string>
#include <fstream>
#include <codecvt>
#include <locale>
#include <sstream>

std::wstring stringStream2wstring(std::stringstream& strs)
{
    std::string str = strs.str();
    typedef std::codecvt_utf8<wchar_t> convert_type;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(str);
}

int main()
{
    std::basic_ifstream<char8_t> input_file("test-utf8.txt"); // utf-8 file
    if (input_file.fail())
    {
        std::cerr << "Failure opening the file: "  << "test-utf8.txt" << "\n";
        return EXIT_FAILURE;
    }

    std::stringstream stream;
    stream << input_file.rdbuf();   // read the file
    std::wstring str = stringStream2wstring(stream); // str holds the content of the file

    std::wofstream output_file("test-utf16.txt");
    output_file.imbue(std::locale(output_file.getloc(), new std::codecvt_utf16<wchar_t>));

    output_file << str;
    return 0;
}