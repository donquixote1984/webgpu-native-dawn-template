#pragma once
#include "BaseRenderPass.h"
class PickerRenderPass: public BaseRenderPass
{
public:
    PickerRenderPass()
    {
        TextureDescriptor textureDesc;
        textureDesc.size = {WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, 1};
        textureDesc.format = WGPUContext::surfaceFormat;
        textureDesc.usage = TextureUsage::CopySrc | TextureUsage::RenderAttachment | TextureUsage::TextureBinding;
        textureDesc.sampleCount = 1;
        textureDesc.mipLevelCount = 1;
        m_ColorTexture = WGPUContext::device.createTexture(textureDesc);


        TextureDescriptor depthDesc;
        depthDesc.size = {WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, 1};
        depthDesc.format = TextureFormat::Depth32Float;
        depthDesc.sampleCount = 1;
        depthDesc.mipLevelCount = 1;
        depthDesc.usage = TextureUsage::RenderAttachment;

        m_DepthTexture = WGPUContext::device.createTexture(depthDesc);

        BufferDescriptor bufferDesc;
        bufferDesc.size = sizeof(glm::vec4);
        bufferDesc.usage = BufferUsage::CopyDst | BufferUsage::MapRead;

        bufferDesc.label = "PickBuffer";
        m_Buffer = WGPUContext::device.createBuffer(bufferDesc);
    }
};