#include <string>
#include <vector>

#include "global.h"

#ifndef VISIX_UXML_BINDING_OPTION_H
#define VISIX_UXML_BINDING_OPTION_H

namespace visix::uxml::binding{

    /// @brief Defines the binding modes available for UXML properties.
    enum class binding_mode{
        /// @brief Data flows from source to target only.
        FromSource,
        /// @brief Data flows bidirectionally between source and target.
        SourceSync,
        /// @brief Default to inherit.
        Undefined,
        /// @brief Binding is not set.
        Unavailable
    };

    /// @brief Represents binding options for UXML properties.
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
        /// @brief Gets the target path for the binding.
        /// @return The target path as a string.
        const std::string& targetPath() STABLE;

        /// @brief Gets the binding mode.
        /// @return The binding mode.
        const binding_mode mode() STABLE;

        /// @brief Gets the converter used in the binding.
        /// @return The converter as a string.
        const std::string& converter() STABLE;

        /// @brief Gets the parameters for the converter.
        /// @return A vector of strings representing the converter parameters.
        const std::vector<std::string>& converterParameters() STABLE;

        /// @brief Gets the type associated with the binding.
        /// @return The type as a string.
        const std::string& type() STABLE;
    };
}

#endif // VISIX_UXML_BINDING_OPTION_H