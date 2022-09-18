//
// ... external header files
//
#include "easyj/easyj.hpp"
#include <pybind11/pybind11.h>

//
// ... easypy header files
//
#include <easypy/easypy.hpp>

namespace easypy::testing {

   using easyj::from_json;
   using easyj::to_json;

   struct Point {

      double x;
      double y;
   };

   PYBIND11_MODULE(aggregate_binding_test, m) {
      m.doc() = "Documentation for this module";
      bind_type(std::type_identity<Point>{}, m);
   }

} // end of namespace easypy::testing
