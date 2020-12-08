#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <unordered_set>

int main( int argc, char **argv )
{
  using PtrType = boost::shared_ptr<int>;
  using SetType = std::unordered_set<PtrType>;
  
  SetType set;
  set.emplace( boost::make_shared<int>( 5 ) );
  
  return 0;
}
