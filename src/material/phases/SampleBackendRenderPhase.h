#pragma once

#include "BackendRenderPhase.h"
#include "../../shader/SampleColoredPipeline.h"

class SampleBackendRenderPhase: public BackendRenderPhase
{
public:
    SampleBackendRenderPhase();
    virtual void CreateBindGroups() override;
    virtual RenderPassEncoder BeginRenderPass(CommandEncoder &encoder) override
    {
        m_ColorTexture = WGPUContext::CreateScreenTexture();
        TextureView depthView = WGPUContext::CreateDepthView2D(m_DepthTexture);
        RenderPassDescriptor desc = WGPUContext::CreateSurfaceRenderPassDesc(depthView);
        RenderPassEncoder renderPass = encoder.beginRenderPass(desc);
        renderPass.setPipeline(m_Pipeline->GetRenderPipeline());
        renderPass.setBindGroup(0, m_UniformBindGroup, 0, nullptr);

        if (m_TextureBindGroup)
        {
            renderPass.setBindGroup(1, m_TextureBindGroup, 0, nullptr);
        }
        if (m_SamplerBindGroup)
        {
            renderPass.setBindGroup(2, m_SamplerBindGroup, 0, nullptr);
        }
        return renderPass;
    }
};