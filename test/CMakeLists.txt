include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

try_compile(HAS_BOOST_SHARED_PTR_HASH "${CMAKE_BINARY_DIR}/temp" "${PROJECT_SOURCE_DIR}/cmake/tests/test_boost_shared_ptr_hash.cpp")
configure_file(config.h.cmake config.h)

add_executable(container_factory_test container_factory_test.cpp)
target_link_libraries(container_factory_test
  GTest::gtest
  GMock::GMock
)
gtest_add_tests(TARGET container_factory_test)
gtest_discover_tests(container_factory_test XML_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/gtestresult)
