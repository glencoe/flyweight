#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <unordered_map>
#include <memory>
#include <type_traits>

namespace flyweight {



  template <class T> using add_lref_t = typename std::add_lvalue_reference<T>::type;
  template <class T> using add_const_t = typename std::add_const<T>::type;
  template <class T> using add_const_lref_t = add_lref_t<add_const_t<T>>;



  template<class T>
  class Storage
  {
    using key_type = T;
    using mapped_type = std::weak_ptr<add_const_t<T>>;
    using shared_element_ptr = std::shared_ptr<add_const_t<T>>;
    using container_type = std::unordered_map<key_type, mapped_type>;
    using size_type = std::size_t;

  public:

    shared_element_ptr
    find(add_const_lref_t<key_type> element)
    {
      auto iter = container.find(element);
      if(iter == container.end())
        {
          return this->add(element);
        }
      return shared_element_ptr(iter->second);
    }

    shared_element_ptr
    get(add_const_lref_t<key_type> element)
    {
      this->find(element);
    }

    size_type
    size() const
    {
      return container.size();
    }

    bool
    empty() const
    {
      return container.empty();
    }


  private:
    shared_element_ptr
    add(add_const_lref_t<key_type> element)
    {
      auto result = container.emplace(element, mapped_type());
      auto iter = result.first;
      const auto& key = std::get<0>(*iter);
      auto shared = shared_element_ptr(std::addressof(key), [this] (const T* ptr) {
          this->remove(ptr);
        });
      iter->second = shared;
      return shared;
    }

    void
    remove(const T* ptr)
    {
      container.erase(*ptr);
    }

  private:
    container_type container;


  };

}
#endif /* end of include guard: STORAGE_HPP */
