#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include "storage.hpp"

namespace flyweight
{
  template<class T>
  class Flyweight
  {

  public:
    Flyweight(const T& other)
      : ptr(getStorage().find(other))
    {
    }

    Flyweight(const Flyweight<T>& other) = default;

    Flyweight<T>&
    operator=(Flyweight<T> other)
    {
      swap(*this, other);
    }

    Flyweight<T>&
    operator=(const Flyweight<T>&& other)
    {
      std::swap<std::shared_ptr<const T>>(ptr, other.ptr);
    }

    const T*
    get() const
    {
      return ptr.get();
    }

    std::size_t
    use_count() const
    {
      return ptr.use_count();
    }

    const T&
    operator*() const
    {
      return *ptr;
    }

    const T*
    operator->() const
    {
      return ptr.operator->();
    }


    bool
    operator<(const Flyweight<T>& other) const
    {
      return std::less<T>()(*ptr, *other);
    }

    bool
    operator>(const Flyweight<T>& other) const
    {
      return std::greater<T>()(*ptr, *other);
    }

    bool
    operator==(const Flyweight<T>& other) const
    {
      return std::equal<T>()(*ptr, *other);
    }

    bool
    operator<=(const Flyweight<T>& other) const
    {
      return std::less_equal<T>()(*ptr, *other);
    }

    bool
    operator>=(const Flyweight<T>& other) const
    {
      return std::greater_equal<T>()(*ptr, *other);
    }

    friend
    void swap(Flyweight<T>& lhs, Flyweight<T>& rhs)
    {
      using std::swap;
      swap(lhs.ptr, rhs.ptr);
    }

  private:

    std::shared_ptr<typename std::add_const<T>::type> ptr;

    static
    Storage<T>& getStorage()
    {
      static Storage<T> storage;
      return storage;
    }
  };
}

#endif /* FLYWEIGHT_H */
