/**
 * @file matrix.h
 * @author Dabudabot
 */

#include <map>
#include <array>

template <class T, T DefaultValue, size_t Dimentions = 2>
class Matrix
{
private:
  using KeyT = std::array<size_t, Dimentions>;
  using StorageT = std::map<KeyT, T>;
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

  class Level<size_t OriginalDepth, size_t CurrentDepth>
  {
    KeyT Key;
    std::shared_ptr<StorageT> Storage;

    Level(const int& inIndex, KeyT&& inKey, std::shared_ptr<StorageT> inStorage)
      : Key(std::move(inKey))
      , Storage(std::move(inStorage))
    {
      Key[OriginalDepth - CurrentDepth] = inIndex;
    }

    Level<OriginalDepth, CurrentDepth - 1>& operator[](const int& index)
    {
      return Level<OriginalDepth, CurrentDepth - 1>(index, std::move(Key), Storage);
    }
  };

  template <size_t OriginalDepth>
  class Level<OriginalDepth, 2>
  {
  public:
    static constexpr bool isBottom = true;

    KeyT Key;
    std::shared_ptr<StorageT> Storage;

    Level(const int& inIndex, KeyT&& inKey, std::shared_ptr<StorageT> inStorage)
      : Key(std::move(inKey))
      , Storage(std::move(inStorage))
    {
      Key[OriginalDepth - 2] = inIndex;
    }

    T& operator[](const int& index)
    {
      Key[OriginalDepth - 1] = index;
      return Storage->operator[](Key);
    }
  };

private:

  StorageT Storage;

public:

  Level<Dimentions, Dimentions>& operator[](size_t index)
  {
    return Level<Dimentions, Dimentions>(index, {}, Storage);
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
