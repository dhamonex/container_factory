#ifndef H_92B2B24078DF43C386E27C1B828375C8
#define H_92B2B24078DF43C386E27C1B828375C8

#include <type_traits>

namespace container_factory::detail
{
  template <class T, class = void> struct has_insert : std::false_type
  {
  };

  template <class T>
  struct has_insert<
    T, std::void_t<decltype( std::declval<T>().insert( std::declval<typename T::value_type>() ) )>>
    : std::true_type
  {
  };

  template <class T> inline constexpr bool has_insert_v = has_insert<T>::value;
} // namespace container_factory::detail

#endif // H_92B2B24078DF43C386E27C1B828375C8
