#ifndef H_5BE7EE57D5AF4C379B522E686BCB3E78
#define H_5BE7EE57D5AF4C379B522E686BCB3E78

#include "has_insert.hpp"
#include "has_pushback.hpp"

namespace container_factory
{
  namespace detail
  {
  }
  
  template <class C, class ...Types>
  void factory( C &container );
}

#endif // H_5BE7EE57D5AF4C379B522E686BCB3E78


