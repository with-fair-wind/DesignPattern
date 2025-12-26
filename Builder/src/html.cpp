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

    const size_t indent_size = 2;
    HtmlElement() = default;
    explicit HtmlElement(std::string name, std::string text) : name(std::move(name)), text(std::move(text)) {}

   public:
    std::string str(int indent = 0) const {
        std::ostringstream oss;
        oss << std::string(indent * indent_size, ' ') << "<" << name << ">" << std::endl;
        if (text.size() > 0) oss << std::string(indent * indent_size + 2, ' ') << text << std::endl;
        for (const auto& e : elements) oss << e.str(indent + 1);
        oss << std::string(indent * indent_size, ' ') << "</" << name << ">" << std::endl;
        return oss.str();
    }

    static std::unique_ptr<HtmlBuilder> build(std::string name);
    static HtmlBuilder build_ref(std::string name);
};

class HtmlBuilder {
   private:
    HtmlElement root;

   public:
    HtmlBuilder(std::string name) { root.name = name; }

    HtmlBuilder& add_child(std::string name, std::string text) {
        root.elements.emplace_back(HtmlElement(std::move(name), std::move(text)));
        return *this;
    }

    std::string str() const { return root.str(); }
    explicit operator HtmlElement() const { return root; }
    HtmlElement build() const { return root; }
};

std::unique_ptr<HtmlBuilder> HtmlElement::build(std::string name) { return std::make_unique<HtmlBuilder>(std::move(name)); }
HtmlBuilder HtmlElement::build_ref(std::string name) { return HtmlBuilder(std::move(name)); }

int main() {
    HtmlBuilder builder("ul");
    builder.add_child("li", "hello").add_child("li", "world");
    std::cout << builder.str() << std::endl;

    auto element = HtmlElement::build("ul")->add_child("li", "hello").add_child("li", "world");
    auto element2 = HtmlElement::build_ref("ul").add_child("li", "hello").add_child("li", "world");
    return 0;
}