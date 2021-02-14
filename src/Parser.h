#pragma once
#include "Tag.h"
#include <string>
#include <vector>

using namespace std;

class Parser {
public:
    Parser(string input);
    void run();

    vector<Tag*>& get_tags()
    {
        return m_tags;
    }

    char peek(size_t offset = 0);
    char consume();
    void consume(size_t size);
    void consume_whitespace();

    vector<Tag*> parse_tag();
    Attribute* parse_attribute();
    string parse_name();
    string parse_value();
    string parse_content();

    bool tag_is_opening();
    bool tag_is_closing();

private:
    size_t m_index { 0 };
    string m_input;
    vector<Tag*> m_tags;
};
