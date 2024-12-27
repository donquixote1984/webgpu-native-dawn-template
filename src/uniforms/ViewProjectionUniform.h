#pragma once
#include <glm/glm.hpp>
#include "UniformBuffer.h"
struct ViewProjectionUniform
{
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 invview;
    glm::mat4 invprojection;
};

class ViewProjectionUniformBuffer: public UniformBuffer
{
private:
    ViewProjectionUniformBuffer(Buffer b):UniformBuffer(b){}
    ViewProjectionUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static ViewProjectionUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(ViewProjectionUniform);
        static ViewProjectionUniformBuffer buffer = {UniformBufferCreator::Create(unitSize), unitSize, 0, "u_viewprojection", false};
        return &buffer;
    }

    virtual void WriteValue(std::any &value) override
    {
        ViewProjectionUniform v = std::any_cast<ViewProjectionUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }
    
    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        ViewProjectionUniform v = std::any_cast<ViewProjectionUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }
};