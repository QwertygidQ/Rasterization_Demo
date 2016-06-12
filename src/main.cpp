#include "Image.hpp"
#include "Geometry.hpp"
#include "Model.hpp"

#include <cstdlib>
#include <iostream>

int main()
{
    Model model("models/african_face.obj");

    Image img(800, 800);
    Pixel red(255, 0, 0), white(255, 255, 255);

    for (size_t i = 0; i < model.getFacesLength(); i++)
    {
        std::vector<int> vec = model.getFace(i);

        Vec2i screenCoords[3];
        Vec3f worldCoords[3];
        for(int j = 0; j < 3; j++)
        {
            worldCoords[j] = model.getVert(vec[j]);
            screenCoords[j] = Vec2i((worldCoords[j].x + 1.) * 800 / 2., (worldCoords[j].y + 1.) * 800 / 2.);
        }

        Vec3f normal = (worldCoords[2] - worldCoords[0]).cross(worldCoords[1] - worldCoords[0]);
        normal.normalize();

        Vec3f light(0, 0, -1);

        float intensity = light.dot(normal);
        if (intensity > 0)
            img.filledTriangle(screenCoords[0], screenCoords[1], screenCoords[2], Pixel(intensity * 255, intensity * 255, intensity * 255));
    }

    img.save("untitled.ppm");

    return 0;
}
