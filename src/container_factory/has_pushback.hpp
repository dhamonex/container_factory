#ifndef H_62AF9DE838BE4830B707D37C127ABC2F
#define H_62AF9DE838BE4830B707D37C127ABC2F

#include <type_traits>

namespace container_factory
{
  template <class T, class = void>
  struct has_push_back : std::false_type
  {
  };
  
  template <class T>
  struct has_push_back<T, std::void_t<decltype( std::declval<T>().push_back( std::declval<typename T::value_type>() ) )> >
    : std::true_type
  {
  };
  
  template <class T>
  inline constexpr bool has_push_back_v = has_push_back<T>::value;
}

#endif // H_62AF9DE838BE4830B707D37C127ABC2F


