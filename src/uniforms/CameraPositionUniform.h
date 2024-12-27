#include "UniformBuffer.h"
class CameraPositionUniformBuffer: public Vec4UniformBuffer
{
private:
    CameraPositionUniformBuffer(Buffer b):Vec4UniformBuffer(b){}
    CameraPositionUniformBuffer(Buffer b, uint16_t unitSize, uint16_t stride, std::string name, bool dynamic): Vec4UniformBuffer(b, unitSize, stride, name, dynamic) {}
public: 
    static CameraPositionUniformBuffer * Get()
    {
        uint16_t unitSize = sizeof(glm::vec4);
        uint16_t unitStride = ((unitSize / WGPUContext::limits.maxVertexBufferArrayStride) + 1) * WGPUContext::limits.maxVertexBufferArrayStride;
        static CameraPositionUniformBuffer buffer = {UniformBufferCreator::Create(unitSize), unitSize, 0, "u_cam_pos", false};
        return &buffer;
    }
};