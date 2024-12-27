#pragma once
#include <glm/glm.hpp>
#include "../base/Constants.h"
#include "UniformBuffer.h"

struct CSMUniform
{
    glm::mat4 csmMatrices[constants::MAX_DIRECTIONAL_LIGHT * constants::MAX_CSM_LVL];
};


class CSMUniformBuffer: public UniformBuffer
{
private:
    CSMUniformBuffer(Buffer b):UniformBuffer(b){}
    CSMUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static CSMUniformBuffer* Get()
    {
        uint16_t unitSize = sizeof(CSMUniform);
        static CSMUniformBuffer buffer = {UniformBufferCreator::Create(unitSize), unitSize, 0, "u_csm", false};
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

