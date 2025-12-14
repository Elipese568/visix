#include <string>
#include <vector>

#include "global.h"
#include "UxmlProperty.hpp"


#ifndef VISIX_UXML_ELEMENT_H
#define VISIX_UXML_ELEMENT_H

namespace visix::uxml{
    class UxmlElement{
    private:
        std::string _name;
        std::string _tag;
        std::vector<UxmlElement> _subElements;
        std::vector<UxmlProperty> _properties;
    public:
        UxmlElement() noexcept = default;
        UxmlElement(const std::string &raw);
        UxmlElement(std::string name, 
                    std::vector<UxmlProperty> properties, 
                    std::vector<UxmlElement> subElements) noexcept;

        const std::string &name() STABLE;
        const std::string &tag() STABLE;
        const std::vector<UxmlElement> &subElements() STABLE;
        const std::vector<UxmlProperty> &properties() STABLE;
        
        const UxmlProperty* getProperty(const std::string &name) const;
        const UxmlElement* getSubElement(const std::string &name) const;
    };
} // namespace visix::uxml

#endif // VISIX_UXML_ELEMENT_H