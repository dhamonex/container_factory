#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

#include "has_insert_test.h"
#include "has_push_back_test.h"
#include "is_unique_ptr_test.h"
#include "is_shared_ptr_test.h"
#include "factory_push_back_test.h"
#include "factory_insert_set_test.h"

int main( int argc, char **argv )
{
  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
