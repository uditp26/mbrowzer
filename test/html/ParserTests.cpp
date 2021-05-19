#include "../../include/html/Parser.h"

#include <gtest/gtest.h>

class ParserTests : public::testing::Test {
    protected:
        void SetUp() override {
            
        }

        void TearDown() override {

        }

    public:
        bool isValidNode(std::unique_ptr<Node> root, NodeType type);
        std::string getData(Text* text);
};

TEST_F(ParserTests, parseText) {
    // Exercise
    std::string html = "This is a sample string. Text Node only!";
    Parser parser{0, html};
    auto node{parser.parseText()};
    Text* text{dynamic_cast<Text*>(&*node)};
    std::string data = getData(text);
    bool isValid = isValidNode(std::move(node), NodeType::Text);

    // Verify
    ASSERT_TRUE(isValid)<<"Node should be a valid text node";
    ASSERT_EQ(data, html)<<"Data value should be equal to \'" + html + "\'";
}

TEST_F(ParserTests, parseElementWithoutAttr) {

}

TEST_F(ParserTests, parseElementWithAttr) {

}

TEST_F(ParserTests, parseHtml) {

}


// **************************************************** Helper functions ****************************************************

/**
 * @brief Check whether the node type matches the expected type
 * 
 * @param root 
 * @param type 
 * @return bool  
 */
bool ParserTests::isValidNode(std::unique_ptr<Node> root, NodeType type) {
    return root->nodeType==type;
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
