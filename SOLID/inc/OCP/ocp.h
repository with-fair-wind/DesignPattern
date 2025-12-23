#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

enum class Color : std::uint8_t { Red, Green, Blue };
enum class Size : std::uint8_t { Small, Medium, Large };

struct Product {
    std::string name;
    Color color;
    Size size;
};

template <typename T>
struct Specification {
    Specification() = default;
    Specification(const Specification&) = default;
    Specification& operator=(const Specification&) = default;
    Specification(Specification&&) = default;
    Specification& operator=(Specification&&) = default;
    virtual ~Specification() = default;
    virtual bool is_satisfied(T* item) const = 0;
};

template <typename T>
struct Filter {
    Filter() = default;
    Filter(const Filter&) = default;
    Filter& operator=(const Filter&) = default;
    Filter(Filter&&) = default;
    Filter& operator=(Filter&&) = default;
    virtual ~Filter() = default;
    [[nodiscard]] virtual std::vector<T*> filter(const std::vector<T*>& items, const Specification<T>& spec) const = 0;
};

template <typename T>
struct AndSpecification : Specification<T> {
    AndSpecification(const Specification<T>& first, const Specification<T>& second) : first_(std::cref(first)), second_(std::cref(second)) {}

    bool is_satisfied(T* item) const override { return first_.get().is_satisfied(item) && second_.get().is_satisfied(item); }

   private:
    std::reference_wrapper<const Specification<T>> first_;
    std::reference_wrapper<const Specification<T>> second_;
};

struct ColorSpecification : Specification<Product> {
    explicit ColorSpecification(Color color) : color_(color) {}

    bool is_satisfied(Product* item) const override { return item->color == color_; }

   private:
    Color color_;
};

struct SizeSpecification : Specification<Product> {
    explicit SizeSpecification(Size size) : size_(size) {}

    bool is_satisfied(Product* item) const override { return item->size == size_; }

   private:
    Size size_;
};

struct BetterFilter : Filter<Product> {
    [[nodiscard]] std::vector<Product*> filter(const std::vector<Product*>& items, const Specification<Product>& spec) const override {
        std::vector<Product*> result;
        for (const auto& item : items) {
            if (spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};