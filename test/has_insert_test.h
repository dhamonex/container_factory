#ifndef H_20C88747452345D8BDADF1C709736A5A
#define H_20C88747452345D8BDADF1C709736A5A

#include <container_factory/has_insert.hpp>

#include <map>
#include <vector>

TEST( HasInsertTest, assert_map_has_insert )
{
  using MapType = std::map<int, int>;
  static_assert( container_factory::has_insert<MapType>::value );
}

TEST( HasInsertTest, assert_vector_has_no_insert )
{
  using VectorType = std::vector<int>;
  static_assert( !container_factory::has_insert<VectorType>::value );
}

#endif // H_20C88747452345D8BDADF1C709736A5A


