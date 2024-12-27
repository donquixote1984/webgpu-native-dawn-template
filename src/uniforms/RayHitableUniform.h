#pragma once
#include <glm/glm.hpp>
#include "UniformBuffer.h"
#include "../ray/AABB.h"

struct HitableMaterialUniform
{
/**
 *     MaterialType type; // 0 lambert, 1 material, 2 diel
    float refractIndex = 0.0f;
    glm::vec4 color = glm::vec4(0.0f, 0.0f,0.0f, 1.0f);
 * 
*/

    int _type;
    float refractIndex;
    float factor= 0.0f;
    int bak1 = 0;
    glm::vec4 color;
};

struct HitablePropertiesUniform
{
    glm::vec4 dim; 

    glm::vec4 mbTowards;
    glm::vec4 center;

    glm::vec4 min;
    glm::vec4 max;
    glm::vec4 normal;
    glm::vec4 u;
    glm::vec4 v;

    glm::vec4 extra;
};

struct HitableUniform
{
/**
 *  PrimitiveType type; //  sphere,  cube
    AABB aabb;
    HitableMaterial material;
    HitableProperties properties = {};
*/
    int _type;
    int index;
    int bak1 = 0;
    int bak2 = 0;
    HitableMaterialUniform material;
    HitablePropertiesUniform properties;
    AABB aabb;
};

struct HitableListUniform
{
    int count = 0;
    int bak0 = 0;
    int bak1 = 0;
    int bak2 = 0;
    HitableUniform hitableList[constants::MAX_HITABLE_SIZE];
    
};

class HitableListUniformBuffer : public UniformBuffer
{
private:
    HitableListUniformBuffer(Buffer b):UniformBuffer(b){}
    HitableListUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic):  UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static HitableListUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(HitableListUniform);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static HitableListUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_bvh", false};
        return &buffer;
    }

    virtual void WriteValue(std::any &value ) override
    {
        HitableListUniform v = std::any_cast<HitableListUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }
    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        HitableListUniform v = std::any_cast<HitableListUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }

};

