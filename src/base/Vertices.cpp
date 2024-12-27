#include "Vertices.h"
#include "../initiator/WGPUContext.h"

Vertices::Vertices()
{
    
}

Vertices::~Vertices()
{
    if (m_VertexBuffer != nullptr) 
    {
        m_VertexBuffer.release();
    }
}

void Vertices::Buffer(std::shared_ptr<float []> buffer, size_t verticesCount, VertexDescriptor desc)
{
    Buffer(buffer.get(), verticesCount, desc);
}

void Vertices::Buffer(float * buffer, size_t verticesCount, VertexDescriptor desc)
{
    m_VerticesCount = verticesCount;
    m_VertexBuffer = WGPUContext::device.createBuffer(desc.GetBufferDescriptor(verticesCount));
    m_VertexBuffer.setLabel("vbuffer");
    WGPUContext::queue.writeBuffer(m_VertexBuffer, 0, buffer, m_VerticesCount * desc.size);
}


void Vertices::Index(std::shared_ptr<int[]> indices, size_t indicesCount, VertexDescriptor desc)
{
    Index(indices.get(), indicesCount, desc);
}

void Vertices::Index(int* indices, size_t indicesCount, VertexDescriptor desc)
{
    m_IndicesCount = indicesCount;
    m_IndexBuffer = WGPUContext::device.createBuffer(desc.GetIndexDescriptor(m_IndicesCount));
    m_IndexBuffer.setLabel("ibuffer");
    WGPUContext::queue.writeBuffer(m_IndexBuffer, 0, indices, m_IndicesCount * sizeof(int));
}

wgpu::Buffer Vertices::GetBuffer()
{
    return m_VertexBuffer;
}

Buffer Vertices::GetIndexBuffer()
{
    return m_IndexBuffer;
}

size_t Vertices::GetCount()
{
    return m_VerticesCount;
}
size_t Vertices::GetIndexCount()
{
    return m_IndicesCount;
}

std::shared_ptr<Vertices> Vertices::From(std::shared_ptr<float []> buffer, size_t verticesCount, VertexDescriptor type)
{
    std::shared_ptr<Vertices> vertices = std::make_shared<Vertices>();
    vertices.get()->Buffer(buffer, verticesCount, type);
    return vertices;
}

std::shared_ptr<Vertices> Vertices::From(std::shared_ptr<float[]> buffer, std::shared_ptr<int[]> indices, size_t verticesCount, size_t indicesCount, VertexDescriptor type)
{
    return From(buffer.get(), indices.get(), verticesCount, indicesCount, type);
}

std::shared_ptr<Vertices> Vertices::From(float* buffer, int* indices, size_t verticesCount, size_t indicesCount, VertexDescriptor type)
{
    std::shared_ptr<Vertices> vertices = std::make_shared<Vertices>();

    vertices.get()->Buffer(buffer, verticesCount, type);
    vertices.get()->Index(indices, indicesCount, type);
    return vertices;
}