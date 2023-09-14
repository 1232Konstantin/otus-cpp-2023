/**
 * @file matrix.h
 * @author Dabudabot
 */

#include <unordered_map>
#include <array>
#include <memory>

/**
 * @breif Matrix class which should be used
 */
template <class T, T DefaultValue, size_t Dimentions = 2>
class Matrix
{
private:

  using KeyT = std::array<size_t, Dimentions>;

  /**
   * @breif we have to explain unordered_map how to use array as a key
   * @reference https://stackoverflow.com/questions/42701688/using-an-unordered-map-with-arrays-as-keys
   */
  class ArrayHasher
  {
  public:
    std::size_t operator()(const KeyT& a) const {
      std::size_t h = 0;

      for (const auto& e : a) {
        h ^= std::hash<size_t>{}(e)+0x9e3779b9 + (h << 6) + (h >> 2);
      }
      return h;
    }
  };
  
  using StorageT = std::unordered_map<KeyT, T, ArrayHasher>;
  using StorageTPtr = std::shared_ptr<StorageT>;
  using StorageItT = typename StorageT::iterator;

public:

  /**
   * @breif wrapper class over default map iterator to be able get x y and value in foreach loop
   * @reference https://www.artificialworlds.net/blog/2017/05/12/c-iterator-wrapperadaptor-example/
   * @reference https://www.internalpointers.com/post/writing-custom-iterators-modern-cpp
   */
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
    bool operator==(const MatrixIt& other) const { return Wrapped.operator==(other.Wrapped); }
    bool operator!=(const MatrixIt& other) const { return Wrapped.operator!=(other.Wrapped); }
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

  /**
   * @breif basically this is returned by key in order not to create object with default value
   */
  class MatrixElement
  {
  private:

    KeyT Key;
    StorageTPtr Storage;

  public:

    MatrixElement(KeyT&& inKey, StorageTPtr inStorage)
      : Key(std::move(inKey))
      , Storage(std::move(inStorage))
    {}

    operator T()
    {
      if (Storage->count(Key))
      {
        return Storage->operator[](Key);
      }
      return DefaultValue;
    }

    MatrixElement& operator=(const T& obj)
    {
      Storage->operator[](Key) = obj;

      if (Storage->operator[](Key) == DefaultValue)
      {
        Storage->erase(Key);
      }
      return *this;
    }

    MatrixElement& operator=(T&& obj)
    {
      Storage->operator[](Key) = std::move(obj);

      if (Storage->operator[](Key) == DefaultValue)
      {
        Storage->erase(Key);
      }
      return *this;
    }
  };

  /**
   * @breif SFINAE class recursivly created from top level to bottom
   */
  template <size_t OriginalDepth, size_t CurrentDepth>
  class Level
  {
  private:

    KeyT Key;
    StorageTPtr Storage;

  public:

    Level(const size_t& inIndex, KeyT&& inKey, StorageTPtr inStorage)
      : Key(std::move(inKey))
      , Storage(std::move(inStorage))
    {
      Key[OriginalDepth - CurrentDepth] = inIndex;
    }

    Level<OriginalDepth, CurrentDepth - 1>& operator[](const size_t& index)
    {
      return Level<OriginalDepth, CurrentDepth - 1>(index, std::move(Key), Storage);
    }
  };

  /**
   * @breif SFINAE bottom of the recursion
   */
  template <size_t OriginalDepth>
  class Level<OriginalDepth, 2>
  {
  private:

    KeyT Key;
    StorageTPtr Storage;
  
  public:

    Level(const size_t& inIndex, KeyT&& inKey, StorageTPtr inStorage)
      : Key(std::move(inKey))
      , Storage(std::move(inStorage))
    {
      Key[OriginalDepth - 2] = inIndex;
    }

    MatrixElement& operator[](const size_t& index)
    {
      Key[OriginalDepth - 1] = index;
      return MatrixElement(std::move(Key), Storage);
    }
  };

private:
  
  StorageTPtr Storage;

public:

  Matrix()
  {
    Storage = std::make_shared<StorageT>();
  }

  Level<Dimentions, Dimentions>& operator[](const size_t& index)
  {
    return Level<Dimentions, Dimentions>(index, {}, Storage);
  }

  std::size_t size() const
  {
    return Storage->size();
  }

  MatrixIt begin()
  {
    return MatrixIt(Storage->begin());
  }

  MatrixIt end()
  {
    return MatrixIt(Storage->end());
  }
};
