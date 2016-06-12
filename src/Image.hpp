#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "Geometry.hpp"

struct Pixel
{
    Pixel();
    Pixel(const unsigned int _r, const unsigned int _g, const unsigned int _b);
    Pixel(const Pixel& _pix);

    Pixel& operator=(const Pixel &_pix);

    unsigned int r, g, b;
};

class Image
{
public:
    Image(const std::size_t _w, const std::size_t _h, const unsigned int _maxColor = 255);

    void set(const std::size_t _x, const std::size_t _y, const Pixel &color);
    Pixel& get(const std::size_t _x, const std::size_t _y);

    const std::size_t getW() const;
    const std::size_t getH() const;

    void line(Vec2i _A, Vec2i _B, const Pixel _color);
    void triangle(const Vec2i _A, const Vec2i _B, const Vec2i _C, const Pixel _color);
    void filledTriangle(Vec2i _A, Vec2i _B, Vec2i _C, const Pixel _color);

    bool save(std::string _path) const;

private:
    const std::size_t w, h;
    const unsigned int maxColor;

    std::vector<std::vector<Pixel>> img;

    void filledBottomFlatTriangle(const Vec2i _A, const Vec2i _B, const Vec2i _C, const Pixel _color);
    void filledTopFlatTriangle(const Vec2i _A, const Vec2i _B, const Vec2i _C, const Pixel _color);
};
