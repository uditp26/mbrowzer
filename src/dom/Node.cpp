#include "../../include/dom/Node.h"

#include <memory>
#include <type_traits>

Node::Node() { }

Node::Node(NodeType nodeType) : nodeType{nodeType} { }

Node::Node(std::vector<std::unique_ptr<Node>> children, NodeType nodeType) : children{std::move(children)}, nodeType{nodeType} { }
