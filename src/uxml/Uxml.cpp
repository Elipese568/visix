#include <sstream>
#include <memory>

#include "Uxml.hpp"

visix::uxml::Uxml::Uxml(const std::string& srcFilePath) noexcept {
    _Src.open(srcFilePath);
    if(!_Src.is_open()){
        _RootElem = nullptr;
        return;
    }
    std::ostringstream ss;
    ss << _Src.rdbuf();
    std::string fileContent = ss.str();
    _RootElem = std::make_unique<UxmlElement>(fileContent);
}