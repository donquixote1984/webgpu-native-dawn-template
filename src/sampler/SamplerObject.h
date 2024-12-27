#pragma once
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"

using namespace wgpu;
class SamplerObject
{
private:
    Sampler m_Sampler;
public:
    Sampler GetSampler()
    {
        return m_Sampler;
    }
    SamplerObject()
    {
        SamplerDescriptor samplerDesc;
        samplerDesc.addressModeU = AddressMode::ClampToEdge;
        samplerDesc.addressModeV = AddressMode::ClampToEdge;
        samplerDesc.addressModeW = AddressMode::ClampToEdge;
        samplerDesc.magFilter = FilterMode::Linear;
        samplerDesc.minFilter = FilterMode::Linear;
        samplerDesc.mipmapFilter = MipmapFilterMode::Linear;
        samplerDesc.lodMinClamp = 0.0f;
        samplerDesc.lodMaxClamp = 10.0f;
        samplerDesc.compare = CompareFunction::Undefined;
        samplerDesc.maxAnisotropy = 1;
        m_Sampler = WGPUContext::device.createSampler(samplerDesc);
    }
    static SamplerObject *Get()
    {
        static SamplerObject s;
        return  &s;
    }
};