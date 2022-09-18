#pragma once

//
// ... easypy header files
//
#include <easypy/details/import.hpp>

namespace easypy::details {

   template<typename T>
   concept Aggregate = is_aggregate_v<T> && ! Introspective<T>;

   template<typename T>
   concept Convertible_to_json = convertible_to<T, json>;

   template<typename T>
   concept Convertible_from_json = convertible_to<json, T>;

   template<typename T>
   class_<T>
   bind_type(module_&);

   class Type_binding {
      template<Introspective T>
      static class_<T>
      bind(module_& m) {
         auto cls = class_<T>(m, string{bare_type_name<T>}.c_str());
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
         if constexpr(Convertible_to_json<T>) {
            cls.def("dumps_json", [](const T& self) {
               return json(self).dump();
            });
         }
         if constexpr(Convertible_from_json<T>) {
            cls.def_static(
              "loads_json",
              [](const std::string& json_string) {
                 T result = json::parse(json_string);
                 return result;
              });
         }
         add_json_conversion(cls);
         return cls;
      }

      template<Aggregate T>
      static class_<T>
      bind(module_& m) {
         class_<T> cls{m, string{bare_type_name<T>}.c_str()};
         constexpr auto member_count = tuple_size_v<T>;
         [ & ]<auto... Index>(index_sequence<Index...>) {
            cls
              .def(init<remove_cvref_t<decltype(get<Index>(
                     declval<T>()))>...>())
              .def("__len__", [ = ](const T&) { return member_count; })
              .def(
                "__getitem__",
                [ = ](const T& self, size_t index) -> decltype(auto) {
                   object obj;
                   (
                     [ & ] {
                        if(index == Index) {
                           obj = cast(get<Index>(self));
                        }
                     }(),
                     ...);
                   return obj;
                })
              .def(
                "__setitem__",
                [ = ](T& self, int index, const object& obj) {
                   (
                     [ & ] {
                        if(index == Index) {
                           get<Index>(self) =
                             cast<tuple_element_t<Index, T>>(obj);
                        }
                     }(),
                     ...);
                   return self;
                });
         }
         (make_index_sequence<member_count>());
         add_json_conversion(cls);
         return cls;
      }

      template<typename T>
      static void
      add_json_conversion(class_<T>& cls) {
         if constexpr(Convertible_to_json<T>) {
            add_conversion_to_json(cls);
         }
         if constexpr(Convertible_from_json<T>) {
            add_conversion_from_json(cls);
         }
      }

      template<typename T>
      static void
      add_conversion_to_json(class_<T>& cls) {
         cls.def("dumps_json", [](const T& self) {
            return json(self).dump();
         });
      }

      template<typename T>
      static void
      add_conversion_from_json(class_<T>& cls) {
         cls.def_static(
           "loads_json",
           [](const std::string& json_string) {
              T result = json::parse(json_string);
              return result;
           });
      }

      template<typename T>
      friend class_<T>
      bind_type(type_identity<T>, module_&);
   };

   template<typename T>
   class_<T>
   bind_type(type_identity<T>, module_& m) {
      return Type_binding::bind<T>(m);
   }

} // end of namespace easypy::details
