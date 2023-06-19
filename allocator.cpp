#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <stack>

struct CustomPool
{
  using PoolBlock = std::shared_ptr<void>;
  std::stack<PoolBlock> blocks;
  std::stack<void*> addresses;
};

template <class T>
struct TCustomAllocator {

  typedef T value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;

  using PoolBlock = std::shared_ptr<void>;

  const std::size_t blockSize = 0;
  std::stack<PoolBlock> blocks;
  std::stack<void*> addresses;

  void AddMoreAddresses()
  {
    PoolBlock block(::operator new(blockSize * sizeof(T)));
    blocks.push(block);

    for (std::size_t i = 0; i < blockSize; ++i)
    {
      addresses.push(static_cast<T*>(block.get()) + i);
    }
  }

  TCustomAllocator(std::size_t inBlockSize)
    : blockSize(inBlockSize)
  {
    if (inBlockSize == 0)
    {
      throw std::bad_alloc();
    }
  }

  template <class U>
  TCustomAllocator(const TCustomAllocator <U>& a)
    : blockSize(a.blockSize)
    , blocks(a.blocks)
    , addresses(a.addresses)
  {
  }

  T* allocate(std::size_t n)
  {
    if (n != 1)
    {
      throw std::bad_alloc();
    }

    if (addresses.empty())
    {
      AddMoreAddresses();
    }

    auto addr = static_cast<T*>(addresses.top());
    addresses.pop();

    return addr;
  }

  void deallocate(T* p, std::size_t n)
  {
    if (!p)
    {
      return;
    }

    if (n != 1)
    {
      throw std::bad_alloc();
    }

    addresses.push(p);
  }

  template <class U>
  struct rebind
  {
    typedef TCustomAllocator<U> other;
  };
};

template <class T, class U>
constexpr bool operator== (const TCustomAllocator<T>& a1, const TCustomAllocator<U>& a2) noexcept
{
  return true;
}

template <class T, class U>
constexpr bool operator!= (const TCustomAllocator<T>& a1, const TCustomAllocator<U>& a2) noexcept
{
  return false;
}

template <class T, class Allocator = std::allocator<T>>
class TContainer
{
private:

  struct Node
  {
    Node* next;
    T val;

    explicit Node(const T& x)
      : next(nullptr)
      , val(x)
    {}
  };

  Node* _head = nullptr;
  Node* _last = nullptr;

  using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
  NodeAllocator _allocator;

public:

  class Iterator
  {
  private:
    Node* _current;

  public:
    explicit Iterator(Node* node)
      : _current(node)
    {}

    T& operator* () const
    {
      return _current->val;
    }

    Iterator& operator++()
    {
      _current = _current->next;
      return *this;
    }

    bool operator!=(const Iterator& other) const
    {
      return _current != other._current;
    }
  };

  TContainer()
    : _head(nullptr)
    , _last(nullptr)
  {}

  TContainer(const Allocator& allocator)
    : _head(nullptr)
    , _last(nullptr)
    , _allocator(allocator)
  {}

  ~TContainer()
  {
    clear();
  }

  void push(const T& x)
  {
    Node* node = _allocator.allocate(1);
    std::allocator_traits<NodeAllocator>::construct(_allocator, node, x);

    if (_head == nullptr)
    {
      _head = node;
      _last = node;
    }
    else
    {
      _last->next = node;
      _last = node;
    }
  }

  void clear()
  {
    auto current = _head;

    while (current)
    {
      auto next = current->next;
      std::allocator_traits<NodeAllocator>::destroy(_allocator, current);
      _allocator.deallocate(current, 1);
      current = next;
    }

    _head = nullptr;
    _last = nullptr;
  }

  Iterator begin() const
  {
    return Iterator(_head);
  }

  Iterator end() const
  {
    return Iterator(nullptr);
  }
};

int main()
{
  {
    TCustomAllocator<std::pair<const int, int>> alloc(10);
    std::map<int, int, std::less<int>, TCustomAllocator<std::pair<const int, int>>> m(alloc);

    for (int i = 0, f = 1; i < 10; ++i, f *= i)
    {
      m[i] = f;
    }

    for (const auto& [k, v] : m)
    {
      std::cout << k << ' ' << v << '\n';
    }
    std::cout << std::endl;
  }

  {
    std::map<int, int> m;

    for (int i = 0, f = 1; i < 10; ++i, f *= i)
    {
      m[i] = f;
    }
  }

  {
    TContainer<int> c;

    for (int i = 0; i < 10; ++i)
    {
      c.push(i);
    }
  }

  {
    TCustomAllocator<int> alloc(10);
    TContainer<int, TCustomAllocator<int>> c(alloc);

    for (int i = 0; i < 10; ++i)
    {
      c.push(i);
    }

    for (const auto& i : c)
    {
      std::cout << i << '\n';
    }
    std::cout << std::endl;
  }

  return 0;
}
