#ifndef TEXT_H
#define TEXT_H

#include "Node.h"

#include <memory>
#include <vector>

class Text: public Node{
    std::string data;
    public:
        Text(std::string data);
        friend void printNode(std::unique_ptr<Node> root);
};

#endif