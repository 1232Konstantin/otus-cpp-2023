/**
 * @file matrix.h
 * @author Dabudabot
 */

#include <unordered_map>
#include <array>

template <class T, T DefaultValue, size_t Dimentions = 2>
class Matrix
{
private:
    using KeyT = std::array<size_t, Dimentions>;
    using StorageT = std::unordered_map<KeyT, T>;
    using StorageItT = typename StorageT::iterator;

private:

    // https://www.artificialworlds.net/blog/2017/05/12/c-iterator-wrapperadaptor-example/
    // https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
    class MatrixIt
    {
    private:

        StorageItT Wrapped;

    public:
        explicit MatrixIt(StorageItT inWrapped) : Wrapped(inWrapped) {}

        auto operator*()
        {
            // https://stackoverflow.com/questions/57510341/how-to-convert-stdarray-to-stdtuple
            // https://en.cppreference.com/w/cpp/utility/tuple/tuple_cat
            return std::tuple_cat(Wrapped->first, std::make_tuple(Wrapped->second));
        }

        // same as in original iterator
        bool operator==(const MatrixIt& other) const { return Wrapped.operator==(other); }
        bool operator!=(const MatrixIt& other) const { return Wrapped.operator!=(other); }
        MatrixIt& operator++()
        {
            ++Wrapped;
            return *this;
        }
        MatrixIt& operator++(int)
        {
            auto temp = *this;
            ++Wrapped;
            return temp;
        }
        MatrixIt& operator--()
        {
            --Wrapped;
            return *this;
        }
        MatrixIt& operator--(int)
        {
            auto temp = *this;
            --Wrapped;
            return temp;
        }
    };

    template <class Depth>
    class Level
    {
    private:

        KeyT Key;

    };

    template <>
    class Level<1>
    {

    };

private:

    StorageT Storage;

public:

    auto operator[](size_t index)
    {
        return Level<Dimentions>(Storage, index);
    }

    std::size_t size() const
    {
        return Storage.size();
    }

    MatrixIt begin()
    {
        return MatrixIt(Storage.begin());
    }

    MatrixIt end()
    {
        return MatrixIt(Storage.end());
    }
    
};
