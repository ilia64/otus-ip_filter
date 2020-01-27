#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <set>
#include <vector>

using Octet = unsigned char;
using Address = std::array<Octet, 4>;
using Pool = std::multiset<Address, std::greater<>>;

template <typename Iter, typename D>
Address split(Iter begin, Iter end, D delimiter)
{
    Address address;

    size_t index = 0;
    while (begin != end)
    {
        Iter pos = std::find(begin, end, delimiter);
        int chunk = std::stoi(std::string(begin, pos));
        assert(chunk >= 0 && chunk <= 255);
        address[index++] = static_cast<Octet>(chunk);
        begin = (pos == end) ? end : std::next(pos);
    }

    assert(index == 4);
    return address;
}

std::ostream& operator<< (std::ostream &out, const Address& address)
{
    bool first = true;
    for (const auto& octet : address)
    {
        if (!first)
        {
            out << '.';
        }
        out << static_cast<unsigned int>(octet);
        first = false;
    }
    return out;
}

std::ostream& operator<< (std::ostream &out, const Pool& pool)
{
    for (const auto& address : pool)
    {
        out << address << '\n';
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
            if (line.empty())
            {
                break;
            }

            auto pos = std::find(line.begin(), line.end(), '\t');
            Address address = split(line.begin(), pos, '.');
            pool.insert(address);
        }

        std::cout << pool;

        std::for_each(pool.begin(), pool.end(), [](const Address& a)
        {
            if (a[0] == 1)
            {
                std::cout << a << '\n';
            }
        });

        std::for_each(pool.begin(), pool.end(), [](const Address& a)
        {
            if (a[0] == 46 && a[1] == 70)
            {
                std::cout << a << '\n';
            }
        });

        std::for_each(pool.begin(), pool.end(), [](const Address& a)
        {
            bool has = std::any_of(a.begin(), a.end(), [](Octet o)
            {
                return o == 46;
            });

            if (has)
            {
                std::cout << a << '\n';
            }
        });

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
