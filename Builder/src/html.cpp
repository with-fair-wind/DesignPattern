#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class HtmlBuilder;
class HtmlElement {
   private:
    friend class HtmlBuilder;
    std::string name;
    std::string text;
    std::vector<HtmlElement> elements;

    static constexpr size_t indent_size = 2;
    HtmlElement() = default;
    explicit HtmlElement(std::string name, std::string text) : name(std::move(name)), text(std::move(text)) {}

   public:
    [[nodiscard]] std::string str(int indent = 0) const {
        std::ostringstream oss;

        struct Frame {
            const HtmlElement* elem;
            int indent;
            size_t child_index;
            bool opened;
        };

        std::vector<Frame> stack;
        stack.push_back({this, indent, 0, false});

        while (!stack.empty()) {
            Frame& frame = stack.back();
            const HtmlElement* current = frame.elem;

            if (!frame.opened) {
                oss << std::string(frame.indent * indent_size, ' ') << "<" << current->name << ">" << '\n';
                if (!current->text.empty()) oss << std::string((frame.indent * indent_size) + 2, ' ') << current->text << '\n';
                frame.opened = true;
            }

            if (frame.child_index < current->elements.size()) {
                const HtmlElement* child = &current->elements[frame.child_index++];
                stack.push_back({child, frame.indent + 1, 0, false});
            } else {
                oss << std::string(frame.indent * indent_size, ' ') << "</" << current->name << ">" << '\n';
                stack.pop_back();
            }
        }

        return oss.str();
    }

    static std::unique_ptr<HtmlBuilder> build(std::string name);
    static HtmlBuilder build_ref(std::string name);
};

class HtmlBuilder {
   private:
    HtmlElement root;

   public:
    explicit HtmlBuilder(std::string name) { root.name = std::move(name); }

    HtmlBuilder& add_child(std::string name, std::string text) {
        root.elements.emplace_back(HtmlElement(std::move(name), std::move(text)));
        return *this;
    }

    [[nodiscard]] std::string str() const { return root.str(); }
    [[nodiscard]] explicit operator HtmlElement() const { return root; }
    [[nodiscard]] HtmlElement build() const { return root; }
};

std::unique_ptr<HtmlBuilder> HtmlElement::build(std::string name) { return std::make_unique<HtmlBuilder>(std::move(name)); }
HtmlBuilder HtmlElement::build_ref(std::string name) { return HtmlBuilder(std::move(name)); }

int main() {
    HtmlBuilder builder("ul");
    builder.add_child("li", "hello").add_child("li", "world");
    std::cout << builder.str() << '\n';

    auto element = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world");
    auto element2 = HtmlElement::build_ref("ul").add_child("li", "hello").add_child("li", "world");
    return 0;
}