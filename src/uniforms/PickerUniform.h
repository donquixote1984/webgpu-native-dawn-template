#pragma once
#include "UniformBuffer.h"
#include <glm/glm.hpp>
#include "../initiator/WGPUContext.h"

class PickerUniformBuffer: public UniformBuffer
{
private:
    PickerUniformBuffer(Buffer b):UniformBuffer(b){}
    PickerUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static PickerUniformBuffer* Get()
    {
        uint16_t unitSize = sizeof(glm::vec4);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static PickerUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_picker", false};
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
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};