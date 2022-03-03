#ifndef H_1C5C43D1DFC04B3A94C1C933DE86CD47
#define H_1C5C43D1DFC04B3A94C1C933DE86CD47

template <class T>
class ContainerFactoryTest : public testing::Test
{
  protected:
    using ContainerType = T;
    using ValueType = typename ContainerType::value_type;

    void TearDown() override
    {
      if constexpr ( std::is_pointer_v<ValueType> ) {
        std::for_each( destinationContainer.begin(), destinationContainer.end(),
                       []( auto value ) { delete value; } );
      }

      destinationContainer.clear();
    }

    ContainerType destinationContainer;
};

#endif // H_1C5C43D1DFC04B3A94C1C933DE86CD47
