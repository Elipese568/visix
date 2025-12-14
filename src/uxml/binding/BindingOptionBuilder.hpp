#include <vector>
#include <string>

#include "BindingOption.hpp"

namespace visix::uxml::binding{
    class BindingOptionBuilder{
    private:
        std::string _target;
        std::string _type;
        std::string _converter;
        std::vector<std::string> _converterParameters;
        binding_mode _mode;
    public:
        BindingOptionBuilder() : _target{""}, _mode{binding_mode::Undefined}, _type{""}, _converter{""}, _converterParameters{} {}
        void target(std::string target) {_target = target;}
        void mode(binding_mode mode) {_mode = mode;}
        void type(std::string type) {_type = type;}
        void converter(std::string converter) {_converter = converter;}
        void addConverterParameters(std::string param) {_converterParameters.push_back(param);}
        void converterParameters(std::vector<std::string>& parameters) {_converterParameters = parameters;}
        BindingOption build() {
            return BindingOption(std::move(_target), std::move(_type), _mode, std::move(_converter), std::move(_converterParameters));
        }
    };
}
