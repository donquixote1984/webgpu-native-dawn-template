#include "RenderPassSubmitter.h"

void RenderPassSubmitter::CreateDepthTextureView()
{
    TextureFormat depthTextureFormat = TextureFormat::Depth32Float;
    TextureDescriptor depthTextureDesc;
    depthTextureDesc.dimension = TextureDimension::_2D;
    depthTextureDesc.format = depthTextureFormat;
	depthTextureDesc.mipLevelCount = 1;
	depthTextureDesc.sampleCount = 1;
    depthTextureDesc.size = {WGPUContext::SCREEN_WIDTH, WGPUContext::SCREEN_HEIGHT, 1};
    depthTextureDesc.usage = TextureUsage::RenderAttachment;
    depthTextureDesc.viewFormatCount = 1;
    depthTextureDesc.viewFormats = (WGPUTextureFormat*)&depthTextureFormat;

    m_DepthTexture = WGPUContext::device.createTexture(depthTextureDesc);

    TextureViewDescriptor depthTextureViewDesc;
    depthTextureViewDesc.aspect = TextureAspect::DepthOnly;
	depthTextureViewDesc.baseArrayLayer = 0;
	depthTextureViewDesc.arrayLayerCount = 1;
	depthTextureViewDesc.baseMipLevel = 0;
	depthTextureViewDesc.mipLevelCount = 1;
	depthTextureViewDesc.dimension = TextureViewDimension::_2D;
	depthTextureViewDesc.format = depthTextureFormat;
    m_DepthView = m_DepthTexture.createView(depthTextureViewDesc);
}



RenderPassEncoder RenderPassSubmitter::BeginRenderPass()
{
    _BeginRenderPass();
    m_TargetView = WGPUContext::GetNextSurfaceTextureView();
    WGPURenderPassDescriptor renderpassDesc = {};
    renderpassDesc.nextInChain = nullptr;
    RenderPassColorAttachment renderpassColorAttachmentDesc = CreateColorAttachment(m_TargetView);
    renderpassColorAttachmentDesc.view = m_TargetView;

    RenderPassDepthStencilAttachment renderpassDepthAttachmentDesc = CreateDepthAttachment(m_DepthView);

    renderpassDesc.colorAttachmentCount = 1;
    renderpassDesc.colorAttachments = &renderpassColorAttachmentDesc;
    renderpassDesc.depthStencilAttachment = &renderpassDepthAttachmentDesc;

    renderpassDesc.timestampWrites = nullptr;
    m_RenderPass = m_CommandEncoder.beginRenderPass(renderpassDesc);
    m_RenderPass.setLabel("render");
    return m_RenderPass;
}