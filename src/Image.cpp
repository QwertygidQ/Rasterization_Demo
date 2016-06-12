#include "Image.hpp"

#include <fstream>
#include <iostream>

//--------Pixel--------//
Pixel::Pixel() :
    r(0), g(0), b(0)
{
}

Pixel::Pixel(const unsigned int _r, const unsigned int _g, const unsigned int _b) :
    r(_r), g(_g), b(_b)
{
}

Pixel::Pixel(const Pixel& _pix) :
    r(_pix.r), g(_pix.g), b(_pix.b)
{
}

Pixel& Pixel::operator=(const Pixel &_pix)
{
    if (this != &_pix)
    {
        r = _pix.r;
        g = _pix.g;
        b = _pix.b;
    }

    return *this;
}

//--------Image--------//
Image::Image(const std::size_t _w, const std::size_t _h, const unsigned int _maxColor) :
    w(_w), h(_h), maxColor(_maxColor)
{
    img.resize(_w, std::vector<Pixel>(_h, Pixel()));
}

void Image::set(const std::size_t _x, const std::size_t _y, const Pixel& color)
{
    img[_x][_y] = color;
}

Pixel& Image::get(const std::size_t _x, const std::size_t _y)
{
    return img[_x][_y];
}

const std::size_t Image::getW() const
{
    return w;
}

const std::size_t Image::getH() const
{
    return w;
}

void Image::line(Vec2i _A, Vec2i _B, const Pixel _color)
{
    bool steep = false;

    if(std::abs(_A.x - _B.x) < std::abs(_A.y - _B.y))
    {
        std::swap(_A.x, _A.y);
        std::swap(_B.x, _B.y);
        steep = true;
    }

    if (_A.x > _B.x)
    {
        std::swap(_A.x, _B.x);
        std::swap(_A.y, _B.y);
    }

    int dx = _B.x - _A.x, dy = _B.y - _A.y, derror = std::abs(dy) * 2, error = 0;
    for (int x = _A.x, y = _A.y; x <= _B.x; x++)
    {
        if (steep)
            img[y][x] = _color;
        else
            img[x][y] = _color;

        error += derror;
        if (error > dx)
        {
            y += (_B.y > _A.y ? 1 : -1);
            error -= dx * 2;
        }
    }
}

void Image::triangle(const Vec2i _A, const Vec2i _B, const Vec2i _C, const Pixel _color)
{
    line(_A, _B, _color);
    line(_B, _C, _color);
    line(_C, _A, _color);
}

void Image::filledTriangle(Vec2i _A, Vec2i _B, Vec2i _C, const Pixel _color)
{
    if (_A.y > _B.y)
        std::swap(_A, _B);
    if (_A.y > _C.y)
        std::swap(_A, _C);
    if (_B.y > _C.y)
        std::swap(_B, _C);

    if (_B.y == _C.y)
        filledBottomFlatTriangle(_A, _B, _C, _color);
    else if (_A.y == _B.y)
        filledTopFlatTriangle(_C, _A, _B, _color);
    else
    {
        Vec2i D((int)(_A.x + ((float)(_B.y - _A.y) / (float)(_C.y - _A.y)) * (_C.x - _A.x)), _B.y);

        filledBottomFlatTriangle(_A, _B, D, _color);
        filledTopFlatTriangle(_C, _B, D, _color);
    }
}

bool Image::save(std::string _path) const
{
    std::ofstream file(_path);
    if (file.fail())
        return false;

    file << "P3" << std::endl << w << " " << h << std::endl << maxColor << std::endl;
    for (std::size_t yIter = 0; yIter < h; yIter++)
    {
        for (std::size_t xIter = 0; xIter < w; xIter++)
        {
            Pixel pix = img[xIter][yIter];
            file << pix.r << " " << pix.g << " " << pix.b;
            if (xIter < (w - 1))
                file << " ";
        }
        file << std::endl;
    }
    file.close();

    return true;
}

void Image::filledBottomFlatTriangle(const Vec2i _A, const Vec2i _B, const Vec2i _C, const Pixel _color)
{
    triangle(_A, _B, _C, _color); // In case of a rounding error, this will help

    int dx1 = _B.x - _A.x, dx2 = _C.x - _A.x, dy = _B.y - _A.y;
    float invk1 = dx1/(float)dy, invk2 = dx2/(float)dy, curX1 = _A.x, curX2 = curX1;

    Vec2i point1, point2;

    for (int y = _A.y; y < _B.y; y++)
    {
        point1 = Vec2i(curX1, y);
        point2 = Vec2i(curX2, y);

        line(point1, point2, _color);

        curX1 += invk1;
        curX2 += invk2;
    }
}

void Image::filledTopFlatTriangle(const Vec2i _A, const Vec2i _B, const Vec2i _C, const Pixel _color)
{
    triangle(_A, _B, _C, _color); // In case of a rounding error, this will help

    int dx1 = _B.x - _A.x, dx2 = _C.x - _A.x, dy = _B.y - _A.y;
    float invk1 = dx1/(float)dy, invk2 = dx2/(float)dy, curX1 = _A.x, curX2 = curX1;

    Vec2i point1, point2;

    for (int y = _A.y; y > _B.y; y--)
    {
        point1 = Vec2i(curX1, y);
        point2 = Vec2i(curX2, y);

        line(point1, point2, _color);

        curX1 -= invk1;
        curX2 -= invk2;
    }
}
