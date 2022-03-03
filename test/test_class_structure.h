#ifndef H_107F4246F0794C3481C63FF948760E6A
#define H_107F4246F0794C3481C63FF948760E6A

#include <string>

class Base
{
  public:
    Base() = default;
    Base( std::string text )
      : m_additionalText{ std::move( text ) }
    {
    }

    Base( int number )
      : m_additionalInteger{ number }
    {
    }

    Base( std::string text, int number )
      : m_additionalText{ std::move( text ) }
      , m_additionalInteger{ number }
    {
    }

    virtual ~Base(){};

    std::string identifierString() const
    {
      auto identifier = classIdentifierString();

      if ( !m_additionalText.empty() ) {
        identifier += "_" + m_additionalText;
      }

      return identifier + "_" + std::to_string( m_additionalInteger );
    }

  protected:
    virtual std::string classIdentifierString() const
    {
      return m_className;
    }

  private:
    std::string m_additionalText;
    int m_additionalInteger{ 0 };

    inline static const std::string m_className{ "Base" };
};

class SubclassA : public Base
{
  public:
    using Base::Base;

  protected:
    std::string classIdentifierString() const override
    {
      return m_className;
    }

  private:
    inline static const std::string m_className{ "SubclassA" };
};

class SubclassB : public Base
{
  public:
    using Base::Base;

  protected:
    std::string classIdentifierString() const override
    {
      return m_className;
    }

  private:
    inline static const std::string m_className{ "SubclassB" };
};

template <typename T>
inline constexpr bool is_pointer_type =
  container_factory::detail::is_shared_ptr_v<T> ||
  container_factory::detail::is_boost_shared_ptr_v<T> ||
  container_factory::detail::is_unique_ptr_v<T> || std::is_pointer_v<T>;

template <class T>
struct TestClassEqualKeyCompare
{
    bool operator()( const T &rhs, const T &lhs ) const
    {
      static_assert( is_pointer_type<T>, "needs to be a pointer type of Base" );
      return rhs->identifierString() == lhs->identifierString();
    }
};

template <class T>
struct TestClassHash
{
  bool operator()( const T &v ) const
    {
      static_assert( is_pointer_type<T>, "needs to be a pointer type of Base" );
      return std::hash<std::string>{}( v->identifierString() );
    }
};


#endif // H_107F4246F0794C3481C63FF948760E6A
