#pragma once
#include <assert.h>
#include <string>
#include <vector>

using namespace std;

class Attribute {
public:
    Attribute(string name, string value)
        : m_name(name)
        , m_value(value)
    {
    }

    string get_name()
    {
        return m_name;
    }

    string get_value()
    {
        return m_value;
    }

private:
    string m_name;
    string m_value;
};

class Tag {
public:
    Tag(string name)
        : m_name(name)
    {
    }

    string get_name()
    {
        return m_name;
    }

    vector<Tag*>& get_children()
    {
        return m_children;
    }

    void add_children(Tag* children)
    {
        assert(children != nullptr);
        m_children.push_back(children);
    }

    void add_children(vector<Tag*> children)
    {
        for (auto* c : children)
            m_children.push_back(c);
    }

    void add_attribute(Attribute* attr)
    {
        assert(attr != nullptr);
        m_attributes.push_back(attr);
    }

    vector<Attribute*>& get_attributes()
    {
        return m_attributes;
    }

    string get_content()
    {
        return m_content;
    }

    void set_content(string content)
    {
        m_content = content;
        m_has_content = content.length() > 0;
    }

    bool has_content() const { return m_has_content; }

private:
    string m_name;
    string m_content;
    vector<Tag*> m_children;
    vector<Attribute*> m_attributes;
    bool m_has_content { false };
};
