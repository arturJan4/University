#include <iostream>
#include <fstream>
#include <iterator>
#include <chrono>
#include <filesystem>

//https://en.cppreference.com/w/cpp/filesystem/last_write_time
auto last_write_time_str(std::filesystem::file_time_type const& ftime)
{

    std::time_t cftime = std::chrono::system_clock::to_time_t(
            std::chrono::file_clock::to_sys(ftime));
    return std::asctime(std::localtime(&cftime));
}

// https://en.cppreference.com/w/cpp/filesystem/status
void status(const std::filesystem::path& p, std::filesystem::file_status s)
{
    namespace fs = std::filesystem;
    std::cout << p;
    // alternative: switch(s.type()) { case fs::file_type::regular: ...}
    if(fs::is_regular_file(s)) std::cout << " is a regular file\n";
    if(fs::is_directory(s)) std::cout << " is a directory\n";
    if(fs::is_block_file(s)) std::cout << " is a block device\n";
    if(fs::is_character_file(s)) std::cout << " is a character device\n";
    if(fs::is_fifo(s)) std::cout << " is a named IPC pipe\n";
    if(fs::is_socket(s)) std::cout << " is a named IPC socket\n";
    if(fs::is_symlink(s)) std::cout << " is a symlink\n";
}

// https://en.cppreference.com/w/cpp/filesystem/permissions
void perms(std::filesystem::perms p)
{
    namespace fs = std::filesystem;
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              << '\n';
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " [fileName | directoryName]+ \n";
        return EXIT_FAILURE;
    }

    // go through files path's one by one
    for (int i = 1; i < argc; ++i)
    {
        if (std::filesystem::exists(argv[i]))
        {
            auto path = std::filesystem::path(argv[i]);
            // paths
            std::cout << "path: " << path<< "\n";
            std::cout << "canonical path: " << std::filesystem::canonical(argv[i]) << "\n";

            // type of file
            status(path, std::filesystem::status(path));

            // # hard links
            std::cout << "Number of hard links:" << std::filesystem::hard_link_count(path) << '\n';

            // size of regular file
            if (std::filesystem::is_regular_file(argv[i])) {
                std::cout << "size: " << std::filesystem::file_size(argv[i]) << " bytes \n";
            }

            // permissions
            std::cout << "permissions: ";
            perms(std::filesystem::status(path).permissions());

            // time of last modification
            std::chrono::time_point modify_time = std::filesystem::last_write_time(argv[i]);
            // convert chrono's time_point to string
            std::cout << "last modification: " << last_write_time_str(modify_time) << "\n";
        }
        else
        {
            std:: cout << argv[i] << " doesn't exist\n";
        }
    }

    return 0;
}
