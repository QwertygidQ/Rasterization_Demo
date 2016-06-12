#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "Geometry.hpp"

class Model
{
public:
    Model(std::string _path);

    std::size_t getVertsLength();
    std::size_t getFacesLength();

    Vec3f getVert(std::size_t _index);
    std::vector<int> getFace(std::size_t _index);

private:
    std::vector<Vec3f> verts;
    std::vector<std::vector<int>> faces;
};
