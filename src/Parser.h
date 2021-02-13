#pragma once
#include "Tag.h"
#include <string>
#include <vector>

using namespace std;

class Parser {
public:
    Parser(string input);
    void run();

    vector<Tag*> get_tags()
    {
        return m_tags;
    }

    char peek(size_t offset = 0);
    char consume(size_t size = 1);
    void consume_whitespace();

    Tag* parse_tag();
    Attribute* parse_attribute();
    string parse_name();
    string parse_value();

private:
    size_t m_index { 0 };
    string m_input;
    vector<Tag*> m_tags;
};
