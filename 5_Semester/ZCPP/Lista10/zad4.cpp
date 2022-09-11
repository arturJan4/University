#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " [directoryName] \n";
        return EXIT_FAILURE;
    }

    auto path = std::filesystem::path(argv[1]);
    if(!fs::exists(path)) {
        std::cerr << argv[1] << " doesn't exist! \n";
        return EXIT_FAILURE;
    }

    if(!fs::is_directory(path)) {
        std::cerr << argv[1] << " is not a directory! \n";
        return 0;
    }

    // print all file names in a given directory
    for(const auto& file : fs::directory_iterator(path))
    {
        std::cout << file.path().filename() << "\n";
    }

    return 0;
}
