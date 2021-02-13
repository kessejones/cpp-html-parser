#pragma once
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

    Tag* get_children()
    {
        return m_children;
    }

    void set_children(Tag* tag)
    {
        m_children = tag;
    }

    void add_attribute(Attribute* attr)
    {
        m_attributes.push_back(attr);
    }

    vector<Attribute*>& get_attributes()
    {
        return m_attributes;
    }

private:
    string m_name;
    Tag* m_children;
    vector<Attribute*> m_attributes;
};
