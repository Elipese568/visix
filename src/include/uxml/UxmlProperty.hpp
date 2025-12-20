#include <string>
#include <vector>
#include <fstream>
#include <optional>

#include "uxml/binding/BindingOption.hpp"

#include "global.h"

#ifndef VISIX_UXML_PROPERTY_H
#define VISIX_UXML_PROPERTY_H

namespace visix::uxml{
    class UxmlProperty{
    private:
        std::string _name;
        std::string _valStr;
        binding::BindingOption _bindOption;
        bool _isBind = false;
    public:
        UxmlProperty(const std::string& name, const std::string& val) : _name{name}, _valStr{val} { }
        UxmlProperty(const std::string& name, binding::BindingOption option) : _name{name}, _valStr{option.targetPath()}, _bindOption{option}, _isBind(true) {}

        const std::string &name() STABLE;
        const std::string &value() STABLE;

        bool isBind() STABLE;
        const binding::BindingOption &bindingOption() STABLE;
    };
} // namespace visix::uxml

#endif // VISIX_UXML_PROPERTY_H