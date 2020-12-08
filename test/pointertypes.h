#ifndef H_68EF5B3DAAC04073AF90D8067EFF4077
#define H_68EF5B3DAAC04073AF90D8067EFF4077

#include <boost/shared_ptr.hpp>
#include <memory>

class Base;

using PointerTypes = boost::mp11::mp_list<Base *, std::shared_ptr<Base>, std::unique_ptr<Base>,
                                          boost::shared_ptr<Base>>;

#endif // H_68EF5B3DAAC04073AF90D8067EFF4077
