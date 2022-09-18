//
// ... external header files
//
#include <introspection/macros.hpp>
#include <pybind11/pybind11.h>

//
// ... easypy header files
//
#include <easypy/easypy.hpp>

namespace easypy::testing {
   enum class Colors {
      red,
      orange,
      yellow,
      green,
      blue,
      indigo,
      violet
   };
   INTROSPECTION_ENUM_DATA(
     Colors,
     red,
     orange,
     yellow,
     green,
     blue,
     indigo,
     violet);

   PYBIND11_MODULE(enum_binding_test, m) {
      m.doc() = "Documentation for this module";
      bind_type(std::type_identity<Colors>{}, m);
   }

} // end of namespace easypy::testing
