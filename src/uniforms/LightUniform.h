#pragma once

#include "../base/Constants.h"
#include "UniformBuffer.h"
#include "../light/PointLight.h"

struct PointLightUniform
{
    glm::vec4 color;
    glm::vec4 position;
};

struct DirectionalLightUniform
{
    glm::vec4 color;
    glm::vec4 direction;
    glm::vec4 csmLvlDist;
    glm::mat4 csm[constants::MAX_CSM_LVL];
};

struct LightUniform
{
    int pCount;
    int dCount;
    int bak1;
    int bak2;
    PointLightUniform pointLights[constants::MAX_POINT_LIGHT];
    DirectionalLightUniform directionalLights[constants::MAX_DIRECTIONAL_LIGHT];
};

class LightUniformBuffer: public UniformBuffer
{
protected:
    LightUniformBuffer(Buffer buffer): UniformBuffer(buffer){}
    LightUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static LightUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(LightUniform);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static LightUniformBuffer buffer = {UniformBufferCreator::Create(unitSize)};
        return &buffer;
    }

    virtual void WriteValue(std::any &value) override
    {
        PointLight v = std::any_cast<PointLight>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }
    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        PointLight v = std::any_cast<PointLight>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};

