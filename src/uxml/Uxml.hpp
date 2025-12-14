#include <string>
#include <fstream>
#include <memory>

#include "UxmlElement.hpp"

#ifndef VISIX_UXML_H
#define VISIX_UXML_H

// App = {
//     $Class = "example::App";
//     $Name = "exampleApp";
//     Property1 = "value";
//     BindProperty1 &= property {
//         Mode = TwoWay;
//         Type = type;
//     };
// }(
//     Element = {
//         $Name = "elem1";
//         PropertyA = "value";
//         PropertyInteger = "1";
//     };
// );

namespace visix::uxml{
    class Uxml{
    private:
        std::ifstream _Src;
        std::unique_ptr<uxml::UxmlElement> _RootElem;
    public:
        Uxml(const std::string&) noexcept;
        const UxmlElement* root() const noexcept { return _RootElem.get(); }
    };
} // namespace visix::uxml


#endif // VISIX_UXML_H