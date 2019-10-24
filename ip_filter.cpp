#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

using Chunk = int;
using Address = std::vector<Chunk>;
using Pool = std::multiset<Address>;
using Cache = std::map<Chunk, Pool>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
template <typename Iter, typename D>
Address split(Iter begin, Iter end, D delimiter)
{
    Address address;

    while (begin != end)
    {
        Iter pos = std::find(begin, end, delimiter);
        Chunk chunk = std::stoi(std::string(begin, pos));
        assert(chunk >= 0 && chunk <= 255);
        address.push_back(chunk);
        begin = (pos == end) ? end : std::next(pos);
    }

    return address;
}

std::ostream& operator<< (std::ostream &out, const Address& address)
{
    bool first = true;
    for (const auto& part : address)
    {
        if (!first)
        {
            out << '.';
        }
        out << part;
        first = false;
    }
    return out;
}

std::ostream& operator<< (std::ostream &out, const Pool& pool)
{
    bool first = true;
    for (auto pos = pool.rbegin(); pos != pool.rend(); ++pos)
    {
        if (!first)
        {
            std::cout << '\n';
        }
        out << *(pos);
        first = false;
    }
    return out;
}

template <bool any = false, typename ...Args>
Pool filter(Cache cache, Args... args)
{
    std::vector<Chunk> target{args...};
    assert(!target.empty() && target.size() <= 4);

    Pool pool = cache.at(target[0]);
    if (any)
    {
        return pool;
    }

    Pool result;

    std::copy_if(pool.begin(), pool.end(),  std::inserter(result, result.end()), [&target](const Address& address)
    {
        size_t size = target.size();
        for (size_t i = 0; i < size; ++i)
        {
            if(address[i] != target[i])
            {
                return false;
            }
        }
        return true;
    });

    return result;
}

int main()
{
    try
    {
        Pool pool;
        Cache cache;

        for(std::string line; std::getline(std::cin, line);)
        {
            //TODO @i.lukin remove on done
            if (line.empty())
            {
                break;
            }

            auto pos = std::find(line.begin(), line.end(), '\t');
            Address address = split(line.begin(), pos, '.');
            assert(address.size() == 4);

            for (size_t i = 0; i < 4; i++)
            {
                Chunk chunk = address[i];
                cache[chunk].insert(address);
            }

            pool.insert(std::move(address));
        }

        std::cout << pool << std::endl;
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        std::cout << filter(cache, 1) << std::endl;
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        std::cout << filter(cache, 46, 70) << std::endl;
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        std::cout << filter<true>(cache, 46) << std::endl;
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
