#pragma once

//
// ... standard header files
//
#include <concepts>
#include <string>
#include <tuple>
#include <type_traits>
//
// ... external header files
//
#include <introspection/introspection.hpp>
#include <nlohmann/json.hpp>
#include <pfr.hpp>
#include <pybind11/pybind11.h>

namespace easypy::details {

   using std::convertible_to;
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
   using pybind11::enum_;
   using pybind11::init;
   using pybind11::module_;
   using pybind11::object;

   using introspection::bare_type_name;
   using introspection::enum_value_count;
   using introspection::enum_values;
   using introspection::member_name;
   using introspection::member_pointer;
   using introspection::Member_type;
   using introspection::unqualified_enum_value_names;
   using introspection::concepts::Introspective;
   using introspection::concepts::Introspective_enum;

   using pfr::get;
   using pfr::tuple_element_t;
   using pfr::tuple_size_v;

   using nlohmann::json;

} // end of namespace easypy::details
