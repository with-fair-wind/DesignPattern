#include <LSP/lsp.h>

int main() {
    constexpr int kInitialSize = 5;

    // 从这个例子（我承认有点人为的）得到的启示是，process()完全不能接受派生类型 Square 而不是基类型 Rectangle，从而破坏了 LSP 原则。如果你给它一个 Rectangle，一切都很好，所以它可能需要一些时间才能出现在你的测试（或者生产，希望不是！）。

    Rectangle rect(Dimensions{.width = kInitialSize, .height = kInitialSize});
    process(rect);

    Square square(kInitialSize);
    process(square);
    return 0;
}