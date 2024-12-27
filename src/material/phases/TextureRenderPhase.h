#pragma once

#include "ScreenRenderPhase.h"
#include "../../initiator/WGPUContext.h"
#include "../../shader/TexturedGeometryPipeline.h"
#include "../../base/Constants.h"

class TextureRenderPhase: public ScreenRenderPhase
{
protected:
   
    bool m_hasBindGroupCreated = false;
    TextureView m_ShadowMapTextureView = nullptr;
public:
    
    TextureRenderPhase();
    
    void CreateTextureBindGroup();
    void CreateSamplerBindGroup();
    virtual void RenderByRenderPass(RenderPassEncoder &renderPass, void ** context) override;
    virtual void CreateBindGroups() override;
/*
    virtual RenderPassEncoder BeginRenderPass(CommandEncoder encoder) override
    {
        if (m_Ready)
        {
            std::cout << "Render Phase not Ready" << std::endl;
            assert(0);
        }
        TextureView depthView = WGPUContext::CreateDepthView2D(m_DepthTexture);
        RenderPassDescriptor desc = WGPUContext::CreateSurfaceRenderPassDesc(depthView);
        RenderPassEncoder renderPass = encoder.beginRenderPass(desc);
        renderPass.setPipeline(m_Pipeline->GetRenderPipeline());

        renderPass.setBindGroup(0, m_UniformBindGroup, this->GetDynamicOffsetCount(), this->GetDynamicOffsets(uniformIndex).data());
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
    */
    
    void FillRemainingBindGroupEntry(std::vector<BindGroupEntry> & entries, int bindIndex)
    {
        auto & options = m_Pipeline->GetTextureBindGroupOptions();
        for (int i = bindIndex; i < constants::MAX_TEXTURE_SLOT; i++)
        {
            BindGroupEntry binding{};
            binding.binding = i;
            if (options[i].bindGroupType == BindGroupType::TEXTURE)
            {
                TextureView textureView = DiskTextureObject::EmptyTextureObject()->GetOrCreateTextureView();
                binding.textureView = textureView;
            }
            entries.push_back(binding);
        }
    }

    void FillFixedTextureSlots();
};