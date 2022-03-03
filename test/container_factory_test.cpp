#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <list>
#include <vector>

#include <boost/mp11.hpp>
#include <boost/unordered_set.hpp>

#include <container_factory/factory.hpp>

#include "config.h"
#include "is_vector_container.hpp"
#include "pointertypes.h"
#include "test_class_structure.h"
#include "containerfactorytest.h"

using namespace testing;

#include "has_insert_test.h"
#include "has_push_back_test.h"
#include "is_shared_ptr_test.h"
#include "is_unique_ptr_test.h"

#include "factory_simple_type_test.h"

#include "factory_type_tests.h"

#include "factory_unique_key_violation_test.h"

int main( int argc, char **argv )
{
  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
