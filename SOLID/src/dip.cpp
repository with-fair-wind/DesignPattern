#include <DIP/dip.h>

int main() {
    auto logger = injector.create<std::shared_ptr<ILogger>>();
    Reporting reporting(*logger);
    reporting.generate_report();

    auto car = injector.create<std::unique_ptr<Car>>();
    std::cout << *car << '\n';
    return 0;
}