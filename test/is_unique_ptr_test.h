#ifndef H_1C1B826D5E9E41C09442DE5D27CCE21A
#define H_1C1B826D5E9E41C09442DE5D27CCE21A

#include <container_factory/is_unique_ptr.hpp>
#include <memory>

#include <boost/shared_ptr.hpp>

TEST( IsUniquePtrTest, check_true_for_unique_ptr )
{
  using PointerType = std::unique_ptr<int>;
  static_assert( container_factory::detail::is_unique_ptr_v<PointerType> );
}

TEST( IsUniquePtrTest, check_false_for_shared_ptr )
{
  using PointerType = std::shared_ptr<int>;
  static_assert( !container_factory::detail::is_unique_ptr<PointerType>::value );
}

TEST( IsUniquePtrTest, check_false_for_boost_shared_ptr )
{
  using PointerType = boost::shared_ptr<int>;
  static_assert( !container_factory::detail::is_unique_ptr<PointerType>::value );
}

TEST( IsUniquePtrTest, check_false_for_normal_ptr )
{
  using PointerType = int*;
  static_assert( !container_factory::detail::is_unique_ptr_v<PointerType> );
}

#endif // H_1C1B826D5E9E41C09442DE5D27CCE21A


