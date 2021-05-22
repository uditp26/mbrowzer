#include "../../include/html/Parser.h"

#include <gtest/gtest.h>

class ParserTests : public testing::TestWithParam<const char*> {
    protected:
        void SetUp() override {
            
        }

        void TearDown() override {

        }

    public:
        bool isValidNode(Node* node, NodeType type);
        std::string getData(Text* text);
        std::vector<std::unique_ptr<Node>> getChildren(Element* element);
        std::string getTagName(Element* element);
        attrMap_t getAttributes(Element* element);
        NodeType getNodeType(Node* node);
};

INSTANTIATE_TEST_SUITE_P(TextParam, 
                        ParserTests, 
                        testing::Values(
                            "This is a sample string. Text Node only!",
                            ""
                            ));

TEST_P(ParserTests, parseText) {
    // Exercise
    std::string html = GetParam();
    Parser parser{0, html};
    auto node{parser.parseText()};
    Text* text{dynamic_cast<Text*>(&*node)};

    // Verify
    bool isValid = isValidNode(text, NodeType::Text);
    ASSERT_TRUE(isValid)<<"Node should be a valid text node";
    std::string data = getData(text);
    EXPECT_EQ(data, html)<<"Data value should be equal to \'" + html + "\'";
}

TEST_F(ParserTests, parseElementWithoutAttr) {
    // Exercise
    std::string html = "<html><head></head><body><p><b></b></p><p></p></body></html>";
    std::vector<std::string> expTagNames{"html", "head", "body", "p", "b", "p"};
    Parser parser{0, html};
    auto node{parser.parseElement()};
    Element* element{dynamic_cast<Element*>(&*node)};
    auto elements = getChildren(element);
    elements.insert(elements.begin(), std::move(node));

    // Verify
    for(int i=0;i<elements.size();i++){
        Element* elem{dynamic_cast<Element*>(&*elements[i])};

        bool isValid = isValidNode(elem, NodeType::Element);
        ASSERT_TRUE(isValid)<<"Node should be a valid element node";

        auto tag = getTagName(elem);
        EXPECT_EQ(tag, expTagNames[i])<<"Tag name should be equal to " + expTagNames[i];

        auto attr = getAttributes(elem);
        EXPECT_EQ(attr.size(), 0)<<"Attributes map should be empty for " + tag;
    }
}

TEST_F(ParserTests, parseElementWithAttr) {
    // Exercise
    std::string html = "<html lang='en'><body style='color:grey'><p id=\"p1\"></p></body></html>";
    std::vector<std::string> expTagNames{"html", "body", "p"};
    attrMap_t expAttrs{{"lang","en"},{"style", "color:grey"},{"id","p1"}};
    Parser parser{0, html};
    auto node{parser.parseElement()};
    Element* element{dynamic_cast<Element*>(&*node)};
    auto elements = getChildren(element);
    elements.insert(elements.begin(), std::move(node));

    // Verify
    for(int i=0;i<elements.size();i++){
        Element* elem{dynamic_cast<Element*>(&*elements[i])};

        bool isValid = isValidNode(elem, NodeType::Element);
        ASSERT_TRUE(isValid)<<"Node should be a valid element node";

        auto tag = getTagName(elem);
        EXPECT_EQ(tag, expTagNames[i])<<"Tag name should be equal to " + expTagNames[i];

        auto attr = getAttributes(elem);
        for(const auto p:attr){
            EXPECT_EQ(p.second, expAttrs[p.first])<<"Attribute value map should be equal to " + expAttrs[p.first];
        }
    }
}

TEST_F(ParserTests, parseHtml) {
    // Exercise
    std::string html = "<html lang='en'><body style='color:grey'><p id=\"p1\">This text belongs to Text Node</p></body></html>";
    std::vector<std::string> expTagNames{"html", "body", "p"};
    attrMap_t expAttrs{{"lang","en"},{"style", "color:grey"},{"id","p1"}};
    std::string expData = "This text belongs to Text Node";
    Parser parser{0, html};
    auto nodes{parser.parseNodes()};

    // Verify
    for(int i=0;i<nodes.size();i++){
        Node* node{&*nodes[i]};
        if(getNodeType(node)==NodeType::Element){
            Element* elem{dynamic_cast<Element*>(node)};
            auto tag = getTagName(elem);
            EXPECT_EQ(tag, expTagNames[i])<<"Tag name should be equal to " + expTagNames[i];

            auto attr = getAttributes(elem);
            for(const auto p:attr){
                EXPECT_EQ(p.second, expAttrs[p.first])<<"Attribute value map should be equal to " + expAttrs[p.first];
            }
        }
        else if(getNodeType(node)==NodeType::Text){
            Text* text{dynamic_cast<Text*>(&*node)};
            std::string data = getData(text);
            EXPECT_EQ(data, expData)<<"Data value should be equal to \'" + expData + "\'";
        }
    }
}


// **************************************************** Helper functions ****************************************************

/**
 * @brief Check whether the node type matches the expected type
 * 
 * @param root 
 * @param type 
 * @return bool  
 */
bool ParserTests::isValidNode(Node* node, NodeType type) {
    return node->nodeType==type;
}

/**
 * @brief Get data stored in Text node
 * 
 * @param text 
 * @return std::string 
 */
std::string ParserTests::getData(Text* text) {
    return text->data;
}

/**
 * @brief 
 * 
 * @param element 
 * @return std::vector<std::unique_ptr<Node>> 
 */
std::vector<std::unique_ptr<Node>> ParserTests::getChildren(Element* element) {
    return std::move(element->children);
}

/**
 * @brief 
 * 
 * @param element 
 * @return attrMap_t 
 */
attrMap_t ParserTests::getAttributes(Element* element){
    return element->attributes;
}

/**
 * @brief 
 * 
 * @param element 
 * @return std::string 
 */
std::string ParserTests::getTagName(Element* element){
    return element->tagName;
}

/**
 * @brief Get the Node Type object
 * 
 * @param node 
 * @return NodeType 
 */
NodeType ParserTests::getNodeType(Node* node){
    return node->nodeType;
}
