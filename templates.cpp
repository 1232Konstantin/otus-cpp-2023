#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <type_traits>

template <class T>
struct is_container : std::false_type {};
template <class... Ts>
struct is_container<std::list<Ts...>> : std::true_type {};
template <class... Ts>
struct is_container<std::vector<Ts...>> : std::true_type {};
template <class T>
inline constexpr bool is_container_v = is_container<T>::value;

template <class T>
void print_ip(const T& ip,
  std::ostream& out = std::cout,
  typename std::enable_if_t<std::is_integral_v<T>>* = {})
{
  for (int i = sizeof(T) - 1; i >= 0; --i)
  {
    if (i != sizeof(T) - 1)
    {
      out << '.';
    }
    out << ((ip >> (8 * i)) & 0xff);
  }
  out << '\n';
}

template <class T>
void print_ip(const T& ip, 
  std::ostream& out = std::cout,
  typename std::enable_if_t<std::is_same_v<T, std::string>>* = {})
{
  out << ip << '\n';
}

template <class T>
void print_ip(const T& ip,
  std::ostream& out = std::cout,
  typename std::enable_if_t<is_container_v<T>>* = {})
{
  for (const auto& i : ip)
  {
    if (i != *(ip.begin()))
    {
      out << '.';
    }
    out << i;
  }
  out << '\n';
}

template <class... Args>
struct is_homogeneous_tuple : std::true_type {};
template <class T>
struct is_homogeneous_tuple<T> : std::true_type {};
template <class T, class U, class... Args>
struct is_homogeneous_tuple<T, U, Args...>
{
  static constexpr bool value = std::is_same_v<T, U> ? is_homogeneous_tuple<U, Args...>::value : false;
};
template <class... Args>
inline constexpr bool is_homogeneous_tuple_v = is_homogeneous_tuple<Args...>::value;

template<std::size_t index, class... Args>
void print_ip(const std::tuple<Args...>& ip,
  std::ostream& out = std::cout,
  typename std::enable_if_t<is_homogeneous_tuple_v<Args...>>* = {})
{
  if constexpr (index >= sizeof...(Args))
  {
    return;
  }
  else
  {
    if constexpr (index != 0)
    {
      out << '.';
    }
    out << std::get<index>(ip);
    print_ip<index + 1, Args...>(ip);
  }
}
 
template<class... Args>
void print_ip(const std::tuple<Args...>& ip,
  std::ostream& out = std::cout,
  typename std::enable_if_t<is_homogeneous_tuple_v<Args...>>* = {})
{
  print_ip<0, Args...>(ip, out);
  out << '\n';
}

int main()
{
  print_ip( int8_t{-1} ); // 255
  print_ip( int16_t{0} ); // 0.0
  print_ip( int32_t{2130706433} ); // 127.0.0.1
  print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
  print_ip( std::string{"Hello, World!"} ); // Hello, World!
  print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
  print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
  print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0

  return 0;
}