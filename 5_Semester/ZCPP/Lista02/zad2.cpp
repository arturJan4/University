#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

#if 1                             // switch between 0 and 1 ...
#define ENABLE_CTOR_DBG_PRINTs    // do testow, wyswietlanie konstruktorow
#endif                            // ... to respectively disable or enable CTOR DETECTION PRINTs

class line_writer
{
private:
    std::ofstream *fileStream;

public:
    line_writer() : fileStream(nullptr){}

    explicit line_writer(const std::string& filePath)
            : fileStream(new std::ofstream(filePath, std::ios::out)){}

    template<typename T>
    line_writer &writeToStream(T data)
    {
        *fileStream << data;
        return *this;
    }

    ~line_writer()
    {
        fileStream->close();
        delete fileStream;

        #ifdef ENABLE_CTOR_DBG_PRINTs
        std::cout << "line_writer dbg[dtor] called";
        #endif
    }
};


int main()
{
    int n = 5;
    const std::string filePath = "test2.txt";

    auto mainWriter = std::make_shared<line_writer>(filePath);

    std::vector<std::shared_ptr<line_writer>> ptrs;

    for (int i = 0; i < n; ++i) {
        ptrs.push_back(mainWriter);
    }

    std::cout << "use count: " << ptrs[0].use_count() << "\n";

    for (int i = 0; i < n; ++i) {
        ptrs[i]->writeToStream("ptrs(" + std::to_string(i) + ") ");
        std::cout << "wrote with ptr: " << i << "\n";
    }

    return 0;
}