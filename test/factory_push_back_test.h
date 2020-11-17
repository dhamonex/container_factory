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

#endif // H_625588CDC2DC42A39FF4E11DBF367F15


