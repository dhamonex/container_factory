#ifndef H_C388D7C870774A9296D4B1307FC54C5C
#define H_C388D7C870774A9296D4B1307FC54C5C

#include <container_factory/is_shared_ptr.hpp>

TEST( IsSharedPtrTest, check_true_for_std_shared_ptr )
{
  using PointerType = std::shared_ptr<int>;
  static_assert( container_factory::detail::is_std_shared_ptr<PointerType>::value );
  static_assert( !container_factory::detail::is_boost_shared_ptr<PointerType>::value );
  static_assert( container_factory::detail::is_shared_ptr<PointerType>::value );
}

TEST( IsSharedPtrTest, check_true_for_boost_shared_ptr )
{
  using PointerType = boost::shared_ptr<int>;
  static_assert( !container_factory::detail::is_std_shared_ptr<PointerType>::value );
  static_assert( container_factory::detail::is_boost_shared_ptr<PointerType>::value );
  static_assert( container_factory::detail::is_shared_ptr<PointerType>::value );
}

#endif // H_C388D7C870774A9296D4B1307FC54C5C


