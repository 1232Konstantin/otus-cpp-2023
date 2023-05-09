#include <tuple>
#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>

typedef std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> IpAddress;

IpAddress ParseIpAddress(const std::string& AddressStr)
{
  constexpr char ADDRESS_DELIM = '.';

  std::array<uint8_t, std::tuple_size<IpAddress>::value> TempContainer{};
  std::string::size_type Start = 0;
  auto Stop = AddressStr.find_first_of(ADDRESS_DELIM);

  for (uint8_t i = 0; i < TempContainer.size(); ++i)
  {
    TempContainer[i] = static_cast<uint8_t>(std::stoi(AddressStr.substr(Start, Stop - Start)));
    Start = Stop + 1;
    Stop = AddressStr.find_first_of(ADDRESS_DELIM, Start);
  }

  // need some template magic to cast array or vector to tuple
  return { TempContainer[0], TempContainer[1], TempContainer[2], TempContainer[3] };
}

std::istream& operator>>(std::istream& is, std::vector<IpAddress>& IpPool)
{
  std::string Line;

  while (std::getline(is, Line))
  {
    auto AddressEnd = Line.find_first_of('\t');
    auto AddressStr = Line.substr(0, AddressEnd);
    IpPool.push_back(ParseIpAddress(AddressStr));
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, const IpAddress& Ip)
{
  os << static_cast<int>(std::get<0>(Ip)) << '.' 
    << static_cast<int>(std::get<1>(Ip)) << '.'
    << static_cast<int>(std::get<2>(Ip)) << '.'
    << static_cast<int>(std::get<3>(Ip));
  return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<IpAddress>& IpPool)
{
  bool isLineBreak = false;
  for (const auto& Ip : IpPool)
  {
    if (isLineBreak)
    {
      os << '\n';
    }
    os << Ip;
    isLineBreak = true;
  }
  return os;
}

int main()
{
  std::vector<IpAddress> IpPool;
  std::cin >> IpPool;
  
  // 1. Reverse lexicographical order
  std::sort(IpPool.begin(), IpPool.end(), std::greater<>());
  std::cout << IpPool << std::endl;

  // 2. only begin with 1
  {
    decltype(IpPool) FilteredIpPool;
    std::copy_if(IpPool.begin(), IpPool.end(), std::back_inserter(FilteredIpPool), [](const auto& Elem)
      {
        return std::get<0>(Elem) == 1;
      }
    );
    std::cout << FilteredIpPool << std::endl;
  }

  // 3. only begin with 46 and second is 70
  {
    decltype(IpPool) FilteredIpPool;
    std::copy_if(IpPool.begin(), IpPool.end(), std::back_inserter(FilteredIpPool), [](const auto& Elem)
      {
        return std::get<0>(Elem) == 46 && std::get<1>(Elem) == 70;
      }
    );
    std::cout << FilteredIpPool << std::endl;
  }

  // 4. any part is 46
  {
    decltype(IpPool) FilteredIpPool;
    std::copy_if(IpPool.begin(), IpPool.end(), std::back_inserter(FilteredIpPool), [](const auto& Elem)
      {
        return std::get<0>(Elem) == 46 || std::get<1>(Elem) == 46 || std::get<2>(Elem) == 46 || std::get<3>(Elem) == 46;
      }
    );
    std::cout << FilteredIpPool << std::endl;
  }

  return 0;
}