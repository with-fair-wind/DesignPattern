#pragma once

struct IPrinter {
    IPrinter() = default;
    IPrinter(const IPrinter&) = default;
    IPrinter& operator=(const IPrinter&) = default;
    IPrinter(IPrinter&&) = default;
    IPrinter& operator=(IPrinter&&) = default;
    virtual ~IPrinter() = default;

    virtual void print(const std::string& document) = 0;
};

struct IScanner {
    IScanner() = default;
    IScanner(const IScanner&) = default;
    IScanner& operator=(const IScanner&) = default;
    IScanner(IScanner&&) = default;
    IScanner& operator=(IScanner&&) = default;
    virtual ~IScanner() = default;

    virtual void scan(const std::string& document) = 0;
};

struct IFax {
    IFax() = default;
    IFax(const IFax&) = default;
    IFax& operator=(const IFax&) = default;
    IFax(IFax&&) = default;
    IFax& operator=(IFax&&) = default;
    virtual ~IFax() = default;

    virtual void fax(const std::string& document) = 0;
};

struct IMachine : IPrinter, IScanner {};

struct Printer : IPrinter {
    void print(const std::string& document) override { std::cout << "Printing " << document << '\n'; }
};

struct Scanner : IScanner {
    void scan(const std::string& document) override { std::cout << "Scanning " << document << '\n'; }
};

class Machine : public IMachine {
   public:
    Machine(std::reference_wrapper<IPrinter> printer, std::reference_wrapper<IScanner> scanner) : printer_(printer), scanner_(scanner) {}

    void print(const std::string& document) override { printer_.get().print(document); }
    void scan(const std::string& document) override { scanner_.get().scan(document); }

   private:
    std::reference_wrapper<IPrinter> printer_;
    std::reference_wrapper<IScanner> scanner_;
};