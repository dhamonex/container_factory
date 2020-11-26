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
    template <class T, class ContainerValueType>
    decltype( auto ) createElement()
    {
      using ElementType = std::decay_t<T>;

      if constexpr ( is_boost_shared_ptr_v<ContainerValueType> ) {
        return boost::make_shared<ElementType>();

      } else if constexpr ( is_std_shared_ptr_v<ContainerValueType> ) {
        return std::make_shared<ElementType>();

      } else if constexpr ( is_unique_ptr_v<ContainerValueType> ) {
        return std::make_unique<ElementType>();

      } else if constexpr ( std::is_pointer_v<ContainerValueType> ) {
        return new ElementType();

      } else {
        return ElementType();
      }
    }

    template <class Element, class... Tail>
    struct AddElements
    {
      template <typename Container>
      static void addElements( Container &container )
      {

        if constexpr ( has_push_back_v<Container> ) {
          container.push_back( createElement<Element, typename Container::value_type>() );

        } else {
          container.insert( createElement<Element, typename Container::value_type>() );
        }

        if constexpr ( sizeof...( Tail ) > 0 ) {
          AddElements<Tail...>::addElements( container );
        }
      }
    };
  } // namespace detail

  template <class... Types, class C, typename... Args>
  void factory( C &container, Args... args )
  {
    static_assert(
      detail::has_insert_v<C> || detail::has_push_back_v<C>,
      "container does not support insert nor push_back hence is not a valid container" );
    detail::AddElements<Types...>::addElements( container );
  }
} // namespace container_factory

#endif // H_5BE7EE57D5AF4C379B522E686BCB3E78
