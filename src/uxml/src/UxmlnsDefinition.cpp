#include <string>
#include "UxmlnsDefinition.hpp"

const std::string& visix::uxml::UxmlnsDefinition::alias() STABLE {
    return this->_alias;
}

const std::string& visix::uxml::UxmlnsDefinition::actualNamespace() STABLE {
    return this->_namespace;
}