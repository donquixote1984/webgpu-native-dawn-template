#pragma once
#include <glm/glm.hpp>
#include <any>
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"
#include "../base/Constants.h"
#include "../base/Indexes.h"

using namespace wgpu;

enum class UniformBufferType
{
    VP,
    MODEL,
    TIME,
    INT, 
    VEC4,
    LIGHT,
    COUNT,
    CAM_POS,
    SCREEN,

    CSM,
    PSM,
    CSMINDEX,
    
    PICKER,
    NONE,
    BVH,
    HITABLE,
};

class UniformBuffer
{
protected:
    Buffer m_Buffer = nullptr;
    uint16_t unitSize = 0;
    uint16_t stride = 0;
    std::string name;
    bool dynamic = false;
    UniformBuffer(Buffer b):m_Buffer(b){}
    UniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): m_Buffer(b), unitSize(unitSize), stride(stride), name(name), dynamic(dynamic){}

public:
   
    static UniformBuffer * GetByType(UniformBufferType type);
    Buffer GetBuffer()
    {
        return m_Buffer;
    }
    uint16_t GetStride()
    {
        return stride;
    }

    uint16_t GetUnitSize()
    {
        return unitSize;
    }

    std::string GetName()
    {
        return name;
    }

    virtual void WriteValue(std::any &value) = 0;
    virtual void WriteValue(std::any &value, const Indexes &indexes) = 0;
};

class UniformBufferCreator
{
public:
    static Buffer Create(size_t size)
    {
        BufferDescriptor bufferDesc{};
        bufferDesc.size = size;
        bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::Uniform;
        bufferDesc.mappedAtCreation = false;
        bufferDesc.label = "UniformBuffer";
        Buffer uniformBuffer = WGPUContext::device.createBuffer(bufferDesc);
        return uniformBuffer;
    }
    static uint16_t CalculateStride(uint16_t unitSize)
    {
        return ((unitSize / WGPUContext::limits.minUniformBufferOffsetAlignment)  + 1)* WGPUContext::limits.minUniformBufferOffsetAlignment;
    }
};

/*
class MVPUniformBuffer: public UniformBuffer
{
protected:
    MVPUniformBuffer(Buffer b):UniformBuffer(b){}
    MVPUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static MVPUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(glm::vec3);
        static MVPUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitSize), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_mvp", false};
        return &buffer;
    }
    void * GetPtr(std::any value) override
    {
        return 
    }
};
*/

class TimeUniformBuffer: public UniformBuffer
{
protected:
    TimeUniformBuffer(Buffer buffer): UniformBuffer(buffer) {}
    TimeUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    float uTime;
    static TimeUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(uTime);
        static TimeUniformBuffer buffer =  {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitSize), unitSize, 0, "u_time", false};

        return &buffer;
    }
   
    virtual void WriteValue(std::any &value) override
    {
        float v = std::any_cast<float>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }

    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        float v = std::any_cast<float>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer,  indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};

class IntUniformBuffer: public UniformBuffer
{
protected:
    IntUniformBuffer(Buffer buffer): UniformBuffer(buffer){}
    IntUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static IntUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(int);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static IntUniformBuffer buffer =  {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_int", true};
        return &buffer;
    }

    virtual void WriteValue(std::any &value) override
    {
        glm::vec4 v = std::any_cast<glm::vec4>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }

    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        int v = std::any_cast<int>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer,  indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};

class Vec4UniformBuffer: public UniformBuffer
{
protected:
    Vec4UniformBuffer(Buffer buffer): UniformBuffer(buffer){}
    Vec4UniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static Vec4UniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(glm::vec4);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static Vec4UniformBuffer buffer =  {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_color", true};
        return &buffer;
    }

    virtual void WriteValue(std::any &value) override
    {
        glm::vec4 v = std::any_cast<glm::vec4>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }

    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        glm::vec4 v = std::any_cast<glm::vec4>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer,  indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};