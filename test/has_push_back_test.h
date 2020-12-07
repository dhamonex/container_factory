#ifndef H_AE754EB4F43349A093DF686DB30DD31E
#define H_AE754EB4F43349A093DF686DB30DD31E

#include <container_factory/has_pushback.hpp>

#include <list>
#include <unordered_map>
#include <vector>

TEST( HasPushBackTest, assert_vector_has_push_back )
{
  using VectorType = std::vector<std::string>;
  static_assert( container_factory::detail::has_push_back<VectorType>::value );
}

TEST( HasPushBackTest, assert_list_has_push_back )
{
  using ListType = std::list<std::string>;
  static_assert( container_factory::detail::has_push_back<ListType>::value );
}

TEST( HasPushBackTest, assert_unordered_map_has_no_push_back )
{
  using MapType = std::unordered_map<int, int>;
  static_assert( !container_factory::detail::has_push_back<MapType>::value );
}

#endif // H_AE754EB4F43349A093DF686DB30DD31E
