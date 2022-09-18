#pragma once

//
// ... easypy header files
//
#include <easypy/details/import.hpp>

namespace easypy::details {

   template<typename T>
   concept Aggregate = is_aggregate_v<T> && ! Introspective<T>;

   template<typename T>
   concept Introspective_or_aggregate =
     Introspective<T> || Aggregate<T>;

   template<typename T>
   concept Convertible_to_json = convertible_to<T, json>;

   template<typename T>
   concept Convertible_from_json = convertible_to<json, T>;

   template<typename T>
   class_<T>
   bind_type(module_&);

   class Type_binding {

      template<Introspective_enum T>
      static enum_<T>
      bind(module_& m) {
         enum_<T> en(m, string{bare_type_name<T>}.c_str());
         [ & ]<auto... Index>(index_sequence<Index...>) {
            (en.value(
               string{unqualified_enum_value_names<T>[ Index ]}.c_str(),
               enum_values<T>[ Index ]),
             ...);
         }
         (make_index_sequence<enum_value_count<T>>());

         return en;
      }

      template<Introspective_or_aggregate T>
      static class_<T>
      bind(module_& m) {
         auto cls = class_<T>(m, string{bare_type_name<T>}.c_str());
         add_default_constructor(cls);
         add_constructor(cls);
         add_fields(cls);
         add_json_conversion(cls);
         add_repr(cls);
         return cls;
      }

      template<typename T>
      static void
      add_default_constructor(class_<T>& cls) {
         cls.def(init<>());
      }

      template<typename T>
      static void
      add_constructor(class_<T>& cls) {
         [ & ]<auto... Index>(index_sequence<Index...>) {
            cls.def(init<remove_cvref_t<decltype(get<Index>(
                      declval<T>()))>...>());
         }
         (make_index_sequence<tuple_size_v<T>>());
      }

      template<Introspective T>
      static void
      add_fields(class_<T>& cls) {
         [ & ]<auto... Index>(index_sequence<Index...>) {
            (
              [ & ] {
                 cls.def_readwrite(
                   string(member_name<T, Index>).c_str(),
                   member_pointer<T, Index>);
              }(),
              ...);
         }
         (make_index_sequence<tuple_size_v<T>>());
      }

      template<Aggregate T>
      static void
      add_fields(class_<T>& cls) {
         [ & ]<auto... Index>(index_sequence<Index...>) {
            cls
              .def(
                "__len__",
                [ = ](const T&) { return tuple_size_v<T>; })
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
         (make_index_sequence<tuple_size_v<T>>());
      }

      template<typename T>
      static void
      add_repr(class_<T>& cls) {
         if constexpr(Convertible_to_json<T>) {
            cls
              .def(
                "__str__",
                [](const T& self) { return json(self).dump(2); })
              .def("__repr__", [](const T& self) {
                 return json(self).dump(2);
              });
         }
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
