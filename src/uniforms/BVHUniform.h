#pragma once
#include <glm/glm.hpp>
#include "UniformBuffer.h"
#include "../ray/BVH.h"
#include "../ray/AABB.h"

struct BVHNodeUniform
{
/**
 *  int left = -1;
    int right = -1;
    int hier;
    bool isLeaf = false;
    Hitable hitable;
    std::vector<Hitable> objs;
    AABB aabb;
*/

    int left;
    int right;
    int isLeaf;
    int hitable;
    AABB aabb;
};

struct BVHUniform
{
    BVHNodeUniform root;
    BVHNodeUniform bvhList[constants::MAX_BVH_SIZE];
};

class BVHUniformBuffer : public UniformBuffer
{
private:
    BVHUniformBuffer(Buffer b):UniformBuffer(b){}
    BVHUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic):  UniformBuffer(b, unitSize, stride, name, dynamic) {}
public:
    static BVHUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(BVHUniform);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static BVHUniformBuffer buffer = {UniformBufferCreator::Create(constants::MAX_OBJ_NUM * unitStride), unitSize, UniformBufferCreator::CalculateStride(unitSize), "u_bvh", false};
        return &buffer;
    }

    virtual void WriteValue(std::any &value ) override
    {
        BVHUniform v = std::any_cast<BVHUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, 0, (void*)&v, unitSize);
    }
    virtual void WriteValue(std::any &value, const Indexes &indexes) override
    {
        BVHUniform v = std::any_cast<BVHUniform>(value);
        //mesh->GetIndex().modelIndex * buffer->GetStride(), value, buffer->GetUnitSize()
        WGPUContext::queue.writeBuffer(m_Buffer, indexes.uniformIndex * stride, (void*)&v, unitSize);
    }

};

