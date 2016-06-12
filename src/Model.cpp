#include "Model.hpp"

#include <sstream>
#include <fstream>

Model::Model(std::string _path)
{
    std::ifstream file(_path);
    if(file.fail())
        return;

    std::string line;
    while (!file.eof())
    {
        std::getline(file, line);
        std::istringstream iss(line.c_str());
        char trash;

        if (!line.compare(0, 2, "v "))
        {
            iss >> trash;
            Vec3f vec;
            iss >> vec.x >> vec.y >> vec.z;

            verts.push_back(vec);
        }
        else if (!line.compare(0, 2, "f "))
        {
            std::vector<int> vec;
            int itrash, index;
            iss >> trash;

            while(iss >> index >> trash >> itrash >> trash >> itrash)
            {
                index--;
                vec.push_back(index);
            }
            faces.push_back(vec);
        }
    }
}

std::size_t Model::getVertsLength()
{
    return verts.size();
}

std::size_t Model::getFacesLength()
{
    return faces.size();
}

Vec3f Model::getVert(std::size_t _index)
{
    return verts[_index];
}

std::vector<int> Model::getFace(std::size_t _index)
{
    return faces[_index];
}
