#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>

#include "tinyobjloader/tiny_obj_loader.h"
#include "../base/Vertices.h"

using namespace tinyobj;
using namespace std;
class ObjLoader
{
public:
    static void Load(const std::string & path, function<void(attrib_t &, vector<shape_t> &, vector<material_t> &)> callback)
    {
        attrib_t attrib;
        vector<shape_t> shapes;
        vector<material_t> materials;
        string warn;
        string error;

        bool ret = LoadObj(&attrib, &shapes, &materials, &warn, &error, path.c_str());
        if (!warn.empty())
        {
            cout << warn << endl;
        }

        if (!error.empty())
        {
            cout << error << endl;
        }
        callback(attrib, shapes, materials);
    }

    static void LoadVertexBase(const std::string &path, std::vector<VertexBase> &vertexBases)
    {
        ObjLoader::Load(path, [&](attrib_t &attrib, std::vector<shape_t> &shapes, std::vector<material_t> &materials) mutable {
            auto shape = shapes[0];
            int verticesCount = shape.mesh.indices.size();
            vertexBases.reserve(verticesCount);
            for (size_t i = 0; i < verticesCount; i++)
            {
                auto index = shape.mesh.indices[i];
                glm::vec3 pos;
                pos.x = attrib.vertices[3 * index.vertex_index];
                pos.y = attrib.vertices[3 * index.vertex_index + 1];
                pos.z = attrib.vertices[3 * index.vertex_index + 2];


                glm::vec3 norm;
                norm.x = attrib.normals[3 * index.normal_index];
                norm.y = attrib.normals[3 * index.normal_index + 1];
                norm.z = attrib.normals[3 * index.normal_index + 2];

                glm::vec2 uv;
                uv.x = attrib.texcoords[2 * index.texcoord_index];
                uv.y = attrib.texcoords[2 * index.texcoord_index + 1];

                VertexBase vb;
                vb.position = pos;
                vb.normal = norm;
                vb.uv = uv;

                vertexBases.push_back(vb);
            }
        });

    }
};