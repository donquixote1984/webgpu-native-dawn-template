#include <functional>
#include "MeshCreator.h"

std::shared_ptr<Mesh> MeshCreator::CreateMesh(std::shared_ptr<float[]> verticesData, size_t verticesCount, VertexDescriptor t)
{
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    
    std::shared_ptr<Vertices> vertices = Vertices::From(verticesData, verticesCount, t);

    //mesh.get()->m_Vertices.Buffer(vertices);
    mesh.get()->SetVertices(vertices);
    mesh.get()->SetObjectType(t.type);

    return mesh;
}

std::shared_ptr<Mesh> MeshCreator::CreateMesh(std::shared_ptr<float[]> verticesData, std::shared_ptr<int[]> indicesData, size_t verticesCount, size_t indicesCount, VertexDescriptor t)
{
    return CreateMesh(verticesData.get(), indicesData.get(), verticesCount, indicesCount, t);
}

std::shared_ptr<Mesh> MeshCreator::CreateMesh(float* verticesData, int* indicesData, size_t verticesCount, size_t indicesCount, VertexDescriptor t)
{
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    std::shared_ptr<Vertices> vertices = Vertices::From(verticesData, indicesData, verticesCount,indicesCount, t);

    // 
    mesh.get()->SetVertices(vertices);
    mesh.get()->SetObjectType(t.type);
    return mesh;
}

std::shared_ptr<Mesh> MeshCreator::CreateMesh(std::string file)
{

}