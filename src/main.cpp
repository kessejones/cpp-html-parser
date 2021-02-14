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

static void dump_tag(vector<Tag*> tags, int indent = 0)
{
    for (auto* tag : tags) {
        print_indent(indent);
        cout << "=> " << tag->get_name() << endl;
        for (auto* attr : tag->get_attributes()) {
            print_indent(indent);
            cout << "  # " << attr->get_name() << " = " << attr->get_value() << endl;
        }

        dump_tag(tag->get_children(), indent + 1);
    }
}

int main(int, char**)
{
    string input = R"(
        <html>
        <body>
            <div>
            </div>
            <main style="color: red" width="300px">
                <img src="x.png" />
                <img src="x.png" />
                <img src="x.png" />
                <img src="x.png" />
                <input type="text" name="username"/>
            </main>
            <footer>
            </footer>
        </body>
        </html>
    )";

    Parser parser(input);
    parser.run();

    auto tags = parser.get_tags();
    dump_tag(tags);

    return 0;
}
