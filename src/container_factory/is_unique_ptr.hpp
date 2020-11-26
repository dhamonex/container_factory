#ifndef H_1B85CF26B0E74DE3854F99C9EF32C289
#define H_1B85CF26B0E74DE3854F99C9EF32C289

#include <memory>
#include <type_traits>

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

  template <typename T>
  inline constexpr bool is_unique_ptr_v = is_unique_ptr<T>::value;
} // namespace container_factory::detail

#endif // H_1B85CF26B0E74DE3854F99C9EF32C289
