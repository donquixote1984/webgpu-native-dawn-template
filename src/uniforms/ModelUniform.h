#pragma once
#include <glm/glm.hpp>
#include "UniformBuffer.h"
struct Channel
{
    bool hasTexture = false;
    float constant = 0.0f;
    glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0); // builtin color
};

struct ModelUniform
{
//    Channel albedo;
//    Channel roughness;
//    Channel normal;
//    Channel metalness;

    glm::mat4 modelMat;
};

class ModelUniformBuffer: public UniformBuffer
{
private:
    ModelUniformBuffer(Buffer b):UniformBuffer(b){}
    ModelUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name ): UniformBuffer(b, unitSize, stride, name, GL_DYNAMIC_DRAW)
    {}
public:
    static ModelUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(ModelUniform);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static ModelUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_model"};
        return &buffer;
    }

    virtual void WriteValue(std::any &value) override
    {
        ModelUniform v = std::any_cast<ModelUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }

    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        ModelUniform v = std::any_cast<ModelUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};

