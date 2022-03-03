#ifndef H_3354BC2E4FA94D378DEABBECE6BC5218
#define H_3354BC2E4FA94D378DEABBECE6BC5218

template <class T>
class ContainerFactoryUniqueKeyViolationTest : public ContainerFactoryTest<T>
{
};

using UniqeKeyContainerTypes = boost::mp11::mp_append<
  boost::mp11::mp_transform<std::unordered_set, PointerTypes,
                            boost::mp11::mp_transform<TestClassHash, PointerTypes>,
                            boost::mp11::mp_transform<TestClassEqualKeyCompare, PointerTypes>>,
  boost::mp11::mp_transform<boost::unordered_set, PointerTypes,
                            boost::mp11::mp_transform<TestClassHash, PointerTypes>,
                            boost::mp11::mp_transform<TestClassEqualKeyCompare, PointerTypes>>>;
using UniqueKeyTestContainerTypes = boost::mp11::mp_apply<Types, UniqeKeyContainerTypes>;

TYPED_TEST_SUITE( ContainerFactoryUniqueKeyViolationTest, UniqueKeyTestContainerTypes );

TYPED_TEST( ContainerFactoryUniqueKeyViolationTest, add_one_base_element )
{
  container_factory::factory<Base, Base>( this->destinationContainer );

  ASSERT_THAT( this->destinationContainer, SizeIs( 1 ) );
}

#endif // H_3354BC2E4FA94D378DEABBECE6BC5218
