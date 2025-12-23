#include <ISP/isp.h>

int main() {
    Printer printer;
    Scanner scanner;
    Machine machine(printer, scanner);
    machine.print("Hello, world!");
    machine.scan("Hello, world!");
    return 0;
}