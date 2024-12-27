#include "UniformBuffer.h"

#pragma once
#include <glm/glm.hpp>
#include "UniformBuffer.h"

struct ScreenUniform 
{
    uint32_t width = 0;
    uint32_t height = 0;
    float aspectRatio = 1;
    uint32_t bak = 0;
};

class ScreenUniformBuffer : public UniformBuffer
{
private:
    ScreenUniformBuffer(Buffer b):UniformBuffer(b){}
    ScreenUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic):  UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static ScreenUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(CountUniform);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static ScreenUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_count", false};
        return &buffer;
    }

    virtual void WriteValue(std::any &value ) override
    {
        ScreenUniformBuffer v = std::any_cast<ScreenUniformBuffer>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }
    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        ScreenUniformBuffer v = std::any_cast<ScreenUniformBuffer>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }

};

