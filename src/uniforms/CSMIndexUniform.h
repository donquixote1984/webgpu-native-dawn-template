#pragma once
#include <glm/glm.hpp>
#include "../base/Constants.h"
#include "UniformBuffer.h"

struct CSMIndexUniform
{
    int index;
};


class CSMIndexUniformBuffer: public UniformBuffer
{
private:
    CSMIndexUniformBuffer(Buffer b):UniformBuffer(b){}
    CSMIndexUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static CSMIndexUniformBuffer* Get()
    {
        int maxCSMIndex = constants::MAX_CSM_LVL * constants::MAX_DIRECTIONAL_LIGHT;
        int stride = UniformBufferCreator::CalculateStride(sizeof(int));
        uint16_t unitSize = sizeof(CSMIndexUniform);
        static CSMIndexUniformBuffer buffer = {UniformBufferCreator::Create(stride * maxCSMIndex), unitSize, 0, "u_csm_index", true};
        
        
        for (int i = 0; i < maxCSMIndex; i++)
        {
            WGPUContext::queue.writeBuffer(buffer.GetBuffer(), i * stride, (void*)&i, sizeof(int));
        }
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
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};

