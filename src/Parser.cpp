#include "Parser.h"
#include <ctype.h>
#include <iostream>

Parser::Parser(string input)
    : m_input(input)
{
}

char Parser::peek(size_t offset)
{
    if (m_index + offset >= m_input.length())
        return '\0';
    return m_input.at(m_index + offset);
}

char Parser::consume()
{
    if (m_index >= m_input.length())
        return '\0';
    return m_input.at(m_index++);
}

void Parser::consume(size_t size)
{
    for (size_t i = 0; i < size; ++i)
        consume();
}

void Parser::consume_whitespace()
{
    while (isspace(peek())) {
        consume();
    }
}

string Parser::parse_name()
{
    string name = "";
    while (peek() != ' ' && peek() != '=' && peek() != '>' && peek() != '/') {
        name += consume();
    }
    return name;
}

string Parser::parse_value()
{
    string value = "";
    if (peek() == '"')
        consume();

    while (peek() != '"' && peek() != '>') {
        value += consume();
    }
    consume();
    return value;
}

Attribute* Parser::parse_attribute()
{
    string attr_name = "";
    string attr_value = "";
    consume_whitespace();
    if (peek() == '/' || peek() == '>')
        return nullptr;

    attr_name = parse_name();
    consume_whitespace();

    if (peek() == '=')
        consume();

    consume_whitespace();
    attr_value = parse_value();

    return new Attribute(attr_name, attr_value);
}

vector<Tag*> Parser::parse_tag()
{
    vector<Tag*> tags;
    Tag* tag = nullptr;
    string tag_name = "";

    auto tag_is_closing = [&]() -> bool {
        return (peek() == '<' && peek(1) == '/');
    };

    consume_whitespace();
    while (peek() == '<') {
        if (tag_is_closing())
            return tags;
        consume();
        consume_whitespace();

        tag_name = parse_name();
        tag = new Tag(tag_name);

        consume_whitespace();
        while (peek() != '>' && peek() != '/') {
            auto* attribute = parse_attribute();
            if (attribute)
                tag->add_attribute(attribute);
        }
        consume_whitespace();
        if (peek() == '/' && peek(1) == '>') {
            consume(2);
            consume_whitespace();
            tags.push_back(tag);
            continue;
        }

        auto consume_close_tag = [&]() {
            consume_whitespace();
            consume(2);
            consume(tag_name.length());
            consume();
            consume_whitespace();

            tags.push_back(tag);
        };

        consume_whitespace();
        if (peek() == '>') {
            consume();
        }

        consume_whitespace();
        if (tag_is_closing()) {
            consume_close_tag();
        } else {
            auto children = parse_tag();
            if (!children.empty())
                tag->add_children(children);

            consume_close_tag();
        }
    }

    return tags;
}

void Parser::run()
{
    while (peek() != '\0') {
        vector<Tag*> tags = parse_tag();
        if (tags.empty())
            break;
        for (auto* tag : tags)
            m_tags.push_back(tag);
    }
}
