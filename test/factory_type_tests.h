#ifndef H_EFA8125317B74D7E9CCFD61B363BB59D
#define H_EFA8125317B74D7E9CCFD61B363BB59D

template <class T>
class ContainerFactoryTypeTest : public ContainerFactoryTest<T>
{
};

#ifndef HAS_BOOST_SHARED_PTR_HASH
namespace std
{

  template <class T>
  struct hash<::boost::shared_ptr<T>>
  {
      std::size_t operator()( ::boost::shared_ptr<T> const &p ) const BOOST_SP_NOEXCEPT
      {
        return std::hash<typename ::boost::shared_ptr<T>::element_type *>()( p.get() );
      }
  };

} // namespace std
#endif

using ContainerTypes =
  boost::mp11::mp_append<boost::mp11::mp_transform<std::vector, PointerTypes>,
                         boost::mp11::mp_transform<std::list, PointerTypes>,
                         boost::mp11::mp_transform<std::unordered_set, PointerTypes>,
                         boost::mp11::mp_transform<boost::unordered_set, PointerTypes>>;
using TestContainerTypes = boost::mp11::mp_apply<Types, ContainerTypes>;

TYPED_TEST_SUITE( ContainerFactoryTypeTest, TestContainerTypes );

TYPED_TEST( ContainerFactoryTypeTest, add_one_base_element )
{
  container_factory::factory<Base>( this->destinationContainer );

  ASSERT_THAT( this->destinationContainer, SizeIs( 1 ) );
}

TYPED_TEST( ContainerFactoryTypeTest, add_two_base_elements )
{
  container_factory::factory<Base, Base>( this->destinationContainer );

  ASSERT_THAT( this->destinationContainer, SizeIs( 2 ) );
}

TYPED_TEST( ContainerFactoryTypeTest, add_subclass_elements )
{
  container_factory::factory<Base, SubclassA, SubclassB>( this->destinationContainer );

  ASSERT_THAT( this->destinationContainer, SizeIs( 3 ) );

  if constexpr ( is_vector_container_v<typename TestFixture::ContainerType> ) {
    for ( auto i = 0; i < this->destinationContainer.size(); ++i ) {
      switch ( i ) {
      case 0:
        ASSERT_THAT( this->destinationContainer[i]->identifierString(), Eq( "Base_0" ) );
        break;

      case 1:
        ASSERT_THAT( this->destinationContainer[i]->identifierString(), Eq( "SubclassA_0" ) );
        break;

      case 2:
        ASSERT_THAT( this->destinationContainer[i]->identifierString(), Eq( "SubclassB_0" ) );
        break;
      }
    }

  } else {
    using RequiredIdentifierStrings = std::unordered_set<std::string>;
    RequiredIdentifierStrings requiredIdentifiers{ "Base_0", "SubclassA_0", "SubclassB_0" };

    for ( const auto &object : this->destinationContainer ) {
      ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
      ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
    }

    ASSERT_THAT( requiredIdentifiers, IsEmpty() );
  }
}

TYPED_TEST( ContainerFactoryTypeTest, add_subclass_elements_with_constructor_integer_parameter )
{
  container_factory::factory<Base, SubclassA, SubclassB>( this->destinationContainer, 2 );

  using RequiredIdentifierStrings = std::unordered_set<std::string>;
  RequiredIdentifierStrings requiredIdentifiers{ "Base_2", "SubclassA_2", "SubclassB_2" };

  for ( const auto &object : this->destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }

  ASSERT_THAT( requiredIdentifiers, IsEmpty() );
}

TYPED_TEST( ContainerFactoryTypeTest, add_subclass_elements_with_constructor_string_parameter )
{
  container_factory::factory<Base, SubclassA, SubclassB>( this->destinationContainer, "Test" );

  using RequiredIdentifierStrings = std::unordered_set<std::string>;
  RequiredIdentifierStrings requiredIdentifiers{ "Base_Test_0", "SubclassA_Test_0",
                                                 "SubclassB_Test_0" };

  for ( const auto &object : this->destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }

  ASSERT_THAT( requiredIdentifiers, IsEmpty() );
}

TYPED_TEST( ContainerFactoryTypeTest,
            add_subclass_elements_with_constructor_string_and_integer_parameter )
{
  container_factory::factory<Base, SubclassA, SubclassB>( this->destinationContainer, "Test", 15 );

  using RequiredIdentifierStrings = std::unordered_set<std::string>;
  RequiredIdentifierStrings requiredIdentifiers{ "Base_Test_15", "SubclassA_Test_15",
                                                 "SubclassB_Test_15" };

  for ( const auto &object : this->destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }

  ASSERT_THAT( requiredIdentifiers, IsEmpty() );
}

TYPED_TEST( ContainerFactoryTypeTest, type_list_as_std_tuple_test )
{
  container_factory::factory<std::tuple<Base, SubclassA, SubclassB>>( this->destinationContainer,
                                                                      "Test", 15 );

  using RequiredIdentifierStrings = std::unordered_set<std::string>;
  RequiredIdentifierStrings requiredIdentifiers{ "Base_Test_15", "SubclassA_Test_15",
                                                 "SubclassB_Test_15" };

  for ( const auto &object : this->destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }

  ASSERT_THAT( requiredIdentifiers, IsEmpty() );
}

TYPED_TEST( ContainerFactoryTypeTest, type_list_as_boost_tuple_test )
{
  container_factory::factory<boost::tuple<Base, SubclassA, SubclassB>>( this->destinationContainer,
                                                                        "Test", 15 );

  using RequiredIdentifierStrings = std::unordered_set<std::string>;
  RequiredIdentifierStrings requiredIdentifiers{ "Base_Test_15", "SubclassA_Test_15",
                                                 "SubclassB_Test_15" };

  for ( const auto &object : this->destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }

  ASSERT_THAT( requiredIdentifiers, IsEmpty() );
}

TYPED_TEST( ContainerFactoryTypeTest, type_list_as_boost_mp_list )
{
  container_factory::factory<boost::mp11::mp_list<Base, SubclassA, SubclassB>>(
    this->destinationContainer, "Test", 15 );

  using RequiredIdentifierStrings = std::unordered_set<std::string>;
  RequiredIdentifierStrings requiredIdentifiers{ "Base_Test_15", "SubclassA_Test_15",
                                                 "SubclassB_Test_15" };

  for ( const auto &object : this->destinationContainer ) {
    ASSERT_THAT( requiredIdentifiers, Contains( object->identifierString() ) );
    ASSERT_THAT( requiredIdentifiers.erase( object->identifierString() ), Eq( 1 ) );
  }

  ASSERT_THAT( requiredIdentifiers, IsEmpty() );
}

#endif // H_EFA8125317B74D7E9CCFD61B363BB59D
