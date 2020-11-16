include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(container_factory_test container_factory_test.cpp)
target_link_libraries(container_factory_test
  GTest::gtest
  GMock::GMock
)
