#pragma once
#include "BaseRenderPass.h"
#include "../shadow/SceneShadowMapCSMTexture.h"
#include "../debug/DebugShadow.h"

class ShadowMapRenderPass: public BaseRenderPass
{
private:
    unsigned int m_LightIndex = 0;
    unsigned int m_Cascade = 0;
public:
    ShadowMapRenderPass()    
    {
        //DebugShadow::Get()->SetWindowTextureView(m_ShadowMapTexture.GetTextureView());
    }
    void SetCascade(unsigned int cascade)
    {
        m_Cascade = cascade;
    }
    void SetLightIndex(unsigned int lightIndex)
    {
        m_LightIndex = lightIndex;
    }
    ~ShadowMapRenderPass()
    {
    }
    virtual RenderPassEncoder BeginScreenRenderPass(CommandEncoder encoder) override
    {
        // Depth only renderpass
        WGPURenderPassDescriptor renderpassDesc = {};
        renderpassDesc.nextInChain = nullptr;
        RenderPassDepthStencilAttachment renderpassDepthAttachmentDesc = WGPUContext::CreateDepthAttachment(SceneShadowMapCSMTexture::Get()->GetRenderTextureView(m_LightIndex * constants::MAX_CSM_LVL + m_Cascade));
        renderpassDepthAttachmentDesc.depthClearValue = 1.0;
        renderpassDesc.colorAttachmentCount = 0;


        renderpassDesc.depthStencilAttachment = &renderpassDepthAttachmentDesc;

        renderpassDesc.timestampWrites = nullptr;
        // TODO make shared command encoder
        RenderPassEncoder renderPass = encoder.beginRenderPass(renderpassDesc);
        renderPass.setLabel("shadow map render pass");
        renderPass.setViewport(0, 0, WGPUContext::SCREEN_WIDTH * 4, WGPUContext::SCREEN_WIDTH * 4, 0, 1);
        return renderPass;
    }
};