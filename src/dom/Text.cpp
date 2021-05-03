#include "../../include/dom/Text.h"

Text::Text(std::string data) : data{data}, Node{NodeType::Text} { }