#pragma once

//
// ... standard header files
//
#include <string>
#include <tuple>
#include <type_traits>

//
// ... external header files
//
#include <introspection/introspection.hpp>
#include <pfr.hpp>
#include <pybind11/pybind11.h>

namespace easypy::details {

   using std::declval;
   using std::get;
   using std::index_sequence;
   using std::is_aggregate_v;
   using std::make_index_sequence;
   using std::remove_cvref_t;
   using std::string;
   using std::type_identity;

   using pybind11::cast;
   using pybind11::class_;
   using pybind11::init;
   using pybind11::module_;
   using pybind11::object;

   using introspection::bare_type_name;
   using introspection::member_name;
   using introspection::member_pointer;
   using introspection::Member_type;
   using introspection::concepts::Introspective;

   using pfr::get;
   using pfr::tuple_element_t;
   using pfr::tuple_size_v;

} // end of namespace easypy::details
