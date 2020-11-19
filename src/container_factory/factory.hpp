#ifndef H_5BE7EE57D5AF4C379B522E686BCB3E78
#define H_5BE7EE57D5AF4C379B522E686BCB3E78

#include "has_insert.hpp"
#include "has_pushback.hpp"
#include "is_shared_ptr.hpp"

#include <boost/make_shared.hpp>

namespace container_factory
{
  namespace detail
  {
    template <class T>
    decltype(auto) createElement()
    {
      using ElementType = std::decay_t<T>;
      
      if constexpr ( is_boost_shared_ptr_v<ElementType> ) {
        return boost::make_shared<typename ElementType::element_type>();
        
      } else if constexpr ( is_std_shared_ptr_v<ElementType> ) {
        return std::make_shared<typename ElementType::element_type>();
        
      } else if constexpr ( is_unique_ptr_v<ElementType> ) {
        return std::make_unique<typename ElementType::element_type>();
        
      } else if constexpr ( std::is_pointer_v<ElementType> ) {
        return new std::remove_pointer_t<ElementType>();
        
      } else {
        return ElementType();
      }
    }
    
    template<class Element, class... Tail>
    struct AddElements
    {
      template<typename Container>
      static void addElements( Container &container )
      {
        container.push_back( createElement<typename Container::value_type>() );
        
        if constexpr ( sizeof...( Tail ) > 0 ) {
          AddElements<Tail...>::addElements( container );
        }
      }
    };
  }
  
  template <class... Types, class C>
  void factory( C &container )
  {
    static_assert( detail::has_insert_v<C> || detail::has_push_back_v<C>, "container does not support insert nor push_back hence is not a valid container" );
    detail::AddElements<Types...>::addElements( container );
  }
}

#endif // H_5BE7EE57D5AF4C379B522E686BCB3E78


