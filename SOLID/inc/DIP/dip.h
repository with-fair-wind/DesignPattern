#pragma once

#if __has_include(<boost/di.hpp>)
#include <boost/di.hpp>
namespace di = boost::di;
#else
// 兼容：如果当前环境/IDE 没配置到 boost-ext/di 的 include 路径，则退化为极简 DI。
// 这样不影响实际构建（CMake 会拉取 boost-ext/di），也能避免 clang-tidy 直接报 “file not found”。
namespace di {
template <class Interface, class Implementation>
struct binding {
    using interface_type = Interface;
    using implementation_type = Implementation;
};

template <class Interface>
struct bind_builder {
    template <class Implementation>
    [[nodiscard]] constexpr auto to() const noexcept -> binding<Interface, Implementation> {
        return {};
    }
};

template <class Interface>
[[nodiscard]] constexpr auto bind() noexcept -> bind_builder<Interface> {
    return {};
}

template <class... Bindings>
struct injector {
    template <class Interface>
    [[nodiscard]] auto create() const -> std::shared_ptr<Interface> {
        return create_impl<Interface, Bindings...>();
    }

   private:
    template <class Interface>
    [[nodiscard]] static auto create_impl() -> std::shared_ptr<Interface> {
        static_assert(!std::is_same<Interface, Interface>::value, "No binding found for requested interface type");
        return {};
    }

    template <class Interface, class First, class... Rest>
    [[nodiscard]] static auto create_impl() -> std::shared_ptr<Interface> {
        if constexpr (std::is_same_v<typename First::interface_type, Interface>) {
            return std::make_shared<typename First::implementation_type>();
        } else {
            return create_impl<Interface, Rest...>();
        }
    }
};

template <class... Bindings>
[[nodiscard]] constexpr auto make_injector(Bindings... /*unused*/) noexcept -> injector<Bindings...> {
    return {};
}
}  // namespace di
#endif

struct ILogger {
    ILogger() = default;
    ILogger(const ILogger&) = default;
    ILogger& operator=(const ILogger&) = default;
    ILogger(ILogger&&) = default;
    ILogger& operator=(ILogger&&) = default;
    virtual ~ILogger() = default;

    virtual void log(const std::string& message) noexcept = 0;
};

struct ConsoleLogger : ILogger {
    void log(const std::string& message) noexcept override { std::cout << message << '\n'; }
};

struct Engine {
    static constexpr float kDefaultVolume = 5.0F;
    static constexpr int kDefaultHorsePower = 400;

    float volume = kDefaultVolume;
    int horse_power = kDefaultHorsePower;

    friend std::ostream& operator<<(std::ostream& output_stream, const Engine& engine) noexcept {
        output_stream << "Volume: " << engine.volume << ", Horse power: " << engine.horse_power;
        return output_stream;
    }
};
class Reporting {
   public:
    explicit Reporting(ILogger& logger) : logger_(logger) {}
    void generate_report() noexcept { logger_.get().log("Report generated"); }

   private:
    std::reference_wrapper<ILogger> logger_;
};

class Car {
   public:
    Car(std::unique_ptr<Engine> engine, std::shared_ptr<ILogger> logger) : engine_(std::move(engine)), logger_(std::move(logger)) { logger_->log("Car created"); }
    // void start() noexcept { engine_->start(); }
    // void stop() noexcept { engine_->stop(); }
    // void drive() noexcept { engine_->drive(); }
    // void refuel() noexcept { engine_->refuel(); }
    // void repair() noexcept { engine_->repair(); }
    // void sell() noexcept { engine_->sell(); }
    // void buy() noexcept { engine_->buy(); }
    // void insure() noexcept { engine_->insure(); }

    friend std::ostream& operator<<(std::ostream& output_stream, const Car& car) noexcept {
        output_stream << "Car: " << *car.engine_ << '\n';
        return output_stream;
    }

   private:
    std::unique_ptr<Engine> engine_;
    std::shared_ptr<ILogger> logger_;
};

inline const auto injector = di::make_injector(di::bind<ILogger>().to<ConsoleLogger>());