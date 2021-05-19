#include "../../include/html/Parser.h"
#include <memory>

Parser::Parser(unsigned int pos, std::string input) : pos(pos), input(input) { }

char Parser::nextChar() {
    return this->input[this->pos];
}

bool Parser::startsWith(std::string s) {
    return (this->input.find(s,this->pos) == this->pos);
}

bool Parser::eof() {
    return this->pos >= this->input.size();
}

char Parser::consumeChar() {
    return this->input[this->pos++];
}

template<typename Function>
std::string Parser::consumeWhile(Function f) {
    std::string result ("");
    while(!this->eof() && f(this->nextChar())) {
        result += this->consumeChar();
    }
    return result;
}

void Parser::consumeWhitespace() {
    this->consumeWhile(isspace);
}

std::string Parser::parseTagName() {
    return this->consumeWhile([] (char c) -> bool {
        if((int(c)>=48 && int(c)<=57) || (int(c)>=65 && int(c)<=90) || (int(c)>=97 && int(c)<=122)) 
            return true;
        return false;
         });
}

std::unique_ptr<Node> Parser::parseNode() {
    if(this->nextChar()=='<')
        return this->parseElement();
    return this->parseText();
}

std::unique_ptr<Node> Parser::parseText(){
    std::unique_ptr<Node> node {
        new Text{this->consumeWhile([] (char c) -> bool {
        return c != '<';
     })}};
    return node;
}

std::unique_ptr<Node> Parser::parseElement(){
    assert(this->consumeChar() == '<');
    std::string tagName = this->parseTagName();
    auto attrs = this->parseAttributes();
    assert(this->consumeChar() == '>');

    auto children = this->parseNodes();

    assert(this->consumeChar() == '<');
    assert(this->consumeChar() == '/');
    assert(this->parseTagName() == tagName);
    assert(this->consumeChar() == '>');

    std::unique_ptr<Node> node {new Element{tagName, attrs, std::move(children)}};
    return node;
}

std::pair<std::string, std::string> Parser::parseAttr(){
    std::string name = this->parseTagName();
    assert(this->consumeChar() == '=');
    std::string value = this->parseAttrValue();
    std::pair<std::string, std::string> p(name, value);
    return p;
}

std::string Parser::parseAttrValue(){
    char openQuote = this->consumeChar();
    assert(openQuote == '"' || openQuote == '\'');
    std::string value = this->consumeWhile([openQuote] (char c) -> bool {
        return c != openQuote;
    });
    assert(this->consumeChar() == openQuote);
    return value;
}

attrMap_t Parser::parseAttributes(){
    attrMap_t attributes;
    while(1) {
        this->consumeWhitespace();
        if(this->nextChar() == '>')
            break;
        auto p = this->parseAttr();
        attributes.insert(p);
    }
    return attributes;
}

std::vector<std::unique_ptr<Node>> Parser::parseNodes(){
    std::vector<std::unique_ptr<Node>> nodes;
    while(1) {
        this->consumeWhitespace();
        if(this->eof() || this->startsWith("</"))
            break;
        nodes.emplace_back(std::move(this->parseNode()));
    }
    return nodes;
}
