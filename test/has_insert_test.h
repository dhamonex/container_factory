#ifndef H_20C88747452345D8BDADF1C709736A5A
#define H_20C88747452345D8BDADF1C709736A5A

#include <container_factory/has_insert.hpp>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

TEST( HasInsertTest, assert_std_map_has_insert )
{
  using MapType = std::map<int, int>;
  static_assert( container_factory::detail::has_insert<MapType>::value );
}

TEST( HasInsertTest, assert_std_unorderd_map_has_insert )
{
  using MapType = std::unordered_map<int, int>;
  static_assert( container_factory::detail::has_insert<MapType>::value );
}

TEST( HasInsertTest, assert_boost_unorderd_map_has_insert )
{
  using MapType = boost::unordered_map<int, int>;
  static_assert( container_factory::detail::has_insert<MapType>::value );
}

TEST( HasInsertTest, assert_set_has_insert )
{
  using SetType = std::set<int>;
  static_assert( container_factory::detail::has_insert_v<SetType> );
}

TEST( HasInsertTest, assert_std_unordered_set_has_insert )
{
  using SetType = std::unordered_set<int>;
  static_assert( container_factory::detail::has_insert_v<SetType> );
}

TEST( HasInsertTest, assert_boost_unordered_set_has_insert )
{
  using SetType = boost::unordered_set<int>;
  static_assert( container_factory::detail::has_insert_v<SetType> );
}

TEST( HasInsertTest, assert_list_has_no_insert )
{
  using ListType = std::list<int>;
  static_assert( !container_factory::detail::has_insert<ListType>::value );
}

TEST( HasInsertTest, assert_vector_has_no_insert )
{
  using VectorType = std::vector<int>;
  static_assert( !container_factory::detail::has_insert<VectorType>::value );
}

TEST( HasInsertTest, assert_basic_type_does_not_have_insert )
{
  static_assert( !container_factory::detail::has_insert_v<int> );
}

#endif // H_20C88747452345D8BDADF1C709736A5A
