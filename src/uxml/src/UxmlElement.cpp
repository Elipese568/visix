#include "UxmlElement.hpp"
#include <cctype>
#include <stdexcept>
#include <format>
#include <algorithm>
#include <unordered_set>

#include "UxmlUtility.hpp"
#include "binding/BindingOptionBuilder.hpp"

namespace visix::uxml{
	namespace {
		class Parser {
		public:
			const std::string &s;
			size_t pos;
			Parser(const std::string &src) : s(src), pos(0) {}

			void skipSpace(){
				while(pos < s.size()){
					if(isspace((unsigned char)s[pos])){ pos++; continue; }
					// skip // comments
					if(s[pos] == '/' && pos+1 < s.size() && s[pos+1] == '/'){
						pos += 2;
						while(pos < s.size() && s[pos] != '\n') pos++;
						continue;
					}
					// skip /* ... */ comments
					if(s[pos] == '/' && pos+1 < s.size() && s[pos+1] == '*'){
						pos += 2;
						while(pos+1 < s.size() && !(s[pos] == '*' && s[pos+1] == '/')) pos++;
						if(pos+1 < s.size()) pos += 2;
						continue;
					}
					break;
				}
			}

			char peek(){ skipSpace(); return pos < s.size() ? s[pos] : '\0'; }
			bool match(char c){ skipSpace(); if(pos < s.size() && s[pos] == c){ pos++; return true; } return false; }
			void expect(char c){ skipSpace(); if(pos >= s.size() || s[pos] != c){ throw std::runtime_error("unexpected char"); } pos++; }

			std::string parseIdentifier(bool allowColon = true){
				skipSpace(); size_t start = pos;
				if(pos < s.size() && (isalpha((unsigned char)s[pos]) || s[pos] == '$' || s[pos] == '_')){
					pos++;
					while(pos < s.size() && (isalnum((unsigned char)s[pos]) || s[pos] == '_' || (s[pos] == ':' && allowColon) || s[pos] == '$')) pos++;
					return s.substr(start, pos - start);
				}
				throw std::runtime_error("identifier expected");
			}

			std::string parseUnquotedValue(){
				skipSpace(); size_t start = pos;
				while(pos < s.size() && !isspace((unsigned char)s[pos]) && s[pos] != ';' && s[pos] != '}' && s[pos] != ')') pos++;
				return s.substr(start, pos - start);
			}

			std::string parseStringLiteral(){
				skipSpace(); if(pos >= s.size() || s[pos] != '"') throw std::runtime_error("string expected");
				pos++; std::string out;
				while(pos < s.size()){
					char c = s[pos++];
					if(c == '\\'){
						if(pos < s.size()) { out.push_back(s[pos++]); }
					} else if(c == '"'){
						return out;
					} else {
						out.push_back(c);
					}
				}
				throw std::runtime_error("unterminated string");
			}

			std::vector<visix::uxml::UxmlProperty> parseProperties(){
				std::vector<visix::uxml::UxmlProperty> props;
				expect('(');
				while(true){
					skipSpace(); if(peek() == ')'){ pos++; break; }
					std::string pname = parseIdentifier();
					skipSpace();
					// check for bind operator &=
					if(peek() == '&'){
						// expect &=
						if(pos+1 < s.size() && s[pos+1] == '='){
                            parseBindingConnection(props, pname);
                            continue;
						} else {
							throw std::runtime_error("expected &=");
						}
					}

					expect('=');
					skipSpace();
					std::string val;
					if(peek() == '"'){
						val = parseStringLiteral();
					} else {
						val = parseUnquotedValue();
					}
					skipSpace(); if(peek() == ';') pos++; // consume ;
					props.emplace_back(pname, val);
				}
				return props;
            }

            void parseBindingConnection(std::vector<visix::uxml::UxmlProperty> &props, std::string &pname)
            {
                pos += 2;
                skipSpace();
                std::string targetPath;
				while(pos < s.size()){
					char c = s[pos++];
					if(c == ' '){
						break;
					} else {
						targetPath.push_back(c);
					}
				}
                skipSpace();
                // nested object
                auto inner = parseProperties();
                // optional semicolon
                skipSpace();
                if (peek() == ';')
                    pos++;
				
				binding::BindingOptionBuilder builder{};
				builder.target(targetPath);
				_Has_Invoke(_Find_Element_By_Name(inner, "Type"), [&builder](std::reference_wrapper<const UxmlProperty> e){builder.type(e.get().value());});
				_Has_Invoke(_Find_Element_By_Name(inner, "Converter"), [&builder](std::reference_wrapper<const UxmlProperty> e){builder.converter(e.get().value());});
				_Has_Invoke(_Find_Element_By_Name(inner, "Mode"), [&builder](std::reference_wrapper<const UxmlProperty> e){
					auto v = e.get().value();
					if(v == "FromSource") builder.mode(binding::binding_mode::FromSource);
					else if(v == "SourceSync") builder.mode(binding::binding_mode::SourceSync);
				});
				
                props.emplace_back(pname, builder.build());
            }
			
			std::vector<visix::uxml::UxmlnsDefinition> parseNamespaceDefinitions(){
				std::vector<visix::uxml::UxmlnsDefinition> uxmlns;
				pos++;
				while(peek() != ']'){
					skipSpace();
					auto alias = parseIdentifier(false);
					expect(':');
					expect('=');
					auto ns = parseUnquotedValue();
					skipSpace();
					if(peek() == ';')
						pos++;
					uxmlns.emplace_back(alias, ns);
				}
				pos++;
				return uxmlns;
			}

            UxmlElement parseElement(){
				std::string name = parseIdentifier();
				std::vector<visix::uxml::UxmlnsDefinition> uxmlns;
				skipSpace(); if(peek() == '['){
					uxmlns = parseNamespaceDefinitions();
				}
				skipSpace();
				expect('=');
				std::vector<visix::uxml::UxmlProperty> properties;
				std::vector<visix::uxml::UxmlElement> subElements;
				skipSpace(); if(peek() == '('){
					properties = parseProperties();
				}
				skipSpace();
				if(peek() == '{'){
					pos++; // consume '('
					// parse children until ')'
					while(true){
						skipSpace(); if(peek() == '}'){ pos++; break; }
						UxmlElement child = parseElement();
						// optional semicolon
						skipSpace(); if(peek() == ';') pos++;
						subElements.push_back(std::move(child));
					}
				}
				// optional semicolon
				skipSpace(); if(peek() == ';') pos++;
				return UxmlElement(std::move(name), std::move(properties), std::move(subElements), std::move(uxmlns));
			}
		};
	}
}

visix::uxml::UxmlElement::UxmlElement(const std::string& rawString){
	Parser p(rawString);
	auto root = p.parseElement();
	*this = std::move(root);
}

visix::uxml::UxmlElement::UxmlElement(
	std::string name, 
	std::vector<visix::uxml::UxmlProperty>&& properties, 
	std::vector<visix::uxml::UxmlElement>&& subElements, 
	std::vector<visix::uxml::UxmlnsDefinition>&& declaredNamespaces) noexcept{
	this->_name = name;
	this->_properties = std::move(properties);
	this->_subElements = std::move(subElements);
	this->_declared_namespaces = std::move(declaredNamespaces);
}

const std::string& visix::uxml::UxmlElement::name() STABLE {
	return this->_name;
}

const std::string& visix::uxml::UxmlElement::tag() STABLE {
	return this->_tag;
}

const std::vector<visix::uxml::UxmlElement>& visix::uxml::UxmlElement::subElements() STABLE {
	return this->_subElements;
}

const std::vector<visix::uxml::UxmlProperty>& visix::uxml::UxmlElement::properties() STABLE {
	return this->_properties;
}

std::vector<visix::uxml::UxmlnsDefinition> visix::uxml::UxmlElement::declaredNamespaces() STABLE {
	std::vector<visix::uxml::UxmlnsDefinition> combined;
	combined.insert(combined.end(), this->_declared_namespaces.begin(), this->_declared_namespaces.end());
	for(const auto &subElem : this->_subElements){
		auto subNs = subElem.declaredNamespaces();
		combined.insert(combined.end(), subNs.begin(), subNs.end());
	}
	auto iter = std::unique(combined.begin(), combined.end(), [](const visix::uxml::UxmlnsDefinition &a, const visix::uxml::UxmlnsDefinition &b){
		return a.alias() == b.alias();
	});
	combined.erase(iter, combined.end());
	return combined;
}

const visix::uxml::UxmlProperty* visix::uxml::UxmlElement::getProperty(const std::string &name) const {
	auto result = _Find_Element_By_Name(GET_CONSTED_REF_TYPE(visix::uxml::UxmlProperty)(&this->_properties), name);
	if(!result.has_value()) [[unlikely]]
		throw std::runtime_error(std::format("Cannot find named property '{}'",name));
	
	return &result.value().get();
}
const visix::uxml::UxmlElement* visix::uxml::UxmlElement::getSubElement(const std::string &name) const{
	auto result = _Find_Element_By_Name(GET_CONSTED_REF_TYPE(visix::uxml::UxmlElement)(&this->_subElements), name);
	if(!result.has_value()) [[unlikely]]
		throw std::runtime_error(std::format("Cannot find named element '{}'",name));
	
	return &result.value().get();
}

const visix::uxml::UxmlnsDefinition* visix::uxml::UxmlElement::getUxmlns(const std::string& alias) const{
	auto ns = this->declaredNamespaces();
	auto result = _Find_Element_By_Name(GET_CONSTED_REF_TYPE(visix::uxml::UxmlnsDefinition)(&ns),alias,[](visix::uxml::UxmlnsDefinition d){return d.alias();});
	if(!result.has_value()) [[unlikely]]
		throw std::runtime_error(std::format("Cannot find named uxml namespace '{}'", alias));
	
	return &result.value().get();
}