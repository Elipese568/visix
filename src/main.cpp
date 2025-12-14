#include<iostream>
#include "uxml/Uxml.hpp"
#include "uxml/UxmlElement.hpp"

void printElement(const visix::uxml::UxmlElement &e, int indent=0){
    std::string pad(indent, ' ');
    std::cout << pad << "Element: " << e.name() << '\n';
    for(const auto &p : e.properties()){
        std::cout << pad << "  Prop: " << p.name() << " = " << p.value();
        if(p.isBind()){
            std::cout << " (bind->" << p.bindingOption().targetPath() << ")";
        }
        std::cout << '\n';
    }
    for(const auto &c : e.subElements()){
        printElement(c, indent + 2);
    }
}

int main(){
    visix::uxml::Uxml a{"D:\\work\\source\\repos\\visix\\tests\\sample.uxml"};
    const visix::uxml::UxmlElement *root = a.root();
    if(root){
        printElement(*root);
        std::cout << "-- Debug property list --" << std::endl;
        for(const auto &p: root->properties()){
            std::cout << "Pname: '" << p.name() << "' val:'" << p.value() << "' bind:" << (p.isBind()?"yes":"no") << "\n";
        }
        if(const auto *p = root->getProperty("Property1")){
            std::cout << "Root Property1: " << p->value() << std::endl;
        }
        if(const auto *bp = root->getProperty("BindProperty1")){
            std::cout << "BindProperty1 target: " << bp->bindingOption().targetPath() << std::endl;
        }
    } else {
        std::cout << "Failed to parse sample.uxml or file missing" << std::endl;
    }
}