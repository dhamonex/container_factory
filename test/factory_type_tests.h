#ifndef H_EFA8125317B74D7E9CCFD61B363BB59D
#define H_EFA8125317B74D7E9CCFD61B363BB59D


#include <vector>
#include <list>

#include <boost/mp11.hpp>

#include <container_factory/factory.hpp>

#include "test_class_structure.h"
#include "is_vector_container.hpp"


template <class T>
class ContainerFactoryTest : public Test
{
  protected:
    using ContainerType = T;
    using ValueType = typename ContainerType::value_type;
    
    void TearDown() override
    {
      if constexpr ( std::is_pointer_v<ValueType> ) {
        std::for_each( destinationContainer.begin(), destinationContainer.end(), []( auto value ){ delete value; } );
      }
      
      destinationContainer.clear();
    }
    
    ContainerType destinationContainer;
};

using PointerTypes = boost::mp11::mp_list<Base *, std::shared_ptr<Base>, std::unique_ptr<Base>, boost::shared_ptr<Base>>;

using ContainerTypes = boost::mp11::mp_append<
  boost::mp11::mp_transform<std::vector, PointerTypes>,
  boost::mp11::mp_transform<std::list, PointerTypes>,
  boost::mp11::mp_transform<std::unordered_set, PointerTypes>,
  boost::mp11::mp_transform<boost::unordered_set, PointerTypes>
>;
using TestContainerTypes = boost::mp11::mp_apply<Types, ContainerTypes>;

TYPED_TEST_SUITE( ContainerFactoryTest, TestContainerTypes );

TYPED_TEST( ContainerFactoryTest, add_one_base_element )
{
  container_factory::factory<Base>( this->destinationContainer );
  
  ASSERT_THAT( this->destinationContainer, SizeIs( 1 ) );
}

TYPED_TEST( ContainerFactoryTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( this->destinationContainer );
  
  ASSERT_THAT( this->destinationContainer, SizeIs( 2 ) );
}

TYPED_TEST( ContainerFactoryTest, add_subclass_elements )
{
  container_factory::factory<Base, SubclassA, SubclassB>( this->destinationContainer );
  
  ASSERT_THAT( this->destinationContainer, SizeIs( 3 ) );
  
  if constexpr ( is_vector_container_v<typename TestFixture::ContainerType> ) {
    for ( auto i = 0; i < this->destinationContainer.size(); ++i ) {
      switch( i ) {
        case 0:
          ASSERT_THAT( this->destinationContainer[i]->identifierString(), Eq( "Base_0" ) );
          break;
          
        case 1:
          ASSERT_THAT( this->destinationContainer[i]->identifierString(), Eq( "SubclassA_0" ) );
          break;
          
        case 2:
          ASSERT_THAT( this->destinationContainer[i]->identifierString(), Eq( "SubclassB_0" ) );
          break;
      }
    }
    
  } else {
    using RequiredIdentifierStrings = std::unordered_set<std::string>; 
    RequiredIdentifierStrings requiredIdentifiers{ "Base_0", "SubclassA_0", "SubclassB_0" };
    
    for ( const auto &object : this->destinationContainer ) {
      ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
      ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
    }
    
    ASSERT_THAT( requiredIdentifiers, IsEmpty() );
  }
}

#endif // H_EFA8125317B74D7E9CCFD61B363BB59D


