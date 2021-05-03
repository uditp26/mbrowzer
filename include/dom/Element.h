#ifndef ELEMENT_H
#define ELEMENT_H

#include "Node.h"

#include <memory>
#include <string>
#include <unordered_map>

using attrMap_t = std::unordered_map<std::string, std::string>;

class Element: public Node{
    std::string tagName;
    attrMap_t attributes;
    public:
        Element(std::string name, attrMap_t attrs, std::vector<std::unique_ptr<Node>> children);
        friend void printNode(std::unique_ptr<Node> root);
};

#endif