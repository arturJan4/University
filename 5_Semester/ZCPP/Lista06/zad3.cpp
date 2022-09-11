#include <iostream>
#include <vector>
#include <map>

auto find_popular(const std::vector<int>& input)
{
    std::map<int, int> num_freq;

    for (const auto &num : input)
        num_freq[num]++;

    std::vector<std::pair<int, int>> num_freq_vec;

    for (const auto &[val, cnt] : num_freq)
        num_freq_vec.emplace_back(val, cnt);

    auto max_freq = std::max_element(num_freq_vec.cbegin(), num_freq_vec.cend(),
                               [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.second < b.second;
    })->second;

    std::vector<std::pair<int, int>> result;
    std::copy_if(num_freq_vec.cbegin(), num_freq_vec.cend(), std::back_inserter(result),
            [&](const auto& p){return p.second == max_freq;});

    return result;
}

int main()
{
    std::vector<int> data = {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};

    for (const auto &[val, cnt] : find_popular(data))
    {
        std::cout << "{" << val << ", " << cnt << "}" << '\n';
    }
}