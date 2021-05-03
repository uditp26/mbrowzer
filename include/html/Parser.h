#ifndef PARSER_H
#define PARSER_H

#include "../dom/Node.h"
#include "../dom/Element.h"
#include "../dom/Text.h"

#include <memory>
#include <string>
#include <cassert>

class Parser {
    unsigned int pos;
    std::string input;
    
    public:
        Parser(unsigned int pos, std::string input);
        char nextChar();
        bool startsWith(std::string s);
        bool eof();
        char consumeChar();
        template<typename Function> std::string consumeWhile(Function f);
        void consumeWhitespace();
        std::string parseTagName();
        std::unique_ptr<Node> parseNode();
        std::unique_ptr<Node> parseText();
        std::unique_ptr<Node> parseElement();
        std::pair<std::string, std::string> parseAttr();
        std::string parseAttrValue();
        attrMap_t parseAttributes();
        std::vector<std::unique_ptr<Node>> parseNodes();
 };

#endif