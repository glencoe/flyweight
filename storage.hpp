#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <unordered_map>
#include <memory>
#include <type_traits>

namespace flyweight {

  template<typename T>
  class Storage
  {
    using key_type = T;
    using const_type = typename std::add_const<key_type>::type;
    using return_type = std::shared_ptr<const_type>;
    using value_type = std::weak_ptr<const_type>;
    using container_type = std::unordered_map<key_type, value_type>;
    using size_type = std::size_t;

  public:

    return_type
    find(const_type& element)
    {
      auto iter = container.find(element);
      if(iter == container.end())
        {
          return this->add(element);
        }
      return return_type(iter->second);
    }

    return_type
    get(const_type& element)
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
    return_type
    add(const_type& element)
    {
      auto result = container.insert(std::make_pair(element, value_type()));
      auto iter = result.first;
      const auto& key = std::get<0>(*iter);
      auto shared = return_type(std::addressof(key), [this] (const T* ptr) {
          this->remove(ptr);
        });
      container[key] = shared;
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
