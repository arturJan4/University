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

    size_t sum = 0;
    // recursively browse files and if they are regular files -> add their size to the sum
    for(const auto& file : fs::recursive_directory_iterator(path))
    {
        if (fs::is_regular_file(file)) {
            //std::cout << "adding " << file << " with size: " << std::filesystem::file_size(file) << " bytes \n";
            sum += std::filesystem::file_size(file);
        }
    }

    std::cout << sum << " bytes\n";
    return 0;
}
