#include "UxmlProperty.hpp"

const std::string &visix::uxml::UxmlProperty::name() STABLE{
    return this->_name;
}
const std::string &visix::uxml::UxmlProperty::value() STABLE{
    return this->_valStr;
}
bool visix::uxml::UxmlProperty::isBind() STABLE{
    return this->_isBind;
}
const visix::uxml::binding::BindingOption &visix::uxml::UxmlProperty::bindingOption() STABLE {
    return this->_bindOption;
}