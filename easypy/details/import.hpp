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

   using std::get;
   using std::index_sequence;
   using std::make_index_sequence;
   using std::string;
   using std::type_identity;

   using pybind11::class_;
   using pybind11::init;
   using pybind11::module_;

   using introspection::bare_type_name;
   using introspection::member_name;
   using introspection::member_pointer;
   using introspection::Member_type;
   using introspection::concepts::Introspective;

   using pfr::get;
   using pfr::tuple_size_v;

} // end of namespace easypy::details
