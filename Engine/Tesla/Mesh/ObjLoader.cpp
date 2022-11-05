﻿#include "TSPch.h"
#include "ObjLoader.h"

#include <assert.h>

const std::string resourcesDirectory = "./res";

std::vector<TESLA::Triangle> TESLA::ObjLoader::LoadFromOBJFile(std::string fileName)
{
    std::vector<Triangle> triangles;
    
    std::ifstream fileStream(resourcesDirectory + "/" + fileName + ".obj");
    assert(fileStream.is_open());

    std::vector<Vector> vertices;
    while (!fileStream.eof())
    {
        char line[128];
        fileStream.getline(line, 128);

        std::stringstream fileStringStream;
        fileStringStream << line;

        char out;
        if(line[0] == 'v')
        {
            Vector v;
            fileStringStream >> out >> v.x >> v.y >> v.z;
            v.w = 1;
            vertices.push_back(v);
        }
        else if(line[0] == 'f')
        {
            int f[3];
            fileStringStream >> out >> f[0] >> f[1] >> f[2];
            triangles.push_back({vertices[f[0] -1], vertices[f[1] - 1], vertices[f[2] - 1]});
        }
    }

    return triangles;
}

