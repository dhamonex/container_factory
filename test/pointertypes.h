#ifndef H_68EF5B3DAAC04073AF90D8067EFF4077
#define H_68EF5B3DAAC04073AF90D8067EFF4077

#if __has_include( <boost/mp11/mpl_list.hpp>)
#include <boost/mp11/mpl_list.hpp>
#define HAS_BOOST_MPL_LIST
#endif

#include <boost/shared_ptr.hpp>
#include <memory>

class Base;

#ifndef HAS_BOOST_MPL_LIST

namespace boost::aux
{
  struct mp11_tag
  {
  };
} // namespace boost::aux

namespace boost::mpl
{
  template <typename Sequence>
  struct sequence_tag;

  template <class... T>
  struct sequence_tag<mp11::mp_list<T...>>
  {
    using type = aux::mp11_tag;
  };
} // namespace boost::mpl

#endif

using PointerTypes = boost::mp11::mp_list<Base *, std::shared_ptr<Base>, std::unique_ptr<Base>,
                                          boost::shared_ptr<Base>>;

#endif // H_68EF5B3DAAC04073AF90D8067EFF4077
