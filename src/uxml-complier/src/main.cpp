#include<iostream>
#include<filesystem>

#include "Uxml.hpp"
#include "UxmlElement.hpp"


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

int main(int argc, char **argv){

    std::filesystem::path uxmlPath{argv[1]};
    std::cout << "Loading file: " << std::filesystem::absolute(uxmlPath).string() << std::endl;
    std::cout << "Exist status: " << std::filesystem::exists(std::filesystem::absolute(uxmlPath)) << std::endl;

    visix::uxml::Uxml a{std::filesystem::absolute(uxmlPath).string()};

    const visix::uxml::UxmlElement *root = a.root();
    if(root){
        printElement(*root);
        std::cout << "-- Debug property list --" << std::endl;
        auto pc = root->properties();
        for(const auto &p: pc){
            std::cout << "Pname: '" << p.name() << "' val:'" << p.value() << "' bind:" << (p.isBind()?"yes":"no") << "\n";
        }
        for(const auto &p: root->properties()){
            std::cout << "Pname: '" << p.name() << "' val:'" << p.value() << "' bind:" << (p.isBind()?"yes":"no") << "\n";
        }
        if(const auto *p = root->getProperty("Property1")){
            std::cout << "Root Property1: " << p->value() << std::endl;
        }
        if(const auto *bp = root->getProperty("BindProperty1")){
            std::cout << "BindProperty1 target: " << bp->bindingOption().targetPath() << std::endl;
        }
        for(const auto &ns : a.declaredNamespaces()){
            std::cout << "Declared namespace: " << ns.alias() << " -> " << ns.actualNamespace() << std::endl;
        }
    } else {
        std::cout << "Failed to parse sample.uxml or file missing" << std::endl;
    }
    
}