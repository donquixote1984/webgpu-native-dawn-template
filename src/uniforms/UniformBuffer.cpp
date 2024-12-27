#include "UniformBuffer.h"
#include "ViewProjectionUniform.h"
#include "ModelUniform.h"
#include "LightUniform.h"
#include "CountUniform.h"
#include "PickerUniform.h"
#include "CSMUniform.h"
#include "CSMIndexUniform.h"
#include "CameraPositionUniform.h"
#include "ScreenUniform.h"
#include "BVHUniform.h"
#include "RayHitableUniform.h"

UniformBuffer *UniformBuffer::GetByType(UniformBufferType type)
{
    switch (type)
    {
    case UniformBufferType::VP:
        return ViewProjectionUniformBuffer::Get();
    case UniformBufferType::MODEL:
        return ModelUniformBuffer::Get();
    case UniformBufferType::TIME:
        return TimeUniformBuffer::Get();
    case UniformBufferType::VEC4:
        return Vec4UniformBuffer::Get();
    case UniformBufferType::LIGHT:
        return LightUniformBuffer::Get();
    case UniformBufferType::COUNT:
        return CountUniformBuffer::Get();
    case UniformBufferType::PICKER:
        return PickerUniformBuffer::Get();
    case UniformBufferType::CSM:
        return CSMUniformBuffer::Get();
    case UniformBufferType::CSMINDEX:
        return CSMIndexUniformBuffer::Get();
    case UniformBufferType::INT:
        return IntUniformBuffer::Get();
    case UniformBufferType::CAM_POS:
        return CameraPositionUniformBuffer::Get();
    case UniformBufferType::SCREEN:
        return ScreenUniformBuffer::Get();
    case UniformBufferType::BVH:
        return BVHUniformBuffer::Get();
    case UniformBufferType::HITABLE:
        return HitableListUniformBuffer::Get();
    default:
        assert(0);
        break;
    }
}