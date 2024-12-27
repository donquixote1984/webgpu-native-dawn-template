#pragma once
#include <webgpu/webgpu.hpp>
#include <glm/glm.hpp>
#include "../initiator/WGPUContext.h"
#include "../render/Submitter.h"
#include "PickerPipeline.h"
#include "../ui/Interactions.h"
#include "save_image.h"


using namespace wgpu;
class PickerSubmitter: public Submitter
{
private:
    Texture m_PickerTexture;
    TextureView m_PickerTextureView;
    Texture m_DepthTexture;
    Buffer m_PickBuffer;
    Interactions m_Interactions;

    PickerSubmitter()
    {
        TextureDescriptor textureDesc;
        textureDesc.size = {WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, 1};
        textureDesc.format = TextureFormat::RGBA8Unorm;
        textureDesc.usage = TextureUsage::CopySrc | TextureUsage::RenderAttachment | TextureUsage::TextureBinding;
        textureDesc.sampleCount = 1;
        textureDesc.mipLevelCount = 1;

        m_PickerTexture = WGPUContext::device.createTexture(textureDesc);

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
        m_PickBuffer = WGPUContext::device.createBuffer(bufferDesc);
    }

public:
    void SetInteractions(Interactions &interactions)
    {
        m_Interactions = interactions;
    }
    virtual RenderPassEncoder BeginRenderPass() override
    {
        _BeginRenderPass();
        RenderPassDescriptor renderPassDesc;
        RenderPassColorAttachment attachment; 
        TextureViewDescriptor tDesc = GetViewDesc();
        // TODO move createview to constructor
        m_PickerTextureView = m_PickerTexture.createView(tDesc);
        attachment.view = m_PickerTextureView;
        attachment.clearValue = {0.0, 0.0, 0.0, 1.0};
        attachment.loadOp = LoadOp::Clear;
        attachment.storeOp = StoreOp::Store;
        attachment.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;

        renderPassDesc.colorAttachmentCount = 1;
        renderPassDesc.colorAttachments = &attachment;

        RenderPassDepthStencilAttachment depth;
        TextureViewDescriptor dDesc = GetDepthDesc();
        // TODO move createview to constructor
        depth.view = m_DepthTexture.createView(dDesc);
        depth.depthClearValue = 1;
        depth.depthLoadOp = LoadOp::Clear;
        depth.depthStoreOp = StoreOp::Store;

        renderPassDesc.depthStencilAttachment = &depth;

        m_RenderPass = m_CommandEncoder.beginRenderPass(renderPassDesc);
        RenderPipeline pipeline = PickerPipeline::Get()->GetRenderPipeline();
        m_RenderPass.setPipeline(pipeline);
        m_RenderPass.setLabel("PickRenderPass");
        return m_RenderPass;
    }

    static PickerSubmitter *Get() 
    {
        static PickerSubmitter submitter;
        return &submitter;
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
        textureViewDesc.format = TextureFormat::RGBA8Unorm;
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

    virtual void SubmitRenderPass() override;

};

