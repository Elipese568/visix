#include <string>
#include <vector>

#include "global.h"

#ifndef VISIX_UXML_BINDING_OPTION_H
#define VISIX_UXML_BINDING_OPTION_H

namespace visix::uxml::binding{
    enum class binding_mode{
        FromSource,
        SourceSync,
        Undefined,
        Unavailable
    };

    class BindingOption{
    private:
        std::string _target;
        std::string _type;
        std::string _converter;
        std::vector<std::string> _converterParameters;
        binding_mode _mode;
    public:
        BindingOption() : _target{""}, _mode{binding_mode::Unavailable}, _type{""}, _converter{""}, _converterParameters{} {};
        BindingOption(const std::string& targetPath, 
                      const std::string& type, 
                      binding_mode mode, 
                      const std::string& converter, 
                      std::vector<std::string> converterParameters) 
            : _target{targetPath}, _type{type}, _mode{mode}, _converter{converter}, _converterParameters{converterParameters} {}
        
        const std::string& targetPath() STABLE;
        const binding_mode mode() STABLE;
        const std::string& converter() STABLE;
        const std::vector<std::string>& converterParameters() STABLE;
        const std::string& type() STABLE;
    };
}

#endif // VISIX_UXML_BINDING_OPTION_H