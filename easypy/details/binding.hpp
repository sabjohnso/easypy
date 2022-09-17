#pragma once

//
// ... easypy header files
//
#include <easypy/details/import.hpp>

namespace easypy::details {

   template<typename T>
   class_<T>
   bind_type(type_identity<T>, module_&);

   class Type_binding {
      template<Introspective T>
      static auto
      bind(type_identity<T>, module_& m) {
         auto cls =
           class_<T>(m, std::string{bare_type_name<T>}.c_str());
         [ & ]<auto... Index>(index_sequence<Index...>) {
            cls.def(init<Member_type<T, Index>...>());
            (
              [ & ] {
                 cls.def_readwrite(
                   string(member_name<T, Index>).c_str(),
                   member_pointer<T, Index>);
              }(),
              ...);
         }
         (make_index_sequence<tuple_size_v<T>>());
         return cls;
      }

      template<typename T>
      friend class_<T>
      bind_type(type_identity<T>, module_&);
   };

   template<typename T>
   class_<T>
   bind_type(type_identity<T>, module_& m) {
      return Type_binding::bind(type_identity<T>{}, m);
   }

} // end of namespace easypy::details
