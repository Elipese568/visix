#include <string>
#include <optional>
#include <vector>

#include "UxmlElement.hpp"

namespace visix::uxml {
    template<class _ElemTy>
    concept NamedElement = requires (_ElemTy val) { val.name(); };

    template<class ElemTy, class StrTy>
    requires NamedElement<ElemTy>
    std::optional<std::reference_wrapper<const ElemTy>> _Find_Element_By_Name(
        const std::vector<ElemTy>& elems, StrTy name) 
    {
        auto result = std::find_if(elems.begin(), elems.end(), [&name](const ElemTy& e) {
            return e.name() == name;
        });

        if (result == elems.end()) {
            return std::nullopt; // Element not found
        }

        return std::ref(*result); // Return a reference to the found element
    }

    template<class _ElemTy, class _Fn>
    concept NameFunction = requires (_Fn fun, _ElemTy elem) { fun(elem); };

    template<class ElemTy, class StrTy, class NameFn>
    requires NameFunction<ElemTy, NameFn>
    std::optional<std::reference_wrapper<const ElemTy>> _Find_Element_By_Name(
        const std::vector<ElemTy>& elems, StrTy name, NameFn keyedFunction)
    {
        auto result = std::find_if(elems.begin(), elems.end(), [&name, &keyedFunction](const ElemTy& e) {
            return keyedFunction(e) == name;
        });

        if (result == elems.end()) {
            return std::nullopt; // Element not found
        }

        return std::ref(*result); // Return a reference to the found element
    }
}