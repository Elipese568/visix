#include <string>
#include <vector>

#include "global.h"
#include "UxmlProperty.hpp"
#include "UxmlnsDefinition.hpp"

#ifndef VISIX_UXML_ELEMENT_H
#define VISIX_UXML_ELEMENT_H

namespace visix::uxml{
    /// @brief Represents an element in a UXML document.
    class UxmlElement{
    private:
        std::string _name;
        std::string _tag;
        std::vector<UxmlElement> _subElements;
        std::vector<UxmlProperty> _properties;
        std::vector<UxmlnsDefinition> _declared_namespaces;
    public:
        UxmlElement() noexcept = default;
        UxmlElement(const std::string &raw);
        UxmlElement(std::string name, 
                    std::vector<UxmlProperty>&& properties, 
                    std::vector<UxmlElement>&& subElements,
                    std::vector<UxmlnsDefinition>&& declaredNamespaces) noexcept;
        
        const std::string &name() STABLE;
        const std::string &tag() STABLE;
        const std::vector<UxmlElement> &subElements() STABLE;
        const std::vector<UxmlProperty> &properties() STABLE;

        /// @brief Gets all declared namespaces in this UXML element(including nested elements).
        /// @return A vector of UxmlnsDefinition representing the declared namespaces.
        std::vector<UxmlnsDefinition> declaredNamespaces() STABLE;
        
        const UxmlProperty* getProperty(const std::string &name) const;
        const UxmlElement* getSubElement(const std::string &name) const;
        const UxmlnsDefinition* getUxmlns(const std::string &name) const;
    };
} // namespace visix::uxml

#endif // VISIX_UXML_ELEMENT_H