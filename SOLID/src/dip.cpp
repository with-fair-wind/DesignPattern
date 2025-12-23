#include <DIP/dip.h>

int main() {
    auto logger = std::make_shared<ConsoleLogger>();
    Reporting reporting(*logger);
    reporting.generate_report();

    auto car = injector.create<Car>();

    // Car car(std::make_unique<Engine>(), logger);
    std::cout << car << '\n';
    return 0;
}