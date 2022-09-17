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

   struct Point {
      double x;
      double y;
      INTROSPECTION_DATA(Point, x, y);
   };

   namespace py = pybind11;

   PYBIND11_MODULE(introspective_binding_test, m) {
      m.doc() = "pybind11 example plugin"; // optional module docstring
      bind_type(std::type_identity<Point>{}, m);
      // py::class_<Point>(m, "Point")
      //   .def(py::init<double, double>())
      //   .def_readwrite("x", &Point::x)
      //   .def_readwrite("y", &Point::y);
   }

} // end of namespace easypy::testing
