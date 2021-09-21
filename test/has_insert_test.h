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

template <typename T>
class HasInsertTest : public Test
{
};

using InsertMapTypes =
  Types<std::map<int, int>, std::unordered_map<int, int>, boost::unordered_map<int, int>,
        std::set<int>, std::unordered_set<int>, boost::unordered_set<int>>;

TYPED_TEST_SUITE( HasInsertTest, InsertMapTypes );

TYPED_TEST( HasInsertTest, assert_type_has_insert )
{
  static_assert( container_factory::detail::has_insert<TypeParam>::value );
}

template <typename T>
class HasNoInsertTest : public Test
{
};

using HasNoInsertTypes = Types<std::list<int>, std::vector<int>, int>;

TYPED_TEST_SUITE( HasNoInsertTest, HasNoInsertTypes );

TYPED_TEST( HasNoInsertTest, assert_type_has_no_insert )
{
  static_assert( !container_factory::detail::has_insert<TypeParam>::value );
}

#endif // H_20C88747452345D8BDADF1C709736A5A
