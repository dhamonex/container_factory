#ifndef H_BA220CAA8A79483090BD48E7251315AC
#define H_BA220CAA8A79483090BD48E7251315AC

#include <container_factory/factory.hpp>
#include "test_class_structure.h"
#include <boost/unordered_set.hpp>
#include <unordered_set>

class ContainerFactoryPointerStdUnorderedSetTest : public Test
{
  protected:
    using SetContainer = std::unordered_set<Base *>;
    
    void TearDown() override
    {
      std::for_each( destinationContainer.begin(), destinationContainer.end(), []( auto value ){ delete value; } );
      destinationContainer.clear();
    }
    
    SetContainer destinationContainer;
};

TEST_F( ContainerFactoryPointerStdUnorderedSetTest, add_one_base_element )
{
  container_factory::factory<Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 1 ) );
}

TEST_F( ContainerFactoryPointerStdUnorderedSetTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 2 ) );
}

TEST_F( ContainerFactoryPointerStdUnorderedSetTest, add_subclass_elements )
{
  container_factory::factory<Base, SubclassA, SubclassB>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 3 ) );
  
  using RequiredIdentifierStrings = std::unordered_set<std::string>; 
  RequiredIdentifierStrings requiredIdentifiers{ "Base_0", "SubclassA_0", "SubclassB_0" };
  
  for ( const auto &object : destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }
}


class ContainerFactoryStdSharedPtrStdUnorderedMapTest : public Test
{
  protected:
    using SetContainer = std::unordered_set<std::shared_ptr<Base>>;
    
    void TearDown() override
    {
      destinationContainer.clear();
    }
    
    SetContainer destinationContainer;
};

TEST_F( ContainerFactoryStdSharedPtrStdUnorderedMapTest, add_one_base_element )
{
  container_factory::factory<Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 1 ) );
}

TEST_F( ContainerFactoryStdSharedPtrStdUnorderedMapTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 2 ) );
}


class ContainerFactoryBoostSharedPtrUnorderedMapTest : public Test
{
  protected:
    using SetContainer = std::unordered_set<boost::shared_ptr<Base>>;
    
    void TearDown() override
    {
      destinationContainer.clear();
    }
    
    SetContainer destinationContainer;
};

TEST_F( ContainerFactoryBoostSharedPtrUnorderedMapTest, add_one_base_element )
{
  container_factory::factory<Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 1 ) );
}

TEST_F( ContainerFactoryBoostSharedPtrUnorderedMapTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 2 ) );
}

TEST_F( ContainerFactoryBoostSharedPtrUnorderedMapTest, add_subclass_elements )
{
  container_factory::factory<Base, SubclassA, SubclassB>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 3 ) );
  
  using RequiredIdentifierStrings = std::unordered_set<std::string>; 
  RequiredIdentifierStrings requiredIdentifiers{ "Base_0", "SubclassA_0", "SubclassB_0" };
  
  for ( const auto &object : destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }
}

class ContainerFactoryUniquePtrUnorderedSetTest : public Test
{
  protected:
    using SetContainer = std::unordered_set<std::unique_ptr<Base>>;
    
    void TearDown() override
    {
      destinationContainer.clear();
    }
    
    SetContainer destinationContainer;
};

TEST_F( ContainerFactoryUniquePtrUnorderedSetTest, add_one_base_element )
{
  container_factory::factory<Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 1 ) );
}

TEST_F( ContainerFactoryUniquePtrUnorderedSetTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 2 ) );
}

TEST_F( ContainerFactoryUniquePtrUnorderedSetTest, add_subclass_elements )
{
  container_factory::factory<Base, SubclassA, SubclassB>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 3 ) );
  
  using RequiredIdentifierStrings = std::unordered_set<std::string>; 
  RequiredIdentifierStrings requiredIdentifiers{ "Base_0", "SubclassA_0", "SubclassB_0" };
  
  for ( const auto &object : destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }
}


#endif // H_BA220CAA8A79483090BD48E7251315AC


