#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <type_traits>
#include <iostream>

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
    add(const_type& element)
    {
      auto container_iterator = container.find(element);
      if(container_iterator == std::end(container))
        {
          std::cout << "Groesse:" << container.size() << std::endl;
          auto result = container.insert(std::make_pair(element, value_type()));
          auto iter = result.first;
          const auto& key = std::get<0>(*iter);
          std::cout << "Groesse:" << container.size() << std::endl;
          auto shared = return_type(std::addressof(key), [this] (const T* ptr) {
              this->remove(*ptr);
            });
          container[key] = shared;
          return shared;
        }
      return return_type(container[element]);
    }

    void
    remove(const_type& element)
    {
      container.erase(element);
    }

    return_type
    get(value_type element)
    {
      return nullptr;
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
    container_type container;

    void
    remove(const T* ptr)
    {
      container.erase(*ptr);
    }


  };

}
#endif /* end of include guard: STORAGE_HPP */
