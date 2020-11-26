#ifndef H_58DD808A49244040BA0B95E471DFFE99
#define H_58DD808A49244040BA0B95E471DFFE99

#include <boost/shared_ptr.hpp>
#include <memory>
#include <type_traits>

namespace container_factory::detail
{
  template <typename T> struct is_std_shared_ptr : std::false_type
  {
  };

  template <typename T> struct is_std_shared_ptr<std::shared_ptr<T>> : std::true_type
  {
  };

  template <typename T> inline constexpr bool is_std_shared_ptr_v = is_std_shared_ptr<T>::value;

  template <typename T> struct is_boost_shared_ptr : std::false_type
  {
  };

  template <typename T> struct is_boost_shared_ptr<boost::shared_ptr<T>> : std::true_type
  {
  };

  template <typename T> inline constexpr bool is_boost_shared_ptr_v = is_boost_shared_ptr<T>::value;

  template <typename T>
  struct is_shared_ptr : std::disjunction<is_std_shared_ptr<T>, is_boost_shared_ptr<T>>
  {
  };

  template <typename T> inline constexpr bool is_shared_ptr_v = is_shared_ptr<T>::value;
} // namespace container_factory::detail

#endif // H_58DD808A49244040BA0B95E471DFFE99
