#pragma once
#include <glm/glm.hpp>
#include "UniformBuffer.h"

struct CountUniform 
{
    uint32_t pointLightCount = 0;
    uint32_t directionalLightCount = 0;
};

class CountUniformBuffer : public UniformBuffer
{
private:
    CountUniformBuffer(Buffer b):UniformBuffer(b){}
    CountUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic):  UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static CountUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(CountUniform);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static CountUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_count", false};
        return &buffer;
    }

    virtual void WriteValue(std::any &value ) override
    {
        CountUniform v = std::any_cast<CountUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }
    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        CountUniform v = std::any_cast<CountUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }

};

