//
// ... external header files
//
#include <easyj/easyj.hpp>
#include <introspection/macros.hpp>
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
      INTROSPECTION_DATA(Point, x, y);
   };

   namespace py = pybind11;

   PYBIND11_MODULE(introspective_binding_test, m) {
      m.doc() = "Documentation for this module";
      bind_type(std::type_identity<Point>{}, m);
   }

} // end of namespace easypy::testing
