#pragma once

#include <memory>
#include <webgpu/webgpu.hpp>
#include <concepts>
#include "Vertex.h"
#include "../enums/ObjectType.h"
using namespace wgpu;


/*
class Vertices 
{
public:
    template < class T>
    VerticesImpl<T> & Get();

}; */


class Vertices
{
private:
    //std::shared_ptr<Vertex[]> m_Vertices;
    //std::shared_ptr<int[]> m_Indices;
    Buffer m_VertexBuffer = nullptr;
    Buffer m_IndexBuffer = nullptr;
    size_t m_VerticesCount = 0;
    size_t m_IndicesCount = 0;


public:
    Vertices();
    ~Vertices();

    void Buffer(std::shared_ptr<float[]> buffer, size_t length, VertexDescriptor type);
    void Buffer(float * buffer, size_t verticesCount, VertexDescriptor desc);
    void Index(std::shared_ptr<int[]> indices, size_t indicesCount, VertexDescriptor desc);
    void Index(int* indices, size_t indicesCount, VertexDescriptor desc);
    wgpu::Buffer GetBuffer();
    wgpu::Buffer GetIndexBuffer();
    size_t GetCount();
    size_t GetIndexCount();
    static std::shared_ptr<Vertices> From(std::shared_ptr<float[]> buffer, size_t length, VertexDescriptor type);
    static std::shared_ptr<Vertices> From(std::shared_ptr<float[]> buffer, std::shared_ptr<int[]> indices, size_t verticesCount, size_t indicesCount, VertexDescriptor type);
    static std::shared_ptr<Vertices> From(float* buffer, int* indices, size_t verticesCount, size_t indicesCount, VertexDescriptor type);
};