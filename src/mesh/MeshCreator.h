#pragma once
#include <memory>
#include "Mesh.h"

class MeshCreator
{
public:
    static std::shared_ptr<Mesh> CreateMesh(std::shared_ptr<float[]> vertices, size_t verticesCount, VertexDescriptor);
    static std::shared_ptr<Mesh> CreateMesh(std::shared_ptr<float[]> verticesData, std::shared_ptr<int[]> indicesData, size_t verticesCount, size_t indicesCount, VertexDescriptor t);
    static std::shared_ptr<Mesh> CreateMesh(float* verticesData, int* indicesData, size_t verticesCount, size_t indicesCount, VertexDescriptor t);
    static std::shared_ptr<Mesh> CreateMesh(std::string file);
};