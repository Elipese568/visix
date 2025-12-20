#include "uxml/binding/BindingOption.hpp"

const std::string& visix::uxml::binding::BindingOption::targetPath() STABLE {
    return this->_target;
}

const visix::uxml::binding::binding_mode visix::uxml::binding::BindingOption::mode() STABLE {
    return this->_mode;
}

const std::string& visix::uxml::binding::BindingOption::type() STABLE {
    return this->_type;
}

const std::string& visix::uxml::binding::BindingOption::converter() STABLE {
    return this->_converter;
}

const std::vector<std::string>& visix::uxml::binding::BindingOption::converterParameters() STABLE {
    return this->_converterParameters;
}