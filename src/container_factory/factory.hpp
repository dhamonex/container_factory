#ifndef H_5BE7EE57D5AF4C379B522E686BCB3E78
#define H_5BE7EE57D5AF4C379B522E686BCB3E78

#include "has_insert.hpp"
#include "has_pushback.hpp"

namespace container_factory
{
  namespace detail
  {
    template<class Element, class... Tail>
    struct AddElements
    {
      template<typename Container>
      static void addElements( Container &container )
      {
        container.push_back( new Element );
        AddElements<Tail...>::addElements( container );
      }
    };
    
    
    template<class Element>
    struct AddElements<Element>
    {
      template<typename Container>
      static void addElements( Container &container )
      {
        container.push_back( new Element );
      }
    };
  }
  
  template <class... Types, class C>
  void factory( C &container )
  {
    static_assert( has_insert_v<C> || has_push_back_v<C>, "container does not support insert nor push_back hence is not a valid container" );
    detail::AddElements<Types...>::addElements( container );
  }
}

#endif // H_5BE7EE57D5AF4C379B522E686BCB3E78


