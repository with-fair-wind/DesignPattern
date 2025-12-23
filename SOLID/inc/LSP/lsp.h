#pragma once

struct Dimensions {
    int width;
    int height;
};

class Rectangle {
   private:
    int width, height;

   public:
    Rectangle() : width(0), height(0) {}
    Rectangle(const Rectangle&) = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(Rectangle&&) = default;

    explicit Rectangle(Dimensions dims) : width(dims.width), height(dims.height) {}
    virtual ~Rectangle() = default;
    [[nodiscard]] virtual int get_area() const { return width * height; }
    virtual void set_width(int width) { this->width = width; }
    virtual void set_height(int height) { this->height = height; }
    [[nodiscard]] virtual int get_width() const { return width; }
    [[nodiscard]] virtual int get_height() const { return height; }
};

class Square : public Rectangle {
   public:
    explicit Square(int size) : Rectangle(Dimensions{.width = size, .height = size}) {}
    void set_width(int width) override {
        Rectangle::set_width(width);
        Rectangle::set_height(width);
    }
    void set_height(int height) override {
        Rectangle::set_height(height);
        Rectangle::set_width(height);
    }
};

struct RectangleFactory {
    [[nodiscard]] static std::unique_ptr<Rectangle> new_rectangle(int width, int height) { return std::make_unique<Rectangle>(Dimensions{.width = width, .height = height}); }
    [[nodiscard]] static std::unique_ptr<Rectangle> new_square(int size) { return std::make_unique<Square>(size); }
};

inline void process(Rectangle& rect) {
    constexpr int kTargetHeight = 10;
    const int width = rect.get_width();
    rect.set_height(kTargetHeight);
    std::cout << "Expected area of " << width << " by " << kTargetHeight << " to be " << width * kTargetHeight << ", but got " << rect.get_area() << '\n';
}