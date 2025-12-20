#include "uxml/binding/BindingOptionBuilder.hpp"

namespace visix::uxml::binding{

BindingOptionBuilder::BindingOptionBuilder()
    : _target{""}, _mode{binding_mode::Undefined}, _type{""}, _converter{""}, _converterParameters{} {}

void BindingOptionBuilder::target(std::string target) {
    _target = std::move(target);
}

void BindingOptionBuilder::mode(binding_mode mode) {
    _mode = mode;
}

void BindingOptionBuilder::type(std::string type) {
    _type = std::move(type);
}

void BindingOptionBuilder::converter(std::string converter) {
    _converter = std::move(converter);
}

void BindingOptionBuilder::addConverterParameters(std::string param) {
    _converterParameters.push_back(std::move(param));
}

void BindingOptionBuilder::converterParameters(std::vector<std::string>& parameters) {
    _converterParameters = parameters;
}

BindingOption BindingOptionBuilder::build() {
    return BindingOption(std::move(_target), std::move(_type), _mode, std::move(_converter), std::move(_converterParameters));
}

} // namespace visix::uxml::binding
