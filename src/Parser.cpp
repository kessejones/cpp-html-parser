#include "Parser.h"
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

char Parser::consume(size_t size)
{
    if (m_index + size >= m_input.length())
        return '\0';
    size_t old_index = m_index;
    m_index += size;
    return m_input.at(old_index);
}

void Parser::consume_whitespace()
{
    while (peek() == ' ')
        consume();
}

string Parser::parse_name()
{
    string name = "";

    while (peek() != ' ' && peek() != '=') {
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
    attr_name = parse_name();
    consume_whitespace();

    if (peek() == '=')
        consume();

    consume_whitespace();
    attr_value = parse_value();

    return new Attribute(attr_name, attr_value);
}

Tag* Parser::parse_tag()
{
    Tag* tag = nullptr;
    string tag_name = "";
    consume_whitespace();
    if (peek() != '<')
        return nullptr;
    consume();

    tag_name = parse_name();
    tag = new Tag(tag_name);

    while (peek() != '>' && peek() != '/') {
        auto* attribute = parse_attribute();
        tag->add_attribute(attribute);
    }
    consume_whitespace();
    if (peek() == '/' && peek(1) == '>') {
        consume(2);
        return tag;
    }

    auto consume_close_tag = [&]() {
        consume_whitespace();
        consume(tag_name.length());
        consume();
    };

    consume_whitespace();
    if (peek() == '>') {
        consume();
    }
    if (peek() == '<' && peek(1) == '/') {
        consume_close_tag();
    } else {
        auto* children = parse_tag();
        if (children)
            tag->set_children(children);
        consume_close_tag();
    }

    return tag;
}

void Parser::run()
{
    while (true) {
        if (peek() == '\0')
            break;
        Tag* tag = parse_tag();
        if (!tag)
            break;
        m_tags.push_back(tag);
    }
}
