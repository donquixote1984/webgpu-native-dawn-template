#pragma once
#include <webgpu/webgpu.hpp>
#include <glm/glm.hpp>
#include <memory>
#include "../shader/Shader.h"
#include "../enums/ObjectType.h"

using namespace wgpu;


struct Position {
    glm::vec3 position = glm::vec3(0);
};

struct PositionNormal: Position {
    glm::vec3 normal = glm::vec3(0);
};

struct VertexBase : PositionNormal{
    glm::vec2 uv = glm::vec2(0);
};

struct Vertex: VertexBase {
    glm::vec3 tangent = glm::vec3(0);
    glm::vec3 bitangent = glm::vec3(0);
};


class BindGroupLayoutCreator {
public:
    static std::vector<BindGroupLayoutEntry> Create()
    {
        std::vector<BindGroupLayoutEntry> bindingLayouts;
        BindGroupLayoutEntry bindingLayout = Default;
	    // The binding index as used in the @binding attribute in the shader
	    bindingLayout.binding = 0;
        bindingLayout.visibility = ShaderStage::Vertex;
	    bindingLayout.buffer.type = BufferBindingType::Uniform;
	    bindingLayout.buffer.minBindingSize = sizeof(float);
        return bindingLayouts;
    }
};
class VertexAttribCreator {
public:
    static VertexAttribute PositionAttrib()
    {
        VertexAttribute positionAttrib;
        positionAttrib.format = VertexFormat::Float32x3;
        positionAttrib.offset = 0;
        positionAttrib.shaderLocation = 0;
        return positionAttrib;
    }

    static VertexAttribute NormalAttrib()
    {
        VertexAttribute normalAttrib;
        normalAttrib.format = VertexFormat::Float32x3;
        normalAttrib.offset = sizeof(Position);
        normalAttrib.shaderLocation = 1;
        return normalAttrib;
    }

    static VertexAttribute UVAttrib() 
    {
        VertexAttribute uvAttrib;
        uvAttrib.format = VertexFormat::Float32x2;
        uvAttrib.offset = sizeof(PositionNormal);
        uvAttrib.shaderLocation = 2;
        return uvAttrib;
    }

};

class BufferDescriptorCreator {
public:
    static BufferDescriptor CreateBufferDesc(size_t verticesCount, size_t size)
    {
        BufferDescriptor bufferDesc;
        bufferDesc.size = verticesCount * size;
        bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::Vertex; // Vertex usage here!
        bufferDesc.mappedAtCreation = false;
        return bufferDesc;
    }

    static BufferDescriptor CreateIndexDesc(size_t verticesCount)
    {
        BufferDescriptor bufferDesc;
        bufferDesc.size = verticesCount * sizeof(int);
        bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::Index; // Vertex usage here!
        bufferDesc.mappedAtCreation = false;
        return bufferDesc;
    }
};

struct VertexDescriptor
{
    ObjectType type;
    size_t size;

    BufferDescriptor GetBufferDescriptor(size_t verticesCount) {
        return BufferDescriptorCreator::CreateBufferDesc(verticesCount, size);
    }
    BufferDescriptor GetIndexDescriptor(size_t verticesCount) {
        return BufferDescriptorCreator::CreateIndexDesc(verticesCount);
    }

    static VertexDescriptor POSITION;
    static VertexDescriptor POSITION_NORMAL;
    static VertexDescriptor VERTEX_BASE;
    static VertexDescriptor VERTEX;
};


