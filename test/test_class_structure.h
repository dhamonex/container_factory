#ifndef H_107F4246F0794C3481C63FF948760E6A
#define H_107F4246F0794C3481C63FF948760E6A

#include <string>

class Base
{
  public:
    Base() = default;
    Base( std::string text )
      : m_additionalText{ std::move( text ) } 
    {}
    
    virtual ~Base() {};
    
    std::string identifierString() const 
    { 
      auto identifier = classIdentifierString();
      
      if ( !m_additionalText.empty() ) {
        identifier += "_" + m_additionalText;
      }
      
      return identifier + "_" + std::to_string( m_additionalInteger ); 
    }
    
  protected:
    virtual std::string classIdentifierString() const { return m_className; }
    
  private:
    std::string m_additionalText;
    int m_additionalInteger{ 0 };
    
    inline static const std::string m_className{ "Base" };
};

class SubclassA : public Base
{
  public:
    std::string classIdentifierString() const override { return m_className; }
      
  private:
    inline static const std::string m_className{ "SubclassA" };
};

class SubclassB : public Base
{
  public:
    std::string classIdentifierString() const override { return m_className; }
      
  private:
    inline static const std::string m_className{ "SubclassB" };
};

#endif // H_107F4246F0794C3481C63FF948760E6A


