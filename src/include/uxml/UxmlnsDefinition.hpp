#include <string>

#include "global.h"

#ifndef VISIX_UXMLNS_DEFINITION_H
#define VISIX_UXMLNS_DEFINITION_H

namespace visix::uxml{
    class UxmlnsDefinition{
    private:
        std::string _alias;
        std::string _namespace;
    public:
        UxmlnsDefinition(std::string alias, std::string uxmlns) : _alias{alias}, _namespace{uxmlns} {};
        const std::string &alias() STABLE;
        const std::string &actualNamespace() STABLE;
    };
}

#endif // VISIX_UXMLNS_DEFINITION_H