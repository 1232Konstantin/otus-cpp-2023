#include <string>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>


typedef std::array<uint8_t, 4> IpAddress;

IpAddress ParseIpAddress(const std::string& AddressStr)
{
  constexpr char ADDRESS_DELIM = '.';

  IpAddress Address{};
  std::string::size_type Start = 0;
  auto Stop = AddressStr.find_first_of(ADDRESS_DELIM);

  for (uint8_t i = 0; i < Address.size(); ++i)
  {
    try
    {
      Address[i] = static_cast<uint8_t>(std::stoi(AddressStr.substr(Start, Stop - Start)));
    }
    catch (std::exception const& ex)
    {
      std::cerr << "Failed to parse: '" << AddressStr.substr(Start, Stop - Start)
        << "' which is a part of the string: '" << AddressStr << "' Start = "
        << Start << " Stop = " << Stop << '\n' << ex.what() << std::endl;
      Address = {};
      break;
    }
    
    Start = Stop + 1;
    Stop = AddressStr.find_first_of(ADDRESS_DELIM, Start);
  }
  
  return Address;
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
  os << static_cast<int>(Ip[0]) << '.'
    << static_cast<int>(Ip[1]) << '.'
    << static_cast<int>(Ip[2]) << '.'
    << static_cast<int>(Ip[3]);
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
        return Elem[0] == 1;
      }
    );
    std::cout << FilteredIpPool << std::endl;
  }

  // 3. only begin with 46 and second is 70
  {
    decltype(IpPool) FilteredIpPool;
    std::copy_if(IpPool.begin(), IpPool.end(), std::back_inserter(FilteredIpPool), [](const auto& Elem)
      {
        return Elem[0] == 46 && Elem[1] == 70;
      }
    );
    std::cout << FilteredIpPool << std::endl;
  }

  // 4. any part is 46
  {
    decltype(IpPool) FilteredIpPool;
    std::copy_if(IpPool.begin(), IpPool.end(), std::back_inserter(FilteredIpPool), [](const auto& Elem)
      {
        for (const auto& Part : Elem)
        {
          if (Part == 46) return true;
        }
        return false;
      }
    );
    std::cout << FilteredIpPool << std::endl;
  }

  return 0;
}