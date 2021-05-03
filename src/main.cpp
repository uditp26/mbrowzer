#include "../include/html/Parser.h"

#include <memory>
#include <string>
#include <iostream>
#include <type_traits>
#include <vector>

std::unique_ptr<Node> parse(std::string source){
    Parser parser(0, source);
    std::vector<std::unique_ptr<Node>> nodes{parser.parseNodes()};
    if(nodes.size()==1){
        return std::move(nodes.front());
    }
    else{
        attrMap_t attr;
        std::unique_ptr<Node> node{new Element {"html", attr, std::move(nodes)}};
        return std::move(node);
    }
}

void printNode(std::unique_ptr<Node> root){
    if(root==nullptr)
        return;
    Node* node{&*root};
    if (root->nodeType==NodeType::Element) {
        Element* elem{dynamic_cast<Element*>(node)};
        std::cout<<"Element Node: "<<elem->tagName<<"\n";
    }
    else if(root->nodeType==NodeType::Text) {
        Text* txt{dynamic_cast<Text*>(node)};
        std::cout<<"Text Node: "<<txt->data<<"\n";
    }
    int i=0;
    while(!root->children.empty()){
        auto child = std::move(root->children[i]);
        printNode(std::move(child));
        i++;
    }
}

int main(){
    std::cout<<"Entry"<<"\n";

    std::string html = "<html><head><h1>Test Html</h1></head><body><p>Hello html!</p></body></html>";
    // std::string html = "<p>Hello html!</p><p>Hello html!</p><p>Hello html!</p>";
    // std::string html = "Hello html";
    // std::string html = "<head></head><body></body>";
    std::unique_ptr<Node> root = parse(html);
    printNode(std::move(root));

    std::cout<<"Exit";
}