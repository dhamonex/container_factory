#ifndef H_625588CDC2DC42A39FF4E11DBF367F15
#define H_625588CDC2DC42A39FF4E11DBF367F15

#include <container_factory/factory.hpp>
#include "test_class_structure.h"

#include <vector>
#include <list>

class ContainerFactoryPointerVectorTest : public Test
{
  protected:
    using VectorContainer = std::vector<Base *>;
    
    void TearDown() override
    {
      std::for_each( destinationContainer.begin(), destinationContainer.end(), []( auto value ){ delete value; } );
      destinationContainer.clear();
    }
    
    VectorContainer destinationContainer;
};

TEST_F( ContainerFactoryPointerVectorTest, add_one_base_element )
{
  container_factory::factory<Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 1 ) );
}

TEST_F( ContainerFactoryPointerVectorTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 2 ) );
}


class ContainerFactoryStdSharedPtrVectorTest : public Test
{
  protected:
    using VectorContainer = std::vector<std::shared_ptr<Base>>;
    
    void TearDown() override
    {
      destinationContainer.clear();
    }
    
    VectorContainer destinationContainer;
};

TEST_F( ContainerFactoryStdSharedPtrVectorTest, add_one_base_element )
{
  container_factory::factory<Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 1 ) );
}

TEST_F( ContainerFactoryStdSharedPtrVectorTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( destinationContainer );
  
  ASSERT_THAT( destinationContainer, SizeIs( 2 ) );
}

#endif // H_625588CDC2DC42A39FF4E11DBF367F15


