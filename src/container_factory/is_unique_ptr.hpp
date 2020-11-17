#ifndef H_1B85CF26B0E74DE3854F99C9EF32C289
#define H_1B85CF26B0E74DE3854F99C9EF32C289

#include <type_traits>
#include <memory>

namespace container_factory::detail
{
  template <typename T>
  struct is_unique_ptr : std::false_type
  {
  };
  
  template <typename T, typename D>
  struct is_unique_ptr<std::unique_ptr<T, D>> : std::true_type
  {
  };
}

#endif // H_1B85CF26B0E74DE3854F99C9EF32C289


