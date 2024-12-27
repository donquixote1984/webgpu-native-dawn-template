#pragma once
#include <glm/glm.hpp>
#include <webgpu/webgpu.hpp>
#include "../initiator/WGPUContext.h"

using namespace wgpu;
class BaseRenderPass
{
protected:
    Texture m_ColorTexture = nullptr;
    Texture m_DepthTexture = nullptr;
    Buffer m_Buffer = nullptr;

    ~BaseRenderPass()
    {
        if (m_ColorTexture != nullptr)
        {
            m_ColorTexture.release();
            m_ColorTexture = nullptr;
        }
        if (m_DepthTexture != nullptr)
        {
            m_DepthTexture.release();
            m_DepthTexture = nullptr;
        }
    }


    TextureViewDescriptor GetViewDesc()
    {
        TextureViewDescriptor textureViewDesc;
        textureViewDesc.aspect = TextureAspect::All;
        textureViewDesc.baseArrayLayer = 0;
        textureViewDesc.arrayLayerCount = 1;
        textureViewDesc.baseMipLevel = 0;
        textureViewDesc.mipLevelCount = 1; //textureDesc.mipLevelCount;
        textureViewDesc.dimension = TextureViewDimension::_2D;
        textureViewDesc.format = WGPUContext::surfaceFormat;
        return textureViewDesc;
    }

    TextureViewDescriptor GetDepthDesc()
    {
        TextureViewDescriptor depthTextureViewDesc;
        depthTextureViewDesc.aspect = TextureAspect::DepthOnly;
        depthTextureViewDesc.baseArrayLayer = 0;
        depthTextureViewDesc.arrayLayerCount = 1;
        depthTextureViewDesc.baseMipLevel = 0;
        depthTextureViewDesc.mipLevelCount = 1;
        depthTextureViewDesc.dimension = TextureViewDimension::_2D;
        depthTextureViewDesc.format = TextureFormat::Depth32Float;

        return depthTextureViewDesc;
    }
public:
    virtual RenderPassEncoder BeginScreenRenderPass(CommandEncoder encoder)
    {
        return WGPUContext::CreateScreenRenderPass(m_ColorTexture, m_DepthTexture, encoder);
    }
    const Texture &GetTexture() const 
    {
        return m_ColorTexture;
    }
    const Texture &GetDepth() const
    {
        return m_DepthTexture;
    }
    Buffer & GetBuffer() 
    {
        return m_Buffer;
    }
};