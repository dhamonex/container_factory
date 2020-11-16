#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

#include "has_insert_test.h"

int main( int argc, char **argv )
{
  InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
