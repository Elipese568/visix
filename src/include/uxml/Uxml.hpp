#include <string>
#include <fstream>
#include <memory>

#include "UxmlElement.hpp"
#include "global.h"

#ifndef VISIX_UXML_H
#define VISIX_UXML_H

namespace visix::uxml{
    /// @brief Represents a UXML document.
    class Uxml{
    private:
        std::ifstream _Src;
        std::unique_ptr<uxml::UxmlElement> _RootElem;
    public:
        Uxml(const std::string&) noexcept;

        /// @brief Gets the root element of the UXML document.
        /// @return A pointer to the root UxmlElement.
        const UxmlElement* root() STABLE;

        /// @brief Gets all declared namespaces in the UXML document.
        /// @return A vector of UxmlnsDefinition representing the declared namespaces.
        std::vector<visix::uxml::UxmlnsDefinition> declaredNamespaces() STABLE;
    };
} // namespace visix::uxml


#endif // VISIX_UXML_H