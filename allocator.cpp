#include <iostream>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <stack>

template <class T>
struct TCustomAllocator {
    using value_type = T;

    using PoolBlock = std::shared_ptr<void>;

    const std::size_t blockSize = 0;
    std::stack<PoolBlock> blocks;
    std::stack<void*> addresses;

    void AddMoreAddresses()
    {
        PoolBlock block(::operator new(blockSize * sizeof(T)));
        blocks.push(block);

        for (size_t i = 0; i < blockSize; ++i)
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
        if (n != 1)
        {
            throw std::bad_alloc();
        }

        addresses.push(p);
    }
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
struct TContainer
{

    TContainer()
    {

    }

    TContainer(const Allocator& allocator)
    {

    }

    void push(const T& x)
    {

    }

    T* begin() const
    {

    }

    null_sentinal_t end() const 
    { 
        return {}; 
    }
};

int main()
{
    {
        std::map<int, int> m;

        for (int i = 0, f = 1; i < 10; ++i, f *= i)
        {
            m[i] = f;
        }
    }

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
