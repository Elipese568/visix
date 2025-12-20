#include <vector>
#include <string>

#include "uxml/binding/BindingOption.hpp"

#ifndef VISIX_BINDING_OPTION_BUILDER
#define VISIX_BINDING_OPTION_BUILDER

namespace visix::uxml::binding{
    class BindingOptionBuilder{
    private:
        std::string _target;
        std::string _type;
        std::string _converter;
        std::vector<std::string> _converterParameters;
        binding_mode _mode;
    public:
        BindingOptionBuilder();
        void target(std::string target);
        void mode(binding_mode mode);
        void type(std::string type);
        void converter(std::string converter);
        void addConverterParameters(std::string param);
        void converterParameters(std::vector<std::string>& parameters);
        BindingOption build();
    };
}

#endif // VISIX_BINDING_OPTION_BUILDER