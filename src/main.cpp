#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static void print_indent(int value)
{
    for (int i = 0; i < value * 4; ++i) {
        printf(" ");
    }
}

static void dump_tag(Tag* tag, int indent = 0)
{
    if (!tag)
        return;

    print_indent(indent);
    cout << "=> " << tag->get_name() << endl;
    for (auto* attr : tag->get_attributes()) {
        print_indent(indent);
        cout << "## " << attr->get_name() << "=" << attr->get_value() << endl;
    }

    dump_tag(tag->get_children(), indent + 1);
}

int main(int, char**)
{
    string input = "<tag1 name=\"HelloWorld\"><tag2 value=\"KKK\"><tag3 name=\"Kesse\"></tag3></tag2></tag1>";
    Parser parser(input);
    parser.run();

    auto tags = parser.get_tags();

    for (auto* tag : tags) {
        dump_tag(tag);
    }

    return 0;
}
