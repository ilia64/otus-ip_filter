#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using Chunk = int;
using Address = std::vector<Chunk>;
using Pool = std::vector<Address>;

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
    for (const auto& address : pool)
    {
        if (!first)
        {
            std::cout << '\n';
        }
        out << address;
        first = false;
    }
    return out;
}

int main()
{
    try
    {
        Pool pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            //TODO @i.lukin remove on done
            if (line.empty())
            {
                break;
            }

            auto pos = std::find(line.begin(), line.end(), '\t');
            Address address = split(line.begin(), pos, '.');
            pool.push_back(std::move(address));
        }

        std::sort(pool.rbegin(), pool.rend());

        std::cout << pool << std::endl;
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

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
