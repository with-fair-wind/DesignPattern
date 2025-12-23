#include <OCP/ocp.h>

int main() {
    Product apple{.name = "Apple", .color = Color::Green, .size = Size::Small};
    Product tree{.name = "Tree", .color = Color::Green, .size = Size::Large};
    Product house{.name = "House", .color = Color::Blue, .size = Size::Large};

    std::vector<Product*> all{&apple, &tree, &house};
    BetterFilter better_filter;
    ColorSpecification green(Color::Green);
    auto green_things = better_filter.filter(all, green);
    for (const auto& item : green_things) {
        std::cout << "Green item: " << item->name << '\n';
    }
    SizeSpecification large(Size::Large);
    AndSpecification<Product> green_and_large(green, large);
    auto green_large_things = better_filter.filter(all, green_and_large);
    for (const auto& item : green_large_things) {
        std::cout << "Large green item: " << item->name << '\n';
    }
    return 0;
}