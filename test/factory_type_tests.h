#ifndef H_EFA8125317B74D7E9CCFD61B363BB59D
#define H_EFA8125317B74D7E9CCFD61B363BB59D

#include <container_factory/factory.hpp>
#include "test_class_structure.h"
#include "is_vector_container.hpp"

#include <vector>
#include <list>

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

using ContainerTypes = Types< 
  // vector types
  std::vector<Base *>, std::vector<std::shared_ptr<Base>>, std::vector<boost::shared_ptr<Base>>, std::vector<std::unique_ptr<Base>>,
  
  // list types
  std::list<Base *>, std::list<std::shared_ptr<Base>>, std::list<boost::shared_ptr<Base>>, std::list<std::unique_ptr<Base>>
>;
TYPED_TEST_SUITE( ContainerFactoryTest, ContainerTypes );

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


