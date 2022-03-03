#ifndef H_5BE7EE57D5AF4C379B522E686BCB3E78
#define H_5BE7EE57D5AF4C379B522E686BCB3E78

#include "has_insert.hpp"
#include "has_pushback.hpp"
#include "is_shared_ptr.hpp"
#include "is_unique_ptr.hpp"

#include <boost/make_shared.hpp>

namespace container_factory
{
  namespace detail
  {
    template <class T, class ContainerValueType, typename... Args>
    decltype( auto ) createElement( Args &&...args )
    {
      using ElementType = std::decay_t<T>;

      if constexpr ( is_boost_shared_ptr_v<ContainerValueType> ) {
        return boost::make_shared<ElementType>( std::forward<Args>( args )... );

      } else if constexpr ( is_std_shared_ptr_v<ContainerValueType> ) {
        return std::make_shared<ElementType>( std::forward<Args>( args )... );

      } else if constexpr ( is_unique_ptr_v<ContainerValueType> ) {
        return std::make_unique<ElementType>( std::forward<Args>( args )... );

      } else if constexpr ( std::is_pointer_v<ContainerValueType> ) {
        return new ElementType( std::forward<Args>( args )... );

      } else {
        return ElementType( std::forward<Args>( args )... );
      }
    }

    template <class T>
    void destroyElement( T &element )
    {
      if constexpr ( std::is_pointer_v<T> ) {
        delete element;
        element = nullptr;
      }
    }

    template <class Element, class... Tail>
    struct AddElements
    {
        template <typename Container, typename... Args>
        static void addElements( Container &container, Args &&...args )
        {
          if constexpr ( !std::is_same_v<Element, boost::tuples::null_type> ) {
            auto element = createElement<Element, typename Container::value_type>(
              std::forward<Args>( args )... );
            if constexpr ( has_push_back_v<Container> ) {
              container.push_back( std::move( element ) );

            } else {
              auto result = container.insert( std::move( element ) ).second;
              if ( !result ) {
                destroyElement( element );
              }
            }

            if constexpr ( sizeof...( Tail ) > 0 ) {
              AddElements<Tail...>::addElements( container, std::forward<Args>( args )... );
            }
          }
        }
    };

    template <template <class...> class ListType, class... Types>
    struct AddElements<ListType<Types...>>
    {
        template <typename Container, typename... Args>
        static void addElements( Container &container, Args &&...args )
        {
          AddElements<Types...>::addElements( container, std::forward<Args>( args )... );
        }
    };

  } // namespace detail

  template <class... Types, class C, typename... Args>
  void factory( C &container, Args &&...args )
  {
    static_assert(
      detail::has_insert_v<C> || detail::has_push_back_v<C>,
      "container does not support insert nor push_back hence is not a valid container" );
    detail::AddElements<Types...>::addElements( container, std::forward<Args>( args )... );
  }
} // namespace container_factory

#endif // H_5BE7EE57D5AF4C379B522E686BCB3E78
