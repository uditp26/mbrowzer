#include "../../include/dom/Element.h"

#include <memory>
#include <type_traits>

Element::Element(std::string name, attrMap_t attrs, std::vector<std::unique_ptr<Node>> children) : tagName{name}, attributes{attrs}, Node{std::move(children), NodeType::Element} { }