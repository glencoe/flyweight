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

    const T*
    get() const
    {
      return ptr.get();
    }

  private:

    std::shared_ptr<const T> ptr;

    static
    Storage<T>& getStorage()
    {
      static Storage<T> storage;
      return storage;
    }
  };
}

#endif /* FLYWEIGHT_H */
