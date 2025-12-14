#include <string>
#include <optional>
#include <vector>

#include "UxmlElement.hpp"

namespace visix::uxml {
    template<class ListTy, class StrTy>
    std::optional<const UxmlElement*> _Find_Element_By_Name(ListTy& elems, StrTy name){
        auto result = std::find_if(elems.begin(), elems.end(), [&name](const UxmlElement& e) {return e.name() == name;});
        if(result == elems.end())
            return std::nullopt;
        return &(*result);
    }
    template<class ListTy, class StrTy>
    std::optional<const UxmlProperty*> _Find_Property_By_Name(ListTy& props, StrTy name){
        auto result = std::find_if(props.begin(), props.end(), [&name](const UxmlProperty& e) {return e.name() == name;});
        if(result == props.end())
            return std::nullopt;
        return &(*result);
    }
}