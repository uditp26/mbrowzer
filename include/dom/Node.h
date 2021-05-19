#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>

enum class NodeType {
    Text,
    Element
 };

class Node {
    std::vector<std::unique_ptr<Node>> children;
    NodeType nodeType;
    public:
        Node();
        Node(NodeType nodeType);
        Node(std::vector<std::unique_ptr<Node>> children, NodeType nodeType);
        virtual ~Node() = default;

        // Friends
        friend class ParserTests;
 };

#endif